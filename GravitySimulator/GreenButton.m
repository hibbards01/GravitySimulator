//
//  GreenButton.m
//  GravitySimulator
//
//  Created by Samuel Hibbard on 11/20/15.
//  Copyright © 2015 samIAm. All rights reserved.
//

#import "GreenButton.h"

@implementation GreenButton

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
//    [self setBezelStyle:NSRoundedBezelStyle];
    _layer.cornerRadius = 7;
    _layer.borderColor = CGColorCreateGenericRGB(0.27734f, 0.6289f, 0.27734f, 1.0f);
    _layer.contentsCenter = CGRectMake(0, 0, 1, 1);
    
    // Set the text color
    NSColor *color = [NSColor whiteColor];
    NSMutableAttributedString *colorTitle = [[NSMutableAttributedString alloc] initWithAttributedString:[self attributedTitle]];
    NSRange titleRange = NSMakeRange(0, [colorTitle length]);
    [colorTitle addAttribute:NSForegroundColorAttributeName value:color range:titleRange];
    [self setAttributedTitle:colorTitle];
    
    if ([_cell isHighlighted])
    {
        _layer.contents = [NSImage imageNamed:@"green_push.png"];
        _layer.borderWidth = 1;
    }
    else
    {
        _layer.contents = [NSImage imageNamed:@"green.png"];
        _layer.borderWidth = 2;
    }
}

//- (void)drawRect:(NSRect)dirtyRect {
//    [super drawRect:dirtyRect];
//    
//    // Drawing code here.
//}

@end
