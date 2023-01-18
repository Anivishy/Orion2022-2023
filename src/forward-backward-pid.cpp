#include "vex.h"
#include "math.h"

void gyroMove(double distance, double speed, double turnAngle) {
  double startLPos = LeftDrive.position(rev);
  double startRPos = RightDrive.position(rev);
  double k1 = 3.0;
  //double k2 = 1.2;

  LeftDrive.spin(reverse, speed,  pct);
  RightDrive.spin(reverse, speed, pct);
  //while (distance > fabs((lEncoder.position(rev)-startLPos + rEncoder.position(rev)-startRPos) / 2.0)) {
  while (distance > fabs((LeftDrive.position(rev)- startLPos + RightDrive.position(rev) - startRPos) / 2.0)) {
    /*Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(gyroS.yaw());*/

    double error = gyroS.yaw() - turnAngle; // positive when right of ideal angle
    double adjustment = error*k1;
    if (fabs(adjustment) > 30.0) adjustment = 30.0*(adjustment/fabs(adjustment));
    if (fabs(error) < 0.25) adjustment = 0;
   
    if ((speed > 0 && adjustment > 0) || (speed < 0 && adjustment < 0)) RightDrive.setVelocity(speed - (adjustment - 5), pct);
    else LeftDrive.setVelocity(speed + (adjustment - 5), pct);

    /*Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(adjustment);
    Controller1.Screen.newLine();
    Controller1.Screen.print(error);*/
  }
  LeftDrive.stop();
  RightDrive.stop();
  LeftDrive.resetRotation();
  RightDrive.resetRotation();
  /*Controller1.Screen.clearLine();
  Controller1.Screen.print(gyroS.yaw());*/

  /*while (1) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(gyroS.pitch());
    Controller1.Screen.print(gyroS.roll());
    Controller1.Screen.print(gyroS.yaw());
  }*/
}

void runFlywheel(double speed, bool needsToRun) {
  if( needsToRun ) {
    //FlywheelMotor.spin(forward, speed, pct);
  } else {
    //FlywheelMotor.stop();
  }
}

// double TRACKWHEEL_CIRCUM = 2.75;
// double DRIVE_CIRCUM = 2.75;


// void drivePID(double inches) {

//   double kP = 0.0;
//   double kI = 0.0;
//   double kD = 0.0;

//   int error = 0;
//   int prevError = 0;
//   int integral = 0;
//   int derivative = 0;

//   int power = 0;

//   int target = (TRACKWHEEL_CIRCUM / inches) * 360;

//   while(true) {
//     error = target - LeftEncoder.position(rotationUnits::deg);
//     integral = integral + error;
    
//     if (error <= 0 || error > /*TUNE LATER*/ 100) {
//       integral = 0;
//     }

//     derivative = error - prevError;
//     prevError = error;

//     power = (error * kP) + (integral*kI) + (derivative*kD);
//     RightDrive.spin(forward, power, pct);
//     LeftDrive.spin(forward, power, pct);

//     task::sleep(20);
//   }
  

// }

// void spinDriveTrainForward(double power) {
//   RightDrive.spin(forward, power, pct);
//   LeftDrive.spin(forward, power, pct);
// }

// void spinDriveTrainBackward(double power) {
//   RightDrive.spin(reverse, power, pct);
//   LeftDrive.spin(reverse, power, pct);
// }