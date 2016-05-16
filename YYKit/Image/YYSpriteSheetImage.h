//
//  YYSpriteImage.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/4/21.
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
 An image to display sprite sheet animation.
 *创建 image 来执行动画精灵表的动画。
 
 @discussion It is a fully compatible `UIImage` subclass.
 The animation can be played by YYAnimatedImageView.
 *这是一个完全兼容`UIImage`的子类。
 *实现动画可以使用YYAnimatedImageView类。
 
 // MARK: - sprite sheet 动画举例
 Sample Code:
  
    // 8 * 12 sprites in a single sheet image
    UIImage *spriteSheet = [UIImage imageNamed:@"sprite-sheet"];
    NSMutableArray *contentRects = [NSMutableArray new];
    NSMutableArray *durations = [NSMutableArray new];
    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 8; i++) {
            CGRect rect;
            rect.size = CGSizeMake(img.size.width / 8, img.size.height / 12);
            rect.origin.x = img.size.width / 8 * i;
            rect.origin.y = img.size.height / 12 * j;
            [contentRects addObject:[NSValue valueWithCGRect:rect]];
            [durations addObject:@(1 / 60.0)];
        }
    }
    YYSpriteSheetImage *sprite;
    sprite = [[YYSpriteSheetImage alloc] initWithSpriteSheetImage:img
                                                     contentRects:contentRects
                                                   frameDurations:durations
                                                        loopCount:0];
    YYAnimatedImageView *imgView = [YYAnimatedImageView new];
    imgView.size = CGSizeMake(img.size.width / 8, img.size.height / 12);
    imgView.image = sprite;
 
 
 
 @discussion It can also be used to display single frame in sprite sheet image.
 *它也可以用来显示一帧在雪碧表的形象。
 Sample Code:
 
    YYSpriteSheetImage *sheet = ...;
    UIImageView *imageView = ...;
    imageView.image = sheet;
    imageView.layer.contentsRect = [sheet contentsRectForCALayerAtIndex:6];
 
 */
@interface YYSpriteSheetImage : UIImage <YYAnimatedImage>

// MARK: - 初始化方法
/**
 Creates and returns an image object.
 *创建并返回一个图片对象。
 
 @param image          The sprite sheet image (contains all frames).
 *参数 image 用来执行 sprite sheet 动画的完整 image(包含所有的帧)
 
 @param contentRects   The sprite sheet image frame rects in the image coordinates.
     The rectangle should not outside the image's bounds. The objects in this array
     should be created with [NSValue valueWithCGRect:].
 *参数 contentRects 创建的 sprite sheet image 的 frame 在第一个参数 image 图片上的坐标。
 
 @param frameDurations The sprite sheet image frame's durations in seconds. 
     The objects in this array should be NSNumber.
 *参数 frameDurations sprite sheet image 的 frame 变化时间的数组（单位s）。
 *数组中存放的应该是NSNumber类型。
 
 @param loopCount      Animation loop count, 0 means infinite looping.
 *参数 loopCount 动画执行的次数，0代表无限次。
 
 @return An image object, or nil if an error occurs.
  *返回值 返回一个 sprite sheet image 对象，或 nil 如果发生错误。
 */
- (nullable instancetype)initWithSpriteSheetImage:(UIImage *)image
                                     contentRects:(NSArray<NSValue *> *)contentRects
                                   frameDurations:(NSArray<NSNumber *> *)frameDurations
                                        loopCount:(NSUInteger)loopCount;

// MARK: - sprite sheet image 属性
/**
 *  sprite sheet image 的 frame 在 image（传入的图片） 图片上的坐标位置的数组。
 */
@property (nonatomic, readonly) NSArray<NSValue *> *contentRects;
/**
 *  sprite sheet image 的 frame 变化时间的数组（单位s）。
 */
@property (nonatomic, readonly) NSArray<NSValue *> *frameDurations;
/**
 *  参数 loopCount 动画执行的次数，0代表无限次。
 */
@property (nonatomic, readonly) NSUInteger loopCount;

//TODO: - 有待研究
/**
 Get the contents rect for CALayer.
 *获得CALayer矩形内容。
 See "contentsRect" property in CALayer for more information.
 *有关更多信息,请参见“contentsRect”属性在CALayer。
 
 @param index Index of frame.
 *参数 index frame 的索引。
 @return Contents Rect.
 *返回值 返回内容的 rect。
 */
- (CGRect)contentsRectForCALayerAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
