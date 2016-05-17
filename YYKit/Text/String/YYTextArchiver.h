//
//  YYTextArchiver.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/3/16.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A subclass of `NSKeyedArchiver` which implement `NSKeyedArchiverDelegate` protocol.
 *这是`NSKeyedArchiver`的一个子类，实现了`NSKeyedArchiverDelegate`协议。
 
 The archiver can encode the object which contains
 CGColor/CGImage/CTRunDelegateRef/.. (such as NSAttributedString).
 存储服务器可以编码的对象包括CGColor/CGImage/CTRunDelegateRef/.. (例如 NSAttributedString)。
 */
@interface YYTextArchiver : NSKeyedArchiver <NSKeyedArchiverDelegate>
@end

/**
 A subclass of `NSKeyedUnarchiver` which implement `NSKeyedUnarchiverDelegate` 
 protocol. The unarchiver can decode the data which is encoded by 
 `YYTextArchiver` or `NSKeyedArchiver`.
 *这个类是`NSKeyedUnarchiver`的一个子类，实现了`NSKeyedUnarchiverDelegate`协议。可以将
 *通过`YYTextArchiver` or `NSKeyedArchiver`编码的对象解码。
 */
@interface YYTextUnarchiver : NSKeyedUnarchiver <NSKeyedUnarchiverDelegate>
@end

NS_ASSUME_NONNULL_END
