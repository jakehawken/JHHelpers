#import <Cedar/Cedar.h>
#import "JHDataSanitizer.h"

using namespace Cedar::Matchers;
using namespace Cedar::Doubles;

SPEC_BEGIN(JHDataSanitizerSpec)

describe(@"JHDataSanitizer", ^{
  
  describe(@"when comparing two arrays of string", ^{
    __block NSArray<NSString *> *array1;
    __block NSArray<NSString *> *array2;
    __block BOOL arraysMatch;
    
    subjectAction(^{
      arraysMatch = [JHDataSanitizer arrayOfStrings:array1 matchesArrayOfStrings:array2];
    });
    
    context(@"when the arrays match", ^{
      
      beforeEach(^{
        array1 = @[@"fart", @"burp", @"sneeze"];
        array2 = @[@"fart", @"burp", @"sneeze"];
      });
      
      it(@"should return NO", ^{
        arraysMatch should equal(YES);
      });
      
    });
    
    context(@"when the arrays do not match", ^{
      
      beforeEach(^{
        array1 = @[@"fart", @"burp", @"sneeze"];
        array2 = @[@"fart", @"burp", @"banana"];
      });
      
      it(@"should return NO", ^{
        arraysMatch should equal(NO);
      });
      
    });
    
    context(@"when the arrays have matching strings but are not the same memory addresses", ^{
      
      beforeEach(^{
        NSString *item1 = @"fart";
        NSString *item2 = @"burp";
        NSString *item3 = @"sneeze";
        array1 = @[item1, item2, item3];
        array2 = @[item1.copy, item2.copy, item3.copy];
      });
      
      it(@"should return NO", ^{
        arraysMatch should equal(YES);
      });
      
    });

    
  });
});

SPEC_END
