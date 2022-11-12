#include "vex.h"

double anglekP = 0.235;
double anglekI = 0.1;
double anglekD = 0.25;


int angleError = 0;
int anglePrevError = 0;
int angleDerivative;
int angleTotalError = 0;


bool enableTurnPID = true;

double sensorAngle;

int turnPIDRight(int desiredAngle,  bool resetGyroSensor) {


  while( enableTurnPID ) {

    if( resetGyroSensor ) {
      resetGyroSensor = false;

      gyroS.setHeading(5, degrees);
      Brain.Screen.print(gyroS.heading());

    }

    sensorAngle = gyroS.heading() - 5;

    angleError = sensorAngle  - desiredAngle;

    angleDerivative = angleError - anglePrevError;


    double motorPower = angleError * anglekP + angleDerivative * anglekD;


    LeftDrive.spin(reverse, motorPower, voltageUnits::volt);
    RightDrive.spin(forward, motorPower, voltageUnits::volt);


    anglePrevError = angleError;
    
    if( angleError > 0 ) {
      Brain.Screen.print("HIiiiiii");
      LeftDrive.stop();
      RightDrive.stop();
      enableTurnPID = false;
      return 1;
    } 

    
    //Brain.Screen.print(sensorAngle);
    wait(20, msec);
  }

  return 1;
}


int turnPIDLeft(int desiredAngle,  bool resetGyroSensor) {


  while( enableTurnPID ) {

    if( resetGyroSensor ) {
      resetGyroSensor = false;

      gyroS.setHeading(358, degrees);
      Brain.Screen.print(gyroS.heading());

      anglekI = 0.0;

    }

    if( desiredAngle <= 15 ) {
      anglekI = 0.5;
    }

    sensorAngle = fabs(( (gyroS.heading() + 1) - 360 ));

    angleError = sensorAngle  - desiredAngle;

    angleDerivative = angleError - anglePrevError;


    double motorPower = angleError * anglekP + angleDerivative * anglekD + anglePrevError * anglekI;


    LeftDrive.spin(forward, motorPower, voltageUnits::volt);
    RightDrive.spin(reverse, motorPower, voltageUnits::volt);


    anglePrevError = angleError;
    
    if( angleError > 0 ) {
      LeftDrive.stop();
      RightDrive.stop();
      enableTurnPID = false;
      return 1;
    } 

    
    //Brain.Screen.print(sensorAngle);
    wait(20, msec);
  }

  return 1;
}
