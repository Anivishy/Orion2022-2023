#include "vex.h"
#include "PID.h"
#include "turn.h"
#include "forward-backward-pid.h"
#include "driverfunctions.h"

void halfLeftSide() {
  // runFlywheel(75, true);

  // //gyroMove(2, 50, 0);
  // drivePID(100, 0, true);
  // IntakeMotor.spinFor(-0.25, rev, true);

  // //gyroMove(-10, 50, 0);
  // drivePID(500, 0, true);
  // IndexerSingleShot_Do();
  // IndexerSingleShot_Do();

  gyroMove(0.1, -50, 0.0);
  IntakeMotor.spinFor(-1, rev, true);
  runFlywheel(75, true);
  gyroMove(0.2, 50, 0);

  //IntakeMotor.spinFor(-0.5, rev, true);
}