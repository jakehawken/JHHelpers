//  JHDataSanitizer.h
//  Created by Jacob Hawken on 6/12/16.

#import <Foundation/Foundation.h>


@interface JHDataSanitizer : NSObject

#pragma mark - checking

+ (BOOL)item:(id)item existsAndIsA:(Class)intendedClass;
+ (BOOL)array:(NSArray *)array existsAndContainsOnlyItemsOfType:(Class)intendedClass;
+ (BOOL)item:(id)item isAnArrayAndOnlyContainsItemsofType:(Class)intendedClass;
+ (BOOL)dictionary:(NSDictionary *)dictionary existsAndContainsOnlyKeysOfType:(Class)keyClass andValuesOfType:(Class)valueClass;
+ (BOOL)item:(id)item isADictionaryAndContainsOnlyKeysOfType:(Class)keyClass andValuesOfType:(Class)valueClass;
+ (BOOL)arrayOfStrings:(NSArray<NSString *> *)stringArray1 matchesArrayOfStrings:(NSArray<NSString *> *)stringArray2;

#pragma mark - filtering

+ (NSArray *)allItemsFromArray:(NSArray *)array ofType:(Class)target;
+ (NSDictionary *)allPairsFromDictionary:(NSDictionary *)dictionary withValuesOfType:(Class)type;

// The following takes an object that is either an array or a dictionary, and performs
// either of the above methods on it, depending on what its type actually is.
// This is useful when working with an SDK like Firebase, in whic data types
// can be volatile and unpredictable.

+ (id)itemsFromDictionaryOrArray:(id)dictOrArr ofType:(Class)targetType;

#pragma mark - strings

+ (NSString *)removeSpacesAndMakeLowerCase:(NSString *)inputString;

@end
