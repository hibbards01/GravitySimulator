/****************************************************
 * Program:
 *   Simulator.mm
 * Author:
 *   Samuel Hibbard
 * Summary:
 *   This will define the subclass for NSOpenGLView.
 *
 * Created by Samuel Hibbard on 11/5/15.
 * Copyright © 2015 samIAm. All rights reserved.
 ****************************************************/

#import <Foundation/Foundation.h>
#import "Simulator.h"
#import "sim.h"

// Define the window size for Position
float Position::xMax = 500;
float Position::xMin = -500;
float Position::yMax = 343;
float Position::yMin = -343;
