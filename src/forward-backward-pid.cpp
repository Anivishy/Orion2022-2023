#include "vex.h"
#include "math.h"

void gyroMove(double distance, double speed, double turnAngle) {
  double startLPos = LeftDrive.position(rev);
  double startRPos = RightDrive.position(rev);
  double k1 = 0.5;
  //double k2 = 1.2;

  LeftDrive.spin(forward, speed,  pct);
  RightDrive.spin(forward, speed, pct);
  //while (distance > fabs((lEncoder.position(rev)-startLPos + rEncoder.position(rev)-startRPos) / 2.0)) {
  while (distance > fabs((LeftDrive.position(rev)- startLPos + RightDrive.position(rev) - startRPos) / 2.0)) {
    /*Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(gyroS.yaw());*/

    double error = gyroS.yaw() - turnAngle; // positive when right of ideal angle
    double adjustment = error*k1;
    if (fabs(adjustment) > 30.0) adjustment = 30.0*(adjustment/fabs(adjustment));
    if (fabs(error) < 0.25) adjustment = 0;
   
    if ((speed > 0 && adjustment > 0) || (speed < 0 && adjustment < 0)) LeftDrive.setVelocity(speed - (adjustment), pct);
    else RightDrive.setVelocity(speed + (adjustment), pct);

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

void gyroTurnRight(double angle, double velocity){
//double incrementValue = angle * 0.5;
LeftDrive.spin(forward, velocity, pct);
RightDrive.spin(reverse, velocity, pct);
//double target = angle -5;
/*
while (gyroS.rotation(degrees) < incrementValue){
  lDrive.spin(reverse, velocity, pct);
  rDrive.spin(forward, velocity, pct);
}
while (gyroS.rotation(degrees) < (incrementValue * 1.5)){
  lDrive.spin(reverse, (velocity * 0.5), pct);
  rDrive.spin(forward, (velocity * 0.5), pct);
}
*/
waitUntil((gyroS.yaw(degrees) >= angle));
LeftDrive.stop();
RightDrive.stop();
gyroS.resetHeading();
gyroS.resetRotation();
}

void gyroTurnLeft(double angle, double velocity){
LeftDrive.spin(reverse, velocity, pct);
RightDrive.spin(forward, velocity, pct);

 

waitUntil((gyroS.yaw(degrees) <= angle));
LeftDrive.stop();
RightDrive.stop();
gyroS.resetHeading();
gyroS.resetRotation();
}

double autonIncrement = 10;

double stepDistance = 0.3;
double stepSpeed = 60;

void calcIncrementAuton(double goalValue, double& velocity, double increment) {
  if (goalValue > velocity + increment/2) {
      velocity += increment;
  } else if (goalValue < velocity - increment/2) {
    velocity -= increment;
  } else {
    velocity = goalValue;
  }
}

double getCurFwdDistance(double startLFPos, double startLBPos, double startRFPos, double startRBPos) { // for 4 motors
  return fabs((LeftMotorFront.position(rev)-startLFPos + LeftMotorBack.position(rev)-startLBPos + RightMotorFront.position(rev)-startRFPos + RightMotorBack.position(rev)-startRBPos) / 4.0);
}
double getCurSideDistance(double startLFPos, double startLBPos, double startRFPos, double startRBPos) {
  return fabs((LeftMotorBack.position(rev)-startLBPos + RightMotorFront.position(rev)-startRFPos - LeftMotorFront.position(rev)+startLFPos - RightMotorBack.position(rev)+startRBPos) / 4.0);
}

void longDistanceMoveNew(double distance, double velocity, double turnAngle) {
  double startLFPos = LeftMotorFront.position(rev);
  double startLMPos = LeftMotorMiddle.position(rev);
  double startLBPos = LeftMotorBack.position(rev);
  double startRFPos = RightMotorFront.position(rev);
  double startRMPos = RightMotorMiddle.position(rev);
  double startRBPos = RightMotorBack.position(rev);
  
  double calcVelocity = 0;
  int steps = (int)round(fabs(velocity)/stepSpeed);

  double k1 = 3.0;
  double maxAdjustment = 30.0;
  double minError = 0.25;

  bool lastStep = false;

  LeftDrive.spin(forward);
  RightDrive.spin(forward);
  while (!lastStep) {
    double error = distance - getCurFwdDistance(startLFPos, startLBPos, startRFPos, startRBPos);
    if (error > stepDistance * steps) {
      if (calcVelocity != velocity) {
        calcIncrementAuton(velocity, calcVelocity, autonIncrement);
      }
    } else {
      int i = 1;
      while (error > stepDistance * i) {
        i++;
      }
      if (i != 1) {
        calcVelocity = stepSpeed * i * velocity / fabs(velocity);
      } else {
        lastStep = true;
      }
    }

    double turnError = gyroS.yaw() - turnAngle;
    double adjustment = turnError * k1;
    if (fabs(adjustment) > maxAdjustment) adjustment = maxAdjustment * (adjustment/fabs(adjustment));
    if (fabs(turnError) < minError) adjustment = 0;

    if ((velocity > 0 && adjustment > 0) || (velocity < 0 && adjustment < 0))  {
      RightDrive.setVelocity(calcVelocity - adjustment, pct);
      LeftDrive.setVelocity(calcVelocity, pct);
    } else {
      LeftDrive.setVelocity(calcVelocity + adjustment, pct);
      RightDrive.setVelocity(calcVelocity, pct);
    }

    wait(10, msec);
  }
  LeftDrive.setVelocity(stepSpeed, pct);
  RightDrive.setVelocity(stepSpeed, pct);
  LeftMotorBack.spinTo(distance * velocity / fabs(velocity) + startLBPos, rev, false);
  RightMotorBack.spinTo(distance * velocity / fabs(velocity) + startLFPos, rev, false);
  RightMotorFront.spinTo(distance * velocity / fabs(velocity) + startRFPos, rev, false);
  LeftMotorFront.spinTo(distance * velocity / fabs(velocity) + startLFPos, rev, false);
  RightMotorMiddle.spinTo(distance * velocity / fabs(velocity) + startLMPos, rev, false);
  LeftMotorMiddle.spinTo(distance * velocity / fabs(velocity) + startRMPos, rev, false);
  waitUntil(LeftDrive.isDone() && RightDrive.isDone());
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