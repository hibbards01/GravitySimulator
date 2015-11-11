/****************************************************
 * Program:
 *   GravityViewController.h
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will be the controller for the NSOpenGLView.
 *
 * Created by Samuel Hibbard on 11/5/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#ifndef Simulator_h
#define Simulator_h

#import <Cocoa/Cocoa.h>
#import "sim.h"

/****************************
 * GravityViewController
 *  Subclass of NSOpenGLView
 ***************************/
@interface GravityViewController : NSOpenGLView
{
    NSTimer * renderTimer; // This helps with the drawing
    Simulator * sim;       // This is to add objects to the simulator
    NSMutableArray *ids;   // These are the ids of the objects.
}

- (void) drawRect: (NSRect) bounds;

@end

#endif /* Simulator_h */
