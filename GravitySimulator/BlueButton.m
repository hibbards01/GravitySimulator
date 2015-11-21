/****************************************************
 * Program:
 *  BlueButton.m
 * Author:
 *   Samuel Hibbard
 * Summary:
 *  Customize the Blue button.
 *
 *  Created by Samuel Hibbard on 11/21/15.
 *  Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/
#import "BlueButton.h"

@implementation BlueButton

/**************************
 * wantsUpdateLayer
 *  Update button if pressed.
 *************************/
- (BOOL)wantsUpdateLayer
{
    return YES;
}

/**************************
 * updateLayer
 *  Update the button if
 *      pressed or not.
 *************************/
- (void)updateLayer
{
    // Customize it
    _layer.cornerRadius = 7;
    _layer.borderColor = CGColorCreateGenericRGB(0.20313f, 0.48047f, 0.71875f, 1.0f);
    _layer.contentsCenter = CGRectMake(0, 0, 1 , 1);
    
    // Set the text color
    NSColor *color = [NSColor whiteColor];
    NSMutableAttributedString *colorTitle = [[NSMutableAttributedString alloc] initWithAttributedString:[self attributedTitle]];
    NSRange titleRange = NSMakeRange(0, [colorTitle length]);
    [colorTitle addAttribute:NSForegroundColorAttributeName value:color range:titleRange];
    [self setAttributedTitle:colorTitle];
    
    if ([_cell isHighlighted])
    {
        _layer.contents = [NSImage imageNamed:@"blue_push.png"];
        _layer.borderWidth = 1;
    }
    else
    {
        _layer.contents = [NSImage imageNamed:@"blue.png"];
        _layer.borderWidth = 2;
    }
}

@end
