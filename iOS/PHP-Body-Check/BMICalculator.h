//
//  BMICalculator.h
//  PHP-Body-Check
//
//  Created by Ilıa Prokhorov on 01.12.2023.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BMICalculator : NSObject

+ (NSString *)bmiFrom:(NSInteger)height weight:(NSInteger)weight;

@end

NS_ASSUME_NONNULL_END
