/*
    Example for moving in continous rotation mode on the Dynamixel AX12-A series servos
    
	Serial:
	GPIO UART: "/dev/ttyTHS0" "/dev/ttyTHS1" "/dev/ttyTHS2"
	USB  UART: "/dev/ttyUSB0"

    Jetson Pins:
    gpio57  or 57,    // J3A1 - Pin 50
	gpio160 or 160,	  // J3A2 - Pin 40	
	gpio161 or 161,    // J3A2 - Pin 43
	gpio162 or 162,    // J3A2 - Pin 46
	gpio163 or 163,    // J3A2 - Pin 49
	gpio164 or 164,    // J3A2 - Pin 52
	gpio165 or 165,    // J3A2 - Pin 55
	gpio166 or 166     // J3A2 - Pin 58
	
	*Rotates Clockwise
		Ax12.turn(ID, RIGHT, 0->1020) : Limit is 1020
		
	*Rotates Counter-Clockwise
		Ax12.turn(ID, LEFT,  0->900) : Limit is 900 (Anything above this for CCW may not work)
	
	*Halts at current position
		Ax12.turn(ID, OFF, 0) : Stops the servo
*/
#include<iostream>
#include "JetsonAX12.h"

#define ID 1        // ID for singl servo
#define USB 1   	// 1 for GPIO, 0 for USB
#define SEC 1000000 // 1 Second in micro second units for delay
#define MSEC 1000	// 1 milli second in micro second units for delay

using namespace std;

int main()
{
    JetsonAX12 control;

#if USB
	control.begin("/dev/ttyUSB0", B1000000);
#else 
	control.begin("/dev/ttyTHS0", B1000000, 166);
#endif
    
    control.setEndless(ID, ON);
    
    for(int i = 0; i < 3; i++)
    {
		control.turn(ID, RIGHT, 1020);
		usleep(3*SEC);
		control.turn(ID, LEFT, 512);
		usleep(3*SEC);
		control.turn(ID, OFF, OFF); // Either clockwise or counter clockwise as long as speed is 0
		usleep(3*SEC);
    }    
    
    control.disconnect();
    return 0;
}

