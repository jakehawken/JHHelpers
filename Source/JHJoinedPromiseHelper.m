//  JHJoinedPromiseHelper.m
//  Created by Jacob Hawken on 1/9/17.
//  Copyright © 2017 Jake Hawken. All rights reserved.

#import "JHJoinedPromiseHelper.h"

#import "HDMapper.h"
#import "KSDeferred.h"


@interface JHJoinedPromiseHelper()
@property (nonatomic, strong) NSArray<KSPromise *> *childPromises;
@end


@implementation JHJoinedPromiseHelper

#pragma mark - initialization

- (instancetype)init
{
  [self doesNotRecognizeSelector:@selector(init)];
  return nil;
}

- (instancetype)initInstanceWithSeedArray:(NSArray *)seedArray promiseBlock:(KSPromise *(^)(id))promiseBlock failureIndentifierBlock:(NSString *(^)(id object, NSError *error))failureIDBlock
{
  self = [super init];
  if (self)
  {
    NSMutableArray<KSPromise *> *promises = [NSMutableArray array];
    NSMutableArray<NSString *> *failures = [NSMutableArray array];
    
    for (id item in seedArray)
    {
      KSPromise *promise = promiseBlock(item);
      [promise finally:^{
        if (promise.rejected)
        {
          NSString *failureID = failureIDBlock(item, promise.error);
          if (failureID)
          {
            [failures addObject:failureID];
          }
          else
          {
            [failures addObject:@""];
          }
        }
      }];
      [promises addObject:promise];
    }
    
    _promise = [KSPromise when:promises];
    _childPromises = promises;
    _failureIDs = failures;
  }
  return self;
}

+ (instancetype)instanceWithSeedArray:(NSArray *)seedArray promiseBlock:(KSPromise<id> *(^)(id))promiseBlock failureIndentifierBlock:(NSString *(^)(id object, NSError *error))failureIDBlock
{
  return [[JHJoinedPromiseHelper alloc] initInstanceWithSeedArray:seedArray promiseBlock:promiseBlock failureIndentifierBlock:failureIDBlock];
}

#pragma mark - accessors

- (NSArray *)successValues
{
  return [HDMapper<KSPromise *, id> filter:self.childPromises withEvaluationBlock:^id(KSPromise *promise) {
    return promise.value;
  }];
}

- (BOOL)hasFailures
{
  return self.failureIDs.count > 0;
}

@end
