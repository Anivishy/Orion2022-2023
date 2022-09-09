using namespace vex;

extern brain Brain;

extern motor RightMotorA;
extern motor RightMotorB;
extern motor RightMotorC;

extern motor LeftMotorA;
extern motor LeftMotorB;
extern motor LeftMotorC;

extern encoder RightEncoder;
extern encoder LeftEncoder;
extern encoder MiddleEncoder;

extern inertial gyroS;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
