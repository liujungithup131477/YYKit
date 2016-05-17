//
//  YYTextKeyboardManager.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/6/3.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

//MARK: - YYTextKeyboardTransition 协议
/**
 System keyboard transition information.
 *系统键盘过渡信息。
 Use -[YYTextKeyboardManager convertRect:toView:] to convert frame to specified view.
 *使用-[YYTextKeyboardManager convertRect:toView:]转换指定的视图的frame。
 */
typedef struct {
    BOOL fromVisible; ///< Keyboard visible before transition. 过渡前键盘可见
    BOOL toVisible;   ///< Keyboard visible after transition. 过渡后键盘可见
    CGRect fromFrame; ///< Keyboard frame before transition.  过渡前的键盘frame
    CGRect toFrame;   ///< Keyboard frame after transition.  过渡后的键盘frame
    NSTimeInterval animationDuration;       ///< Keyboard transition animation duration.
    /// 键盘过渡执行动画时间
    UIViewAnimationCurve animationCurve;    ///< Keyboard transition animation curve.
    /// 键盘过渡的动画曲线。
    UIViewAnimationOptions animationOption; ///< Keybaord transition animation option.
    /// 键盘过渡的动画操作
} YYTextKeyboardTransition;


/**
 The YYTextKeyboardObserver protocol defines the method you can use
 to receive system keyboard change information.
 *你可以使用YYTextKeyboardObserver协议定义的方法来接收系统键盘改变的信息。
 */
@protocol YYTextKeyboardObserver <NSObject>
@optional
- (void)keyboardChangedWithTransition:(YYTextKeyboardTransition)transition;
@end


/**
 A YYTextKeyboardManager object lets you get the system keyboard information,
 and track the keyboard visible/frame/transition.
 *通过YYTextKeyboardManager对象可以获得系统键盘的信息，并可以跟踪键盘的可见性/frame/过渡过程。
 
 @discussion You should access this class in main thread.
 *你应该访问这个类在主线程。
 Compatible: iPhone/iPad with iOS6/7/8/9.
 *兼容的版本：iPhone/iPad with iOS6/7/8/9。
 */
@interface YYTextKeyboardManager : NSObject

//MARK: - 不可用的创建方式
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

//MARK: - 创建键盘管理器的方法
/// Get the default manager (returns nil in App Extension).
/// 获得默认的管理对象（返回nil在应用程序扩展）。
//TODO: - 如果是应用程扩展（自定义键盘）返回nil，不是应用程序扩展返回键盘管理器。
+ (nullable instancetype)defaultManager;

//MARK: - 键盘管理器的属性
/// Get the keyboard window. nil if there's no keyboard window.
/// 获得键盘的窗口。 nil 如果没有键盘的窗口。
@property (nullable, nonatomic, readonly) UIWindow *keyboardWindow;

/// Get the keyboard view. nil if there's no keyboard view.
/// 获得键盘视图。nil 如果没有键盘视图。
@property (nullable, nonatomic, readonly) UIView *keyboardView;

/// Whether the keyboard is visible.
/// 键盘是否可见。
@property (nonatomic, readonly, getter=isKeyboardVisible) BOOL keyboardVisible;

/// Get the keyboard frame. CGRectNull if there's no keyboard view.
/// Use convertRect:toView: to convert frame to specified view.
/// 获得键盘的frame。CGRectNull 如果没有键盘视图。
/// 使用convertRect:toView:去转换frame到指定的视图。
@property (nonatomic, readonly) CGRect keyboardFrame;


//MARK: - 键盘管理器的相关方法
/**
 Add an observer to manager to get keyboard change information.
 *添加键盘管理器的观察者去获得键盘变化的信息。
 This method makes a weak reference to the observer.
 *这个方法对观察者做了弱引用。
 
 @param observer An observer. 
 *参数 observer 观察者。
 This method will do nothing if the observer is nil, or already added.
 *这个方法将什么都不做如果观察者为nil，或者已经添加。
 */
- (void)addObserver:(id<YYTextKeyboardObserver>)observer;

/**
 Remove an observer from manager.
 *把观察者从管理器移除。
 
 @param observer An observer.
 *参数 observer 观察者。
 This method will do nothing if the observer is nil, or not in manager.
 *这个方法将什么都不做如果观察者为nil，或者已经不在管理器。
 */
- (void)removeObserver:(id<YYTextKeyboardObserver>)observer;

/**
 Convert rect to specified view or window.
 *转换到指定的视图或窗口。
 
 @param rect The frame rect.
 *参数 rect frame 的结构体。
 @param view A specified view or window (pass nil to convert for main window).
 参数 view 指定的视图或窗口（传nil 转换主窗口）。
 @return The converted rect in specifeid view.
 *返回指定的rect在指定的视图。
 */
//TODO: - 有待研究
- (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;

@end

NS_ASSUME_NONNULL_END
