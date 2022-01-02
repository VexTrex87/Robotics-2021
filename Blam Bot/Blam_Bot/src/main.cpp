/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Cyrus                                            */
/*    Created:      Tue Dec 21 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftMotors           motor_group   1, 2            
// RightMotors          motor_group   3, 4            
// Lift                 motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>

using namespace vex;


competition Competition;
bool debugEnabled = true;
float speed = 1.0;
float liftSpeed = 0.5;



///////////////////////////////////////////////////////////////
/////////A DEBUG FOR FUN/////////

int debug()
{
  int leftMotorsTemp;
  int rightMotorsTemp;

  while (1)
  {
    leftMotorsTemp = LeftMotors.temperature(percent);
    rightMotorsTemp = RightMotors.temperature(percent); 

    Controller1.Screen.clearScreen();

    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("LM Temp: %d", leftMotorsTemp);

    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("RM Temp: %d", rightMotorsTemp);

    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("Speed: %f", speed);

    vex::task::sleep(4000);
  }

}
/////END OF DEBUG FUNCTION/////
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
////////DRIVER CONTROL FUNCTION////////

void drivercontrol()
{
  int thirdAxisPos;
  int fourthAxisPos;
  int secondAxisPos;

  while(1)
  {
    thirdAxisPos = Controller1.Axis3.position();
    fourthAxisPos = Controller1.Axis4.position();
    secondAxisPos = Controller1.Axis2.position();

    // Drives and turns the robot with left analog stick
    if (thirdAxisPos != 0 || fourthAxisPos != 0)
    {
      LeftMotors.spin(forward, (thirdAxisPos + fourthAxisPos) * speed, percent);
      RightMotors.spin(forward, (thirdAxisPos - fourthAxisPos) * speed, percent);
    }
    else
    {
      LeftMotors.stop(coast);
      RightMotors.stop(coast);
    }
    
    // Moves the lift up and down with right analog stick
    if (secondAxisPos != 0)
    {
      Lift.spin(forward, secondAxisPos * liftSpeed, percent);
    }
    else
    {
      Lift.stop(brake);
    }

  }

}

/////END OF DRIVER CONTROLL FUNCTION/////
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
/////////AUTONOMOUS FUNCTION/////////

void autonomous()
{
  //Blam_bot.doAuton(true) 
  //yay we win!
}

/////END OF AUTONOMOUS FUNCTION/////
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
///MAIN FUNCTION *CALLED WHEN SCRIPT IS RAN*///

int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  if (debugEnabled)
  {
    vex::task debugginTool(debug);
  }

  Competition.drivercontrol(drivercontrol);

  return 0;
}

/////////////END OF MAIN FUNCTION/////////////
///////////////////////////////////////////////////////////////
