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
    planetIDs = [[NSMutableArray alloc] init];
    planetNames = [[NSMutableArray alloc] init];
    vectorIDs = [[NSMutableArray alloc] init];
    vectorNames = [[NSMutableArray alloc] init];
    
    // Customize the button
    [_run setFont:[NSFont fontWithName:@"Arial" size:15]];
    _run.frame = CGRectMake(_run.frame.origin.x, _run.frame.origin.y, _run.frame.size.width, 44.0f);
    
    // Hide one label and button
    _formLabel3.hidden = YES;
    _formSelectBtn.hidden = YES;
    
    // Send self to GravityViewControlller
    [self.delegate sendSelf:self];
    
    // Add a moon and earth
    [planetIDs addObject:[NSNumber numberWithInt:1]];
    [planetIDs addObject:[NSNumber numberWithInt:3]];
    
    [planetNames addObject:@"Moon"];
    [planetNames addObject:@"Earth"];
    
    [vectorIDs addObject:[NSNumber numberWithInt:2]];
    [vectorNames addObject:@"Moon's Velocity"];
    
    // Populate the NSPopUpButton
    [self populateButton];
}

/*************************************
 * populateButton
 *  This will populate the NSPopUpButton.
 ************************************/
- (void) populateButton
{
    // Clear the menu
    [self.editItem removeAllItems];
    
    // Add an empty cell
    NSMenuItem *empty = [[NSMenuItem alloc] init];
    [empty setTitle:@""];
    [empty setTag:-1];
    [self.editItem.menu addItem:empty];
    
    // Loop through all the planets
    for (int i = 0; i < [planetNames count]; ++i)
    {
        // Create a new cell
        NSMenuItem *cell = [[NSMenuItem alloc] init];
        
        // Now add the title and tag
        [cell setTitle:[planetNames objectAtIndex:i]];
        [cell setTag:[[planetIDs objectAtIndex:i] integerValue]];
        
        // Now add it
        [self.editItem.menu addItem:cell];
    }
    
    // Now the velocities
    for (int i = 0; i < [vectorNames count]; ++i)
    {
        // Create a new cell
        NSMenuItem *cell = [[NSMenuItem alloc] init];
        
        // Now add the title and tag
        [cell setTitle:[vectorNames objectAtIndex:i]];
        [cell setTag:[[vectorIDs objectAtIndex:i] integerValue]];
        
        // Now add it
        [self.editItem.menu addItem:cell];
    }
}

/*************************************
 * clickedEditBtn
 *  This will change the edit form
 *      if they clicked on a different
 *      object.
 ************************************/
- (IBAction)clickedEditBtn:(id)sender
{
    // Grab the value
    int objId = (int)[[self.editItem selectedItem] tag];
    
    // Now grab the data from the GravityViewController
    NSDictionary *data = [self.delegate selectObject:objId];
    
    // Update the form
    [self addValuesToEditForm:data selectedID:objId];
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
        [planetIDs addObject:currentID];
        [planetNames addObject:[data objectForKey:@"name"]];
    }
    else
    {
        // Add to the list of vectors
        [vectorIDs addObject:currentID];
        [vectorNames addObject:[data objectForKey:@"name"]];
    }
    
    // Now change the edit form
    [self addValuesToEditForm: data selectedID:[currentID intValue]];
    
    // Repopulate the nspopbutton
    [self populateButton];
}

/*************************************
 * updateEditItem
 *  This will update it after a run.
 *************************************/
- (void) updateEditItem: (NSMutableArray *) ids vectorNames: (NSMutableArray *) names
{
    vectorIDs = ids;
    vectorNames = names;
    
    [self populateButton];
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
        [[_formLabel1 cell] setTitle:@"Speed"];
        [[_formLabel2 cell] setTitle:@"Angle (°)"];
        
        // Put the values into the input fields
        [[_formInputTextField1 cell] setFloatValue: [[data objectForKey:@"mag"] floatValue]];
        [[_formInputTextField2 cell] setIntValue: [[data objectForKey:@"angle"] intValue]];
        
        // Delete what is currently in the formSelectBtn
        [_formSelectBtn removeAllItems];
        
        // Add the object name to the formSelectBtn
        for (int i = 0; i < [planetNames count]; ++i)
        {
            // Add to the btn
            [_formSelectBtn addItemWithTitle: [planetNames objectAtIndex: i]];
            
            // See if it is the one that has to be selected
            if ([[planetIDs objectAtIndex: i] intValue] == [[data objectForKey:@"objName"] intValue])
            {
                // Now select the current object
                [_formSelectBtn selectItemAtIndex: i];
            }
        }
        
        // Also make them not hidden
        _formLabel3.hidden = NO;
        _formSelectBtn.hidden = NO;
    }
    
    // Set the id that is selected
    currentlySelected = id;
    
    // Select the correct thing in the editItem button
    [self.editItem selectItemWithTag:currentlySelected];
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
    
    for (int i = 0; i < [planetNames count]; ++i)
    {
        // Find the item
        if ([[planetNames objectAtIndex:i] isEqualToString: [[_formSelectBtn selectedItem] title]])
        {
            // Grab the id!
            newObject = [[planetIDs objectAtIndex:i] intValue];
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
        _editItem.enabled = NO;
        
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
        _editItem.enabled = YES;
        
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
    // See which button clicked this
    BOOL planet = true;
    
    if ([[sender title] isEqualToString:@"Add Velocity"])
    {
        planet = false;
    }
    
    // Grab the controller
    CreateViewController *view = (CreateViewController *) [self.storyboard instantiateControllerWithIdentifier:@"CreateView"];
    
    // Delegate itself to the controller
    view.delegate = self;
    
    // Present the controller
    [self presentViewControllerAsSheet: view];
    
    // Send it some data.
    [view sendObjects: planetIDs names: planetNames whichObject:planet];
}

@end