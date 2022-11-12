#include "vex.h"
#include "PID.h"
#include "turn.h"
#include "forward-backward-pid.h"
#include "driverfunctions.h"

void halfLeftSide() {
  

  runFlywheel(75, true);
  IntakeMotor.spin(reverse, 100, pct);
  wait(500, msec);
  gyroMove(0.2, -50, 0.0);
  wait(1000, msec);
  IntakeMotor.stop();
  turnPIDLeft(15, true);
  wait(100, msec);
  singleShot();
  wait(700, msec);
  singleShot();
  turnPIDRight(45, true);
  wait(43000, msec);
  ExpansionPneumatic.close();



}