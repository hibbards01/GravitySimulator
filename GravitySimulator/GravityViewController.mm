/****************************************************
 * Program:
 *   GravityViewController.mm
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will define the subclass for NSOpenGLView.
 *
 * Created by Samuel Hibbard on 11/5/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#import <Foundation/Foundation.h>
#import "GravityViewController.h"
#include <OpenGL/gl.h>
#import "SimulatorViewController.h"

// Define the window size for Position
// *** Warning ***
// This points are in accordance to the NSOpenGLView window size.
// If view is changed then these need to be changed as well.
float Position::xMax = 500;
float Position::xMin = -500;
float Position::yMax = 500;
float Position::yMin = -500;

@implementation GravityViewController

/************************************************
 * perpareOpenGL
 *  This will synchronize buffer swaps with
 *      vertical refresh rate.
 ***********************************************/
- (void) perpareOpenGL
{
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
}


/*************************************
 * awakeFromNib
 *  This will initalize variables at 
 *      the beginnning.
 *************************************/
- (void) awakeFromNib
{
    sim = Simulator::getInstance();
    renderTimer = nil;
}

/*************************************
 * addObject
 *  Add an object.
 *************************************/
- (NSNumber *) addToViewObject: (NSDictionary *)data
{
    NSNumber *newID; // Grab the object id or vector id.
    
    // See which object that we should make
    if ([[data objectForKey:@"object"] isEqualToString:@"Planet"])
    {
        // Change the radius to what it should be for the view
        int radius = [[data objectForKey:@"diam"] doubleValue] / sim->getGravity().getMeter();
        
        // Create new object
        Object * object = new Planet(0, 0, 0, 0, [[data objectForKey:@"mass"] doubleValue], radius, 0, [[data objectForKey:@"name"] UTF8String]);
        
        // Now save it to the simulator
        sim->addObject(object);
        
        // Grab the id
        newID = [NSNumber numberWithInt:object->getId()];
    }
    else
    {
        // Create new vector
    }
    
    // Redraw the view
    [self setNeedsDisplay:YES];
    
    return newID;
}

/*************************************
 * editObject
 *  Edit an object.
 *************************************/
- (void) editObject: (NSDictionary *) data id:(NSNumber *)id
{
    
}

/*************************************
 * runTimer
 *  This will start the timer and 
 *      redraw the view every 60 frames
 *      per second. This will be called
 *      when the simulator has been 
 *      started.
 *************************************/
- (void) runTimer
{
    renderTimer = [NSTimer timerWithTimeInterval:0.0167   // 60 frames per second
                                          target:self
                                        selector:@selector(timerFired:)
                                        userInfo:nil
                                         repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSEventTrackingRunLoopMode]; //Ensure timer fires during resize
}

/*************************************
 * stopTimer
 *  What the name implies.
 *************************************/
- (void) stopTimer
{
    [renderTimer invalidate];
    renderTimer = nil;
}

/*************************************
 * timerFired
 *  This will tell the view to redraw
 *      itself.
 *************************************/
- (void) timerFired: (id) sender
{
    [self setNeedsDisplay:YES];
}

/************************************************
 * drawRect
 *  This will draw the shapes to the NSOpenGLView
 ************************************************/
- (void) drawRect: (NSRect) bounds
{
    // Draw the background to black
    glClearColor(0, 0, 0, 0);
    
    // Clear the color bufer in preparation for drawing
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Now draw everything!
    sim->run();
    
    // Draws the content provided by your routine to the view
    glFlush();
}


/*************************************
 * dealloc
 *  Delete the pointer within the 
 *      class Simulator.
 *************************************/
- (void) dealloc
{
    Simulator::deleteInstanc();
}

@end