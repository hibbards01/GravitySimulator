/****************************************************
 * Program:
 *  CreateViewController.m
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   Define all the functions for the CreateViewController
 *      class.
 *
 * Created by Samuel Hibbard on 11/9/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#import <Foundation/Foundation.h>
#import "SimulatorViewController.h"
#import "CreateViewController.h"

@implementation CreateViewController

/*************************************
 * clickedWhichObj
 *  This is the pop up button. This will
 *      change the other labels, depending
 *      on what was clicked.
 *************************************/
- (IBAction)clickedWhichObj:(id)sender
{
    
}

/*************************************
 * clickedExisting
 *  This will add values to the input
 *      tags.
 *************************************/
- (IBAction)clickedExisting:(id)sender
{
    
}

/*************************************
 * validNumber
 *  This will check if the string is 
 *      a valid number.
 ************************************/
- (BOOL) validNumber: (NSString *) text
{
    return YES;
}

/*************************************
 * clickedCreate
 *  The create button was clicked. This
 *      will check the data and then
 *      save it to the newObj variable.
 *************************************/
- (IBAction)clickedCreate:(id)sender
{
    BOOL valid = NO;
    
    // Grab the data
    NSString *name = self.nameInput.stringValue;
    
    
    // Check the data
    valid = (name.length > 0) ? YES : NO;
    
    self->newObj = [[NSDictionary alloc] init];
    [self.delegate grabData:self->newObj];
    [self dismissViewController:self];
//    valid = ()
}

/*************************************
 * clickedCancel
 *  Dimiss the view.
 *************************************/
- (IBAction)clickedCancel:(id)sender
{
    // Dismiss the sheet
    [self dismissViewController:self];
}

@end