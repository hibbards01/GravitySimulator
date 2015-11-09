/****************************************************
 * Program:
 *   SimulatorView.h
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
 * Simulator
 *  Subclass of NSOpenGLView
 ***************************/
@interface SimulatorView : NSOpenGLView
{
    NSTimer * renderTimer;
    Simulator * sim;
}

- (void) drawRect: (NSRect) bounds;

- (void) addPlanet: (int) objID name:(NSString *) name size:(float) size mass:(float) mass;

- (void) addVector: (int) vectorID name:(NSString *) name magnitude:(float) mag angle:(float) angle object:(int) objID;

@end

#endif /* Simulator_h */
