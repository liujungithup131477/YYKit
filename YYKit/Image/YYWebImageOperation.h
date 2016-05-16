//
//  YYWebImageOperation.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/2/15.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

#if __has_include(<YYKit/YYKit.h>)
#import <YYKit/YYImageCache.h>
#import <YYKit/YYWebImageManager.h>
#else
#import "YYImageCache.h"
#import "YYWebImageManager.h"
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 The YYWebImageOperation class is an NSOperation subclass used to fetch image 
 from URL request.
 *YYWebImageOperation类是NSOperation类的子类，用于获取图像从URL请求。
 
 @discussion It's an asynchronous operation. You typically execute it by adding 
 it to an operation queue, or calls 'start' to execute it manually. When the 
 operation is started, it will:
 *这是一个异步操作。你通常的执行方式是将该操作添加到一个操作队列中，或者手动的调用'start'方法执行。
 *当操作开始，它将：
 
     1. Get the image from the cache, if exist, return it with `completion` block.
     *首先从缓存获取image对象，如果为空，返回 ’completion‘ block。
     2. Start an URL connection to fetch image from the request, invoke the `progress`
        to notify request progress (and invoke `completion` block to return the 
        progressive image if enabled by progressive option).
     *通过请求开始从一个URL连接获取图片，然后发送请求过程的通知，执行`progress`block，（如果 progressive 的选项有效，返回进度）。
     3. Process the image by invoke the `transform` block.
     *之后调用`transform`block对图片做裁剪等操作。
     4. Put the image to cache and return it with `completion` block.
     *将图片保存到缓存并且返回`completion` block。
 
 */
@interface YYWebImageOperation : NSOperation

//MARK: - 图片下载操作的属性
/**
 *  ///< The image URL request.
 *  ///< 图片请求的url。
 */
@property (nonatomic, strong, readonly)           NSURLRequest      *request;
/**
 *  ///< The response for request.
 *  ///< 请求的响应信息。
 */
@property (nullable, nonatomic, strong, readonly) NSURLResponse     *response;
/**
 *  ///< The image cache.
 *  ///< 图片缓存。
 */
@property (nullable, nonatomic, strong, readonly) YYImageCache      *cache;
/**
 *  ///< The image cache key.
 *  ///< 在图片缓存区的存储图片的键值。
 */
@property (nonatomic, strong, readonly)           NSString          *cacheKey;
/**
 *  ///< The operation's option.
 *  ///< 请求操作。
 */
@property (nonatomic, readonly)                   YYWebImageOptions options;

/**
 Whether the URL connection should consult the credential storage for authenticating 
 the connection. Default is YES.
 *此属性是说url的连接是否应该咨询存储认证。默认是 YES。
 
 @discussion This is the value that is returned in the `NSURLConnectionDelegate` 
 method `-connectionShouldUseCredentialStorage:`.
 *这是`NSURLConnectionDelegate`方法`-connectionShouldUseCredentialStorage:`返回的值。
 */
@property (nonatomic) BOOL shouldUseCredentialStorage;

/**
 The credential used for authentication challenges in `-connection:didReceiveAuthenticationChallenge:`.
 
 @discussion This will be overridden by any shared credentials that exist for the 
 username or password of the request URL, if present.
 *如果存在 共享的credentials  这个属性 就会被重写
 */
@property (nullable, nonatomic, strong) NSURLCredential *credential;

//MARK: - 创建图片下载操作的方法
/**
 Creates and returns a new operation.
 *创建并返回一个新的操作。
 
 You should call `start` to execute this operation, or you can add the operation
 to an operation queue.
 *你应该调用`start`来执行这个操作，或者将这个操作添加到操作队列中。
 
 @param request    The Image request. This value should not be nil.
 *获取图片的请求。这个值不应该为 nil。
 @param options    A mask to specify options to use for this operation.
 参数 options 图片下载操作的选项，支持位运算。
 @param cache      An image cache. Pass nil to avoid image cache.
 参数 cache 图片缓存。传nil将不使用图片缓存。
 @param cacheKey   An image cache key. Pass nil to avoid image cache.
 参数 cacheKey 图片在缓存中的键。传nil将不适用图片缓存。
 @param progress   A block invoked in image fetch progress.
 参数 progress 这个block在图片获取过程中被调用。
                     The block will be invoked in background thread. Pass nil to avoid it.
 *在后台线程被调用。传nil忽略它。
 @param transform  A block invoked before image fetch finished to do additional image process.
                     The block will be invoked in background thread. Pass nil to avoid it.
 参数 transform 这个block在图片获取完成后调用，可以用来执行图片的裁剪等操作。这个block将在后台线程执行。传
 nil表示忽略。
 @param completion A block invoked when image fetch finished or cancelled.
                     The block will be invoked in background thread. Pass nil to avoid it.
 参数 completion 这个block当图片获取完成或者取消被调用。这个block将在后台线程执行。传nil忽略。
 
 @return The image request opeartion, or nil if an error occurs.
 *返回值 返回一个图片的操作请求，或者nil如果出现错误。
 */
- (instancetype)initWithRequest:(NSURLRequest *)request
                        options:(YYWebImageOptions)options
                          cache:(nullable YYImageCache *)cache
                       cacheKey:(nullable NSString *)cacheKey
                       progress:(nullable YYWebImageProgressBlock)progress
                      transform:(nullable YYWebImageTransformBlock)transform
                     completion:(nullable YYWebImageCompletionBlock)completion NS_DESIGNATED_INITIALIZER;

//MARK: - 不可用的创建图像操作的方式
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
