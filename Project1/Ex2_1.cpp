#include <stdio.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#include "SpasserBib.h"

float computeMoment(IplImage* img, int j, int k, CvPoint center = { 0, 0 })
{
	unsigned int w = img->width, h = img->height;

	float moment = 0;

	for (unsigned int y = 0; y < h; y++)
	{
		for (unsigned int x = 0; x < w; x++)
		{
			int n = (y*w + x) * 3; // Pixel array index

			int value = 0;
			if (!img->imageData[n])
				value = 1;

			moment += (float)pow(x - center.x, j) * (float)pow(y - center.y, k) * (float)value;
		}
	}

	return moment;
}

CvPoint computeCOM(IplImage* img)
{
	float M_00, M_10, M_01;
	CvPoint COM;

	M_00 = computeMoment(img, 0, 0);
	M_10 = computeMoment(img, 1, 0);
	M_01 = computeMoment(img, 0, 1);

	COM.x = M_10 / M_00;
	COM.y = M_01 / M_00;

	return COM;
}

int main(int argc, char* argv[]) {
	const char* wName = "Image!"; // window name    
	const char* wNameThresh = "Threshold image"; // window name    
	const char* wNameHist = "Histogram"; // window name
	cvNamedWindow(wNameHist, 0);
	cvNamedWindow(wNameThresh, 0);
	cvNamedWindow(wName, 0); // create simple window 

	unsigned char threshold = 100;

	IplImage* img1 = cvLoadImage("C:/Users/30330/Documents/Spassere/Project1/moment_test4.png");
	//IplImage* img1 = cvLoadImage("C:/Users/30330/Documents/Exercises/PEN.pgm");
	IplImage* imgThresh = 0;
	IplImage* imgHist = 0; // pointers to hist image

	imgHist = histogram(img1, 0);

	imgThresh = cvCreateImage(cvSize(img1->width, img1->height), img1->depth, img1->nChannels);
	cvCopy(img1, imgThresh, 0);
	printf("# channels: %d\n", img1->nChannels);

	//printf("%d", OPENCV_PIXEL)

	for (int i = 0; i < imgThresh->width*imgThresh->height*imgThresh->nChannels; i++)
	{
		if ((uchar)imgThresh->imageData[i] > threshold) // Remember to typecast, or weird things happen!
		{
			imgThresh->imageData[i] = 255;
		}
		else
		{
			imgThresh->imageData[i] = 0;
		}

		// Invert binary image
		//imgThresh->imageData[i] = 255 - imgThresh->imageData[i];
	}

	/* Part 2 - Center of mass */
	CvPoint com = computeCOM(imgThresh);
	printf("COM: (%d, %d)\n", com.x, com.y);

	/* Part 3 - Image moments */
	float u_20, u_02, u_11;
	u_20 = computeMoment(imgThresh, 2, 0, com);
	u_02 = computeMoment(imgThresh, 0, 2, com);
	u_11 = computeMoment(imgThresh, 1, 1, com);
	printf("%.2f   %.2f   %.2f\n", u_20, u_02, u_11);

	float u_2 = u_20 + u_02;

	float theta = atan2(2.0 * u_11, u_20 - u_02) / 2.0;
	printf("Orientation: %f rad\n", theta);

	cvDrawCircle(imgThresh, com, 5, cvScalar(0, 0, 255)); // Draw center of mass

	float a = tan(theta);
	float b = com.y - a*com.x;

	printf("a = %f \nb = %f \n", a, b);

	cvDrawLine(imgThresh, cvPoint(0, b), cvPoint(imgThresh->width, a * imgThresh->width + b), cvScalar(255, 0, 0));
	//cvDrawLine(imgThresh, cvPoint(com.x - 50, a * (com.x - 50) + b), cvPoint(com.x + 50, a * (com.x + 50) + b), cvScalar(0, 0, 255));

	cvResizeWindow(wName, img1->width, img1->height);
	cvResizeWindow(wNameThresh, imgThresh->width, imgThresh->height);
	cvResizeWindow(wNameHist, imgHist->width, imgHist->height);
	cvShowImage(wNameHist, imgHist);
	cvShowImage(wNameThresh, imgThresh);

	cvShowImage(wName, img1);

	cvWaitKey(0);

	cvDestroyAllWindows();

	return 0;
}