//
//  YYWebImageManager.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/2/19.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

#if __has_include(<YYKit/YYKit.h>)
#import <YYKit/YYImageCache.h>
#else
#import "YYImageCache.h"
#endif

@class YYWebImageOperation;

NS_ASSUME_NONNULL_BEGIN

// MARK: - 相关枚举
// MARK: - 图像下载操作选项
/// The options to control image operation.
/// 控制图像操作的选项。
typedef NS_OPTIONS(NSUInteger, YYWebImageOptions) {
    
    /// Show network activity on status bar when download image.
    /// 当下载图片时在状态栏显示网络活动。
    YYWebImageOptionShowNetworkActivity = 1 << 0,
    
    /// Display progressive/interlaced/baseline image during download (same as web browser).
    /// 显示进度/隔行/当图片下载开始时（类似于web浏览器）。
    YYWebImageOptionProgressive = 1 << 1,
    
    /// Display blurred progressive JPEG or interlaced PNG image during download.
    /// This will ignore baseline image for better user experience.
    /// 意思就是让你在下载图片的时候渐进式显示图片,也就是一个模糊加载的过程。
    YYWebImageOptionProgressiveBlur = 1 << 2,
    
    /// Use NSURLCache instead of YYImageCache.
    /// 用NSURLCache代替YYImageCache。
    YYWebImageOptionUseNSURLCache = 1 << 3,
    
    /// Allows untrusted SSL ceriticates.
    /// 允许不信任的 SSL 证书。
    /// 可以出于测试目的使用，在正式产品中慎用。
    YYWebImageOptionAllowInvalidSSLCertificates = 1 << 4,
    
    /// Allows background task to download image when app is in background.
    /// 当应用程序进入后台时允许任务在后台继续下载。
    YYWebImageOptionAllowBackgroundTask = 1 << 5,
    
    /// Handles cookies stored in NSHTTPCookieStore.
    /// 通过设置
    /// NSMutableURLRequest.HTTPShouldHandleCookies = YES;
    /// 处理保存在 NSHTTPCookieStore 中的 cookies
    YYWebImageOptionHandleCookies = 1 << 6,
    
    /// Load the image from remote and refresh the image cache.
    /// 从远程加载图片并且刷新图片缓存。
    YYWebImageOptionRefreshImageCache = 1 << 7,
    
    /// Do not load image from/to disk cache.
    /// 不从磁盘缓存加载图片，也不把图片缓存到磁盘。
    YYWebImageOptionIgnoreDiskCache = 1 << 8,
    
    /// Do not change the view's image before set a new URL to it.
    /// 在新的url来之前不改变视图的图片。也就是忽略占位图片。
    YYWebImageOptionIgnorePlaceHolder = 1 << 9,
    
    /// Ignore image decoding.
    /// 忽略图片解码
    /// This may used for image downloading without display.
    /// 这可能用于图像下载没有显示。
    YYWebImageOptionIgnoreImageDecoding = 1 << 10,
    
    /// Ignore multi-frame image decoding.
    /// 忽略额外的图片类型（WebP, APNG and GIF）解码。
    /// This will handle the GIF/APNG/WebP/ICO image as single frame image.
    /// 这将处理GIF / APNG / WebP /ICO 等格式图片的单帧图像。
    YYWebImageOptionIgnoreAnimatedImage = 1 << 11,
    
    /// Set the image to view with a fade animation.
    /// 设置视图图片和渐变动画。
    /// This will add a "fade" animation on image view's layer for better user experience.
    /// 这将添加一个渐变式的动画在图片视图的layer上，以此增强用户体验。
    YYWebImageOptionSetImageWithFadeAnimation = 1 << 12,
    
    /// Do not set the image to the view when image fetch complete.
    /// 不设置视图的图片当图片获取完成。
    /// You may set the image manually.
    /// 你可以手动设置的图像。
    YYWebImageOptionAvoidSetImage = 1 << 13,
    
    /// This flag will add the URL to a blacklist (in memory) when the URL fail to be downloaded,
    /// so the library won't keep trying.
    /// 当图片下载失败此标志会将该url添加到黑名单，不在尝试下载。
    YYWebImageOptionIgnoreFailedURL = 1 << 14,
};

// MARK: - image 来源
/// Indicated where the image came from.
/// 表示图像是从哪里来的。
typedef NS_ENUM(NSUInteger, YYWebImageFromType) {
    
    /// No value. 无值
    YYWebImageFromNone = 0,
    
    /// Fetched from memory cache immediately.
    /// 立即从内存缓存获取。
    /// If you called "setImageWithURL:..." and the image is already in memory,
    /// 如果"setImageWithURL:..."已被调用并且图像已经存在内存中，
    /// then you will get this value at the same call.
    /// 然后你将获得这个值在同一调用。
    YYWebImageFromMemoryCacheFast,
    
    /// Fetched from memory cache.
    /// 从内存缓存中获取
    YYWebImageFromMemoryCache,
    
    /// Fetched from disk cache.
    /// 从磁盘获取
    YYWebImageFromDiskCache,
    
    /// Fetched from remote (web or file path).
    YYWebImageFromRemote,
};

// MARK: - 图像获取完整的阶段
/// Indicated image fetch complete stage.
/// 表示图像获取完整的阶段。
typedef NS_ENUM(NSInteger, YYWebImageStage) {
    
    /// Incomplete, progressive image.
    /// 不完整的，进行中的图片。
    YYWebImageStageProgress  = -1,
    
    /// Cancelled.
    /// 取消的。
    YYWebImageStageCancelled = 0,
    
    /// Finished (succeed or failed).
    /// 完成的（成功或失败）。
    YYWebImageStageFinished  = 1,
};


/**
 The block invoked in remote image fetch progress.
 *在这个block块中可以获取图片下载的进度。
 
 @param receivedSize Current received size in bytes.
 *参数 receivedSize 当前接收到的字节数
 @param expectedSize Expected total size in bytes (-1 means unknown).
 *参数 expectedSize 预计图片的总字节数（-1 表示未知）。
 */
typedef void(^YYWebImageProgressBlock)(NSInteger receivedSize, NSInteger expectedSize);

/**
 The block invoked before remote image fetch finished to do additional image process.
 *这个block中我们可以对获得图片做一些操作，比如调整大小等。
 
 @discussion This block will be invoked before `YYWebImageCompletionBlock` to give
 you a chance to do additional image process (such as resize or crop). If there's
 no need to transform the image, just return the `image` parameter.
 *这个block给你在调用`YYWebImageCompletionBlock`之前修改image的机会。如果不需要处理图片直接返回image参数。
 
 @example You can clip the image, blur it and add rounded corners with these code:
 *在这个block回调中你可以裁剪图片，做模糊操作，并且添加圆角。
    ^(UIImage *image, NSURL *url) {
        // Maybe you need to create an @autoreleasepool to limit memory cost.
        image = [image imageByResizeToSize:CGSizeMake(100, 100) contentMode:UIViewContentModeScaleAspectFill];
        image = [image imageByBlurRadius:20 tintColor:nil tintMode:kCGBlendModeNormal saturation:1.2 maskImage:nil];
        image = [image imageByRoundCornerRadius:5];
        return image;
    }
 
 @param image The image fetched from url.
 *参数 image 根据url获取到的图片。
 @param url   The image url (remote or local file path).
 *参数 url 图片的url （远程的或本地的文件路径）。
 @return The transformed image.
 返回值 返回处理过的图片。
 */
typedef UIImage * _Nullable (^YYWebImageTransformBlock)(UIImage *image, NSURL *url);

/**
 The block invoked when image fetch finished or cancelled.
 *这个block是图片获取完成之后的回调。
 
 @param image       The image.
 @param url         The image url (remote or local file path).
 @param from        Where the image came from.  // 获取的图片的来源
 @param error       Error during image fetching.  // 获取图片过程中的错误
 @param finished    If the operation is cancelled, this value is NO, otherwise YES.
                    如果选项是cancelled，这个值是'NO'，否则是'YES'。
 */
typedef void (^YYWebImageCompletionBlock)(UIImage * _Nullable image,
                                          NSURL *url,
                                          YYWebImageFromType from,  //YYWebImageFromType 加载的图片来源的位置
                                          YYWebImageStage stage,
                                          NSError * _Nullable error);




/**
 A manager to create and manage web image operation.
 *管理image操作的图片管理器。
 */
@interface YYWebImageManager : NSObject

// MARK: - 管理器的创建方式
/**
 Returns global YYWebImageManager instance.
 *返回全局的YYWebImageManager单列。
 
 @return YYWebImageManager shared instance.
 *返回值 返回 YYWebImageManager 共享实例。
 */
+ (instancetype)sharedManager;

/**
 Creates a manager with an image cache and operation queue.
 *用图像缓存和操作队列创建图像下载管理器。
 
 @param cache  Image cache used by manager (pass nil to avoid image cache).
 *所使用的图像缓存管理器(通过nil避免图像缓存)。
 @param queue  The operation queue on which image operations are scheduled and run
                (pass nil to make the new operation start immediately without queue).
 *对图片的操作已经加入到操作队列中了。
 *你可以把它设置为零，使新的操作立即开始不排队。
 @return A new manager.
 *返回一个新的管理器。
 */
- (instancetype)initWithCache:(nullable YYImageCache *)cache
                        queue:(nullable NSOperationQueue *)queue NS_DESIGNATED_INITIALIZER;

// MARK: - 无效的实例化方式
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

// MARK: - 图片的下载操作创建方式
/**
 Creates and returns a new image operation, the operation will start immediately.
 *创建并返回一个新的图片操作，这个操作将立刻开始。
 
 @param url        The image url (remote or local file path).
 *参数 url 图片的url（远程的或本地的文件路径）
 @param options    The options to control image operation.
 参数 options 控制图片操作的选项。
 @param progress   Progress block which will be invoked on background thread (pass nil to avoid).
 *参数 progress progress block 可以处理图片下载的进度。
 @param transform  Transform block which will be invoked on background thread  (pass nil to avoid).
 *参数 transform 可以对图片裁剪，添加圆角等操作。
 @param completion Completion block which will be invoked on background thread  (pass nil to avoid).
 *参数 completion 最后的完成回调，可以获取到最后图片的信息。
 @return A new image operation.
 *返回一个图片操作。
 */
- (nullable YYWebImageOperation *)requestImageWithURL:(NSURL *)url
                                              options:(YYWebImageOptions)options
                                             progress:(nullable YYWebImageProgressBlock)progress
                                            transform:(nullable YYWebImageTransformBlock)transform
                                           completion:(nullable YYWebImageCompletionBlock)completion;

// MARK: - 图片操作管理器的属性
/**
 The image cache used by image operation.
 *图片操作使用的图片缓存。
 You can set it to nil to avoid image cache.
 *您可以将它设置为零,以避免图像缓存。
 *
 */
@property (nullable, nonatomic, strong) YYImageCache *cache;

/**
 The operation queue on which image operations are scheduled and run.
 *对图片的操作已经加入到操作队列中了。
 You can set it to nil to make the new operation start immediately without queue.
 *你可以把它设置为零，使新的操作立即开始不排队。
 
 You can use this queue to control maximum number of concurrent operations, to obtain 
 the status of the current operations, or to cancel all operations in this manager.
 *您可以使用此队列控制最大数量的并发操作,获得当前操作的状态,或取消所有操作在这个管理器。
 */
@property (nullable, nonatomic, strong) NSOperationQueue *queue;

/**
 The shared transform block to process image. Default is nil.
 *这个block中我们可以对获得图片做一些操作，比如调整大小等。
 
 When called `requestImageWithURL:options:progress:transform:completion` and
 the `transform` is nil, this block will be used.
 *当调用`requestImageWithURL:options:progress:transform:completion`并且`transform`设置为nil，这个block将被使用。
 */
@property (nullable, nonatomic, copy) YYWebImageTransformBlock sharedTransformBlock;

/**
 The image request timeout interval in seconds. Default is 15.
 *请求超时时间。默认是15s。
 */
@property (nonatomic) NSTimeInterval timeout;

/**
 The username used by NSURLCredential, default is nil.
 *NSURLCredential所使用的用户名,默认值是零。
 */
@property (nullable, nonatomic, copy) NSString *username;

/**
 The password used by NSURLCredential, default is nil.
 *NSURLCredential所使用的密码,默认值是零。
 */
@property (nullable, nonatomic, copy) NSString *password;

/**
 The image HTTP request header. Default is "Accept:image/webp,image/\*;q=0.8".
 *image HTTP的请求头。
 */
@property (nullable, nonatomic, copy) NSDictionary<NSString *, NSString *> *headers;

/**
 A block which will be invoked for each image HTTP request to do additional
 HTTP header process. Default is nil.
 *这个block在每一个HTTP请求时被调用，可以在HTTP头中做一些操作。默认是 nil。
 
 Use this block to add or remove HTTP header field for a specified URL.
 *这个block可以对HTTP报头字段做增加或删除操作。
 */
@property (nullable, nonatomic, copy) NSDictionary<NSString *, NSString *> *(^headersFilter)(NSURL *url, NSDictionary<NSString *, NSString *> * _Nullable header);

/**
 A block which will be invoked for each image operation. Default is nil.
 *缓存键过滤器将被每一个image操作调用。默认是nil。
 
 Use this block to provide a custom image cache key for a specified URL.
 *这个block可以设置自定义的图片缓存键。
 */
@property (nullable, nonatomic, copy) NSString *(^cacheKeyFilter)(NSURL *url);

// MARK: - 查看资源的方法
/**
 Returns the HTTP headers for a specified URL.
 *返回指定的url的HTTP头。
 
 @param url A specified URL.
 *参数 url 指定的url
 @return HTTP headers.
 *返回值 返回HTTP的头。
 */
- (nullable NSDictionary<NSString *, NSString *> *)headersForURL:(NSURL *)url;

/**
 Returns the cache key for a specified URL.
 *返回指定的url的缓存键。
 
 @param url A specified URL
 *参数 url 指定的url。
 @return Cache key used in YYImageCache.
 *返回值 返回使用YYImageCache的键值。
 */
- (NSString *)cacheKeyForURL:(NSURL *)url;

@end

NS_ASSUME_NONNULL_END
