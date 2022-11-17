#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller1 = controller(primary);

motor RightMotorFront = motor(PORT9, ratio18_1, true);
motor RightMotorMiddle = motor(PORT10, ratio18_1, true);
motor RightMotorBack = motor(PORT3, ratio18_1, false);
motor_group RightDrive = motor_group(RightMotorFront, RightMotorMiddle, RightMotorBack);

motor LeftMotorFront = motor(PORT12, ratio18_1, false);
motor LeftMotorMiddle = motor(PORT1, ratio18_1, false);
motor LeftMotorBack = motor(PORT13, ratio18_1, true);
motor_group LeftDrive = motor_group(LeftMotorFront, LeftMotorMiddle, LeftMotorBack);

motor IntakeMotor = motor(PORT2, ratio18_1, false);
motor FlywheelMotor = motor(PORT8, ratio36_1, true);

// encoder RightEncoder = encoder(Brain.ThreeWirePort.A);
// encoder LeftEncoder = encoder(Brain.ThreeWirePort.B);
// encoder MiddleEncoder = encoder(Brain.ThreeWirePort.C);

inertial gyroS = inertial(PORT11);

//vision

pneumatics Indexer = pneumatics(Brain.ThreeWirePort.H);
pneumatics ExpansionPneumatic = pneumatics(Brain.ThreeWirePort.A);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}