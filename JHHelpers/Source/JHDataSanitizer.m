//  JHDataSanitizer.m
//  Created by Jacob Hawken on 6/12/16.

#import "JHDataSanitizer.h"

@implementation JHDataSanitizer

+ (BOOL)item:(id)item existsAndIsA:(Class)intendedClass
{
  return item != nil && [item isKindOfClass:intendedClass];
}

+ (BOOL)array:(NSArray *)array existsAndContainsOnlyItemsOfType:(Class)intendedClass
{
  if (array == nil) {return NO;}
  BOOL arrayContainsOnlyCorrectClass = YES;
  for (int i = 0; i < array.count; i++)
  {
    if (![array[i] isKindOfClass:intendedClass])
    {
      arrayContainsOnlyCorrectClass = NO;
      break;
    }
  }
  return arrayContainsOnlyCorrectClass;
}

+ (BOOL)item:(id)item isAnArrayAndOnlyContainsItemsofType:(Class)intendedClass
{
  if (![JHDataSanitizer item:item existsAndIsA:[NSArray class]])
  {
    return NO;
  }
  NSArray *array = (NSArray *)item;
  return [JHDataSanitizer array:array existsAndContainsOnlyItemsOfType:intendedClass];
}

+ (BOOL)dictionary:(NSDictionary *)dictionary existsAndContainsOnlyKeysOfType:(Class)keyClass andValuesOfType:(Class)valueClass
{
  BOOL allKeysAreCorrectClass = [JHDataSanitizer array:[dictionary allKeys] existsAndContainsOnlyItemsOfType:keyClass];
  BOOL allValuesAreCorrectClass = [JHDataSanitizer array:[dictionary allValues] existsAndContainsOnlyItemsOfType:valueClass];
  return allKeysAreCorrectClass && allValuesAreCorrectClass;
}

+ (BOOL)item:(id)item isADictionaryAndContainsOnlyKeysOfType:(Class)keyClass andValuesOfType:(Class)valueClass
{
  if (![item isKindOfClass:NSDictionary.class])
  {
    return NO;
  }
  
  return [JHDataSanitizer dictionary:(NSDictionary *)item existsAndContainsOnlyKeysOfType:keyClass andValuesOfType:valueClass];
}

+(BOOL)arrayOfStrings:(NSArray<NSString *> *)stringArray1 matchesArrayOfStrings:(NSArray<NSString *> *)stringArray2
{
  if (stringArray1.count != stringArray2.count)
  {
    return NO;
  }
  BOOL allStringsMatch = YES;
  
  for (NSInteger i = 0; i < stringArray1.count; i++)
  {
    NSString *string1 = stringArray1[i];
    NSString *string2 = stringArray2[i];
    if (![string1 isEqualToString:string2])
    {
      allStringsMatch = NO;
      break;
    }
  }
  
  return allStringsMatch;
}

+ (NSArray *)allItemsFromArray:(NSArray *)array ofType:(Class)targetClass
{
  NSMutableArray *targetArray = [NSMutableArray array];
  for (id item in array)
  {
    if ([item isKindOfClass:targetClass])
    {
      [targetArray addObject:item];
    }
  }
  return targetArray;
}

+ (NSDictionary *)allPairsFromDictionary:(NSDictionary *)dictionary withValuesOfType:(Class)targetType
{
  NSMutableDictionary *targetDict = [NSMutableDictionary dictionary];
  for (id key in dictionary.allKeys)
  {
    id object = dictionary[key];
    if ([object isKindOfClass:targetType])
    {
      [targetDict setObject:object forKey:key];
    }
  }
  return targetDict;
}

+ (id)itemsFromDictionaryOrArray:(id)dictOrArr ofType:(Class)targetType
{
  if (![dictOrArr isKindOfClass:NSArray.class] && ![dictOrArr isKindOfClass:NSDictionary.class])
  {
    return nil;
  }
  
  id targetCollection;
  
  if ([dictOrArr isKindOfClass:NSArray.class])
  {
    NSArray *itsAnArray = dictOrArr;
    targetCollection = [self allItemsFromArray:itsAnArray ofType:targetType];
  }
  else if ([dictOrArr isKindOfClass:NSDictionary.class])
  {
    NSDictionary *itsADict = dictOrArr;
    targetCollection = [self allPairsFromDictionary:itsADict withValuesOfType:targetType];
  }
  
  return targetCollection;
}

+ (NSString *)removeSpacesAndMakeLowerCase:(NSString *)inputString
{
  NSString *lowerCaseString = [inputString lowercaseString];
  return [lowerCaseString stringByReplacingOccurrencesOfString:@" " withString:@""];
}

@end
