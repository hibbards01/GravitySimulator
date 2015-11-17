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
#import "SimulatorViewController.h"

/****************************
 * GravityViewController
 *  Subclass of NSOpenGLView
 ***************************/
@interface GravityViewController : NSOpenGLView
{
    NSTimer * renderTimer;               // This helps with the drawing
    Simulator * sim;                     // This is to add objects to the simulator
    BOOL dragging;                       // Allow the user to drag an object
    int id;                              // Current clicked object
    SimulatorViewController *controller; // Tell it when to change the edit form
}

- (void) drawRect: (NSRect) bounds;

@end

#endif /* Simulator_h */
