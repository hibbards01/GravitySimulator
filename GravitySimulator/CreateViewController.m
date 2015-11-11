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
 * viewDidLoad
 *  Set some values.
 ************************************/
- (void) viewDidLoad
{
    // Hide the label and button.
    // This is the last question. Only
    // used for the vector object.
    self.objectLabel.hidden = YES;
    self.objBtn.hidden = YES;
}

/*************************************
 * clickedWhichObj
 *  This is the pop up button. This will
 *      change the other labels, depending
 *      on what was clicked.
 *************************************/
- (IBAction)clickedWhichObj:(id)sender
{
    // Grab which object was clicked
    NSString *obj = [[self.whichObjectBtn selectedItem] title];
    
    // Now see what was clicked on
    if ([obj isEqualToString:@"Planet"])
    {
        // Hide the label and button
        self.objectLabel.hidden = YES;
        self.objBtn.hidden = YES;
    }
    else
    {
        // Show the extra label and button
        self.objectLabel.hidden = NO;
        self.objBtn.hidden = NO;
    }
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
    // See if it is a valid number
    NSScanner *scan = [NSScanner scannerWithString:text];
    float val;
    
    return [scan scanFloat: &val] && [scan isAtEnd];
}

/*************************************
 * clickedCreate
 *  The create button was clicked. This
 *      will check the data and then
 *      save it to the newObj variable.
 *************************************/
- (IBAction)clickedCreate:(id)sender
{
    int valid = 0;
    
    // Grab the data
    NSString *obj         = [[self.whichObjectBtn selectedItem] title];
    NSString *name        = self.nameInput.stringValue;
    NSString *diamOrMag   = self.diamOrMagInput.stringValue;
    NSString *massOrAngle = self.massOrAngleInput.stringValue;
    NSString *objName = @"none";
    
    // See if vector was selected
    if ([obj isEqualToString:@"Vector"])
    {
        // If so then grab the objName
        objName = [[self.objBtn selectedItem] title];
    }
    
    // Check the data
    valid = (name.length > 0) ? 0 : 1;
    valid = ([self validNumber:diamOrMag] && valid == 0) ? 0: 2;
    valid = ([self validNumber:massOrAngle] && valid == 0) ? 0 : 3;
    
    
    // Now check the error code
    if (valid == 0)
    {
        // Create the keys
        NSString *diamOrMagKey = ([obj isEqualToString:@"Planet"]) ? @"diam" : @"mag";
        NSString *massOrAngleKey  = ([obj isEqualToString:@"Planet"]) ? @"mass" : @"angle";
        
        // Now save the values and keys into newObj
        NSDictionary *newObj = @{
                                 @"object"    : obj,
                                 @"name"      : name,
                                 diamOrMagKey : [NSNumber numberWithFloat:[diamOrMag doubleValue]],
                                 massOrAngleKey : [NSNumber numberWithFloat:[massOrAngle doubleValue]],
                                 @"objName"   : objName
                                 };
        
        // Send it on it's way
        [self.delegate grabData:newObj];
        
        // Now close the sheet.
        [self dismissViewController:self];
    }
    else
    {
        // Show error
        NSString *error = [NSString stringWithFormat:@"ERROR code number: %d", valid];
        NSLog(@"%@", error);
    }
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