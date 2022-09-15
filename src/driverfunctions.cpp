#include "vex.h"

//PNEUMATIC CODE

//TOGGLE FUNCTIONS FOR PNEUMATICS

//INDEXER FUNCTIONS
void singleShot(){
  indexer.open();
  wait (100, msec);
  indexer.close();
}

void tripleShot(){
  indexer.open();
  wait (100, msec);
  indexer.close();

  indexer.open();
  wait (100, msec);
  indexer.close();

  indexer.open();
  wait (100, msec);
  indexer.close();
}

//EXPANSION FUNCTIONS
void expand(){
  expandLeft.open();
  expandRight.open();
}

//INDEXER CODE
//Indexer init
void indexer_Init(){
  indexer.close();
}
//Shoots a single disc
void indexerSingleShot_Do(){
  Controller1.ButtonL1.pressed(singleShot);
}
//Shoots 3 discs
void indexerTripleShot_Do(){
  Controller1.ButtonL2.pressed(tripleShot);
}

//EXPANSION CODE
//expansion init
void expand_Init(){
  expandLeft.close();
  expandRight.close();
}

void expand_Do(){
  if(Controller1.ButtonY.pressing()){
    Controller1.ButtonRight.pressed(expand);
  }
}
