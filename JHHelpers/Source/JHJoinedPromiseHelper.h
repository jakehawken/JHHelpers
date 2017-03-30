//  JHJoinedPromiseHelper.h
//  Copyright © 2017 Jake Hawken. All rights reserved.

#import <Foundation/Foundation.h>
#import <KSDeferred/KSPromise.h>

/*!
 @class JHJoinedPromiseHelper
 
 @brief A helper object for chaining together KSPromise objects of the same value type.
 
 @discussion    Expanding on the "when" option in KSPromise for creating a master promise from multiple child promises, this object goes a step further to collect all the success values for the child promises that succeed, and a string identifier for each of the promises that fails, and holds them all within one object. This allows your app to act on all the successful asynch promises, without having to worry about the failures, and allows you to handle the failures separately, rather than in the same block of code.
 
 @helps This KSPromise and any object that needs to aggregate promises of similar types.
*/

NS_ASSUME_NONNULL_BEGIN

@interface JHJoinedPromiseHelper<SeedType, PromiseValue> : NSObject

/*!
 @brief Creates an instance of JHJoinedPromiseHelper.
 
 @discussion For each item in the seed array, the promise block is called. The joined promise is exposed synchronously as the <i>promise</i> property. The <i>successValues</i> and <i>failureIDs</i> properties are populated asynchronously when <i>promise</i> returns, so they will be empty at initialization.
 
 This class supports generics, which will allow the types in the <i>seedArray</i> and the <i>successValues</i>, respectively, to be specified.
 
 Example:
 
 @code
 [JHJoinedPromiseHelper<NSString *, ModelObject *> instanceWithSeedArray:self.modelIDs promiseBlock:^KSPromise<ModelObject *> *(NSString *modelID) {
    return [modelProvider promiseForModelWithID: modelID];
 } failureIndentifierBlock:^NSString *(NSString *modelID) {
    return modelID;
 }];
 @endcode
 
 @param  seedArray The input array, made up of items of type <SeedType>.
 
 @param  promiseBlock A block which will generate a KSPromise, given a <SeedType> object. Called once for each item in the <i>seedArray</i>. Values from the successfully fulfilled promises populate the successValues array.
 
 @param  failureIDBlock A block which will generate an NSString identifier, given a <SeedType> object. Called once for each of the underlying child promises that fails. Populates the <i>failureIDs</i> array. If the string returned in this block evaluates to nil, an empty string will be added to the <i>failureIDs</i> array for this item.  
 
 @return JHJoinedPromiseHelper The helper object.
*/

+ (instancetype)instanceWithSeedArray:(NSArray<SeedType> *)seedArray promiseBlock:(KSPromise<PromiseValue> *(^)(SeedType object))promiseBlock failureIndentifierBlock:(NSString *(^)(SeedType object, NSError *error))failureIDBlock;

#pragma mark - INTERFACE

/*! @brief The joined/master promise generated at initialization. When it finally returns, the successValues and failureIDs properties will be populated.*/
@property (nonatomic, readonly) KSPromise *promise;

/*! @brief Once the promise returns, this array will be populated with the values of each of the successfully fulfilled child promises.*/
@property (nonatomic, readonly) NSArray<PromiseValue> * _Nullable successValues;

/*! @brief Once the promise returns, this array will be populated with a string identifier for each of the failed child promises.*/
@property (nonatomic, readonly) NSArray<NSString *> * _Nullable failureIDs;

/*! @brief This is a convenience property for checking if any of the child promises failed. Will not be meaningful until <i>promise</i> has returned.*/
@property (nonatomic, readonly) BOOL hasFailures;

@end

NS_ASSUME_NONNULL_END
