/****************************************************
 * Program:
 *  GrayButton.m
 * Author:
 *   Samuel Hibbard
 * Summary:
 *  Customize the Gray button.
 *
 *  Created by Samuel Hibbard on 11/21/15.
 *  Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/
#import "GrayButton.h"

@implementation GrayButton

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
    _layer.borderColor = CGColorCreateGenericRGB(0.65234f, 0.65234f, 0.65234f, 1.0f);
    _layer.contentsCenter = CGRectMake(0, 0, 1 , 1);
    
    // Set the text color
    NSColor *color = [NSColor blackColor];
    NSMutableAttributedString *colorTitle = [[NSMutableAttributedString alloc] initWithAttributedString:[self attributedTitle]];
    NSRange titleRange = NSMakeRange(0, [colorTitle length]);
    [colorTitle addAttribute:NSForegroundColorAttributeName value:color range:titleRange];
    [self setAttributedTitle:colorTitle];
    
    if ([_cell isHighlighted])
    {
        _layer.contents = [NSImage imageNamed:@"gray_push.png"];
        _layer.borderWidth = 1;
    }
    else
    {
        _layer.contents = [NSImage imageNamed:@"gray.png"];
        _layer.borderWidth = 2;
    }
}

@end
