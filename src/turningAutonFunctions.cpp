#include "vex.h"

double kP = 1;
double kI = 1;
double kD = 1;

void turnRight(double deg){
  double error;
  double prevError = deg;
  double errorAsPercent;
  double powerIn;
  double integral;
  double derivative; 
  while(gyroS.yaw() <= deg){ //this assumes that the robot starts at 0. This value increases as the robot truns right. "gyroS.yaw()" might change based on how the sensor is mounted
    error = deg - gyroS.yaw();
    errorAsPercent = ((error / deg) * 100);
    integral += error;
    if(error <= 0){
      integral = 0;
    }
    derivative = error - prevError;
    //might need to add a limiter to integral if it gets too large during testing
    powerIn = (errorAsPercent * kP) + (integral * kI) + (derivative * kD);
    LeftDrive.spin(forward, powerIn, pct);
    RightDrive.spin(reverse, powerIn, pct);
    prevError = error;
    wait(15, msec);

  }
}