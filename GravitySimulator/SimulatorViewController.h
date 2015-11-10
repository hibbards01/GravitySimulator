/****************************************************
 * Program:
 *   SimulatorViewController.h
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will be the main controller for the main 
 *      view of the application. It is the one that
 *      communicates the objects with the Simulator
 *      class.
 *
 * Created by Samuel Hibbard on 11/6/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#ifndef SimulatorViewController_h
#define SimulatorViewController_h

#import <Cocoa/Cocoa.h>
//#import "sim.h"

/*************************************
 * SimulatorViewController
 *  This is what will control everything
 *      inside the view.
 *************************************/
@interface SimulatorViewController : NSViewController
{
    // Private Members
    //Simulator * sim;
}

// Here are all the actions that are needed to be controlled.
@property (weak) IBOutlet NSButton *newbtn;
@property (weak) IBOutlet NSScrollView *treeTable;
@property (weak) IBOutlet NSTextField *editTitle;
@property (weak) IBOutlet NSTextField *formLabel1;
@property (weak) IBOutlet NSTextField *formLabel2;
@property (weak) IBOutlet NSTextField *formLabel3;
@property (weak) IBOutlet NSTextField *formInputTextField1;
@property (weak) IBOutlet NSTextField *formInputTextField2;
@property (weak) IBOutlet NSPopUpButton *formSelectBtn;
@property (weak) IBOutlet NSButton *deleteBtn;
@property (weak) IBOutlet NSButton *clear;
@property (weak) IBOutlet NSButton *reset;
@property (weak) IBOutlet NSButton *run;
@property (weak) IBOutlet NSOpenGLView *simulator;

// Member methods

@end

#endif /* SimulatorViewController_h */
