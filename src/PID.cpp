#include "vex.h"



double TRACKWHEEL_CIRCUM = 2.75;
double DRIVE_CIRCUM = 4*3.141592;


double kP = 0.01;
double kI = 0.0;
double kD = 0.01;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

int desiredInches = 0;

int error = 0;
int prevError = 0;
int derivative;
int totalError = 0;

int turnError = 0;
int turnPrevError = 0;
int turnDerivative;
int turnTotalError = 0;

bool enableDrivePID = true;

int drivePID(int desiredValue, int desiredTurnValue, bool resetDriveSensors) {

  double testl;
  double testr;
  while( enableDrivePID ) {

    if( resetDriveSensors ) {
      resetDriveSensors = false;

      LeftMotorFront.setPosition(0, degrees);
      LeftMotorBack.setPosition(0, degrees);

      RightMotorFront.setPosition(0, degrees);
      RightMotorBack.setPosition(0, degrees);

    }

    double leftDrivePosition = -1 * ( ( LeftMotorFront.position(degrees) + LeftMotorBack.position(degrees) + LeftMotorMiddle.position(degrees) ) / 3.0 );
    double rightDrivePosition = -1 * ( ( RightMotorFront.position(degrees) + RightMotorBack.position(degrees) + RightMotorMiddle.position(degrees) )  / 3.0 );
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Forward Backward Movement
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    double averagePosition = ( leftDrivePosition);

    error = averagePosition - desiredValue;

    if( error < 10 ) {
      return 1;
    }

    derivative = error - prevError;

    //totalError += error;

    double lateralMotorPower = error * kP + derivative * kD;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Turning Movement PID
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    double turnDifference = leftDrivePosition - rightDrivePosition;

    turnError = turnDifference - desiredTurnValue;

    turnDerivative = turnError - turnPrevError;

    //turnTotalError += turnError;

    double turnMotorPower = turnError * turnkP + turnDerivative * turnkD;


    LeftDrive.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    RightDrive.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);


    prevError = error;
    turnPrevError = turnError;

    testl = leftDrivePosition;
    testr = rightDrivePosition;    
    
    // Brain.Screen.setCursor(2, 1);
    // Brain.Screen.print(rightDrivePosition);
    vex::task::sleep(20);

    
  }

  Brain.Screen.print(testl);
  
  Brain.Screen.print(testr);

  return 1;
}


// void moveDrive(double inches) {
//   double desiredValue = 360/
// }