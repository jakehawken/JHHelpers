//  JHMapper.h
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import <Foundation/Foundation.h>

/*!
 @class JHMapper
 
 @brief A handful of helper methods for doing work with arrays and dictionaries.
 
 @discussion    This class is conceived of as a helper for performing repetetive tasks, mutations, conversions, and general manipulation of data stored in Objective-C arrays and dictionaries.
 
 @helps This helps any object or class that needs to transform data structures or convert collections of objects from one form to another.
*/

NS_ASSUME_NONNULL_BEGIN

@interface JHMapper<Q,T> : NSObject

#pragma mark - GENERIC DO/MUTATE

/*!
 @brief Does a bit of work for each item in an array.
 
 @discussion Just one extra layer on top of NSArray fast iteration. For every item in a given array, perform a specific bit of work, whether it's mutating that object, or doing something else entirely.
 
 Example:
 
 @code
 [JHMapper<Cookie *> forEachIn:cookies perform:^(Cookie *cookie) {
    [self eat:cookie];
 }];
 @endcode
 
 @param  array The input array, made up of items of type <Q>.
 
 @param  perform The block which is called for each item in the array, which receives an item of type Q and then peforms a task.
*/

+ (void)forEachIn:(NSArray<Q> *)array perform:(void(^)(Q object))block;

#pragma mark - MAPPING

/*!
 @brief Using the contents of one typed array, generates a new typed array of equal or fewer items.
 
 @discussion For each item in the passed in array of items of type <Q>, the evaluation block is called. The block returns an object of type <T>. If that object is non-nil, it is added to the output array. If it's nil, there will be no entry in the output array for that given item of type <Q>.
 
 Example:
 
 @code
 [JHMapper<NSDictionary *, NSString*> mapFilter:dictionaries withEvaluationBlock:^NSString *(NSDictionary *dictionary) {
    if (dictionary.count > 0) {
        return @(object.count).stringValue;
    }
    return nil;
 }];
 @endcode
 
 This takes in an array of dictionaries, and returns an array of NStrings for all the dictionaries with counts greater than 0.
 
 @param  array The input array, made up of items of type <Q>.
 
 @param  evaluationBlock The evaluation block, which receives an item of type Q and returns a nullable item of type T.
 
 @return NSArray<T> The filtered array, of items of type T. Will have a count of equal or lesser than the input array.
*/

+ (NSArray<T> *)mapFilter:(NSArray<Q> *)array withBlock:(T(^)(Q object))evaluationBlock;

/*!
 @brief Using the contents of one typed array, generates a dictionary with those items as values.
 
 @discussion For each item in the passed in array of items of type <T>, the key block is called. The block takes in each of items from the input array generates the corresponding keys for those items in the new dictionary.
 
 Example:
 
 @code
 cowDictionary = [JHMapper<Cow *> inflateArray:cows toDictionaryWithKeyBlock:^NSString *(Cow *cow) {
    return cow.name;
 }];
 @endcode
 
 This takes in an array of custom objects, and returns a dictionary of those items, using one of the object's properties as the key.
 
 @param  array The input array, made up of items of type <T>.
 
 @param  keyBlock The key block, which receives an item of type T and returns an NSString *.
 
 @return NSDictionary<NSString *, T> The dictionary, with NSString keys and values of type T.
*/

+ (NSDictionary<NSString *, T> *)inflateArray:(NSArray<T> *)array toDictionaryWithKeyBlock:(NSString *(^)(T object))keyBlock;

/*!
 @brief Using the contents of one typed dictionary, generates a new typed dictionary with values of a (potentially) different type.
 
 @discussion For each item in the passed in array of items of type <Q>, the key block is called. The block takes in each of the values from the input dictionary and is used to generate the keys for those item in the new dictionary. The valueBlock is then called, which takes in each of the values from the original dictionary and returns corresponding items of type <T>. Each value generated by the valueBlock is placed in the new dictionary at the corresponding key generated by the keyBlock.
 
 Example:
 
 @code
 beefDictionary = [JHMapper<Cow *, Beef *> mapValuesToNewDictionaryFrom:cowDictionary withKeyBlock:^NSString *(NSString *originalKey, Cow *cow) {
    return originalKey;
 } valueBlock:^Beef*(Cow *) {
    return [ButcherShop process:cow];
 }];
 @endcode
 
 This takes in a dictionary of custom objects, and returns a dictionary of different items, using the same key from the item in the old dictionary.
 
 @param  dictionary The input dictionary, with NSString keys, and values of type <T>.
 
 @param  keyBlock A block which receives an item of type Q, as well as its key from the input dictionary, and returns an NSString. Determines the key of that item in the new dictionary.

 @param  valueBlock A block which receives an item of type Q and returns an item of type T.
 
 @return NSDictionary<NSString *, T> The dictionary, with NSString keys and values of type T.
*/

+ (NSDictionary<NSString *, T> *)mapValuesToNewDictionaryFrom:(NSDictionary<NSString *, Q> *)dictionary withKeyBlock:(NSString *(^)(NSString *originalKey, Q object))keyBlock valueBlock:(T(^)(Q object))valueBlock;

#pragma mark auto-map

/*!
 @brief Using the contents of a typed array, generates a dictionary of the items from that array, using each item's description property for its key.
 
 @param  array The input array, made up of items of type <T>.
 
 @return NSDictionary<NSString *, T> The dictionary, with NSString keys and values of type <T>.
*/

+ (NSDictionary<NSString *, T> *)mapToDictionaryWithValueDescriptionsAsKeys:(NSArray<T> *)array;

/*!
 @brief Using the contents of a typed array, generates a dictionary of the items from that array, using a string of each item's index in the array as its key in the new dictionary.
 
 @param  array The input array, made up of items of type <T>.
 
 @return NSDictionary<NSString *, T> The dictionary, with NSString keys and values of type <T>.
*/

+ (NSDictionary<NSString *, T> *)mapToDictionaryWithNumberedKeysFrom:(NSArray<T> *)array;

#pragma mark - Dictionary helpers

/*!
 @brief  Takes in a dictionary and returns an array of its values, sorted in the ascending order of the corresponding keys.
 
 @param  dictionary The input dictionary.

 @discussion This method takes in a dictionary and sorts its keys in ascending order. It then creates an array of the values of that dictionary, using the order determined by the sorted keys.
 
 Example:
 
 @code
 NSDictionary *stuff = @{
                            @"hat" : @"cat",
                            @"1" : @"dog",
                            @"zulu" : @"snake",
                            @"apple" : @"horse"
                        };
 NSArray *sortedValues = [JHMapper valuesFromDictionarySortedByKeys:stuff];
 //sortedValues will equal @[@"dog", @"horse", @"cat", @"snake"];
 @endcode
 
 @return NSArray  An array of the values from the dictionary sorted in the ascending order of their keys.
*/

+ (NSArray *)valuesFromDictionarySortedByKeys:(NSDictionary<NSString *, id> *)dictionary;

/*!
 @brief  Takes in a dictionary and generates a sorted array of the keys.
 
 @param  dictionary  The input dictionary.
 
 @return NSArray  An array of the keys from the dictionary sorted in ascending order.
*/

+ (NSArray<NSString *> *)sortedKeysFromDictionary:(NSDictionary<NSString *, id> *)dictionary;

@end

NS_ASSUME_NONNULL_END