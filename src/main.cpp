/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\anivi                                            */
/*    Created:      Wed Sep 07 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "driverFunctions.h"
#include "turningAutonFunctions.h"
#include "forward-backward-pid.h"

using namespace vex;

void usercontrol(void) {
  //user control code 
  while (1) {
    
    //driving forward/backward
    if(Controller1.Axis2.position(percent) > 20 || Controller1.Axis2.position(percent) < -20) {
      RightMotorC.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      LeftMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorB.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
    }

    //turning  
    else if(Controller1.Axis1.position(percent) > 20){
      RightMotorC.spin(fwd, Controller1.Axis1.value(), velocityUnits::pct);
      LeftMotorA.spin(fwd, Controller1.Axis1.value(), velocityUnits::pct);
      RightMotorA.spin(directionType::rev, Controller1.Axis1.value(), velocityUnits::pct);
      RightMotorB.spin(directionType::rev, Controller1.Axis1.value(), velocityUnits::pct);
    }

    else {
      RightMotorC.stop(brake);
      LeftMotorA.stop(brake);
      RightMotorA.stop(brake);
      RightMotorB.stop(brake);
    }

    wait(20, msec); 

  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
