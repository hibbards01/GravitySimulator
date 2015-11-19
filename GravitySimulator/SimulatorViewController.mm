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
    
    // This will save all the ids
    ids = [[NSMutableArray alloc] init];
    names = [[NSMutableArray alloc] init];
    
    // Customize the button
    [_run setFont:[NSFont fontWithName:@"Arial" size:15]];
    _run.frame = CGRectMake(_run.frame.origin.x, _run.frame.origin.y, _run.frame.size.width, 44.0f);
    
    // Hide one label and button
    _formLabel3.hidden = YES;
    _formSelectBtn.hidden = YES;
    
    // Send self to GravityViewControlller
    [self.delegate sendSelf:self];
}

/*************************************
 * grabData
 *  The data will be sent to this funciton.
 ************************************/
- (void) grabData: (NSDictionary *) data
{
    // Send the data to the GravityViewController and grab the id
    // Save the name
    NSNumber *currentID = [self.delegate addToViewObject:data];

    // Only add to the list if it is a planet
    if ([[data objectForKey:@"object"] isEqualToString:@"Planet"])
    {
        [ids addObject:currentID];
        [names addObject:[data objectForKey:@"name"]];
    }
    
    // Now change the edit form
    [self addValuesToEditForm: data selectedID:[currentID intValue]];
}

/*************************************
 * addValuesToEditForm
 *  This will add the values to the form.
 ************************************/
- (void) addValuesToEditForm: (NSDictionary *) data selectedID: (int) id
{
    // Change the inputs and labels to the data
    if ([[data objectForKey:@"object"] isEqualToString:@"Planet"])
    {
        // Change the form labels
        [[_formLabel1 cell] setTitle:@"Radius (m)"];
        [[_formLabel2 cell] setTitle:@"Mass (kg)"];
        
        // Now the input fields
        [[_formInputTextField1 cell] setTitle: [data objectForKey:@"radius"]];
        [[_formInputTextField2 cell] setTitle: [data objectForKey:@"mass"]];
        
        // Make the last question disappear
        _formLabel3.hidden = YES;
        _formSelectBtn.hidden = YES;
    }
    else
    {
        
    }
    
    // Change the edit form label
    [[_editTitle cell] setTitle: [data objectForKey:@"name"]];
    
    // Set the id that is selected
    currentlySelected = id;
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
    // Grab the controller
    CreateViewController *view = (CreateViewController *) [self.storyboard instantiateControllerWithIdentifier:@"CreateView"];
    
    // Delegate itself to the controller
    view.delegate = self;
    
    // Present the controller
    [self presentViewControllerAsSheet: view];
    
    // Send it some data.
    [view sendObjects: ids names: names];
}

@end