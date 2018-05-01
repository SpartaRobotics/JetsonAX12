#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "JetsonAX12.h"

using namespace std;
using namespace cv;

#define USB 1   	// 1 for USB, 0 for GPIO
#define SEC 1000000 // 1 Second in micro second units for delay
#define MSEC 1000	// 1 milli second in micro second units for delay

int lowThreshold = 512;
int const max_Threshold = 1023;
JetsonAX12 control;

void Threshold1(int, void*)
{
	control.move(1,lowThreshold);
}

void Threshold2(int, void*)
{
	control.move(2,lowThreshold);
}

int main()
{

#if USB
	control.begin("/dev/ttyUSB0", B1000000);
#else 
	control.begin("/dev/ttyTHS0", B1000000, 166);
#endif

	control.setEndless(1, OFF); // Sets the servo to "Servo" mode
	control.setEndless(2, OFF); // Sets the servo to "Servo" mode

	namedWindow("Window", CV_WINDOW_AUTOSIZE);
	createTrackbar( "Servo1:", "Window", &lowThreshold, max_Threshold, Threshold1);
	createTrackbar( "Servo2:", "Window", &lowThreshold, max_Threshold, Threshold2);

	char c;

	control.move(1,512);
	usleep(MSEC);
	control.move(2,512);
	usleep(2*SEC);

	while(1)
	{

		c = waitKey(33);
		if( c == 'q') break;
	}

	destroyAllWindows();
	control.disconnect();
	return 0;
}
