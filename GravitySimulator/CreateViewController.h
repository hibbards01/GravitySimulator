/****************************************************
 * Program:
 *  CreateViewController.h
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will control the modal view.
 *
 * Created by Samuel Hibbard on 11/9/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#ifndef CreateViewController_h
#define CreateViewController_h

#import <Cocoa/Cocoa.h>

// Define the protocol
@protocol sendDataProtocol <NSObject>

- (void) grabData: (NSDictionary *) data;

@end

@interface CreateViewController : NSViewController
{
    NSMutableArray *ids;   // These are the ids of the objects
    NSMutableArray *names; // Save the names for the list
}

// Grab all the input tags
@property (weak) IBOutlet NSPopUpButton *whichObjectBtn;
@property (weak) IBOutlet NSTextField *nameInput;
@property (weak) IBOutlet NSTextField *diamOrMagInput;
@property (weak) IBOutlet NSTextField *massOrAngleInput;
@property (weak) IBOutlet NSPopUpButton *objBtn;

// Grab all the buttons
@property (weak) IBOutlet NSButton *cancel;
@property (weak) IBOutlet NSButton *create;

// And one label
@property (weak) IBOutlet NSTextField *objectLabel;
@property (weak) IBOutlet NSTextField *label2;
@property (weak) IBOutlet NSTextField *label3;
@property (weak) IBOutlet NSTextField *mainTitle;

// This will hold the delegate
@property(nonatomic,assign) id delegate;

- (void) sendObjects: (NSMutableArray *) sentIds names: (NSMutableArray *) sentNames whichObject: (BOOL)planet;

@end

#endif /* CreateViewController_h */
