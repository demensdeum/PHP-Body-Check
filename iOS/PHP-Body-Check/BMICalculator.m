//
//  BMICalculator.m
//  PHP-Body-Check
//
//  Created by Ilıa Prokhorov on 01.12.2023.
//

#import "BMICalculator.h"

#include "main.h"

@implementation BMICalculator

+ (NSString *)bmiFrom:(NSInteger)height weight:(NSInteger)weight
{
    const char *result = bodyStatus((int)height, (int)weight);
    NSString *resultString = [[NSString alloc] initWithCString:result encoding:NSUTF8StringEncoding];
    return resultString;
}

@end
