#include "vex.h"






double anglekP = 0.535;
double anglekI = 0.0;
double anglekD = 0.25;


int angleError = 0;
int anglePrevError = 0;
int angleDerivative;
int angleTotalError = 0;


bool enableTurnPID = true;

double sensorAngle;

int turnPID(int desiredAngle,  bool resetGyroSensor) {


  while( enableTurnPID ) {

    if( resetGyroSensor ) {
      resetGyroSensor = false;

      gyroS.setHeading(5, degrees);
      Brain.Screen.print(gyroS.heading());

    }

    sensorAngle = gyroS.heading() - 5;

    angleError = sensorAngle  - desiredAngle;

    angleDerivative = angleError - anglePrevError;

    //totalError += error;

    double motorPower = angleError * anglekP + angleDerivative * anglekD;


    LeftDrive.spin(forward, motorPower, voltageUnits::volt);
    RightDrive.spin(reverse, motorPower, voltageUnits::volt);


    anglePrevError = angleError;
    
    if( angleError < 3 ) {
      LeftDrive.stop();
      RightDrive.stop();
      return 1;
    } 

    
    //Brain.Screen.print(sensorAngle);
    wait(20, msec);
  }

  return 1;
}
