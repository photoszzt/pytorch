from .optimizer import Optimizer, required, _use_grad_for_differentiable  # type: ignore[attr-defined]
import torch
from typing import List, Optional
from torch import Tensor

__all__ = ["LARS", "lars"]


class LARS(Optimizer):
    """Implements LARS algorithm."""

    def __init__(
        self,
        params,
        lr=required,
        momentum: float = 0,
        dampening: float = 0,
        weight_decay: float = 0,
        nesterov: bool = False,
        *,
        trust_coefficient: float = 0.001,
        eps: float = 1e-8,
        maximize: bool = False,
        differentiable: bool = False,
    ):
        if lr is not required and lr < 0.0:
            raise ValueError(f"Invalid learning rate: {lr}")
        if weight_decay < 0.0:
            raise ValueError(f"Invalid weight decay value: {weight_decay}")
        if momentum < 0.0:
            raise ValueError(f"Invalid momentum value: {momentum}")
        if nesterov and (momentum <= 0 or dampening != 0):
            raise ValueError("Nesterov momentum requires a momentum and zero dampening")

        defaults = dict(
            lr=lr,
            momentum=momentum,
            dampening=dampening,
            weight_decay=weight_decay,
            nesterov=nesterov,
            trust_coefficient=trust_coefficient,
            eps=eps,
            maximize=maximize,
            differentiable=differentiable,
        )

        super().__init__(params, defaults)

    def __setstate__(self, state):
        super().__setstate__(state)
        for group in self.param_groups:
            group.setdefault("nesterov", False)
            group.setdefault("maximize", False)
            group.setdefault("differentiable", False)

    @_use_grad_for_differentiable
    def step(self, closure=None):
        loss = None
        if closure is not None:
            with torch.enable_grad():
                loss = closure()

        for group in self.param_groups:
            params_with_grad = []
            grads = []
            momentum_buffer_list = []

            for p in group["params"]:
                if p.grad is not None:
                    params_with_grad.append(p)
                    grads.append(p.grad)

                    state = self.state[p]

                    momentum_buffer_list.append(state.get("momentum_buffer"))

            lars(
                params_with_grad,
                grads,
                momentum_buffer_list,
                lr=group["lr"],
                momentum=group["momentum"],
                dampening=group["dampening"],
                weight_decay=group["weight_decay"],
                nesterov=group["nesterov"],
                trust_coefficient=group["trust_coefficient"],
                eps=group["eps"],
                maximize=group["maximize"],
            )

            for p, momentum_buffer in zip(params_with_grad, momentum_buffer_list):
                state = self.state[p]
                state["momentum_buffer"] = momentum_buffer

        return loss


def lars(
    params: List[Tensor],
    grads: List[Tensor],
    momentum_buffer_list: List[Optional[Tensor]],
    *,
    lr: float,
    momentum: float,
    dampening: float,
    weight_decay: float,
    nesterov: bool,
    trust_coefficient: float,
    eps: float,
    maximize: bool,
):
    if torch.jit.is_scripting():
        raise RuntimeError('torch.jit.script not supported with foreach optimizers')

    if not torch.jit.is_scripting():
        func = _single_tensor_lars

    func(
        params,
        grads,
        momentum_buffer_list,
        lr=lr,
        momentum=momentum,
        dampening=dampening,
        weight_decay=weight_decay,
        nesterov=nesterov,
        trust_coefficient=trust_coefficient,
        eps=eps,
        maximize=maximize,
    )


def _single_tensor_lars(
    params: List[Tensor],
    grads: List[Tensor],
    momentum_buffer_list: List[Optional[Tensor]],
    *,
    lr: float,
    momentum: float,
    dampening: float,
    weight_decay: float,
    nesterov: bool,
    trust_coefficient: float,
    eps: float,
    maximize: bool,
):
    for i, param in enumerate(params):
        d_p = grads[i] if not maximize else -grads[i]

        p_norm = torch.norm(param.data)
        g_norm = torch.norm(d_p.data)

        if weight_decay != 0:
            # LARS scaling:
            if p_norm * g_norm > 0:
                lars_lr = trust_coefficient * p_norm / (g_norm + p_norm * weight_decay + eps)

                d_p = d_p.add(param, alpha=weight_decay)
                d_p.mul_(lars_lr)

        if momentum != 0:
            buf = momentum_buffer_list[i]

            if buf is None:
                buf = torch.clone(d_p).detach()
                momentum_buffer_list[i] = buf
            else:
                buf.mul_(momentum).add_(d_p, alpha=1 - dampening)

            d_p = d_p.add(buf, alpha=momentum) if nesterov else buf

    param.add_(d_p, alpha=-lr)
