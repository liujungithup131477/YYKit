//
//  YYAnimatedImageView.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 14/10/19.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// MARK: - YYAnimatedImageView 描述和举例
/**
 An image view for displaying animated image.
 *一个 image 视图显示动画图像。
 
 @discussion It is a fully compatible `UIImageView` subclass.
 If the `image` or `highlightedImage` property adopt to the `YYAnimatedImage` protocol,
 then it can be used to play the multi-frame animation. The animation can also be 
 controlled with the UIImageView methods `-startAnimating`, `-stopAnimating` and `-isAnimating`.
 *这是一个完全兼容 UIImageView 类的子类。如果“image” 或 “highlightedImage” 属性遵循 “YYAnimatedImage” 协议,
 它可以用来播放multi-frame动画。UIImageView方法‘startanimating’,‘-stopAnimating’和‘-isAnimating’ 也可以控制该动画属性。
 
 This view request the frame data just in time. When the device has enough free memory, 
 this view may cache some or all future frames in an inner buffer for lower CPU cost.
 Buffer size is dynamically adjusted based on the current state of the device memory.
 *这个视图会及时请求 frame 数据。当设备有足够的空闲内存,这个视图可能缓存部分或全部的 frame 在一个内部缓冲区中，以此降低CPU成本。
 *缓冲区大小是根据设备的当前状态动态调整内存。
 
 Sample Code:
 
     // ani@3x.gif
     YYImage *image = [YYImage imageNamed:@"ani"];
     YYAnimatedImageView *imageView = [YYAnimatedImageView alloc] initWithImage:image];
     [view addSubView:imageView];
 */

@interface YYAnimatedImageView : UIImageView

// MARK: - YYAnimatedImageView 属性
/**
 If the image has more than one frame, set this value to `YES` will automatically 
 play/stop the animation when the view become visible/invisible.
 *如果 image 有多个帧时，设置这个属性值为 'YES' 将会自动播放/停止当视图可见/不可见。
 
 The default value is `YES`.
 *属性默认返回 'YES'。
 */
@property (nonatomic) BOOL autoPlayAnimatedImage;

/**
 Index of the currently displayed frame (index from 0).
 *当前播放的动画帧（index 从 0 开始）。
 
 Set a new value to this property will cause to display the new frame immediately.
 If the new value is invalid, this method has no effect.
 *给这个属性设置一个新值将会立即显示新的 image 帧。
 *如果新值是无效的,这种方法没有效果。
 
 You can add an observer to this property to observe the playing status.
 *你可以对该属性添加观察者来观察该属性的状态变化。
 */
@property (nonatomic) NSUInteger currentAnimatedImageIndex;

/**
 Whether the image view is playing animation currently.
 *目前图像视图是否播放动画。
 
 You can add an observer to this property to observe the playing status.
 *你可以对该属性添加观察者来观察该属性的状态变化。
 */
@property (nonatomic, readonly) BOOL currentIsPlayingAnimation;

/**
 The animation timer's runloop mode, default is `NSRunLoopCommonModes`.
 *该动画时钟的运行循环模式，默认是`NSRunLoopCommonModes`。
 
 Set this property to `NSDefaultRunLoopMode` will make the animation pause during
 UIScrollView scrolling.
 *将该视图设置为 `NSDefaultRunLoopMode` 模式，在 UIScrollView 滚动过程动画将会停止。
 */
@property (nonatomic, copy) NSString *runloopMode;

/**
 The max size (in bytes) for inner frame buffer size, default is 0 (dynamically).
 *内部帧缓冲区(以字节为单位)的最大大小,默认是0(动态)。
 
 When the device has enough free memory, this view will request and decode some or 
 all future frame image into an inner buffer. If this property's value is 0, then 
 the max buffer size will be dynamically adjusted based on the current state of 
 the device free memory. Otherwise, the buffer size will be limited by this value.
 *当设备有足够的空闲内存，这个视图将会请求和解析部分或全部将要显示的图片到内部缓存区。如果这个属性的值为
 *0，那么最大缓存大小将根据当前设备的空闲内存状态自动调整。否则，该最大缓存大小是有限的。
 
 When receive memory warning or app enter background, the buffer will be released 
 immediately, and may grow back at the right time.
 *当设备接到内存警告时或应用程序进入后台时，缓存区可能会在正确的时间立即释放缓存空间。
 */
@property (nonatomic) NSUInteger maxBufferSize;

@end



/**
 The YYAnimatedImage protocol declares the required methods for animated image
 display with YYAnimatedImageView.
 *YYAnimatedImage 协议中定义了显示 YYAnimatedImageView 视图动画的必备方法。
 
 Subclass a UIImage and implement this protocol, so that instances of that class 
 can be set to YYAnimatedImageView.image or YYAnimatedImageView.highlightedImage
 to display animation.
 *UIImage 的子类和实现这个协议的类，他们类的实例可以设置 YYAnimatedImageView.image
 *or YYAnimatedImageView.highlightedImage 去显示动画。
 
 See `YYImage` and `YYFrameImage` for example.
 *看`YYImage` and `YYFrameImage` 的实例。
 */
@protocol YYAnimatedImage <NSObject>
// MARK: - required协议方法
@required
/// Total animated frame count.
/// 执行动画的图片的总数。
/// It the frame count is less than 1, then the methods below will be ignored.
/// 图片的张数小于1，下面的方法将被忽略。
- (NSUInteger)animatedImageFrameCount;

/// Animation loop count, 0 means infinite looping.
/// 动画执行的次数，0代表无限次。
- (NSUInteger)animatedImageLoopCount;

/// Bytes per frame (in memory). It may used to optimize memory buffer size.
/// 每帧字节(在内存中)。它可以用来优化内存缓冲区大小。
- (NSUInteger)animatedImageBytesPerFrame;

/// Returns the frame image from a specified index.
/// 返回指定的帧图片
/// This method may be called on background thread.
/// 这个方法可能会被后台线程调用。
///
/// @param index  Frame index (zero based).
/// 参数 index 帧图片的索引（从0开始）。
- (nullable UIImage *)animatedImageFrameAtIndex:(NSUInteger)index;

/// Returns the frames's duration from a specified index.
/// 返回指定的帧图像动画时间。
/// @param index  Frame index (zero based).
/// 参数 index 帧图像的索引（从0开始）。
- (NSTimeInterval)animatedImageDurationAtIndex:(NSUInteger)index;

@optional
//TODO: - 有待研究
/// A rectangle in image coordinates defining the subrectangle of the image that
/// will be displayed. The rectangle should not outside the image's bounds.
/// It may used to display sprite animation with a single image (sprite sheet).
- (CGRect)animatedImageContentsRectAtIndex:(NSUInteger)index;
@end

NS_ASSUME_NONNULL_END
