//  JHMapper.m
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import "JHMapper.h"


@implementation JHMapper

#pragma mark - MAP

+ (NSArray *)mapFilter:(NSArray *)array withBlock:(id(^)(id object))evaluationBlock
{
  NSMutableArray *mappedArray = [NSMutableArray array];
  
  for (id item in array)
  {
    id itemToAdd = evaluationBlock(item);
    if (itemToAdd)
    {
      [mappedArray addObject:itemToAdd];
    }
  }
  
  return mappedArray.copy;
}

+ (NSDictionary *)inflateArray:(NSArray *)array toDictionaryWithKeyBlock:(NSString *(^)(id object))keyBlock
{
  NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
  
  for (id item in array)
  {
    NSString *key = keyBlock(item);
    [dictionary setValue:item forKey:key];
  }
  
  return dictionary;
}

+ (NSDictionary<NSString *, id> *)mapValuesToNewDictionaryFrom:(NSDictionary<NSString *, id> *)dictionary withKeyBlock:(NSString *(^)(NSString *originalKey, id object))keyBlock valueBlock:(id(^)(id object))valueBlock
{
  NSMutableDictionary *newDictionary = [NSMutableDictionary dictionary];
  
  for (id key in dictionary.allKeys)
  {
    id value = dictionary[key];
    id newValue = valueBlock(value);
    id newKey = keyBlock(key,value);
    if (newKey && newValue)
    {
      [newDictionary setValue:newValue forKey:newKey];
    }
  }
  
  return newDictionary;
}

#pragma mark - DO/MUTATE

+ (void)forEachIn:(NSArray *)array perform:(void(^)(id object))block
{
  for (id object in array)
  {
    block(object);
  }
}

#pragma mark - AUTO-MAP

+ (NSDictionary<NSString *, id> *)mapToDictionaryWithValueDescriptionsAsKeys:(NSArray *)array
{
  NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
  
  for (NSObject *item in array)
  {
    [dictionary setObject:item forKey:item.description];
  }
  
  return dictionary;
}

+ (NSDictionary<NSString *, id> *)mapToDictionaryWithNumberedKeysFrom:(NSArray *)array
{
  NSMutableDictionary *dictionary = [NSMutableDictionary dictionary];
  
  for (int i = 0; i < array.count; i++)
  {
    NSString *keyString = [NSString stringWithFormat:@"%d", i];
    [dictionary setObject:array[i] forKey:keyString];
  }
  
  return dictionary;
}

#pragma mark - Dictionaries helpers

+ (NSArray *)valuesFromDictionarySortedByKeys:(NSDictionary<NSString *, id> *)dictionary
{
  NSArray *sortedKeys = [self sortedKeysFromDictionary:dictionary];
  
  NSMutableArray *arrayFromDict = [NSMutableArray array];
  
  for (int i = 0; i < sortedKeys.count; i++)
  {
    NSString *keyString = sortedKeys[i];
    [arrayFromDict addObject:[dictionary objectForKey:keyString]];
  }
  
  return arrayFromDict;
}

+ (NSArray<NSString *> *)sortedKeysFromDictionary:(NSDictionary<NSString *, id> *)dictionary
{
  NSArray *allKeys = [dictionary allKeys];
  return [allKeys sortedArrayUsingSelector:@selector(localizedStandardCompare:)];
}

@end
