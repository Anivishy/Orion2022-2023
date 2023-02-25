
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
#include "forward-backward-pid.h"

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
  //Indexer_Init();
  cata_Init();

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

int cata_shoot_int_auto(){
  CataMotor.spin(forward, 100, pct);
  wait(500, msec);
  CataMotor.stop();
  wait(100, msec);
  while (cataLine.reflectivity(pct) < 94){
    CataMotor.spin(forward, 100, pct);
  }
  CataMotor.stop();
  wait(250, msec);
  CataMotor.setPosition(25, deg);
  //amount += 0.05;
  return 0;

}
void cata_shoot_auto(){
  task multi = task(cata_shoot_int_auto);
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  /*
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(gyroS.yaw());
  gyroMove(5, -50, 0);
  Brain.Screen.setCursor(2,2);
  Brain.Screen.print(gyroS.yaw());
  */
  //skills
  //1st 2 rollers
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.1, 30, 0);
  wait(100, msec);
  gyroMove(0.25, -30, 0);
  wait(50, msec);
  gyroTurnRight(25, 10);
  gyroMove(2.2, -30, 35);
  wait(50, msec);
  IntakeMotor.spin(forward, 100, pct);
  gyroTurnRight(90, 10);
  wait(50, msec);
  gyroMove(3.1, 30, 90);
  //delay for pickup up 3rd disc
  wait(650, msec);
  gyroMove(0.4, 20, 90);
  //roller wait time
  wait(125, msec);
  gyroMove(0.95, -20, 90);
  // end of 2nd roller
  
  //turn and move towards the goal + shoot
  gyroTurnLeft(9, 10);
  gyroMove(5.5, -30, 0);
  //gyroTurnRight()
  gyroTurnRight(7, 10);
  cata_shoot_auto();
  wait(50, msec);
  // end of 1st shot

  //movement towards 1st disc in row of 3
  gyroTurnLeft(0, 10);
  gyroMove(1.5, 15, 0);
  gyroMove(2.45, 15, -60);
  gyroTurnLeft(-125, 10);
  gyroMove(3.7, 15, -135);
  wait(300, msec);
  //finish intaking 3rd disc

  //turn and movement sequence towards goal for 2nd shot
  gyroTurnRight(0, 10);
  gyroMove(3.75, -30, 0);////////
  gyroTurnLeft(-65, 10);
  gyroMove(2, -30, -75);
  gyroTurnLeft(-85, 10);
  cata_shoot_auto();
  wait(1500, msec);
  //end of 2nd shot

  //movement toward matchload spot
  gyroTurnRight(-85, 10);
  gyroMove(1.2, 30, -90);
  gyroTurnRight(-5, 10);
  gyroMove(0.95, -20, 0);//
  //delay for person to load in discs
  wait(3000, msec);
  //gyroMove(0.2, 20, 0); this is a movement away from the feeder before the next shot, should not be needed but just in case... very small if anything

  //turn + move toward the goal for 3rd shot
  gyroMove(0.1, 30, 0);//-----
  gyroTurnLeft(-95, 10);
  gyroMove(1.5, -30, -85);
  gyroTurnLeft(-93, 10);
  cata_shoot_auto();
  wait(1500, msec);
  //end of 3rd shot

  //movement towards 3rd roller
  gyroMove(5.5, 30, -90);
  //turn toward the roller
  gyroTurnLeft(-150, 10);
  //get roller
  gyroMove(0.7, 30, -165);
  wait(750, msec);
  gyroMove(1.5, -30, -165);
  IntakeMotor.stop();
  wait(100, msec);
  // end of roller + backup from it

  //turn to shoot expansion
  gyroTurnRight(35, 10);
  wait(100, msec);
  //movement back after turn to center on the 4 tiles
  gyroMove(0.2, -30, 45);
  wait(1500, msec);
  //expansion
  ExpansionPneumatic.open();
/*
//short skills
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.1, 30, 0);
  wait(100, msec);
  gyroMove(0.25, -30, 0);
  wait(50, msec);
  gyroTurnRight(35, 10);
  gyroMove(2.2, -30, 35);
  wait(50, msec);
  IntakeMotor.spin(forward, 100, pct);
  gyroTurnRight(90, 10);
  wait(50, msec);
  gyroMove(3.1, 30, 90);
  wait(650, msec);
  gyroMove(0.6, 20, 96);
  wait(125, msec);
  gyroMove(0.95, -20, 90);
  gyroTurnLeft(10, 10);
  gyroMove(5.5, -30, 0);
  //gyroTurnRight()
  gyroTurnRight(7, 10);
  cata_shoot_auto();
  wait(50, msec);
  IntakeMotor.spin(reverse);
  wait(50, msec);
  gyroTurnLeft(-10, 10);
  gyroMove(4.9, 30, -15);
  gyroTurnLeft(-125, 10);
  gyroMove(1.2, -20, -135);
  wait(1500, msec);
  ExpansionPneumatic.open();
*/
  /*
  gyroTurnRight(-80, 10);
  gyroMove(6, 30, -85);
  gyroTurnLeft(-150, 10);
  gyroMove(0.9, 30, -165);
  wait(100, msec);
  gyroMove(1.1, 30, -175);
  gyroTurnRight(30, 10);
  wait(2000, msec);
  ExpansionPneumatic.open();
  */

//weak
/*
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.1, 30, 0);
  wait(40, msec);
  gyroMove(0.1, -30, 0);
  gyroTurnRight(60, 10);
  gyroMove(0.3, -30, 75);
  cata_shoot_auto();
*/
//double
/*
// 5 disk lowgoal auto
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.1, 30, 0);
  wait(40, msec);
  gyroMove(0.1, -30, 0);
  gyroTurnRight(60, 10);
  gyroMove(0.3, -30, 75);
  cata_shoot_auto();
  gyroTurnLeft(-115, 10);
  gyroMove(3, 30, -135);
  IntakeMotor.spin(forward, 100, pct);
  gyroMove(2.1, 20, -135);
  gyroTurnRight(135, 10);
  cata_shoot_auto();
*/
/*
// add this in for full double roller auton, needs to be tuned
  gyroTurnLeft(-80, 30);
  gyroMove(7.3, 40, -135);
  gyroTurnRight(-110, 10);
  gyroMove(0.5, 30, -90);
  wait(50, msec);
  gyroMove(0.1, -30, -90);
*/

//strong
/*
  wait(1500, msec);
  cata_shoot_auto();
  gyroMove(2, 20, 0);
  gyroTurnRight(60, 10);
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.65, 20, 80);
  wait(50, msec);
  gyroMove(0.1, -10, 80);
*/

  /*
  IntakeMotor.spin(reverse, 100, pct);
  gyroMove(0.1, 30, 0);
  wait(60, msec);
  gyroMove(0.2, -30, 0);
  wait(500, msec);
  cata_shoot();
  wait(200, msec);
  gyroTurnLeft(-115,10);
  gyroMove(3, 50, -120);
  wait(100, msec);
  IntakeMotor.spin(forward, 100, pct);
  gyroMove(3, 10, -125);
  IntakeMotor.spin(reverse, 100, pct);
  */

  //longDistanceMoveNew(1, 50, 0);
}

void usercontrol(void) {
  //init
  //tank_drive_Init();
  driveMoveSlope_Init();
  Indexer_Init();
  expand_Init();
  intake_Init();
  cata_Init();
  //cataRotation.resetPosition();
  //flywheel_Init();
  

  while (1) {
    tank_drive_Do();
    task cata_shoot = task(cata_Do);
    //driveMoveSlope_Do();
    IndexerSingleShot_Do();
    IndexerTripleShot_Do();
    expand_Do();
    intake_Do();
    //flywheel_Do();
    //change_speed();
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(3,3);
    Brain.Screen.print(cataLine.reflectivity());
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

