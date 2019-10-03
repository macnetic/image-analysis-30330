#include <stdio.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#include "SpasserBib.h"

void computeAverageLP(IplImage* img, IplImage* imgResult) {
	uint8_t n = 1;

	uint32_t x, y;
	uint16_t k, l;
	uint32_t idx; //

	uint16_t temp;

	for (y = n; y < img->height - n; y++) {
		for (x = n; x < img->width - n; x++) {
			// Loop over kernel
			temp = 0;
			for (l = y - n; l <= y + n; l++) {
				for (k = x - n; k <= x + n; k++) {
					idx = img->width * l + k;

					temp += (uint8_t)img->imageData[idx];
				}
			}
			temp = round(temp / pow(2 * n + 1, 2));
			idx = img->width*y + x;
			imgResult->imageData[idx] = (uint8_t)temp;
		}
	}
}

void computeHP(IplImage* img, IplImage* imgResult) {
	int16_t n = 2;

	int16_t kernel[5][5] =
	{
		{0, 0, -1, 0, 0},
		{0, -1, -2, -1, 0},
		{-1, -2, 16, -2, -1},
		{0, -1, -2, -1, 0},
		{0, 0, -1, 0, 0}
	};
	//uint8_t n = 1;

	//int16_t kernel[3][3] = {
	//	{0, 1, 0},
	//	{1, -4, 1},
	//	{0, 1, 0}
	//};

	uint32_t x, y;
	int16_t k, l;
	uint32_t idx; //

	int16_t temp;

	for (y = n; y < img->height - n; y++) {
		for (x = n; x < img->width - n; x++) {
			// Loop over kernel
			temp = 128;
			for (l = -n; l <= n; l++) {
				for (k = n; k <= n; k++) {
					idx = img->width * (y - l) + (x - k);

					temp += (int16_t) img->imageData[idx] * kernel[l+n][k+n];
				}
			}
			//temp = round(temp / pow(2 * n + 1, 2));
			idx = img->width*y + x;

			if (temp < 0)
				temp = 0;
			else if (temp > 255)
				temp = 255;
			imgResult->imageData[idx] = (uint8_t)temp;
		}
	}
}

int main(int argc, char* argv[]) {
	/* Part 1 - low-pass filters */
	const char* wName = "Image!"; // window name    
	const char* wNameLP = "Lowpass filtered image!"; // window name    
	const char* wNameHP = "Highpass filtered image!"; // window name    
	cvNamedWindow(wName, 0); // create simple window 
	cvNamedWindow(wNameLP, 0); // create simple window 
	cvNamedWindow(wNameHP, 0); // create simple window 
	//int i, j;

	//IplImage* img1 = cvLoadImage("C:/Users/30330/Documents/Spassere/Project1/moment_test2.png");
	IplImage* img = cvLoadImage("C:/Users/30330/Documents/Exercises/CC_640_480.jpg");
	IplImage* imgGrey = 0, *imgGreyLP = 0, *imgGreyHP = 0;
	imgGrey = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
	imgGreyLP = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);
	imgGreyHP = cvCreateImage(cvSize(img->width, img->height), img->depth, 1);

	cvCvtColor(img, imgGrey, CV_RGB2GRAY);

	double t = (double)cvGetTickCount();

	//for (i = 0; i < (img->width*img->height); i++){//Copy one channel from img to imgGrey.
	//	j = i * 3;
	//	imgGrey->imageData[i] = img->imageData[j];
	//}

	//cvCopyImage(imgGrey, imgGreyLP);

	computeAverageLP(imgGrey, imgGreyLP); // Oour version

	computeHP(imgGrey, imgGreyHP); // Oour version

	//int K[] =
	//{
	//	1, 1, 1,
	//	1, 1, 1,
	//	1, 1, 1
	//};
	//CvMat kernel = cvMat(3, 3, CV_32FC1, K);
	//cvFilter2D(imgGrey, imgGreyLP, &kernel);

		//cvFilter2D(const CvArr* src, CvArr* dst, const CvMat* kernel,
		//	CvPoint anchor CV_DEFAULT(cvPoint(-1, -1)));

	t = ((double)cvGetTickCount() - t) / cvGetTickFrequency(); //

	printf("%x\n", imgGrey->imageData[50717]);

	printf("Time = %f\n", t);
	printf("Freq = %f\n", cvGetTickFrequency());

	cvResizeWindow(wName, imgGrey->width, imgGrey->height);
	cvShowImage(wName, imgGrey);

	cvResizeWindow(wNameLP, imgGreyLP->width, imgGreyLP->height);
	cvShowImage(wNameLP, imgGreyLP);

	cvResizeWindow(wNameHP, imgGreyHP->width, imgGreyHP->height);
	cvShowImage(wNameHP, imgGreyHP);

	printf("N channels = %d \n", imgGrey->nChannels);
	printf("Depth = %d \n", imgGrey->depth);

	cvWaitKey(0);

	cvDestroyAllWindows();

	return 0;
}
