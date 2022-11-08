#include "vex.h"
#include "math.h"

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