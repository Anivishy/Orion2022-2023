#include "vex.h"

//Driver Control
void tank_drive_Init(){
  RightDrive.stop();
  LeftDrive.stop();
}

void tank_drive_Do(){
  /*
    // code for 4 motor drive
    if(Controller1.Axis2.position(percent) > 20 || Controller1.Axis2.position(percent) < -20) {
      RightMotorC.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      LeftMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorB.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
    }

    //turning  
    else if(Controller1.Axis1.position(percent) > 20 || Controller1.Axis1.position(percent) < -20){
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
  */

  // user control code for 6 motor drive - haven't tested 
 
  
  //driving forward/backward - right side
  if(Controller1.Axis2.position(percent) > 50 || Controller1.Axis2.position(percent) < -50) {
    
    RightMotorFront.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
    RightMotorMiddle.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
    RightMotorBack.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);

  }

  // break - right side
  else {

    RightMotorFront.stop(brake);
    RightMotorMiddle.stop(brake);
    RightMotorBack.stop(brake);
    
  }

  //driving forward/backward - left side
  if(Controller1.Axis3.position(percent) > 50 || Controller1.Axis3.position(percent) < -50) {
    
    LeftMotorFront.spin(fwd, Controller1.Axis3.value(), velocityUnits::pct);
    LeftMotorMiddle.spin(fwd, Controller1.Axis3.value(), velocityUnits::pct);
    LeftMotorBack.spin(fwd, Controller1.Axis3.value(), velocityUnits::pct);

  }

  // break - left side
  else {

    LeftMotorFront.stop(brake);
    LeftMotorMiddle.stop(brake);
    LeftMotorBack.stop(brake);
    
  }

  wait(20, msec); 

}

//PNEUMATIC CODE

//TOGGLE FUNCTIONS FOR PNEUMATICS

//Indexer FUNCTIONS
void singleShot(){
  Indexer.open();
  wait (300, msec);
  Indexer.close();
}

void tripleShot(){
  Indexer.open();
  wait (300, msec);
  Indexer.close();

  wait(700, msec);

  Indexer.open();
  wait (300, msec);
  Indexer.close();

  wait(700, msec);

  Indexer.open();
  wait (300, msec);
  Indexer.close();
}

//EXPANSION FUNCTIONS
void expand(){
  ExpansionPneumatic.open();
}

//Indexer CODE
//Indexer init
void Indexer_Init(){
  Indexer.close();
}
//Shoots a single disc
void IndexerSingleShot_Do(){
  Controller1.ButtonL1.pressed(singleShot);
}
//Shoots 3 discs
void IndexerTripleShot_Do(){
  Controller1.ButtonL2.pressed(tripleShot);
}

//EXPANSION CODE
//expansion init
void expand_Init(){
  ExpansionPneumatic.close();
}
  
void expand_Do(){
  if(Controller1.ButtonY.pressing()){
    Controller1.ButtonLeft.pressed(expand);
  }
}

void intake_Init(){
  IntakeMotor.stop();
}

void intake_Do(){
  if (Controller1.ButtonR2.pressing()){
    IntakeMotor.spin(reverse, 100, pct);
  }
  else if (Controller1.ButtonR1.pressing()){
    IntakeMotor.spin(forward, 100, pct);
  }
  else{
    IntakeMotor.stop();
  }
}

// FLYWHEEL CODE
double flywheel_speed = 0;
int f_count = 0;

// flywheel init
void flywheel_Init(){
  FlywheelMotor.stop();
}

void flywheel_Do(){
  FlywheelMotor.spin(forward, flywheel_speed, pct);
}

void flywheel_toggle(){
  f_count ++;
  if (f_count % 2 == 1){
    flywheel_speed = 75;
  }
  else{
    flywheel_speed = 61;
  }
}

void change_speed(){
  Controller1.ButtonRight.pressed(flywheel_toggle);
}
