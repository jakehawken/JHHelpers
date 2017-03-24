//  JHErrorHandler.h
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import <Foundation/Foundation.h>
#import "HDServiceLayerProtocols.h"

/*!
 @class JHErrorHandler
 
 @brief A little helper object for doing handy things with NSError objects. (More features forthcoming.)
 
 @discussion    This class is a helper object intended to make dealing with NSError objects a little easier. (More features forthcoming.)
 
 @helps This helps any object that has to deal with NSError objects.
*/

NS_ASSUME_NONNULL_BEGIN

@interface JHErrorHandler : NSObject

/*!
 @brief Appends a string to the end of the domain of an existing NSError.
 
 @discussion Generates a dupicate of the passed-in NSError, but with the identifier string appended to the previous error's domain.
 
 @param  identifier The identifier string to append.

 @param  inputError The error to be duplicated.
 
 @return NSError The new error.
*/

+ (NSError *)errorByAppendingIdentifier:(NSString *)identifier toError:(NSError *)inputError;

/*!
 @brief Prepends a string to the end of the domain of an existing NSError.
 
 @discussion Generates a dupicate of the passed-in NSError, but with the identifier string prepended to the previous error's domain.
 
 @param  identifier The identifier string to prepend.

 @param  inputError The error to be duplicated.
 
 @return NSError The new error.
*/

+ (NSError *)errorByPrependingIdentifier:(NSString *)identifier toError:(NSError *)inputError;

@end

NS_ASSUME_NONNULL_END