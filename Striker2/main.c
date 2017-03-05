#pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Sensor, in2,    gyro,           sensorAnalog)
#pragma config(Sensor, in3,    status,         sensorAnalog)
#pragma config(Sensor, in4,    rLine,          sensorLineFollower)
#pragma config(Sensor, in5,    lLine,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl10, backSonar,      sensorSONAR_raw)
#pragma config(Sensor, dgtl12, intake,         sensorDigitalOut)
#pragma config(Motor,  port2,           driveR2,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           driveR1,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           driveR3,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           liftR1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           liftL1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           driveL3,       tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           driveL1,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           driveL2,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "LCD_Vex_Competition_Includes.c"

#include "LCD.c"
#include "Robot.c"
#include "Auton.c"

void pre_auton()
{
  GyroInit(gyro);
  GyroCalibration();
  startTask(GyroTask);
}

void PSC()
{
    startTask(liftHeight);
    int turnAngVel = 120;
	  int turnStartSpeed = 70;
	  int currentHeading = 0;

	  // Pick up corner cube
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  setClaw(0);
	  wait1Msec(500);
	  driveHoldHeading(190, 70, currentHeading);
	  setClaw(1);
	  driveHoldHeading(-150, -70, currentHeading);
	  brake(-1);

	  // Turn towards corner cube #2 near fence
	  currentHeading += ROTATE_RIGHT;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading);
	  setClaw(0);
	  driveHoldHeading(480, 50, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 90);
	  setClaw(1);
	  wait1Msec(200);

	  // Go back to tile to get matchloads
	  driveHoldHeading(-140, -70, currentHeading);
	  SetLiftHeight(LIFT_HIGH_HEIGHT);
	  driveHoldHeading(-550, -60, currentHeading, DRIVE_LINES);
	  driveHoldHeading(-275, -60, currentHeading);
	  brake(-1);
	  wait1Msec(1000);

	  // Score #1
	  driveHoldHeading(450, 50, currentHeading);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 50);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(50);
	  wait1Msec(1000);

	  // Backup from fence
	  driveHoldHeading(-400, -60, currentHeading);
	  driveHoldHeading(-1400, -50, currentHeading, DRIVE_LINES);
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  driveHoldHeading(-70, -50, currentHeading);
	  brake(-1);

	  // Turn towards cube
	  currentHeading += ROTATE_RIGHT;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading);
	  driveHoldHeading(800, 50, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 90);
	  setClaw(1);
	  SetLiftHeight(LIFT_HIGH_HEIGHT);
	  driveHoldHeading(4000, -50, currentHeading, DRIVE_BACK_SONAR, ACCEL_FAST, -60);

	  // Rotate towards fence and get match loads
	  currentHeading += ROTATE_LEFT;
	  turnLeft(turnStartSpeed, turnAngVel, currentHeading, TYPE_BACKWARD);
	  driveHoldHeading(-200, -50, currentHeading);
	  drivePower(-70);
	  wait1Msec(500);
	  drivePower(0);
	  wait1Msec(500);

	  // Recalibrate on fence
	  GyroResetAngle(currentHeading);

	  // Score #2 cubes.
	  driveHoldHeading(450, 50, currentHeading);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 50);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(50);
	  wait1Msec(1500);
	  driveHoldHeading(-350, -70, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -50);
	  SetLiftHeight(LIFT_LOW_HEIGHT);

	  // Move away from fence, lining up with the wall
	  driveHoldHeading(3000, -50, currentHeading, DRIVE_BACK_SONAR);
	  brake(-1);

	  // Turn 45 degrees to stack
	  currentHeading += ROTATE_RIGHT / 2;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading);
	  driveHoldHeading(400, 50, currentHeading);
	  brake(1);
	  currentHeading += ROTATE_RIGHT / 2;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading);
	  brake(1);

	  driveHoldHeading(8500, 70, currentHeading, DRIVE_BACK_SONAR_FORWARD);
	  driveHoldHeading(800, 70, currentHeading);
	  brake(1);

	  currentHeading += ROTATE_LEFT / 2;
	  turnLeft(turnStartSpeed, turnAngVel, currentHeading, TYPE_FORWARD);
	  setClaw(1);
	  driveHoldHeading(70, 50, currentHeading);
	  currentHeading += ROTATE_LEFT / 2;
	  turnLeft(turnStartSpeed, turnAngVel, currentHeading, TYPE_BACKWARD);

	  SetLiftHeight(LIFT_HIGH_HEIGHT);
	  driveHoldHeading(-150, -50, currentHeading);
	  drivePower(0);
	  wait1MSec(1000);
	  driveHoldHeading(375, 80, currentHeading);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(50);
	  wait1Msec(1500);
	  driveHoldHeading(-325, -50, currentHeading);
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  driveHoldHeading(-325, -50, currentHeading);
}

task autonomous()
{
  PSC();
}


#include "UserControl.c"
