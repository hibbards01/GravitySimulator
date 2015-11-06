/****************************************************
 * Program:
 *   SimulatorView.mm
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will define the subclass for NSOpenGLView.
 *
 * Created by Samuel Hibbard on 11/5/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#import <Foundation/Foundation.h>
#import "SimulatorView.h"
#import "sim.h"

// Define the window size for Position
float Position::xMax = 500;
float Position::xMin = -500;
float Position::yMax = 343;
float Position::yMin = -343;

@implementation SimulatorView

/************************************************
 * drawRect
 *  This will draw the shapes to the NSOpenGLView
 ************************************************/
- (void) drawRect: (NSRect) bounds
{
    
}

@end