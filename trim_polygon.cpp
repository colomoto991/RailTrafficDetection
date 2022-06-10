/******************************************************
 This program is to pick the area and filled by mouse.

 usage: Click and hold the lbutton to start drawing the contour of the region. 
 Release the button will end the drawing and save the mask.

**************************************************************/





#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>  // cvtColor
#include "opencv2/imgproc/types_c.h"

using namespace std;
using namespace cv;

#define CV_EVENT_MOUSEMOVE 0                   
#define CV_EVENT_LBUTTONDOWN 1           
#define CV_EVENT_RBUTTONDOWN 2          
#define CV_EVENT_MBUTTONDOWN 3          
#define CV_EVENT_LBUTTONUP 4           
#define CV_EVENT_RBUTTONUP 5             
#define CV_EVENT_MBUTTONUP 6           
#define CV_EVENT_LBUTTONDBLCLK 7       
#define CV_EVENT_RBUTTONDBLCLK 8     


#define CV_EVENT_MBUTTONDBLCLK 9     
#define CV_EVENT_FLAG_LBUTTON 1      
#define CV_EVENT_FLAG_RBUTTON 2     
#define CV_EVENT_FLAG_MBUTTON 4     
#define CV_EVENT_FLAG_CTRLKEY 8    
#define CV_EVENT_FLAG_SHIFTKEY 16   
#define CV_EVENT_FLAG_ALTKEY 32    


static vector<vector<Point>> vctvctPoint;
Mat source = imread("lc-00378.png");
Mat dst, maskImage, dstimg, roi;
static vector<Point> vctPoint;
static Point ptStart(-1, -1); 
static Point cur_pt(-1, -1); 
char temp[16];


void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cout << "x:" << x << " y:" << y << endl;
		ptStart = Point(x, y);
		vctPoint.push_back(ptStart);
		circle(source, ptStart, 1, Scalar(255, 0, 255), FILLED, LINE_AA, 0);
		imshow("image", source);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))
	{
		cout << "x:" << x << " y:" << y << endl;
		cur_pt = Point(x, y);
		line(source, vctPoint.back(), cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0); // auto close the curve
		circle(source, cur_pt, 1, Scalar(255, 0, 255), FILLED, LINE_AA, 0);
		imshow("image", source);
		vctPoint.push_back(cur_pt);
		//putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 0));
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		cout << "x:" << x << " y:" << y << endl;
		cur_pt = Point(x, y);
		line(source, ptStart, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);
		circle(source, cur_pt, 1, Scalar(255, 0, 255), FILLED, LINE_AA, 0);
		imshow("image", source);
		vctPoint.push_back(cur_pt);
		vctvctPoint.push_back(vctPoint);

		// fill the polygon
		const Point* ppt[1] = { &vctPoint[0] };
		int len = vctPoint.size();
		int *npt = &len;

		// initiate the mask image as the same size filled with black background
		source.copyTo(maskImage);
		maskImage.setTo(Scalar(0, 0, 0, 0));

		fillPoly(maskImage, ppt, npt, 1, Scalar(255, 255, 255, 0));
		//polylines(maskImage, ppt, npt,1,1, Scalar(0, 0, 255), 1);

		imshow("mask", maskImage);
		imwrite("mask.png", maskImage);

		waitKey(0);
	}
}

int main()
{

	namedWindow("image");
	setMouseCallback("image", on_mouse, 0);
	imshow("image", source);
	waitKey(0);
	return 0;
}
