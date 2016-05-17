//
//  UIControl+YYAdd.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 13/4/5.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides extensions for `UIControl`.
 *提供`UIControl`的扩展。
 */
@interface UIControl (YYAdd)

// MARK: - 删除监听事件
/**
 Removes all targets and actions for a particular event (or events)
 from an internal dispatch table.
 *删除所有特定事件（或者有多个事件）目标和动作
 */
- (void)removeAllTargets;

/**
 Adds or replaces a target and action for a particular event (or events)
 to an internal dispatch table.
 *增加或替换目标和事件从指定的事件（或多个事件）到内部的分配表。
 
 @param target         The target object—that is, the object to which the
                       action message is sent. If this is nil, the responder
                       chain is searched for an object willing to respond to the
                       action message.
 参数 target 目标对象，指定系统在发送响应事件的消息时接收的对象。如果为nil，系统将会根据响应者链条找到可以接收这条消息的对象。
 
 @param action         A selector identifying an action message. It cannot be NULL.
 *参数 action 对应的响应方法。
 
 @param controlEvents  A bitmask specifying the control events for which the
                       action message is sent.
 *参数 controlEvents 事件的响应类型。
 */
- (void)setTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

/**
 Adds a block for a particular event (or events) to an internal dispatch table.
 It will cause a strong reference to @a block.
 
 @param block          The block which is invoked then the action message is
                       sent  (cannot be nil). The block is retained.
 
 @param controlEvents  A bitmask specifying the control events for which the
                       action message is sent.
 */
- (void)addBlockForControlEvents:(UIControlEvents)controlEvents block:(void (^)(id sender))block;

/**
 Adds or replaces a block for a particular event (or events) to an internal
 dispatch table. It will cause a strong reference to @a block.
 
 @param block          The block which is invoked then the action message is
                       sent (cannot be nil). The block is retained.
 
 @param controlEvents  A bitmask specifying the control events for which the
                       action message is sent.
 */
- (void)setBlockForControlEvents:(UIControlEvents)controlEvents block:(void (^)(id sender))block;

/**
 Removes all blocks for a particular event (or events) from an internal
 dispatch table.
 
 @param controlEvents  A bitmask specifying the control events for which the
                       action message is sent.
 */
- (void)removeAllBlocksForControlEvents:(UIControlEvents)controlEvents;

@end

NS_ASSUME_NONNULL_END
