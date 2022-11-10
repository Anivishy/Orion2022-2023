#include "vex.h"
#include "PID.h"
#include "turn.h"
#include "forward-backward-pid.h"

void halfLeftSide() {
  runFlywheel(75, true);

  gyroMove(-10, 50, 0);
  IntakeMotor.spinFor(-0.25, rev, true);

  gyroMove(50, 50, 0);
}