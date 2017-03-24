//  JHDisposable.h
//  Created by Jacob Hawken on 10/6/16.
//  Copyright © 2016 Jake Hawken. All rights reserved.

#import <Foundation/Foundation.h>
@class FIRDatabaseReference;

/*!
 @class JHDisposable
 
 @brief An Rx-style disposable for ending continuous fetch calls to Firebase.
 
 @discussion    This class is a helper object which allows an object outside of an app's Firebase service layer to cancel an open-socket continuous fetch from Firebase without having to leak any encapsulation or expose any of Firebase to that object. Use this object as the immediate return type on methods that trigger continuous fetching. It goes without saying that this class assumes the Firebase SDK has been imported.
 
 @helps This helps both the service layer that creates it (to keep it from leaking encapsulation), as well as the object that receives it, to abstract cancellation logic away from it.
*/

@interface JHDisposable: NSObject

/*!
 @brief Creates an instance of JHDisposable.
 
 @discussion Constructor for the JHDisposable object. Takes in a FIRDatabaseReference object and returns the disposable. It is recommended that the reference to this object be nilled out on error, as the continuous fetch is automatically cancelled by the Firebase SDK anyway on error.
 
 Example usage:
 
 @code
 self.disposable = [someFirebaseService observeUser:@"someUserID" withSuccessBlock:^(User *user) {
    self.user = user;
    [self.delegate refreshData];
  } errorBlock:^(NSError * _Nullable error) {
    [self.delegate encounteredError:error];
    self.disposable = nil;
  }];
 @endcode
 
 @param  reference The FIRDatabaseReference object for that particular continuous fetch.
 
 @return JHDisposable The helper object.
*/

+ (instancetype)instanceWithDatabaseReference:(FIRDatabaseReference *)reference;

/*!
 @brief Cancels the fetch.
 @discussion This will stop the observation of that FIRDatabaseReference and trigger the closing of that socket.
*/

- (void)cancelContinuousFetch;

@end
