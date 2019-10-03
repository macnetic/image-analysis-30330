#include "SpasserBib.h"

IplImage* histogram(IplImage* img, uint8_t colSel){
	unsigned char value = 0; // index value for the histogram (not really needed) 
	long histogram[256]; // histogram array - remember to set to zero initially 
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
	long max = 0;
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

int cmpfunc(const void * a, const void * b) {
	return (*(uint8_t*)a - *(uint8_t*)b);
}

void computeMedian(IplImage* img, IplImage* imgResult) {
	uint8_t n = 1;

	int32_t x, y;
	int16_t k, l;
	int32_t idx;
	uint8_t vectorIdx;
	uint8_t filterSize = (2 * n + 1)*(2 * n + 1);

	uint8_t ValueVect[9]; //NOTE! THe number is filterSize, i.e. filterSize = (2 * n + 1)*(2 * n + 1);

	for (y = n; y < img->height - n; y++) {
		for (x = n; x < img->width - n; x++) {
			vectorIdx = 0;
			for (l = -n; l <= n; l++) {
				for (k = -n; k <= n; k++) {
					idx = img->width * (y - l) + (x - k);

					ValueVect[vectorIdx] = ((uint8_t)img->imageData[idx]);
					vectorIdx++;
				}
			}

			qsort(ValueVect, filterSize, sizeof(uint8_t), cmpfunc);

			idx = img->width*y + x;

			imgResult->imageData[idx] = ValueVect[filterSize / 2]; //(filterSize/2) Gives middle of odd vector
		}
	}
}