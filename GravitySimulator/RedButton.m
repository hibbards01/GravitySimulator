/****************************************************
 * Program:
 *  RedButton.h
 * Author:
 *   Samuel Hibbard
 * Summary:
 *  Customize the Red button.
 *
 *  Created by Samuel Hibbard on 11/21/15.
 *  Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/
#import "RedButton.h"

@implementation RedButton

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
    _layer.borderColor = CGColorCreateGenericRGB(0.57422f, 0.14063f, 0.12891f, 1.0f);
    _layer.contentsCenter = CGRectMake(0, 0, 1 , 1);
    
    // Set the text color
    NSColor *color = [NSColor whiteColor];
    NSMutableAttributedString *colorTitle = [[NSMutableAttributedString alloc] initWithAttributedString:[self attributedTitle]];
    NSRange titleRange = NSMakeRange(0, [colorTitle length]);
    [colorTitle addAttribute:NSForegroundColorAttributeName value:color range:titleRange];
    [self setAttributedTitle:colorTitle];
    
    if ([_cell isHighlighted])
    {
        _layer.contents = [NSImage imageNamed:@"red_push.png"];
        _layer.borderWidth = 1;
    }
    else
    {
        _layer.contents = [NSImage imageNamed:@"red.png"];
        _layer.borderWidth = 2;
    }
}

@end
