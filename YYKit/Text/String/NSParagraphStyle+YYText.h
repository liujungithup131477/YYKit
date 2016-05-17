//
//  NSParagraphStyle+YYText.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 14/10/7.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *Paragraph：段
 Provides extensions for `NSParagraphStyle` to work with CoreText.
 *提供了`NSParagraphStyle`扩展类去完成CoreText的工作。
 */
@interface NSParagraphStyle (YYText)

/**
 Creates a new NSParagraphStyle object from the CoreText Style.
 *从CoreText样式创建一个新的 NSParagraphStyle 对象。
 
 @param CTStyle CoreText Paragraph Style.
 *参数 CTStyle CoreText 的段样式。
 
 @return a new NSParagraphStyle
 *返回值 返回一个新的 NSParagraphStyle 对象。
 */
+ (nullable NSParagraphStyle *)styleWithCTStyle:(CTParagraphStyleRef)CTStyle;

/**
 Creates and returns a CoreText Paragraph Style. (need call CFRelease() after used)
 *创建并且返回一个 CoreText 段样式。（需要使用之后调用CFRelease()）
 */
- (nullable CTParagraphStyleRef)CTStyle CF_RETURNS_RETAINED;

@end

NS_ASSUME_NONNULL_END
