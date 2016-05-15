//
//  YYCache.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/2/13.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

@class YYMemoryCache, YYDiskCache;

NS_ASSUME_NONNULL_BEGIN

/**
 `YYCache` is a thread safe key-value cache.
 *`YYCache` 是一个线程安全的键值缓存。
 
 It use `YYMemoryCache` to store objects in a small and fast memory cache,
 and use `YYDiskCache` to persisting objects to a large and slow disk cache.
 See `YYMemoryCache` and `YYDiskCache` for more information.
 *它使用“YYMemoryCache”存储对象在一个小而快内存缓存,
 *并使用“YYDiskCache”持久化对象很大和慢磁盘缓存。
 *见“YYMemoryCache”和“YYDiskCache”获得更多信息。
 */
@interface YYCache : NSObject

/** The name of the cache, readonly. 
 * 缓存的名称,只读的。
 */
@property (copy, readonly) NSString *name;

/** The underlying memory cache. see `YYMemoryCache` for more information.
 *底层的内存缓存。有关更多信息,请参见“YYMemoryCache”。
 */
@property (strong, readonly) YYMemoryCache *memoryCache;

/** The underlying disk cache. see `YYDiskCache` for more information.
 *底层磁盘高速缓存。有关更多信息,请参见“YYDiskCache”。
 */
@property (strong, readonly) YYDiskCache *diskCache;

/**
 Create a new instance with the specified name.
 *用指定的名称创建一个新的缓存实例。
 Multiple instances with the same name will make the cache unstable.
 *具有相同名称的多个实例将缓存不稳定。
 
 @param name  The name of the cache. It will create a dictionary with the name in
     the app's caches dictionary for disk cache. Once initialized you should not 
     read and write to this directory.
 *参数 名称 缓存的名称。通过这个名字将创建在磁盘上的缓存，缓存在应用程序的沙盒的 cache 目录下，名称为 name。同时在内存上根据 name 创建内存缓存。
 一旦初始化你不应该读和写这个目录。
 @result A new cache object, or nil if an error occurs.
 *返回值 返回一个新的缓存对象,或 nil 如果出现错误。
 */
- (nullable instancetype)initWithName:(NSString *)name;

/**
 Create a new instance with the specified path.
 *创建一个新的缓存实例对象根据指定的路径。
 Multiple instances with the same name will make the cache unstable.
 *具有相同名称的多个实例将缓存不稳定。
 
 @param path  Full path of a directory in which the cache will write data.
     Once initialized you should not read and write to this directory.
 *参数 path 这个缓存目录的全路径创建的缓存将被写入二进制数据。
 @result A new cache object, or nil if an error occurs.
 *返回值 返回一个新的缓存对象，或者 nil 如果方式错误。
 *NS_DESIGNATED_INITIALIZER 指定的初始化方法
 */
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

/**
 Convenience Initializers
 *便利的初始化方法
 Create a new instance with the specified name.
 *用指定的名称创建一个新的缓存实例。
 Multiple instances with the same name will make the cache unstable.
  *具有相同名称的多个实例将缓存不稳定。
 @param name  The name of the cache. It will create a dictionary with the name in
     the app's caches dictionary for disk cache. Once initialized you should not 
     read and write to this directory.
  *参数 名称 缓存的名称。通过这个名字将创建在磁盘上的缓存，缓存在应用程序的沙盒的 cache 目录下，名称为 name。同时在内存上根据 name 创建内存缓存。
  一旦初始化你不应该读和写这个目录。
 @result A new cache object, or nil if an error occurs.
  *返回值 返回一个新的缓存对象,或 nil 如果出现错误。
 */
+ (nullable instancetype)cacheWithName:(NSString *)name;

/**
 Convenience Initializers
  *便利的初始化方法
 Create a new instance with the specified path.
 *创建一个新的缓存实例对象根据指定的路径。
 Multiple instances with the same name will make the cache unstable.
 *具有相同名称的多个实例将缓存不稳定。
 
 @param path  Full path of a directory in which the cache will write data.
     Once initialized you should not read and write to this directory.
 *参数 path 这个缓存目录的全路径创建的缓存将被写入二进制数据。
 @result A new cache object, or nil if an error occurs.
*返回值 返回一个新的缓存对象，或者 nil 如果方式错误。
 */
+ (nullable instancetype)cacheWithPath:(NSString *)path;

/** 不可用的*/
- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

#pragma mark - Access Methods
///=============================================================================
/// @name Access Methods  访问方法
///=============================================================================

/**
 Returns a boolean value that indicates whether a given key is in cache.
 *返回一个布尔值,根据给定的键值查看缓存中是否包含对应的缓存对象。
 This method may blocks the calling thread until file read finished.
 这种方法可能会阻塞调用线程,直到文件读取完成。
 
 @param key A string identifying the value. If nil, just return NO.
 *键字符串标识值。如果为零,就返回 NO。
 @return Whether the key is in cache.
 *返回对应的键值是否在缓存中。
 */
- (BOOL)containsObjectForKey:(NSString *)key;

/**
 Returns a boolean value with the block that indicates whether a given key is in cache.
*返回一个布尔值,在block回调中根据返回的条件查看缓存中是否包含对应的缓存对象，并且可以做一些后续处理。

 This method returns immediately and invoke the passed block in background queue
 when the operation finished.
 *该方法立即返回当后台操作完成后在对应的后台线程唤醒block。
 
 
 @param key   A string identifying the value. If nil, just return NO.
*键字符串标识值。如果为零,就返回 NO。
 @param block A block which will be invoked in background queue when finished.
 *参数block 当后台操作完成后会被调用。
 */
- (void)containsObjectForKey:(NSString *)key withBlock:(nullable void(^)(NSString *key, BOOL contains))block;

/**
 Returns the value associated with a given key.
 *返回与给定的键相关联的值。
 This method may blocks the calling thread until file read finished.
 这种方法可能会阻塞调用线程,直到文件读取完成。
 
 @param key A string identifying the value. If nil, just return nil.
 *键字符串标识值。如果为零,就返回 NO。
 @return The value associated with key, or nil if no value is associated with key.
 *返回值 返回与键值相关联的值，或者 nil 如果没有与键值相关联的值。
 */
- (nullable id<NSCoding>)objectForKey:(NSString *)key;

/**
 Returns the value associated with a given key.
 *返回与给定的键相关联的值。
 This method returns immediately and invoke the passed block in background queue
 when the operation finished.
 *该方法立即返回当后台操作完成后在对应的后台线程唤醒block。
 
 @param key A string identifying the value. If nil, just return nil.
 *键字符串标识值。如果为零,就返回 NO。
 @param block A block which will be invoked in background queue when finished.
 *参数block 当后台操作完成后会被调用。
 */
- (void)objectForKey:(NSString *)key withBlock:(nullable void(^)(NSString *key, id<NSCoding> object))block;

/**
 Sets the value of the specified key in the cache.
 *根据指定的键值在缓存中设置值。
 This method may blocks the calling thread until file write finished.
 *这种方法可能会阻塞调用线程,直到文件写入完成。
 
 @param object The object to be stored in the cache. If nil, it calls `removeObjectForKey:`.
 *参数 object 对象存储在缓存中。如果为 nil,它调用“removeObjectForKey:”。
 @param key    The key with which to associate the value. If nil, this method has no effect.
 *参数 key 对应存储在缓存中的键值，如果为 nil，这个方法没有效果。
 */
- (void)setObject:(nullable id<NSCoding>)object forKey:(NSString *)key;

/**
 Sets the value of the specified key in the cache.
 *根据指定的键值在缓存中设置值。
 This method returns immediately and invoke the passed block in background queue
 when the operation finished.
 *该方法立即返回当后台操作完成后在对应的后台线程唤醒block。
 
 @param object The object to be stored in the cache. If nil, it calls `removeObjectForKey:`.
 *参数 object 对象存储在缓存中。如果为 nil,它调用“removeObjectForKey:”。
 @param block  A block which will be invoked in background queue when finished.
 *参数block 当后台操作完成后会被调用。
 */
- (void)setObject:(nullable id<NSCoding>)object forKey:(NSString *)key withBlock:(nullable void(^)(void))block;

/**
 Removes the value of the specified key in the cache.
 *在缓存中移除指定键的值。
 This method may blocks the calling thread until file delete finished.
 *这种方法可能会阻塞调用线程,直到文件写入完成。
 
 @param key The key identifying the value to be removed. If nil, this method has no effect.
 *确定要删除的值的key。如果为 nil ,这种方法没有效果。
 */
- (void)removeObjectForKey:(NSString *)key;

/**
 Removes the value of the specified key in the cache.
 *在缓存中移除指定键的值。
 This method returns immediately and invoke the passed block in background queue
 when the operation finished.
 *该方法立即返回当后台操作完成后在对应的后台线程唤醒block。
 
 @param key The key identifying the value to be removed. If nil, this method has no effect.
 *确定要删除的值的key。如果为 nil ,这种方法没有效果。
 @param block  A block which will be invoked in background queue when finished.
 *参数block 当后台操作完成后会被调用。
 */
- (void)removeObjectForKey:(NSString *)key withBlock:(nullable void(^)(NSString *key))block;

/**
 Empties the cache.
 *清空缓存。
 This method may blocks the calling thread until file delete finished.
 *这种方法可能会阻塞调用线程,直到文件删除了。
 */
- (void)removeAllObjects;

/**
 Empties the cache.
 *清空缓存。
 This method returns immediately and invoke the passed block in background queue
 when the operation finished.
 *该方法立即返回当后台操作完成后在对应的后台线程唤醒block。
 
 @param block  A block which will be invoked in background queue when finished.
 *参数block 当后台操作完成后会被调用。
 */
- (void)removeAllObjectsWithBlock:(void(^)(void))block;

/**
 Empties the cache with block.
 *清空缓存
 This method returns immediately and executes the clear operation with block in background.
 *这个方法立即返回并且执行清除操作，在后台线程执行 block。
 
 @warning You should not send message to this instance in these blocks.
 *警告 你不应该在这些 block 中发送消息到这个实例对象。
 @param progress This block will be invoked during removing, pass nil to ignore.
 *参数 progress 在删除中这个 block 将被调用，传 nil 被忽略。
 @param end      This block will be invoked at the end, pass nil to ignore.
 *参数 end 这个 block 在最后将被唤醒，传 nil 被忽略。
 */
- (void)removeAllObjectsWithProgressBlock:(nullable void(^)(int removedCount, int totalCount))progress
                                 endBlock:(nullable void(^)(BOOL error))end;

@end

NS_ASSUME_NONNULL_END
