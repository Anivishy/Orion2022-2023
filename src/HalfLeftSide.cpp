#include "vex.h"
#include "PID.h"
#include "turn.h"
#include "forward-backward-pid.h"
#include "driverfunctions.h"

void halfLeftSide() {

  Drive.setVelocity(20, pct);  
  IntakeMotor.spin(reverse, 100, pct);
  Drive.rotateFor(forward, 0.3, rev);
  wait(50, msec);
  //IntakeMotor.stop();
  Drive.rotateFor(forward, -0.3, rev);
  
  /*
  RightDrive.rotateFor(reverse, 1.8, rev);
  Drive.rotateFor(forward, 2.2, rev);
  wait(200, msec);
  Drive.rotateFor(forward, -1, rev);
  RightDrive.rotateFor(forward, 0.5, rev);
  wait(1000, msec);
  ExpansionPneumatic.open();
  */
  
  //Drive.rotateFor(forward, 0.6, rev);\
  //RightDrive.rotateFor(reverse, 0.7, rev);
  


  // runFlywheel(75, true);
  // IntakeMotor.spin(reverse, 100, pct);
  // wait(500, msec
  // gyroMove(0.1, -50, 0.0);
  // IntakeMotor.stop();
  // turnPIDRight(45, true);
  // gyroMove(2, -50, 45);
  // turnPIDLeft(90, true);
  // wait(100, msec);
  // singleShot();
  // wait(700, msec);
  // singleShot();
  
  drivePIDBackward(300, 0, true);
  Brain.Screen.print("HII");

  // wait(3000, msec);
  // drivePIDBackward(2, 0, true);
 
  
  // while( true ) {
  //   Brain.Screen.setCursor(1, 1);
  //   Brain.Screen.print(gyroS.yaw());
  //   wait(20, msec);
  //   Brain.Screen.clearScreen();
  // }
  




}