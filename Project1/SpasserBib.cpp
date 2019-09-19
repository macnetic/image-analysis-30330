#include "SpasserBib.h"

IplImage* histogram(IplImage* img, uint8_t colSel){
	unsigned char value = 0; // index value for the histogram (not really needed) 
	unsigned long histogram[256]; // histogram array - remember to set to zero initially 
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

	width = img->width;
	height = img->height;
	channel = (img->imageData);


	int k = 256;
	while (k-- > 0)
		histogram[k] = 0; // reset histogram entry 

	for (i = colSel; i < width*height * 3; i += 3) {
		value = channel[i];
		histogram[value] += 1;
	}

	IplImage* imgHist = cvCreateImage(histSize, IPL_DEPTH_8U, 1);
	//cvRectangle(img1, P1, P2, Col, 1, 8, 0);
	//cvLine(img1, P1, P2, Col, 1, 8, 0);

	//Find max:
	unsigned long max = 0;
	for (i = 0; i < 256; i++) {
		if (histogram[i] > max){
			max = histogram[i];
		}
	}

	for (j = 0; j < 256; j++) {
		P2.y = P1.y - histogram[j]* histSize.height/max;
		cvLine(imgHist, P1, P2, Col, 1, 8, 0);
		P1.x++;
		P2.x++;
	}
	return imgHist;
}