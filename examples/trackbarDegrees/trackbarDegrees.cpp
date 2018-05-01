#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "JetsonAX12.h"

using namespace std;
using namespace cv;

#define USB 1   	// 1 for USB, 0 for GPIO
#define SEC 1000000 // 1 Second in micro second units for delay
#define MSEC 1000	// 1 milli second in micro second units for delay

int lowThreshold = 150;
int const max_Threshold = 300;
JetsonAX12 control;

void Threshold1(int, void*)
{
	int degrees = lowThreshold - 150;
	control.moveDeg(1,degrees);
}

void Threshold2(int, void*)
{
	int degrees = lowThreshold - 150;
	control.moveDeg(2,degrees);
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

	control.moveDeg(1,0);
	usleep(2*SEC);
	control.moveDeg(2,0);
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
