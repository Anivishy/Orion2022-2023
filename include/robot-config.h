using namespace vex;

extern brain Brain;
extern controller Controller1;

extern motor RightMotorFront;
extern motor RightMotorMiddle;
extern motor RightMotorBack;
extern motor_group RightDrive;

extern motor LeftMotorFront;
extern motor LeftMotorMiddle;
extern motor LeftMotorBack;
extern motor_group LeftDrive;

extern pneumatics Indexer;
extern pneumatics ExpansionPneumatic;

//extern inertial gyroS;
//vision


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
