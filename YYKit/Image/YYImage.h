//
//  YYImage.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 14/10/20.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

/**
 *  功能强大的 iOS 图像框架。
 */

#import <UIKit/UIKit.h>

#if __has_include(<YYKit/YYKit.h>)
#import <YYKit/YYAnimatedImageView.h>
#import <YYKit/YYImageCoder.h>
#else
#import "YYAnimatedImageView.h"
#import "YYImageCoder.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 A YYImage object is a high-level way to display animated image data.
 *YYImage对象是一个高级的方式来显示动画图像数据。
 
 @discussion It is a fully compatible `UIImage` subclass. It extends the UIImage
 to support animated WebP, APNG and GIF format image data decoding. It also 
 support NSCoding protocol to archive and unarchive multi-frame image data.
 *这是一个完全兼容`UIImage`图像的子类。它对 UIImage 类做了扩展，以此支持WebP, APNG and GIF格式
 *图片动画的数据解析。它也 NSCoding 协议去归档和解档更多架构的图片数据。
 
 If the image is created from multi-frame image data, and you want to play the 
 animation, try replace UIImageView with `YYAnimatedImageView`.
 *如果图片是从多种架构数据创建的图片，并且你想让它播放动画，那就用`YYAnimatedImageView`类替换UIImageView类。
 
 Sample Code:
 
     // animation@3x.webp
     YYImage *image = [YYImage imageNamed:@"animation.webp"];
     YYAnimatedImageView *imageView = [YYAnimatedImageView alloc] initWithImage:image];
     [view addSubView:imageView];
    
 */
@interface YYImage : UIImage <YYAnimatedImage>

// MARK: - image 图片的创建方式
+ (nullable YYImage *)imageNamed:(NSString *)name; // no cache!
+ (nullable YYImage *)imageWithContentsOfFile:(NSString *)path;
/** 此方法默认创建的图片是@1的*/
+ (nullable YYImage *)imageWithData:(NSData *)data;
+ (nullable YYImage *)imageWithData:(NSData *)data scale:(CGFloat)scale;

// MARK: - image 的属性
/**
 If the image is created from data or file, then the value indicates the data type.
 *如果图片的创建来自数据或文件，那么它的类型就是数据的类型。
 */
@property (nonatomic, readonly) YYImageType animatedImageType;

/**
 If the image is created from animated image data (multi-frame GIF/APNG/WebP),
 this property stores the original image data.
 *如果图片的创建来源于动画图片数据（更多架构 GIF/APNG/WebP），这个属性用来存储图片的原始数据。
 */
@property (nullable, nonatomic, readonly) NSData *animatedImageData;

/**
 The total memory usage (in bytes) if all frame images was loaded into memory.
 The value is 0 if the image is not created from a multi-frame image data.
 *内存的总使用量（字节）如果所有的帧图像被加载到内存。
 *这个值默认是0如果图片的创建不是来源于更多的架构图片的数据。
 */
@property (nonatomic, readonly) NSUInteger animatedImageMemorySize;

/**
 Preload all frame image to memory.
 *预加载所有帧图像到内存中。
 
 @discussion Set this property to `YES` will block the calling thread to decode 
 all animation frame image to memory, set to `NO` will release the preloaded frames.
 If the image is shared by lots of image views (such as emoticon), preload all
 frames will reduce the CPU cost.
 *设置这个属性为 'YES' 将阻塞调用线程去解码所有的图片数据并且加载到内存中，设置为 'NO' 将释放预加载的图片。
 *如果图片是大量分享的图片视图（例如表情符号），预加载所有的图片帧将可以减少CPU成本消耗。
 
 See `animatedImageMemorySize` for memory cost.
 */
@property (nonatomic) BOOL preloadAllAnimatedImageFrames;

@end

NS_ASSUME_NONNULL_END
