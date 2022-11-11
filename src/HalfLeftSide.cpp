#include "vex.h"
#include "PID.h"
#include "turn.h"
#include "forward-backward-pid.h"
#include "driverfunctions.h"

void halfLeftSide() {
  

  // runFlywheel(75, true);
  // IntakeMotor.spin(reverse, 100, pct);
  // wait(500, msec);
  // gyroMove(0.1, -50, 0.0);
  // wait(1000, msec);
  // IntakeMotor.stop();
  // gyroMove(0.15, 50, 0);
  // turnPID(350, true);
  // wait(500, msec);
  // singleShot();
  // wait(750, msec);
  // singleShot();

  turnPID(-10, true);

}