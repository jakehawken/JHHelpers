//  JHDisposable.m
//  Created by Jacob Hawken on 10/6/16.
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import "JHDisposable.h"
#import <FirebaseDatabase/FIRDatabaseReference.h>


@implementation JHDisposable

- (instancetype)init
{
  [self doesNotRecognizeSelector:@selector(init)];
  return nil;
}

- (instancetype)initWithDatabaseReference:(FIRDatabaseReference *)reference
{
  self = [super init];
  if (self)
  {
    _reference = reference;
  }
  return self;
}

+ (instancetype)instanceWithDatabaseReference:(FIRDatabaseReference *)reference
{
  return [[JHDisposable alloc] initWithDatabaseReference:reference];
}

- (void)cancelContinuousFetch
{
  [self.reference removeAllObservers];
}

@end
