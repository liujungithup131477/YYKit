//
//  UITextField+YYAdd.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 14/5/12.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides extensions for `UITextField`.
 */
@interface UITextField (YYAdd)

// MARK: - 选中所有的文本
/**
 Set all text selected.
 */
- (void)selectAllText;

// MARK: - 选中文档中的某一部分
/**
 Set text in range selected.
 
 @param range  The range of selected text in a document.
 */
- (void)setSelectedRange:(NSRange)range;

@end

NS_ASSUME_NONNULL_END
