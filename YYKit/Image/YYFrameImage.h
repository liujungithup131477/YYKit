//
//  YYFrameImage.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 14/12/9.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

#if __has_include(<YYKit/YYKit.h>)
#import <YYKit/YYAnimatedImageView.h>
#else
#import "YYAnimatedImageView.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 An image to display frame-based animation.
 *一个image显示的基础框架。
 
 @discussion It is a fully compatible `UIImage` subclass.
 It only support system image format such as png and jpeg.
 The animation can be played by YYAnimatedImageView.
 *这是一个完全兼容`UIImage`的子类。仅仅支持系统格式例如png and jpeg。
 *实现动画可以使用YYAnimatedImageView类。
 // MARK: - 帧动画的创建方式-事例
 Sample Code:
     
     NSArray *paths = @[@"/ani/frame1.png", @"/ani/frame2.png", @"/ani/frame3.png"];
     NSArray *times = @[@0.1, @0.2, @0.1];
     YYFrameImage *image = [YYFrameImage alloc] initWithImagePaths:paths frameDurations:times repeats:YES];
     YYAnimatedImageView *imageView = [YYAnimatedImageView alloc] initWithImage:image];
     [view addSubView:imageView];
 */
@interface YYFrameImage : UIImage <YYAnimatedImage>

/**
 Create a frame animated image from files.
 *根据图片文件路径创建动画图片。每一个帧图像执行动画的时间相同。
 
 @param paths            An array of NSString objects, contains the full or 
                         partial path to each image file.
                         e.g. @[@"/ani/1.png",@"/ani/2.png",@"/ani/3.png"]
 *参数 path 一个包含字符串对象的数组，字符串是动画文件的全路径或部分路径。例如：
 *@[@"/ani/1.png",@"/ani/2.png",@"/ani/3.png"]。
 
 @param oneFrameDuration The duration (in seconds) per frame.
 *参数 oneFrameDuration 每一个帧图像执行动画地时间（单位s）。
 
 @param loopCount        The animation loop count, 0 means infinite.
 *参数 loopCount 动画执行的次数，0代表无限次。
 
 @return An initialized YYFrameImage object, or nil when an error occurs.
 *返回值 返回一个 YYFrameImage 对象，或 nil 如果发生错误。
 */
- (nullable instancetype)initWithImagePaths:(NSArray<NSString *> *)paths
                           oneFrameDuration:(NSTimeInterval)oneFrameDuration
                                  loopCount:(NSUInteger)loopCount;

/**
 Create a frame animated image from files.
 *根据图片文件路径创建动画图片。每一个帧图像执行动画的时间可以自定义。
 
 @param paths          An array of NSString objects, contains the full or
                       partial path to each image file.
                       e.g. @[@"/ani/frame1.png",@"/ani/frame2.png",@"/ani/frame3.png"]
 *参数 path 一个包含字符串对象的数组，字符串是动画文件的全路径或部分路径。例如：
 *@[@"/ani/frame1.png",@"/ani/frame2.png",@"/ani/frame3.png"]。
 
 @param frameDurations An array of NSNumber objects, contains the duration (in seconds) per frame.
                       e.g. @[@0.1, @0.2, @0.3];
 *参数 frameDurations 每一个帧图像执行动画的时间的数组。
 
 @param loopCount      The animation loop count, 0 means infinite.
 *参数 loopCount 动画执行的次数，0代表无限次。
 
 @return An initialized YYFrameImage object, or nil when an error occurs.
 *返回值 返回一个 YYFrameImage 对象，或 nil 如果发生错误。
 */
- (nullable instancetype)initWithImagePaths:(NSArray<NSString *> *)paths
                             frameDurations:(NSArray<NSNumber *> *)frameDurations
                                  loopCount:(NSUInteger)loopCount;

/**
 Create a frame animated image from an array of data.
 *创建一个动画帧图像根据二进制图片数据数组。
 
 @param dataArray        An array of NSData objects.
 *参数 dataArray 存放图片二进制数据的数组。
 
 @param oneFrameDuration The duration (in seconds) per frame.
 *参数 oneFrameDuration 统一设置每一个动画图片的动画执行时间。
 
 @param loopCount        The animation loop count, 0 means infinite.
 *参数 loopCount 动画执行的次数，0代表无限次。
 
 @return An initialized YYFrameImage object, or nil when an error occurs.
 *返回值 返回一个 YYFrameImage 对象，或 nil 如果发生错误。
 */
- (nullable instancetype)initWithImageDataArray:(NSArray<NSData *> *)dataArray
                               oneFrameDuration:(NSTimeInterval)oneFrameDuration
                                      loopCount:(NSUInteger)loopCount;

/**
 Create a frame animated image from an array of data.
 *创建一个动画帧图像根据二进制图片数据数组。
 
 @param dataArray      An array of NSData objects.
 *参数 dataArray 存放图片二进制数据的数组。
 
 @param frameDurations An array of NSNumber objects, contains the duration (in seconds) per frame.
                       e.g. @[@0.1, @0.2, @0.3];
 *参数 frameDurations 每一个帧图像执行动画的时间的数组。
 
 @param loopCount      The animation loop count, 0 means infinite.
 *参数 loopCount 动画执行的次数，0代表无限次。
 
 @return An initialized YYFrameImage object, or nil when an error occurs.
 *返回值 返回一个 YYFrameImage 对象，或 nil 如果发生错误。
 */
- (nullable instancetype)initWithImageDataArray:(NSArray<NSData *> *)dataArray
                                 frameDurations:(NSArray *)frameDurations
                                      loopCount:(NSUInteger)loopCount;

@end

NS_ASSUME_NONNULL_END
