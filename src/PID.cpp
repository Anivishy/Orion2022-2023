#include "vex.h"



double TRACKWHEEL_CIRCUM = 2.75;
double DRIVE_CIRCUM = 4*3.141592;


double kP = 0.015;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

int desiredInches = 0;

int leftError = 0;
int rightError = 0;
int leftPrevError = 0;
int rightPrevError = 0;

int leftDerivative;
int rightDerivative;
int totalError = 0;

int turnError = 0;
int turnPrevError = 0;
int turnDerivative;
int turnTotalError = 0;

bool enableDrivePID = true;

int drivePIDBackward(int desiredValue, int desiredTurnValue, bool resetDriveSensors) {

  desiredValue = -1 * desiredValue;

  while( enableDrivePID ) {

    if( resetDriveSensors ) {
      resetDriveSensors = false;

      // LeftMotorFront.setPosition(0, degrees);
      // LeftMotorBack.setPosition(0, degrees);
      // LeftMotorMiddle.setPosition(0, degrees);

      // RightMotorFront.setPosition(0, degrees);
      // RightMotorBack.setPosition(0, degrees);
      // RightMotorMiddle.setPosition(0, degrees);

      leftRotation.setPosition(0, deg);
      rightRotation.setPosition(0, deg);

    }

    

    double leftDrivePosition = ( leftRotation.position(deg) );
    double rightDrivePosition = ( rightRotation.position(deg) );
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Forward Backward Movement
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    leftError = leftDrivePosition - desiredValue;
    rightError = rightDrivePosition - desiredValue;
  

    leftDerivative = leftError - leftPrevError;
    rightDerivative = rightError - rightPrevError;

    //totalError += error;

    double leftMotorPower = leftError * kP + leftDerivative * kD;
    double rightMotorPower = rightError * kP + rightDerivative * kD;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Turning Movement PID
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // double turnDifference = leftDrivePosition - rightDrivePosition;

    // turnError = turnDifference - desiredTurnValue;

    // turnDerivative = turnError - turnPrevError;

    // //turnTotalError += turnError;

    // double turnMotorPower = turnError * turnkP + turnDerivative * turnkD;


    LeftDrive.spin(reverse, leftMotorPower, voltageUnits::volt);
    RightDrive.spin(reverse, rightMotorPower, voltageUnits::volt);


    leftPrevError = leftError;
    rightPrevError = rightError;
    
    //turnPrevError = turnError;

    // if( leftError >= -2 ) { 
    //   LeftDrive.stop();
    //   Brain.Screen.setCursor(3, 0);
    //   Brain.Screen.print("left done");
    //   return 1;
    // }

    // if( rightError >= -2 ) {
    //   RightDrive.stop();
    //   Brain.Screen.setCursor(4, 0);
    //   Brain.Screen.print("right done");
    // }
  
    //Brain.Screen.clearScreen();
    vex::task::sleep(20);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(rightError);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(leftError);
    
  }


  return 1;
}

// // int drivePIDForward(int desiredValue, int desiredTurnValue, bool resetDriveSensors) {


// //   while( enableDrivePID ) {

// //     if( resetDriveSensors ) {
// //       resetDriveSensors = false;

// //       LeftMotorFront.setPosition(0, degrees);
// //       LeftMotorBack.setPosition(0, degrees);

// //       RightMotorFront.setPosition(0, degrees);
// //       RightMotorBack.setPosition(0, degrees);

// //     }

    

// //     double leftDrivePosition = ( ( LeftMotorFront.position(degrees) + LeftMotorBack.position(degrees) + LeftMotorMiddle.position(degrees) ) / 3.0 );
// //     double rightDrivePosition = ( ( RightMotorFront.position(degrees) + RightMotorBack.position(degrees) + RightMotorMiddle.position(degrees) )  / 3.0 );
    
// //     ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //     // Forward Backward Movement
// //     ///////////////////////////////////////////////////////////////////////////////////////////////////////////
// //     double averagePosition = ( leftDrivePosition + rightDrivePosition ) / 2.0;

// //     error = averagePosition - desiredValue;

  

// //     derivative = error - prevError;

// //     //totalError += error;

// //     double lateralMotorPower = error * kP + derivative * kD;

// //     ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //     // Turning Movement PID
// //     ///////////////////////////////////////////////////////////////////////////////////////////////////////////
// //     // double turnDifference = leftDrivePosition - rightDrivePosition;

// //     // turnError = turnDifference - desiredTurnValue;

// //     // turnDerivative = turnError - turnPrevError;

// //     // //turnTotalError += turnError;

// //     // double turnMotorPower = turnError * turnkP + turnDerivative * turnkD;


// //     LeftDrive.spin(forward, lateralMotorPower, voltageUnits::volt);
// //     RightDrive.spin(forward, lateralMotorPower, voltageUnits::volt);


// //     prevError = error;
// //     //turnPrevError = turnError;

// //     if( error <= -3 ) { 
// //       LeftDrive.stop();
// //       RightDrive.stop();
// //       Brain.Screen.print("HII");
// //       return 1;
// //     }
    
// //     // Brain.Screen.setCursor(2, 1);
// //     // Brain.Screen.print(rightDrivePosition);
// //     vex::task::sleep(20);

    
// //   }


// //   return 1;
// // }