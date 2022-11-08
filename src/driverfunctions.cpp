#include "vex.h"

//Driver Control
void tank_drive_Init(){
  RightDrive.stop();
  LeftDrive.stop();
}

void tank_drive_Do(){
  /*
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

  /* user control code for 6 motor drive - haven't tested 
  while (1) {
    
    //driving forward/backward
    if(Controller1.Axis2.position(percent) > 20 || Controller1.Axis2.position(percent) < -20) {
      
      RightMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorB.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      RightMotorC.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      LeftMotorA.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      LeftMotorB.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
      LeftMotorC.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);

    }

    //turning  
    else if(Controller1.Axis1.position(percent) > 20 || Controller1.Axis1.position(percent) < -20){

      RightMotorA.spin(fwd, Controller1.Axis1.value(), velocityUnits::pct);
      RightMotorB.spin(fwd, Controller1.Axis1.value(), velocityUnits::pct);
      RightMotorC.spin(fwd, Controller1.Axis1.value(), velocityUnits::pct);
      LeftMotorA.spin(directionType::rev, Controller1.Axis1.value(), velocityUnits::pct);
      LeftMotorB.spin(directionType::rev, Controller1.Axis1.value(), velocityUnits::pct);
      LeftMotorC.spin(directionType::rev, Controller1.Axis1.value(), velocityUnits::pct);

    }

    else {

      RightMotorA.stop(brake);
      RightMotorB.stop(brake);
      RightMotorC.stop(brake);
      LeftMotorA.stop(brake);
      LeftMotorB.stop(brake);
      LeftMotorC.stop(brake);
      
    }
  
    wait(20, msec); 
  
  }
  */
  

}

//PNEUMATIC CODE

//TOGGLE FUNCTIONS FOR PNEUMATICS

//Indexer FUNCTIONS
void singleShot(){
  Indexer.open();
  wait (100, msec);
  Indexer.close();
}

void tripleShot(){
  Indexer.open();
  wait (100, msec);
  Indexer.close();

  Indexer.open();
  wait (100, msec);
  Indexer.close();

  Indexer.open();
  wait (100, msec);
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
    Controller1.ButtonRight.pressed(expand);
  }
}

void intake_Init(){
  IntakeMotor.stop();
}

void intake_Do(){
  if (Controller1.ButtonR1.pressing()){
    IntakeMotor.spin(reverse, 100, pct);
  }
  else if (Controller1.ButtonR2.pressing()){
    IntakeMotor.spin(forward, 100, pct);
  }
  else{
    IntakeMotor.stop();
  }
}
