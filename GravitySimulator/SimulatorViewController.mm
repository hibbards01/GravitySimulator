/****************************************************
 * Program:
 *   SimulatorViewController.h
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This is where all the functions for 
 *      SimulatorViewController's class are defined.
 *
 * Created by Samuel Hibbard on 11/6/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#import <Foundation/Foundation.h>
#import "SimulatorViewController.h"
#import "CreateViewController.h"
#include <OpenGL/gl.h>
#import "GravityViewController.h"

@implementation SimulatorViewController

/*************************************
 * viewDidLoad
 ************************************/
- (void) viewDidLoad
{
    // Add the delegation for the GravityViewController
    self.delegate = self.simulator;
}

/*************************************
 * grabData
 *  The data will be sent to this funciton.
 ************************************/
- (void) grabData: (NSDictionary *) data
{
    NSLog(@"HERE!");
    // Send the data to the GravityViewController
    [self.delegate addObject:data];
}

/*************************************
 * clickedRun
 *  This grabs the event of when this
 *      button was clicked.
 *************************************/
- (IBAction)clickedRun: (id)sender
{
    
}

/*************************************
 * clickedReset
 *  Grab the click event for reset.
 *************************************/
- (IBAction)clickedReset: (id)sender
{
    
}

/*************************************
 * clickedClear
 *  Grab the click event for the clear.
 *************************************/
- (IBAction)clickedClear: (id)sender
{
    
}

/*************************************
 * clickedDelete
 *  Grab the click event for the delete.
 *************************************/
- (IBAction)clickedDelete: (id)sender
{
    
}

/*************************************
 * clickedNew
 *  Grab the click event for the new.
 *************************************/
- (IBAction)clickedNew: (id)sender
{
    CreateViewController *view = (CreateViewController *) [self.storyboard instantiateControllerWithIdentifier:@"CreateView"];
    view.delegate = self;
    [self presentViewControllerAsSheet: view];
}

@end