#pragma config(UART_Usage, UART1, uartUserControl, baudRate38400, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartUserControl, baudRate38400, IOPins, None, None)
#pragma config(Sensor, in1,    rLine,          sensorLineFollower)
#pragma config(Sensor, in2,    selector1,      sensorAnalog)
#pragma config(Sensor, in3,    selector2,      sensorAnalog)
#pragma config(Sensor, in4,    pot,            sensorAnalog)
#pragma config(Sensor, in5,    lLine,          sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  hangingLock,    sensorDigitalOut)
#pragma config(Sensor, dgtl4,  intake,         sensorDigitalOut)
#pragma config(Sensor, dgtl5,  pusher,         sensorDigitalOut)
#pragma config(Sensor, dgtl6,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  frontSonar,     sensorSONAR_raw)
#pragma config(Sensor, dgtl10, backSonar,      sensorSONAR_raw)
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
#include "xsens.c"
#include "Robot.c"
#include "Auton.c"
#include "pixy.c"
#include "pixyAuto.c"

task gyroCalib()
{

}

void pre_auton()
{
  startTask(xsens);
  //startTask(gyroCalib);
  GyroCalibration();
  //writeDebugStreamLine("Gyro calib done");
	setClaw(0);
	setHangingLock(0);
	startTask(PixyPackets);
}

void clawFlip()
{
	SetLiftHeight(LIFT_LOW_HEIGHT);
	  setClaw(1);
	  wait1Msec(100);
	  setClaw(0);
}

float PushTwo(float currentHeading);
float PSC_HangingPushing(float currentHeading);

void PSC()
{
    startTask(liftHeight);
    int turnAngVel = 120;
	  int turnStartSpeed = 80;
	  int currentHeading = 0;
	  int overshootConstant = 30;
    setPusher(0);
    setHangingLock(0);
    //toggleSonar(BACK_ON);

	  clawFlip();

	  driveHoldHeading(75, 80, currentHeading);
	  setClaw(1);
	  drivePower(0);
	  wait1Msec(500);

	  // Turn towards corner star #2 near fence
	  currentHeading += ROTATE_RIGHT - ROTATE_RIGHT*0.05;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_WITH_DRAGGING_STARS, 10);
	  //turnRight(turnStartSpeed, turnAngVel, currentHeading + 10);
	  setClaw(0);
	  driveHoldHeading(650, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
	  setClaw(1);

	  //currentHeading += ROTATE_LEFT * 2.0/13.0;
	  //turnLeft(turnStartSpeed, turnAngVel, currentHeading - overshootConstant/7, TYPE_BACKWARD);

	  // Go back to tile to get matchloads
	  currentHeading -= ROTATE_RIGHT*0.02;
	  driveHoldHeading(-50, -127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -70);
	  SetLiftHeight(LIFT_HIGH_HEIGHT);
	  driveHoldHeading(-300, -127, currentHeading);
	  driveHoldHeading(2000, -70, currentHeading, DRIVE_BACK_SONAR);

	  // LOADING #1
	  brake(-1);
	  wait1Msec(750);
	  //currentHeading += ROTATE_RIGHT / 7;
	  //turnRight(turnStartSpeed, turnAngVel, currentHeading + overshootConstant/7);
	  //drivePower(0);

	  //currentHeading += ROTATE_RIGHT * 0.08;

	  // Score #1
	  //currentHeading += ROTATE_RIGHT * 0.05;
	  //currentHeading += ROTATE_RIGHT * 0.05;
	  driveHoldHeading(750, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 40, 4);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(80);
	  wait1Msec(250);

	  currentHeading += ROTATE_RIGHT * 0.07;
	  //currentHeading += ROTATE_RIGHT / 14;

	  // Backup from fence
	  driveHoldHeading(-300, -90, currentHeading);
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  driveHoldHeading(5500, -90, currentHeading, DRIVE_BACK_SONAR);
	  brake(-1);

	  // Turn towards cube
	  currentHeading += ROTATE_RIGHT;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 10);
	  driveHoldHeading(300, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 40);
	  driveHoldHeading(8000, 127, currentHeading, DRIVE_BACK_SONAR_FORWARD);

	  // Grab Cube
	  setClaw(1);
	  SetLiftHeight(LIFT_MID_HEIGHT);
	  currentHeading += ROTATE_LEFT / 2.5;
	  driveHoldHeading(-350, -127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -70);
    brake(-0.5);
    currentHeading += ROTATE_LEFT * 1.5/2.5;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_WITH_CUBE);

	  // LOADING #2
	  //wait1Msec(250);

	  // Score #2 cubes.
	  SetLiftHeight(LIFT_HIGH_HEIGHT);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  //drivePower(50);
	  //wait1Msec(250);

	  // Backup from fence
	  driveHoldHeading(-200, -100, currentHeading);
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  driveHoldHeading(5000, -90, currentHeading, DRIVE_BACK_SONAR);

	  // Turn to get "3+1" stars in the front row.
	  currentHeading += ROTATE_RIGHT * 3.0 / 6.0;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading + overshootConstant);
	  driveHoldHeading(450, 90, currentHeading);
	  currentHeading += ROTATE_RIGHT * 3.0 / 6.0;
	  turnRight(turnStartSpeed, turnAngVel, currentHeading + overshootConstant/2);

	  // Get the 4 stars
	  driveHoldHeading(8500, 127, currentHeading, DRIVE_BACK_SONAR_FORWARD, ACCEL_FAST, 70, 5);
	  driveHoldHeading(1000, 127, currentHeading, DRIVE_ENCODERS, ACCEL_NONE, 127, 5, -10);
    setClaw(1);
    drivePower(127);
    wait1Msec(200);

    currentHeading += ROTATE_LEFT * 0.8;
    turnLeft(turnStartSpeed, turnAngVel, currentHeading, TYPE_BACKWARD);

    SetLiftHeight(LIFT_HIGH_HEIGHT);
    driveHoldHeading(-150, -100, currentHeading);

    currentHeading += ROTATE_LEFT * 0.5;
    driveTurnInPlace(currentHeading);

    //currentHeading += ROTATE_RIGHT * 0.5;
    //driveTurnInPlace(currentHeading);

    // Score #3
    driveHoldHeading(200, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(50);
	  wait1Msec(250);

	  // Nudge 4th star if it happens to still be there
	  currentHeading += ROTATE_RIGHT;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 30);
	  currentHeading += ROTATE_LEFT;
    driveHoldHeading(-75, -100, currentHeading);
	  // --- Delete Later
	  //SetLiftHeight(LIFT_HIGH_HEIGHT);
	  //setClaw(0);
	  //setHangingLock(0);
	  // ---

	  driveHoldHeading(-300, -90, currentHeading);
    brake(-1);


    currentHeading += ROTATE_LEFT * 0.7;
    driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);
    SetLiftHeight(LIFT_LOW_HEIGHT);

	  // Correct on wall
	  //currentHeading += ROTATE_LEFT;
	  //driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);

	  driveHoldHeading(2000, -90, currentHeading, DRIVE_BACK_SONAR);

	  // Turn towards star in corner
	  currentHeading += ROTATE_LEFT;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);

	  driveHoldHeading(300, 100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
	  setClaw(1);
	  driveHoldHeading(-250, -100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -70);

	  currentHeading += ROTATE_RIGHT * 0.35 ;
    driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);

	  // Pick up cube on red tile
	  setClaw(0);
	  driveHoldHeading(500, 100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
    setClaw(1);

    SetLiftHeight(LIFT_HIGH_HEIGHT);
    driveHoldHeading(-50, -100, currentHeading);

	  // Turn towards fence and raise lift
	  currentHeading += ROTATE_RIGHT * 0.65;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_PUSHER, 10); // Pusher = star + cube? lol

	  driveHoldHeading(2300, -90, currentHeading, DRIVE_BACK_SONAR);
	  currentHeading += ROTATE_RIGHT;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_PUSHER, 10); // Pusher = star + cube? lol

	  // Score #4
	  //driveHoldHeading(100, 100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);
	  driveHoldHeading(300, 127, currentHeading);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 70);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(50);
	  wait1Msec(250);

	  // Delete later
	  //SetLiftHeight(LIFT_HIGH_HEIGHT);
	  // ------------

	  driveHoldHeading(-300, -90, currentHeading);
	  SetLiftHeight(LIFT_LOW_HEIGHT);
	  driveHoldHeading(4700, -100, currentHeading, DRIVE_BACK_SONAR);
	  //driveHoldHeading(-400, -70, currentHeading);
	  brake(-1);

	  // Correct on wall
	  currentHeading += ROTATE_LEFT;
	  //driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);
	  //driveHoldHeading(2500, -65, currentHeading, DRIVE_BACK_SONAR);

	  // Pick up last 3 stars
	  currentHeading += ROTATE_LEFT / 3;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_SMALL_NORMAL);
	  driveHoldHeading(100, 100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 70);

	  // Don't do a turn here since hold heading will do a "smooth" turn automatically
	  currentHeading += ROTATE_RIGHT / 3;
	  driveHoldHeading(700, 127, currentHeading);
	  driveHoldHeading(1000, 127, currentHeading, DRIVE_LINES);
	  setClaw(1);
	  SetLiftHeight(LIFT_NEARLY_HIGH_HEIGHT);
	  driveHoldHeading(200, 127, currentHeading);

	  currentHeading += ROTATE_RIGHT + ROTATE_RIGHT * 0.30;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_WITH_CUBE); // 3 stars = cube

	  // Score #5
    driveHoldHeading(700, 127, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 50, 4);
	  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_NONE, 127, 4);
	  setClaw(0);
	  drivePower(127);
	  wait1Msec(100);
	  drivePower(127);
	  wait1Msec(250);

	  // Nudge 3rd star if it happens to still be there
	  currentHeading += ROTATE_LEFT;
	  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 35);
	  currentHeading += ROTATE_RIGHT;

	  // Push & Hang
	  currentHeading += ROTATE_LEFT * 0.30;
    currentHeading = PushTwo(currentHeading);
	  currentHeading = PSC_HangingPushing(currentHeading);
}

void AutonCubeFar()
{
  startTask(liftHeight);
  float currentHeading = 0;

  // Turn a little and pick up cube
  currentHeading += ROTATE_RIGHT * 0.15;
  clawFlip();
  driveHoldHeading(600, 100, currentHeading, DRIVE_ENCODERS);

  currentHeading += ROTATE_RIGHT * 0.35;

  setClaw(1);
  SetLiftHeight(LIFT_LITTLE_BIT_HEIGHT);
  driveTurnInPlace(currentHeading, PID_INPLACE_TURN_NORMAL, 20);
  driveHoldHeading(500, 100, currentHeading);
  currentHeading += ROTATE_LEFT;

  SetLiftHeight(LIFT_HIGH_HEIGHT);
  driveTurnInPlace(currentHeading);
  waitForLiftUp(LIFT_MID_CUBE_HEIGHT);

  // Score #1
  driveHoldHeading(200, 80, currentHeading);
  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 80);
  setClaw(0);
  drivePower(127);
  wait1Msec(100);
  drivePower(50);
  wait1Msec(250);
	drivePower(0);


  drivePower(0);
}

float AutonCubeMid()
{
  startTask(liftHeight);
  float currentHeading = 0;

  // Turn a little and pick up cube
  currentHeading += ROTATE_RIGHT * 0.15;
  clawFlip();
  driveHoldHeading(700, 100, currentHeading, DRIVE_ENCODERS);
  setClaw(1);
  SetLiftHeight(LIFT_HIGH_HEIGHT);

  // Turn towards fence
  currentHeading += ROTATE_LEFT / 2 + ROTATE_LEFT * 0.15;
  driveTurnInPlace(currentHeading);
  drivePower(0);
  waitForLiftUp(LIFT_LITTLE_BIT_HEIGHT);

  // Score #1
  driveHoldHeading(100, 80, currentHeading);
  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 80);
  setClaw(0);
  drivePower(127);
  wait1Msec(100);
  drivePower(50);
  wait1Msec(250);
	drivePower(0);

	currentHeading += ROTATE_RIGHT / 1.7;
	driveHoldHeading(-300, -65, currentHeading);
	SetLiftHeight(LIFT_LOW_HEIGHT);
	driveHoldHeading(-1000, -100, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -60);

	currentHeading += ROTATE_RIGHT * (0.9/1.7);
	driveTurnInPlace(currentHeading);
  driveHoldHeading(2000, 110, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, 60);
  setClaw(1);
  drivePower(0);
  wait1Msec(300);
  SetLiftHeight(LIFT_HIGH_HEIGHT);
  waitForLiftUp(LIFT_LITTLE_BIT_HEIGHT);

  currentHeading += ROTATE_LEFT;
  driveTurnInPlace(currentHeading);

  driveHoldHeading(400, 80, currentHeading);
  driveHoldHeading(550, 127, currentHeading, DRIVE_LINES, ACCEL_FAST, 80);
  setClaw(0);
  drivePower(127);
  wait1Msec(100);
  drivePower(50);
  wait1Msec(250);
	drivePower(0);

	return currentHeading;
}


float PSC_HangingWithoutPushing(float currentHeading)
{
  SetLiftHeight(LIFT_HIGH_HEIGHT);
  driveHoldHeading(200, -127, currentHeading);
  driveHoldHeading(4850, -100, currentHeading, DRIVE_BACK_SONAR);

  currentHeading += ROTATE_LEFT;
  driveTurnInPlace(currentHeading);
  driveHoldHeading(4850, -100, currentHeading, DRIVE_BACK_SONAR);
  setHangingLock(1);
  currentHeading += ROTATE_RIGHT/2;
  driveTurnInPlace(currentHeading);

  driveHoldHeading(-300, -80, currentHeading);

  drivePower(-90);
  wait1Msec(1000);

  drivePower(0);
  wait1Msec(500);

  stopTask(liftHeight);
  liftPower(-127);
  wait1Msec(4000);

  liftPower(0);

  return currentHeading;
}

float PSC_HangingPushing(float currentHeading)
{
  driveHoldHeading(600, 127, currentHeading, DRIVE_LINES);

  SetLiftHeight(LIFT_HIGH_HEIGHT);
  driveHoldHeading(200, 127, currentHeading);

  setPusher(0);
  currentHeading += ROTATE_RIGHT;
  driveTurnInPlace(currentHeading);
  driveHoldHeading(5000, -100, currentHeading, DRIVE_BACK_SONAR);
  brake(-1);

  setHangingLock(1);
  currentHeading += ROTATE_RIGHT/2;
  driveTurnInPlace(currentHeading);

  driveHoldHeading(-300, -80, currentHeading);

  drivePower(-100);
  wait1Msec(1250);

  drivePower(0);
  wait1Msec(500);

  stopTask(liftHeight);
  liftPower(-127);
  wait1Msec(4000);

  liftPower(0);

  return currentHeading;
}


float PushTwo(float currentHeading)
{
  SetLiftHeight(LIFT_HIGH_HEIGHT);
  driveHoldHeading(-300, -110, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -70);
	driveHoldHeading(4000, -110, currentHeading, DRIVE_BACK_SONAR, ACCEL_FAST, -100);

	currentHeading += ROTATE_RIGHT;

	driveTurnInPlace(currentHeading);
	driveHoldHeading(-300, -110, currentHeading, DRIVE_ENCODERS, ACCEL_FAST, -60);
	driveHoldHeading(5500, -110, currentHeading, DRIVE_BACK_SONAR, ACCEL_FAST, -80);
	driveHoldHeading(-200, -110, currentHeading, DRIVE_ENCODERS, ACCEL_SLOW, -80);
	brake(-1);

	currentHeading += ROTATE_RIGHT;
	deployTimer = 250;
	startTask(delayedDeploy);

	driveTurnInPlace(currentHeading, PID_INPLACE_TURN_PUSHER_FALLING);
	drivePower(0);
	wait1Msec(400);

	driveHoldHeading(-300, -127, currentHeading, DRIVE_RIGHT_LINES, ACCEL_FAST, -70);
	drivePower(-127);
	wait1Msec(500); // Push
	currentHeading += ROTATE_LEFT * 0.5;
	driveHoldHeading(900, 127, currentHeading);

	currentHeading += ROTATE_RIGHT * 1;
	driveTurnInPlace(currentHeading);

	driveHoldHeading(-50, -127, currentHeading);
	currentHeading += ROTATE_LEFT * 0.5;
  driveHoldHeading(-500, -127, currentHeading);
  drivePower(-127);
	wait1Msec(750); // Push #2

	return currentHeading;
}

task autonomous()
{
	autoQuit = 0;
	float currentHeading;
	if(SensorValue(selector2) > 3000)
	{
  	PSC();
  }
  else
  {
  	currentHeading = AutonCubeMid();
  	PixyAuton(currentHeading);
  }
}

#include "UserControl.c"
