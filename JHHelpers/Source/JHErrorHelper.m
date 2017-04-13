//  JHErrorHelper.m
//  Created by Jacob Hawken on 7/20/16.
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import "JHErrorHelper.h"

@implementation JHErrorHelper

//NOTE: Most of these error codes and strings are directly related to the errors that Firebase returns.

+ (NSError *)errorByAppendingIdentifier:(NSString *)identifier toError:(NSError *)inputError
{
  if (!identifier && !inputError)
  {
    return nil;
  }
  if (!identifier && inputError)
  {
    return inputError;
  }
  
  NSString *newDomain = [NSString stringWithFormat:@"%@ --- IDENTIFIER: %@", inputError.domain, identifier];
  
  return [NSError errorWithDomain:newDomain code:inputError.code userInfo:inputError.userInfo];
}

+ (NSError *)errorByPrependingIdentifier:(NSString *)identifier toError:(NSError *)inputError
{
  if (!identifier && !inputError)
  {
    return nil;
  }
  if (!identifier && inputError)
  {
    return inputError;
  }
  
  NSString *newDomain = [NSString stringWithFormat:@"%@ --- %@", identifier, inputError.domain];
  
  return [NSError errorWithDomain:newDomain code:inputError.code userInfo:inputError.userInfo];
}

@end
