//
//  UIBarButtonItem+YYAdd.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 13/10/15.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides extensions for `UIBarButtonItem`.
 */
@interface UIBarButtonItem (YYAdd)

/**
 The block that invoked when the item is selected. The objects captured by block
 will retained by the ButtonItem.
 *item被选中的时候该block将被调用。item对象将被该block强引用。
 
 @discussion This param is conflict with `target` and `action` property.
 *参数 这个参数是和`target` and `action`属性冲突的。
 Set this will set `target` and `action` property to some internal objects.
 *设置这个block可以替换对应的`target` and `action`方法。
 */
@property (nullable, nonatomic, copy) void (^actionBlock)(id);

@end

NS_ASSUME_NONNULL_END