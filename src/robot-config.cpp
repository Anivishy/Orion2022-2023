#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller1 = controller(primary);

motor RightMotorA = motor(PORT1, ratio18_1, false);
motor RightMotorB = motor(PORT2, ratio18_1, false);
motor RightMotorC = motor(PORT3, ratio18_1, false);
motor_group RightDrive = motor_group(RightMotorA, RightMotorB, RightMotorC);

motor LeftMotorA = motor(PORT4, ratio18_1, false);
motor LeftMotorB = motor(PORT5, ratio18_1, false);
motor LeftMotorC = motor(PORT6, ratio18_1, false);
motor_group LeftDrive = motor_group(LeftMotorA, LeftMotorB, LeftMotorC);

encoder RightEncoder = encoder(Brain.ThreeWirePort.A);
encoder LeftEncoder = encoder(Brain.ThreeWirePort.B);
encoder MiddleEncoder = encoder(Brain.ThreeWirePort.C);

inertial gyroS = inertial(PORT12);

pneumatics indexer = pneumatics(Brain.ThreeWirePort.H);
pneumatics expandLeft = pneumatics(Brain.ThreeWirePort.G);
pneumatics expandRight = pneumatics(Brain.ThreeWirePort.F);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}