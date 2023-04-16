#pragma once
#include <MetalPerformanceShadersGraph/MetalPerformanceShadersGraph.h>

// TODO: Remove me when moved to MacOS 13
#if !defined(__MAC_13_0) && \
    (!defined(MAC_OS_X_VERSION_13_0) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_13_0))


@interface MPSGraphConvolution3DOpDescriptor : NSObject<NSCopying>
+(nullable instancetype) descriptorWithStrideInX:(NSUInteger) strideInX
                                       strideInY:(NSUInteger) strideInY
                                       strideInZ:(NSUInteger) strideInZ
                                 dilationRateInX:(NSUInteger) dilationRateInX
                                 dilationRateInY:(NSUInteger) dilationRateInY
                                 dilationRateInZ:(NSUInteger) dilationRateInZ
                                          groups:(NSUInteger) groups
                                     paddingLeft:(NSUInteger) paddingLeft
                                    paddingRight:(NSUInteger) paddingRight
                                      paddingTop:(NSUInteger) paddingTop
                                   paddingBottom:(NSUInteger) paddingBottom
                                    paddingFront:(NSUInteger) paddingFront
                                     paddingBack:(NSUInteger) paddingBack
                                    paddingStyle:(MPSGraphPaddingStyle) paddingStyle
                                      dataLayout:(MPSGraphTensorNamedDataLayout) dataLayout
                                   weightsLayout:(MPSGraphTensorNamedDataLayout) weightsLayout;
@end
#endif


@interface MPSGraph (VenturaOps)

#if !defined(__MAC_13_0) && \
    (!defined(MAC_OS_X_VERSION_13_0) || (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_13_0))

typedef NS_ENUM(NSUInteger, MPSGraphResizeNearestRoundingMode)
{
    MPSGraphResizeNearestRoundingModeRoundPreferCeil   =  0L,
    MPSGraphResizeNearestRoundingModeRoundPreferFloor  =  1L,
    MPSGraphResizeNearestRoundingModeCeil              =  2L,
    MPSGraphResizeNearestRoundingModeFloor             =  3L,
    MPSGraphResizeNearestRoundingModeRoundToEven       =  4L,
    MPSGraphResizeNearestRoundingModeRoundToOdd        =  5L,
};
#endif


- (MPSGraphTensor * _Nonnull) convolution3DWithSourceTensor:(MPSGraphTensor * _Nonnull) source
                                    weightsTensor:(MPSGraphTensor * _Nonnull) weights
                                       descriptor:(MPSGraphConvolution3DOpDescriptor * _Nonnull) descriptor
                                                      name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) convolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor * _Nonnull) incomingGradient
                                                          weightsTensor:(MPSGraphTensor * _Nonnull) weights
                                                            outputShape:(MPSShape * _Nonnull) outputShape
                                           forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor * _Nonnull) forwardConvolutionDescriptor
                                                                   name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) convolution3DDataGradientWithIncomingGradientTensor:(MPSGraphTensor * _Nonnull) gradient
                                                          weightsTensor:(MPSGraphTensor * _Nonnull) weights
                                                      outputShapeTensor:(MPSGraphTensor * _Nonnull) outputShapeTensor
                                           forwardConvolutionDescriptor:(MPSGraphConvolution3DOpDescriptor * _Nonnull) forwardConvolutionDescriptor
                                                                             name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull)cumulativeSumWithTensor:(MPSGraphTensor * _Nonnull)tensor
                                                axis:(NSInteger)axis
                                                name:(NSString * _Nullable)name;

- (MPSGraphTensor * _Nonnull)sortWithTensor:(MPSGraphTensor * _Nonnull)tensor
                                       axis:(NSInteger)axis
                                       name:(NSString * _Nullable)name;

- (MPSGraphTensor * _Nonnull) sortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                               axis:(NSInteger) axis
                         descending:(BOOL) descending
                               name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) sortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                         axisTensor:(MPSGraphTensor * _Nonnull) axisTensor
                         descending:(BOOL) descending
                               name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) sortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                         axisTensor:(MPSGraphTensor * _Nonnull) axisTensor
                               name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull)argSortWithTensor:(MPSGraphTensor * _Nonnull)tensor
                                          axis:(NSInteger)axis
                                          name:(NSString * _Nullable)name;

- (MPSGraphTensor * _Nonnull) argSortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                                  axis:(NSInteger) axis
                            descending:(BOOL) descending
                                  name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) argSortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                           axisTensor:(MPSGraphTensor * _Nonnull) axisTensor
                           descending:(BOOL) descending
                                 name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) argSortWithTensor:(MPSGraphTensor * _Nonnull) tensor
                           axisTensor:(MPSGraphTensor * _Nonnull) axisTensor
                                 name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull)inverseOfTensor:(MPSGraphTensor * _Nonnull) inputTensor
                                        name:(NSString * _Nullable)name;

- (MPSGraphTensor * _Nonnull) resizeNearestWithTensor:(MPSGraphTensor * _Nonnull) imagesTensor
                                           sizeTensor:(MPSGraphTensor * _Nonnull) size
                                  nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                         centerResult:(BOOL) centerResult
                                         alignCorners:(BOOL) alignCorners
                                               layout:(MPSGraphTensorNamedDataLayout) layout
                                                 name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeNearestWithTensor:(MPSGraphTensor * _Nonnull) imagesTensor
                                           sizeTensor:(MPSGraphTensor * _Nonnull) size
                                    scaleOffsetTensor:(MPSGraphTensor * _Nonnull) scaleOffset
                                  nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                               layout:(MPSGraphTensorNamedDataLayout) layout
                                                 name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeBilinearWithTensor:(MPSGraphTensor * _Nonnull) imagesTensor
                                            sizeTensor:(MPSGraphTensor * _Nonnull) size
                                          centerResult:(BOOL) centerResult
                                          alignCorners:(BOOL) alignCorners
                                                layout:(MPSGraphTensorNamedDataLayout) layout
                                                  name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeBilinearWithTensor:(MPSGraphTensor * _Nonnull) imagesTensor
                                            sizeTensor:(MPSGraphTensor * _Nonnull) size
                                     scaleOffsetTensor:(MPSGraphTensor * _Nonnull) scaleOffset
                                                layout:(MPSGraphTensorNamedDataLayout) layout
                                                  name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeNearestWithGradientTensor:(MPSGraphTensor * _Nonnull) gradient
                                                        input:(MPSGraphTensor * _Nonnull) input
                                          nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                                 centerResult:(BOOL) centerResult
                                                 alignCorners:(BOOL) alignCorners
                                                       layout:(MPSGraphTensorNamedDataLayout) layout
                                                         name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeNearestWithGradientTensor:(MPSGraphTensor * _Nonnull) gradient
                                                        input:(MPSGraphTensor * _Nonnull) input
                                            scaleOffsetTensor:(MPSGraphTensor * _Nonnull) scaleOffset
                                          nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                                       layout:(MPSGraphTensorNamedDataLayout) layout
                                                         name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeBilinearWithGradientTensor:(MPSGraphTensor * _Nonnull) gradient
                                                         input:(MPSGraphTensor * _Nonnull) input
                                                  centerResult:(BOOL) centerResult
                                                  alignCorners:(BOOL) alignCorners
                                                        layout:(MPSGraphTensorNamedDataLayout) layout
                                                          name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) resizeBilinearWithGradientTensor:(MPSGraphTensor * _Nonnull) gradient
                                                         input:(MPSGraphTensor * _Nonnull) input
                                             scaleOffsetTensor:(MPSGraphTensor * _Nonnull) scaleOffset
                                                        layout:(MPSGraphTensorNamedDataLayout) layout
                                                          name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) sampleGridWithSourceTensor:(MPSGraphTensor * _Nonnull) source
                                        coordinateTensor:(MPSGraphTensor * _Nonnull) coordinates
                                                  layout:(MPSGraphTensorNamedDataLayout) layout
                                    normalizeCoordinates:(BOOL) normalizeCoordinates
                                     relativeCoordinates:(BOOL) relativeCoordinates
                                            alignCorners:(BOOL) alignCorners
                                             paddingMode:(MPSGraphPaddingMode) paddingMode
                                            samplingMode:(MPSGraphResizeMode) samplingMode
                                           constantValue:(double) constantValue
                                                    name:(NSString * _Nullable) name;

- (MPSGraphTensor * _Nonnull) sampleGridWithSourceTensor:(MPSGraphTensor * _Nonnull) source
                                        coordinateTensor:(MPSGraphTensor * _Nonnull) coordinates
                                                  layout:(MPSGraphTensorNamedDataLayout) layout
                                    normalizeCoordinates:(BOOL) normalizeCoordinates
                                     relativeCoordinates:(BOOL) relativeCoordinates
                                            alignCorners:(BOOL) alignCorners
                                             paddingMode:(MPSGraphPaddingMode) paddingMode
                                     nearestRoundingMode:(MPSGraphResizeNearestRoundingMode) nearestRoundingMode
                                           constantValue:(double) constantValue
                                                    name:(NSString * _Nullable) name;
- (MPSGraphTensor * _Nonnull) truncateWithTensor:(MPSGraphTensor * _Nonnull) tensor
                                            name:(NSString * _Nullable) name;

@end
