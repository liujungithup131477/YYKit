//
//  NSObject+YYModel.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/5/10.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provide some data-model method:
 提供一些数据模型的方法：
 
 * Convert json to any object, or convert any object to json.
 * 将 json 转化成任何对象，或者将任何对象转化为 json。
 * Set object properties with a key-value dictionary (like KVC).
 * 设置对象的属性的键-值 字典（如 KVC）。
 * Implementations of `NSCoding`, `NSCopying`, `-hash` and `-isEqual:`.
 * 实现`NSCoding`, `NSCopying`协议, `-hash` and `-isEqual:`方法。
 
 See `YYModel` protocol for custom methods.
 * 见 `YYModel` 协议自定义方法。
 
 
 Sample Code:
 * 示例代码：
    
     ********************** json convertor *********************
     ********************** json 转换器     *********************
     @interface YYAuthor : NSObject
     @property (nonatomic, strong) NSString *name;
     @property (nonatomic, assign) NSDate *birthday;
     @end
     @implementation YYAuthor
     @end
 
     @interface YYBook : NSObject
     @property (nonatomic, copy) NSString *name;
     @property (nonatomic, assign) NSUInteger pages;
     @property (nonatomic, strong) YYAuthor *author;
     @end
     @implementation YYBook
     @end
    
     int main() {
         // create model from json
         // 从 json 创建模型
         YYBook *book = [YYBook modelWithJSON:@"{\"name\": \"Harry Potter\", \"pages\": 256, \"author\": {\"name\": \"J.K.Rowling\", \"birthday\": \"1965-07-31\" }}"];
 
         // convert model to json
         // 将模型转换为 json
         NSString *json = [book modelToJSONString];
         // {"author":{"name":"J.K.Rowling","birthday":"1965-07-31T00:00:00+0000"},"name":"Harry Potter","pages":256}
     }
 
     ********************** Coding/Copying/hash/equal *********************
     @interface YYShadow :NSObject <NSCoding, NSCopying>
     @property (nonatomic, copy) NSString *name;
     @property (nonatomic, assign) CGSize size;
     @end
 
     @implementation YYShadow
     // 归档
     - (void)encodeWithCoder:(NSCoder *)aCoder { [self modelEncodeWithCoder:aCoder]; }
     // 解档
     - (id)initWithCoder:(NSCoder *)aDecoder { self = [super init]; return [self modelInitWithCoder:aDecoder]; }
     // copy 操作
     - (id)copyWithZone:(NSZone *)zone { return [self modelCopy]; }
     // hash 操作
     - (NSUInteger)hash { return [self modelHash]; }
     // 判断模型对象是否相同
     - (BOOL)isEqual:(id)object { return [self modelIsEqual:object]; }
     @end
 
 */

@interface NSObject (YYModel)

/**
 Creates and returns a new instance of the receiver from a json.
 This method is thread-safe.
 // 创建并且返回一个根据 json 实例的模型对象。是线程安全的。
 
 @param json  A json object in `NSDictionary`, `NSString` or `NSData`.
 // 参数 json json 对象是一个`NSDictionary`, `NSString` or `NSData`。
 
 @return A new instance created from the json, or nil if an error occurs.
 // 返回值： 创建一个新的模型实例对象根据 json， 或者 nil 如果出现错误。
 */
+ (nullable instancetype)modelWithJSON:(id)json;

/**
 Creates and returns a new instance of the receiver from a key-value dictionary.
 This method is thread-safe.
 * 通过一个键值-字典创建和返回一个新的模型实例。这个方法是线程安全的。
 
 @param dictionary  A key-value dictionary mapped to the instance's properties.
 Any invalid key-value pair in dictionary will be ignored.
 *参数 dictionary 通过一个键值-字典映射到实例对象属相。任何字典中无效的键值对都会被忽略。
 
 @return A new instance created from the dictionary, or nil if an error occurs.
 *返回值 返回根据一个字典创建的新的实例对象，或者如果发生错误返回 nil。
 
 @discussion The key in `dictionary` will mapped to the reciever's property name,
 and the value will set to the property. If the value's type does not match the
 property, this method will try to convert the value based on these rules:
 *此方法是根据字典的键值和对应的接收的模型的属性名做映射，并且赋值。如果值不能匹配属性，则方法
 将根据以下规则尝试转换：
 
     `NSString` or `NSNumber` -> c number, such as BOOL, int, long, float, NSUInteger...
     `NSString` -> NSDate, parsed with format "yyyy-MM-dd'T'HH:mm:ssZ", "yyyy-MM-dd HH:mm:ss" or "yyyy-MM-dd".
     *NSString` -> NSDate, 带"yyyy-MM-dd'T'HH:mm:ssZ", "yyyy-MM-dd HH:mm:ss" or "yyyy-MM-dd"格式的转换。
     `NSString` -> NSURL.
     `NSValue` -> struct or union, such as CGRect, CGSize, ...
     `NSString` -> SEL, Class.
 */
+ (nullable instancetype)modelWithDictionary:(NSDictionary *)dictionary;

/**
 Set the receiver's properties with a json object.
 *通过 json 设置接收者的属性。
 
 @discussion Any invalid data in json will be ignored.
 *此方法会将无效的 json 数据忽略。
 
 @param json  A json object of `NSDictionary`, `NSString` or `NSData`, mapped to the
 receiver's properties.
 *参数 json 一个 字典，字符串，二进制的 json 对象转换到对应的模型对象。
 
 @return Whether succeed.
 *返回值 返回是否成功。
 */
- (BOOL)modelSetWithJSON:(id)json;

/**
 Set the receiver's properties with a key-value dictionary.
 *通过字典设置模型的属性。
 
 @param dic  A key-value dictionary mapped to the receiver's properties.
 Any invalid key-value pair in dictionary will be ignored.
 *参数 dic 通过字典映射到对应的模型的属性。任何无效的字典的键值对都将被忽略。
 
 @discussion The key in `dictionary` will mapped to the reciever's property name,
 and the value will set to the property. If the value's type doesn't match the
 property, this method will try to convert the value based on these rules:
 *此方法是根据字典的键值和对应的接收的模型的属性名做映射，并且赋值。如果值不能匹配属性，则方法
 将根据以下规则尝试转换：
 
     `NSString`, `NSNumber` -> c number, such as BOOL, int, long, float, NSUInteger...
     `NSString` -> NSDate, parsed with format "yyyy-MM-dd'T'HH:mm:ssZ", "yyyy-MM-dd HH:mm:ss" or "yyyy-MM-dd".
     *NSString` -> NSDate, 带"yyyy-MM-dd'T'HH:mm:ssZ", "yyyy-MM-dd HH:mm:ss" or "yyyy-MM-dd"格式的转换。
     `NSString` -> NSURL.
     `NSValue` -> struct or union, such as CGRect, CGSize, ...
     `NSString` -> SEL, Class.
 
 @return Whether succeed.
 *返回值 是否成功。
 */
- (BOOL)modelSetWithDictionary:(NSDictionary *)dic;

/**
 Generate a json object from the receiver's properties.
 *根据模型的属性生成 json 对象。
 
 @return A json object in `NSDictionary` or `NSArray`, or nil if an error occurs.
 See [NSJSONSerialization isValidJSONObject] for more information.
 *返回一个 json 对象 ，通过字典或数组转化，如果方式错误就返回 nil。看 [NSJSONSerialization isValidJSONObject] 方法的注释可以查看对应的转化条件。
 
 @discussion Any of the invalid property is ignored.
 *任何无效的属性将被忽略。
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it just convert
 the inner object to json object.
 *如果模型是 `NSArray`, `NSDictionary` or `NSSet` ，它只是转换内部对象的 json 对象。
 */
- (nullable id)modelToJSONObject;

/**
 Generate a json string's data from the receiver's properties.
 *根据模型转换成 json 字符串的二进制数据。
 
 @return A json string's data, or nil if an error occurs.
 *返回一个 json 字符串的二进制数据，如果出错就返回 nil。
 
 @discussion Any of the invalid property is ignored.
 *任何无效的属性都将被忽略。
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it will also convert the 
 inner object to json string.
 *如果模型是`NSArray`, `NSDictionary` or `NSSet`,它还将转换内部对象的 json 字符串。
 */
- (nullable NSData *)modelToJSONData;

/**
 Generate a json string from the receiver's properties.
 *根据模型的属性生成 json字符串。
 
 @return A json string, or nil if an error occurs.
 *返回一个 json 字符串，或者 nil 如果发生错误。
 
 @discussion Any of the invalid property is ignored.
 *任何无效的属性将被忽略。
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it will also convert the 
 inner object to json string.
 *如果模型是`NSArray`, `NSDictionary` or `NSSet`,它还将转换内部对象的 json 字符串。
 */
- (nullable NSString *)modelToJSONString;

/**
 Copy a instance with the receiver's properties.
 
 @return A copied instance, or nil if an error occurs.
 */
- (nullable id)modelCopy;

/**
 Encode the receiver's properties to a coder.
 
 @param aCoder  An archiver object.
 */
- (void)modelEncodeWithCoder:(NSCoder *)aCoder;

/**
 Decode the receiver's properties from a decoder.
 
 @param aDecoder  An archiver object.
 
 @return self
 */
- (id)modelInitWithCoder:(NSCoder *)aDecoder;

/**
 Get a hash code with the receiver's properties.
 
 @return Hash code.
 */
- (NSUInteger)modelHash;

/**
 Compares the receiver with another object for equality, based on properties.
 
 @param model  Another object.
 
 @return `YES` if the reciever is equal to the object, otherwise `NO`.
 */
- (BOOL)modelIsEqual:(id)model;

/**
 Description method for debugging purposes based on properties.
 
 @return A string that describes the contents of the receiver.
 */
- (NSString *)modelDescription;

@end



/**
 Provide some data-model method for NSArray.
 */
@interface NSArray (YYModel)

/**
 Creates and returns an array from a json-array.
 This method is thread-safe.
 
 @param cls  The instance's class in array.
 @param json  A json array of `NSArray`, `NSString` or `NSData`.
              Example: [{"name","Mary"},{name:"Joe"}]
 
 @return A array, or nil if an error occurs.
 */
+ (nullable NSArray *)modelArrayWithClass:(Class)cls json:(id)json;

@end



/**
 Provide some data-model method for NSDictionary.
 */
@interface NSDictionary (YYModel)

/**
 Creates and returns a dictionary from a json.
 This method is thread-safe.
 
 @param cls  The value instance's class in dictionary.
 @param json  A json dictionary of `NSDictionary`, `NSString` or `NSData`.
              Example: {"user1":{"name","Mary"}, "user2": {name:"Joe"}}
 
 @return A array, or nil if an error occurs.
 */
+ (nullable NSDictionary *)modelDictionaryWithClass:(Class)cls json:(id)json;
@end



/**
 If the default model transform does not fit to your model class, implement one or
 more method in this protocol to change the default key-value transform process.
 There's no need to add '<YYModel>' to your class header.
 */
@protocol YYModel <NSObject>
@optional

/**
 Custom property mapper.
 
 @discussion If the key in JSON/Dictionary does not match to the model's property name,
 implements this method and returns the additional mapper.
 
 Example:
    
    json: 
        {
            "n":"Harry Pottery",
            "p": 256,
            "ext" : {
                "desc" : "A book written by J.K.Rowling."
            },
            "ID" : 100010
        }
 
    model:
        @interface YYBook : NSObject
        @property NSString *name;
        @property NSInteger page;
        @property NSString *desc;
        @property NSString *bookID;
        @end
        
        @implementation YYBook
        + (NSDictionary *)modelCustomPropertyMapper {
            return @{@"name"  : @"n",
                     @"page"  : @"p",
                     @"desc"  : @"ext.desc",
                     @"bookID": @[@"id", @"ID", @"book_id"]};
        }
        @end
 
 @return A custom mapper for properties.
 */
+ (nullable NSDictionary<NSString *, id> *)modelCustomPropertyMapper;

/**
 The generic class mapper for container properties.
 
 @discussion If the property is a container object, such as NSArray/NSSet/NSDictionary,
 implements this method and returns a property->class mapper, tells which kind of 
 object will be add to the array/set/dictionary.
 
  Example:
        @class YYShadow, YYBorder, YYAttachment;
 
        @interface YYAttributes
        @property NSString *name;
        @property NSArray *shadows;
        @property NSSet *borders;
        @property NSDictionary *attachments;
        @end
 
        @implementation YYAttributes
        + (NSDictionary *)modelContainerPropertyGenericClass {
            return @{@"shadows" : [YYShadow class],
                     @"borders" : YYBorder.class,
                     @"attachments" : @"YYAttachment" };
        }
        @end
 
 @return A class mapper.
 */
+ (nullable NSDictionary<NSString *, id> *)modelContainerPropertyGenericClass;

/**
 If you need to create instances of different classes during json->object transform,
 use the method to choose custom class based on dictionary data.
 
 @discussion If the model implements this method, it will be called to determine resulting class
 during `+modelWithJSON:`, `+modelWithDictionary:`, conveting object of properties of parent objects 
 (both singular and containers via `+modelContainerPropertyGenericClass`).
 
 Example:
        @class YYCircle, YYRectangle, YYLine;
 
        @implementation YYShape

        + (Class)modelCustomClassForDictionary:(NSDictionary*)dictionary {
            if (dictionary[@"radius"] != nil) {
                return [YYCircle class];
            } else if (dictionary[@"width"] != nil) {
                return [YYRectangle class];
            } else if (dictionary[@"y2"] != nil) {
                return [YYLine class];
            } else {
                return [self class];
            }
        }

        @end

 @param dictionary The json/kv dictionary.
 
 @return Class to create from this dictionary, `nil` to use current class.

 */
+ (nullable Class)modelCustomClassForDictionary:(NSDictionary*)dictionary;

/**
 All the properties in blacklist will be ignored in model transform process.
 Returns nil to ignore this feature.
 
 @return An array of property's name (Array<NSString>).
 */
+ (nullable NSArray<NSString *> *)modelPropertyBlacklist;

/**
 If a property is not in the whitelist, it will be ignored in model transform process.
 Returns nil to ignore this feature.
 
 @return An array of property's name (Array<NSString>).
 */
+ (nullable NSArray<NSString *> *)modelPropertyWhitelist;

/**
 This method's behavior is similar to `- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic;`, 
 but be called before the model transform.
 
 @discussion If the model implements this method, it will be called before
 `+modelWithJSON:`, `+modelWithDictionary:`, `-modelSetWithJSON:` and `-modelSetWithDictionary:`.
 If this method returns nil, the transform process will ignore this model.
 
 @param dic  The json/kv dictionary.
 
 @return Returns the modified dictionary, or nil to ignore this model.
 */
- (NSDictionary *)modelCustomWillTransformFromDictionary:(NSDictionary *)dic;

/**
 If the default json-to-model transform does not fit to your model object, implement
 this method to do additional process. You can also use this method to validate the 
 model's properties.
 
 @discussion If the model implements this method, it will be called at the end of
 `+modelWithJSON:`, `+modelWithDictionary:`, `-modelSetWithJSON:` and `-modelSetWithDictionary:`.
 If this method returns NO, the transform process will ignore this model.
 
 @param dic  The json/kv dictionary.
 
 @return Returns YES if the model is valid, or NO to ignore this model.
 */
- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic;

/**
 If the default model-to-json transform does not fit to your model class, implement
 this method to do additional process. You can also use this method to validate the
 json dictionary.
 
 @discussion If the model implements this method, it will be called at the end of
 `-modelToJSONObject` and `-modelToJSONString`.
 If this method returns NO, the transform process will ignore this json dictionary.
 
 @param dic  The json dictionary.
 
 @return Returns YES if the model is valid, or NO to ignore this model.
 */
- (BOOL)modelCustomTransformToDictionary:(NSMutableDictionary *)dic;

@end

NS_ASSUME_NONNULL_END
