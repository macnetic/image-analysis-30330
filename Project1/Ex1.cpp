//Exercise 1

#include <stdio.h>
#include "cv.h"
#include "cxcore.h" 
#include "highgui.h" 
#include <conio.h> 

int main(int argc, char* argv[]) {

	unsigned char value = 0; // index value for the histogram (not really needed) 
	int histogram[256]; // histogram array - remember to set to zero initially 
	int width; // say, 320 
	int height; // say, 240
	int i;
	int j;

	CvPoint P1;
	CvPoint P2;
	CvScalar Col;
	CvSize histSize;

	P1.x = 0;
	P1.y = 255;
	P2.x = 0;
	P2.y = 0;

	histSize.width = 256;
	histSize.height = 256;

	Col.val[0] = 0.0;
	Col.val[1] = 0.0;
	Col.val[2] = 0.0;
	Col.val[3] = 0.0;
	char *channel; // pre-allocated array holding image data for the color channel or the grayscale image. 

	const char* wName = "Hello world!"; // window name
	const char* wNameHist = "Histogram"; // window name

	//IplImage* img1 = cvLoadImage("C:\Users\30330\Documents\Exercises\ariane5_1b.jpg");
	IplImage* img1 = cvLoadImage("C:/Users/30330/Documents/Exercises/ariane5_1b.jpg");
	//IplImage* 

	width = img1->width;
	height = img1->height;
	channel = (img1->imageData);


	int k = 256; 
	while (k-- > 0)  
		histogram[k] = 0; // reset histogram entry 

	for (i = 2; i < width*height*3; i+=3){ 
		value = channel[i];
		histogram[value] += 1;
	}

	IplImage* imgHist = cvCreateImage(histSize, IPL_DEPTH_8U, 1);
	cvNamedWindow(wNameHist, 0);
	//cvRectangle(img1, P1, P2, Col, 1, 8, 0);
	//cvLine(img1, P1, P2, Col, 1, 8, 0);

	cvResizeWindow(wNameHist, 256, 256);
	for (j = 0; j < 256; j++){
		P2.y = P1.y - histogram[j]/20;
		cvLine(imgHist, P1, P2, Col, 1, 8, 0);
		P1.x++;
		P2.x++;
	}
	cvShowImage(wNameHist, imgHist);


	/*
	cvNamedWindow(wName, 0);
	cvResizeWindow(wName, 1400, 1200);
	cvWaitKey(10000);
	cvShowImage(wName, img1);
	cvWaitKey(10000);
	cvResizeWindow(wName, 800, 600);
	cvWaitKey(10000);
	cvMoveWindow(wName, 10, 0);
	*/
	while(1){
		if (cvWaitKey(5) > 0) {
			break;
		}
	}
	return 0;
}