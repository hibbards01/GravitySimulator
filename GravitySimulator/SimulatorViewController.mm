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
#import "RedButton.h"
#import "GreenButton.h"

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
    
    // Change the button colors
//    NSBackgroundStyle *style = [NSBackgroundStyle [NSColor redColor];
//    [[_run cell] setBackgroundStyle:;]
    
    // Add a moon and earth
    NSNumber *moon = [NSNumber numberWithInt:1];
    NSNumber *earth = [NSNumber numberWithInt:3];
    [ids addObject:moon];
    [ids addObject:earth];
    
    [names addObject:@"Moon"];
    [names addObject:@"Earth"];
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
        [[_formInputTextField1 cell] setDoubleValue: [[data objectForKey:@"radius"] doubleValue]];
        [[_formInputTextField2 cell] setDoubleValue: [[data objectForKey:@"mass"] doubleValue]];
        
        // Make the last question disappear
        _formLabel3.hidden = YES;
        _formSelectBtn.hidden = YES;
    }
    else
    {
        // Change the form lables
        [[_formLabel1 cell] setTitle:@"Magnitude (m/s)"];
        [[_formLabel2 cell] setTitle:@"Angle (°)"];
        
        // Put the values into the input fields
        [[_formInputTextField1 cell] setFloatValue: [[data objectForKey:@"mag"] floatValue]];
        [[_formInputTextField2 cell] setIntValue: [[data objectForKey:@"angle"] intValue]];
        
        // Delete what is currently in the formSelectBtn
        [_formSelectBtn removeAllItems];
        
        // Add the object name to the formSelectBtn
        for (int i = 0; i < [names count]; ++i)
        {
            // Add to the btn
            [_formSelectBtn addItemWithTitle: [names objectAtIndex: i]];
            
            // See if it is the one that has to be selected
            if ([[ids objectAtIndex: i] intValue] == [[data objectForKey:@"objName"] intValue])
            {
                // Now select the current object
                [_formSelectBtn selectItemAtIndex: i];
            }
        }
        
        // Also make them not hidden
        _formLabel3.hidden = NO;
        _formSelectBtn.hidden = NO;
    }
    
    // Change the edit form label
    [[_editTitle cell] setTitle: [data objectForKey:@"name"]];
    
    // Set the id that is selected
    currentlySelected = id;
}

/*************************************
 * input1Action
 *  This will grab the <enter> event
 *      and when the input is out of
 *      focus.
 *************************************/
- (IBAction)input1Action:(id)sender
{
    NSNumber *newNumber;
    
    // See which label this is
    // Grab the value
    if ([_formLabel1.cell.stringValue isEqualToString:@"Radius (m)"])
    {
        newNumber = [NSNumber numberWithDouble: _formInputTextField1.doubleValue];
    }
    else
    {
        newNumber = [NSNumber numberWithFloat: _formInputTextField1.floatValue];
    }
    
    // Now tell the GravityController of the change
    [_delegate editObject:currentlySelected number:newNumber edit:@"radiusOrMag"];
}

/*************************************
 * input2Action
 *  Same actions as input1Action.
 *************************************/
- (IBAction)input2Action:(id)sender
{
    NSNumber *newNumber;
    
    // See which label it is
    // Grab the values
    if ([_formLabel2.cell.stringValue isEqualToString:@"Mass (kg)"])
    {
        newNumber = [NSNumber numberWithDouble: _formInputTextField2.doubleValue];
    }
    else
    {
        newNumber = [NSNumber numberWithInt: _formInputTextField2.intValue];
    }
    
    // Now tell the GravityController of the change
    [_delegate editObject:currentlySelected number:newNumber edit:@"massOrAngle"];
}

/*************************************
 * selectBtnAction
 *  This is when the user selects 
 *      a different option.
 *************************************/
- (IBAction)selectBtnAction:(id)sender
{
    // Find the change
    int newObject = -1;
    
    for (int i = 0; i < [names count]; ++i)
    {
        // Find the item
        if ([[names objectAtIndex:i] isEqualToString: [[_formSelectBtn selectedItem] title]])
        {
            // Grab the id!
            newObject = [[ids objectAtIndex:i] intValue];
        }
    }
    
    // Now tell the Gravity Simulator
    [_delegate changeVector:currentlySelected object:newObject];
}

/*************************************
 * clickedRun
 *  This grabs the event of when this
 *      button was clicked.
 *************************************/
- (IBAction)clickedRun: (id)sender
{
    // Show the arrows?
    BOOL enable = YES;
    
    // See what label it is
    if ([[sender title] isEqualToString:@"Run"])
    {
        // Disable all buttons and textfields
        _formInputTextField1.enabled = NO;
        _formInputTextField2.enabled = NO;
        _deleteBtn.enabled = NO;
        _clear.enabled = NO;
        _reset.enabled = NO;
        _formSelectBtn.enabled = NO;
        
        // Hide the run button
        _run.hidden = YES;
        enable = NO;
        
        // Show the red color
        _stop.hidden = NO;
    }
    else
    {
        // Enable all buttons and textfields
        _formInputTextField1.enabled = YES;
        _formInputTextField2.enabled = YES;
        _deleteBtn.enabled = YES;
        _clear.enabled = YES;
        _reset.enabled = YES;
        _formSelectBtn.enabled = YES;
        
        // Hide the stop button
        _stop.hidden = YES;
        
        // Show the red button
        _run.hidden = NO;
    }
    
    [_delegate runSimulation:enable];
}

/*************************************
 * clickedReset
 *  Grab the click event for reset.
 *************************************/
- (IBAction)clickedReset: (id)sender
{
    [_delegate resetObjects];
}

/*************************************
 * clickedClear
 *  Grab the click event for the clear.
 *************************************/
- (IBAction)clickedClear: (id)sender
{
    // Delete all objects
    [_delegate deleteObject:0 type:@"all"];
    
    // Remove text
    [self removeText];
}

/*************************************
 * clickedDelete
 *  Grab the click event for the delete.
 *************************************/
- (IBAction)clickedDelete: (id)sender
{
    // Delete the one object
    [_delegate deleteObject:currentlySelected type:@"one"];
    
    // Remove text
    [self removeText];
}

/*************************************
 * removeText
 *  Remove the text.
 ************************************/
- (void) removeText
{
    [[_editTitle cell] setTitle:@""];
    [[_formLabel1 cell] setTitle:@"Radius (m)"];
    [[_formLabel2 cell] setTitle:@"Mass (kg)"];
    [[_formInputTextField1 cell] setTitle:@""];
    [[_formInputTextField2 cell] setTitle:@""];
    _formSelectBtn.hidden = YES;
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