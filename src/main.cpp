
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// EncoderA             encoder       A, B
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "driverFunctions.h"

////////////////////////////////////////////////
//AUTON ROUTINES
////////////////////////////////////////////////
#include "HalfLeftSide.h"

//#include "visionSensorConfig.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
/*int count = 0;
int speed = 0;
int view = 0;
int regulator = 1;
int perspectiveToggle = 1;*/

void ctrlrDisplayInt(int variable, int row, int col) {
  Controller1.Screen.setCursor(row, col);
  Controller1.Screen.clearLine();
  Controller1.Screen.print(variable);
}
void ctrlrDisplayDouble(double variable, int row, int col) {
  Controller1.Screen.setCursor(row, col);
  Controller1.Screen.clearLine();
  Controller1.Screen.print(variable);
}
void ctrlrDisplayClear(int row, int col) {
  Controller1.Screen.setCursor(row, col);
  Controller1.Screen.clearLine();
}

/*void perspective(){
  count++;
 }*/


  

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */ //driving forward/backward
  /*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  gyroS.calibrate();
  while(gyroS.isCalibrating()) wait(10, msec);
  Indexer_Init();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  halfLeftSide();
}

void usercontrol(void) {
  //init
  tank_drive_Init();
  Indexer_Init();
  expand_Init();
  intake_Init();
  flywheel_Init();
  

  while (1) {
    tank_drive_Do();
    IndexerSingleShot_Do();
    IndexerTripleShot_Do();
    expand_Do();
    intake_Do();
    flywheel_Do();
    change_speed();

    wait(1, msec); /* Sleep the task for a short amount of time to
                     prevent wasted resources. */
                  
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //Controller1.ButtonUp.pressed(Toggle);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

