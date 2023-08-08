#pragma comment(lib, "opencv_world343d.lib")
#include "opencv2/opencv.hpp"
#include "opencv2/video/tracking.hpp"
#define MINTRACKAREA 50
using namespace cv;
Mat trackobj();
void main()
{
	trackobj();
}
Mat trackobj()
{
	VideoCapture cap;
	Mat frame;
	cap >> frame;
	Mat hsvFrame;
	cvtColor(frame, hsvFrame, CV_RGB2HSV);
	blur(hsvFrame, hsvFrame, Size(1, 1));
	Scalar lowerBound = cv::Scalar(55, 100, 50), upperBound = cv::Scalar(90, 255, 255);
	Mat threshFrame;
	inRange(hsvFrame, lowerBound, upperBound, threshFrame);
	Moments m = moments(threshFrame, false);
	Point com(m.m10 / m.m00, m.m01 / m.m00);
	Scalar color = cv::Scalar(0, 0, 255);
	drawMarker(frame, com, color, cv::MARKER_CROSS, 50, 5);
	imshow("object", frame);
	imshow("object", threshFrame);
	return threshFrame;
}