//
//  YYTextParser.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/3/6.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// MARK: - 文本解析协议
/**
 The YYTextParser protocol declares the required method for YYTextView and YYLabel
 to modify the text during editing.
 
 You can implement this protocol to add code highlighting or emoticon replacement for
 YYTextView and YYLabel. See `YYTextSimpleMarkdownParser` and `YYTextSimpleEmoticonParser` for example.
 */
@protocol YYTextParser <NSObject>
@required
/**
 When text is changed in YYTextView or YYLabel, this method will be called.
 
 @param text  The original attributed string. This method may parse the text and
 change the text attributes or content.
 
 @param selectedRange  Current selected range in `text`.
 This method should correct the range if the text content is changed. If there's 
 no selected range (such as YYLabel), this value is NULL.
 
 @return If the 'text' is modified in this method, returns `YES`, otherwise returns `NO`.
 */
- (BOOL)parseText:(nullable NSMutableAttributedString *)text selectedRange:(nullable NSRangePointer)selectedRange;
@end


// MARK: - 简单的 Markdown 解析文本
/**
 A simple markdown parser.
 *一个简单的markdown 解析器
 
 It'a very simple markdown parser, you can use this parser to highlight some 
 small piece of markdown text.
 *这是一个非常简单的 markdown 的解析器，你可以使用这个解析器去突出小块的 markdown 文本。
 
 This markdown parser use regular expression to parse text, slow and weak.
 If you want to write a better parser, try these projests:
 *这个 markdown 解析器使用正则表达式来解析文本，缓慢而脆弱。如果你想写一个更好的解析器，
 *试试下面的项目。
 https://github.com/NimbusKit/markdown
 https://github.com/dreamwieber/AttributedMarkdown
 https://github.com/indragiek/CocoaMarkdown
 
 Or you can use lex/yacc to generate your custom parser.
 *或者你可以使用lex和yacc来生成自定义解析器。
 */
@interface YYTextSimpleMarkdownParser : NSObject <YYTextParser>
@property (nonatomic) CGFloat fontSize;         ///< default is 14
@property (nonatomic) CGFloat headerFontSize;   ///< default is 20

@property (nullable, nonatomic, strong) UIColor *textColor;
@property (nullable, nonatomic, strong) UIColor *controlTextColor;
@property (nullable, nonatomic, strong) UIColor *headerTextColor;
@property (nullable, nonatomic, strong) UIColor *inlineTextColor;
@property (nullable, nonatomic, strong) UIColor *codeTextColor;
@property (nullable, nonatomic, strong) UIColor *linkTextColor;

/**
 *  设置明亮主题的颜色
 */
- (void)setColorWithBrightTheme; ///< reset the color properties to pre-defined value. 重新设置颜色属性，默认是预定义的。
/**
 *  设置黑暗主题的颜色
 */
- (void)setColorWithDarkTheme;   ///< reset the color properties to pre-defined value.
@end


// MARK: - 简单的表情符号解析
/**
 A simple emoticon parser.
 
 Use this parser to map some specified piece of string to image emoticon.
 *使用这个解析器将一些指定的字符串映射到图像表情符号。
 Example: "Hello :smile:"  ->  "Hello 😀"
 
 It can also be used to extend the "unicode emoticon".
 *它也可以用来扩展“unicode表情符号”。
 */
@interface YYTextSimpleEmoticonParser : NSObject <YYTextParser>

/**
 The custom emoticon mapper.
 The key is a specified plain string, such as @":smile:".
 The value is a UIImage which will replace the specified plain string in text.
 */
@property (nullable, copy) NSDictionary<NSString *, __kindof UIImage *> *emoticonMapper;
@end

NS_ASSUME_NONNULL_END
