//
//  UIApplication+YYAdd.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 13/4/4.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides extensions for `UIApplication`.
 *提供对`UIApplication`的扩展。
 */
@interface UIApplication (YYAdd)

// MARK: - 对应用程序中的一些常用信息做了计算型属性处理
/// "Documents" folder in this app's sandbox.
@property (nonatomic, readonly) NSURL *documentsURL;
@property (nonatomic, readonly) NSString *documentsPath;

/// "Caches" folder in this app's sandbox.
@property (nonatomic, readonly) NSURL *cachesURL;
@property (nonatomic, readonly) NSString *cachesPath;

/// "Library" folder in this app's sandbox.
@property (nonatomic, readonly) NSURL *libraryURL;
@property (nonatomic, readonly) NSString *libraryPath;

/// Application's Bundle Name (show in SpringBoard).
@property (nullable, nonatomic, readonly) NSString *appBundleName;

/// Application's Bundle ID.  e.g. "com.ibireme.MyApp"
@property (nullable, nonatomic, readonly) NSString *appBundleID;

/// Application's Version.  e.g. "1.2.0"
@property (nullable, nonatomic, readonly) NSString *appVersion;

/// Application's Build number. e.g. "123"
@property (nullable, nonatomic, readonly) NSString *appBuildVersion;

/// Whether this app is pirated (not install from appstore).
/// 应用程序是否是盗版（不是从appstore上安装的）。
@property (nonatomic, readonly) BOOL isPirated;

/// Whether this app is being debugged (debugger attached).
/// 这个程序是否正在调试(调试器连接)。
@property (nonatomic, readonly) BOOL isBeingDebugged;

/// Current thread real memory used in byte. (-1 when error occurs)
/// 当前线程中使用的实际内存字节。发生错误时(-1)。
@property (nonatomic, readonly) int64_t memoryUsage;

/// Current thread CPU usage, 1.0 means 100%. (-1 when error occurs)
/// 当前线程CPU使用率,1.0意味着100%。发生错误时(-1)。
@property (nonatomic, readonly) float cpuUsage;

// MARK: - 网络指示器方法
/**
 Increments the number of active network requests.
 *增加活动网络的请求数量。
 If this number was zero before incrementing, this will start animating the 
 status bar network activity indicator.
 *如果这个数字是从0开始增加，在状态栏将会执行网络指示器的动画。
 
 This method is thread safe.
 *这个方法是线程安全的。
 
 This method has no effect in App Extension.
 *在应用程序扩展这种方法没有效果。
 */
- (void)incrementNetworkActivityCount;

/**
 Decrements the number of active network requests. 
 *减少网络请求的数量。
 If this number becomes zero after decrementing, this will stop animating the 
 status bar network activity indicator.
 *如果这个数字递减之后是0，将停止网络指示器。
 
 This method is thread safe.
 *这个方法是线程安全的。
 
 This method has no effect in App Extension.
 *在应用程序扩展这种方法没有效果。
 */
- (void)decrementNetworkActivityCount;

// MARK: - 是否是应用程序扩展
/// Returns YES in App Extension.
/// 如果是应用程序扩展返回 YES。
+ (BOOL)isAppExtension;

/// Same as sharedApplication, but returns nil in App Extension.
/// 和sharedApplication方法一样，但是如果是应用程序扩展返回nil。
+ (nullable UIApplication *)sharedExtensionApplication;

@end

NS_ASSUME_NONNULL_END
