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
float Position::xMax = 375;
float Position::xMin = -375;
float Position::yMax = 375;
float Position::yMin = -375;

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
    dragging = NO;
    id = -1;
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
        int radius = [[data objectForKey:@"diam"] doubleValue] / sim->getMeter();
        
        // Create new object
        Object * object = new Planet(0, 0, 0, 0, [[data objectForKey:@"mass"] doubleValue], radius, 0, [[data objectForKey:@"name"] UTF8String]);
        
        // Now save it to the simulator
        sim->addObject(object, id);
        
        // Grab the id
        id = object->getId();
        newID = [NSNumber numberWithInt: id];
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
 * mouseDown
 *  This will check if the user can
 *      can drag the element.
 ************************************/
- (void) mouseDown: (NSEvent *) event
{
    // See if this event is over an object
    // Grab where the mouse was clicked on.
    NSPoint event_location = event.locationInWindow;
    NSPoint location = [self convertPoint:event_location fromView:nil];
    float x = [self changeX: location.x];
    float y = [self changeY: location.y];
    
    // Now see if an object was clicked on
    if (sim->clickedObject(x, y, id))
    {
        // If so then we need to allow dragging.
        dragging = YES;
    }
    else
    {
        dragging = NO;
    }
    
    [self setNeedsDisplay:YES];
}

/*************************************
 * mouseDragged
 *  This will then move the object
 *      with the mouse.
 ************************************/
- (void) mouseDragged: (NSEvent *) event
{
    // Make sure an object was clicked on
    if (dragging)
    {
        // Now move the object
        // Grab the points
        NSPoint event_location = event.locationInWindow;
        NSPoint location = [self convertPoint:event_location fromView:nil];
        float x = [self changeX: location.x];
        float y = [self changeY: location.y];
        
        // Move the object to that point
        sim->moveObject(x, y, id);
        
        // Now redraw the picture
        [self setNeedsDisplay:YES];
    }
}

/*************************************
 * chagneX
 *  This will change the x coordinate
 *      to the coordinate in the OpenGl
 ************************************/
- (float) changeX: (float) x
{
    return x - 375;
}

/*************************************
 * chagneY
 *  This will change the y coordinate
 *      to the coordinate in the OpenGl
 ************************************/
- (float) changeY: (float) y
{
    return y - 375;
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
    sim->run(dragging);
    
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
    Simulator::deleteInstance();
}

@end