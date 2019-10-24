#include <stdio.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#include "SpasserBib.h"
#include <stdlib.h>

#define MAX_RIM 1000

void computeGradientMag(IplImage* img, IplImage* imgResult) {
	int16_t n = 1;

	int16_t G_x[3][3] =
	{
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	};

	int16_t G_y[3][3] =
	{
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};

	int32_t x, y;
	int16_t k, l;
	int32_t idx; //

	int32_t temp_x;
	int32_t temp_y;
	int32_t temp_mag;

	for (y = n; y < img->height - n; y++) {
		for (x = n; x < img->width - n; x++) {
			// Loop over kernel
			temp_x = 0;
			temp_y = 0;
			for (l = -n; l <= n; l++) {
				for (k = -n; k <= n; k++) {
					idx = img->width * (y - l) + (x - k);

					temp_x += (uint8_t)img->imageData[idx] * G_x[l + n][k + n];
					temp_y += (uint8_t)img->imageData[idx] * G_y[l + n][k + n];
				}
			}
			idx = img->width*y + x;

			temp_mag = sqrt(pow(temp_x, 2) + pow(temp_y, 2));

			if (temp_mag < 0)
				temp_mag = 0;
			else if (temp_mag > 255)
				temp_mag = 255;
			imgResult->imageData[idx] = (uint8_t)temp_mag;
		}
	}
}

void threshold(IplImage* src, IplImage* dst, int threshold, int invert = 0)
{
	for (int i = 0; i < src->width * src->height * src->nChannels; i++)
	{
		if ((uint8_t)src->imageData[i] > threshold) // Remember to typecast, or weird things happen!
		{
			dst->imageData[i] = 255;
		}
		else
		{
			dst->imageData[i] = 0;
		}

		// Invert binary image
		if (invert)
			dst->imageData[i] = 255 - dst->imageData[i];
	}
}

//void contourSearch()
//{
//	unsigned char *pic; // placeholder for image data 
//	int rimx[MAX_RAND], rimy[MAX_RAND];
//	int newpos, local_tresh, draw_type;
//	draw_type = 0;
//	newpos = pos; // pos equals the starting position in the image ( = y*Width+x) 
//
//	while (newpos >= 0L && newpos < end)
//	{
//		rimx[count] = newpos % B; // save current position in list 
//		rimy[count] = newpos / B;
//		count++;
//		draw_type = (draw_type + 6) % 8; // Select next search direction 
//
//		switch (draw_type) {
//			case 0: if (pic[newpos + 1] > local_tresh) {newpos += 1; draw_type = 0; break; }
//			case 1: if (pic[newpos + B + 1] > local_tresh) { newpos += B + 1; draw_type = 1; break; }
//			case 2: if (pic[newpos + B] > local_tresh) { newpos += B; draw_type = 2; break; }
//			case 3: if (pic[newpos + B - 1] > local_tresh) { newpos += B-1; draw_type = 3; break; }
//			case 4: if (pic[newpos - 1] > local_tresh) { newpos -= 1; draw_type = 4; break; }
//			case 5: if (pic[newpos - B - 1] > local_tresh) { newpos = B + 1; draw_type = 5; break; }
//			case 6: if (pic[newpos - B] > local_tresh) { newpos -= B; draw_type = 6; break; }
//			case 7: if (pic[newpos - B + 1] > local_tresh) { newpos -= B-1; draw_type = 7; break; }
//
//			case 8: if (pic[newpos + 1] > local_tresh) { newpos += 1; draw_type = 0; break; }
//			case 9: if (pic[newpos + B + 1] > local_tresh) { newpos += B + 1; draw_type = 1; break; }
//			case 10: if (pic[newpos + B] > local_tresh) { newpos += B; draw_type = 2; break; }
//			case 11: if (pic[newpos + B - 1] > local_tresh) { newpos += B-1; draw_type = 3; break; }
//			case 12: if (pic[newpos - 1] > local_tresh) { newpos -= 1; draw_type = 4; break; }
//			case 13: if (pic[newpos - B - 1] > local_tresh) { newpos = B + 1; draw_type = 5; break; }
//			case 14: if (pic[newpos - B] > local_tresh) { newpos -= B; draw_type = 6; break; }
//		}
//
//		// If we are back at the beginning, we declare success 
//		if (newpos == pos) break;
//
//		// Abort if the contour is too complex. 
//		if (count >= MAX_RAND) break;
//	}
//}

int NOTmain4(int argc, char* argv[])
{
	const char* wName = "Greyscale"; // window name    
	//const char* wNameSmooth = "Median smoothed";
	//const char* wNameGradient = "Gradient magnitude"; // window name  
	//const char* wNameThreshold = "Thresholded gradient magnitude"; // window name  

	cvNamedWindow(wName, 0); // create simple window 
	//cvNamedWindow(wNameGradient, 0); // create simple window

	IplImage* img_original = 0, *img_grey = 0, *img_gradient = 0, *img_threshold = 0, *img_smooth = 0;

	const char* filepath;
	//filepath = "C:/Users/30330/Documents/Exercises/CC_640_480.jpg";
	//filepath = "C:/Users/30330/Documents/Exercises/ariane5_1b.jpg";
	filepath = "C:/Users/30330/Documents/Spassere/Project1/contour_test.png"; 
	img_original = cvLoadImage(filepath);

	img_grey = cvCreateImage(cvSize(img_original->width, img_original->height), IPL_DEPTH_8U, 1);
	//img_smooth = cvCreateImage(cvSize(img_original->width, img_original->height), IPL_DEPTH_8U, 1);
	//img_gradient = cvCreateImage(cvSize(img_original->width, img_original->height), IPL_DEPTH_8U, 1);
	//img_threshold = cvCreateImage(cvSize(img_original->width, img_original->height), IPL_DEPTH_8U, 1);

	cvCvtColor(img_original, img_grey, CV_RGB2GRAY);

	//computeMedian(img_grey, img_smooth);

	//computeGradientMag(img_smooth, img_gradient);

	//threshold(img_gradient, img_threshold, 100, 1);

	//cvResizeWindow(wName, img_grey->width, img_grey->height);
	//cvResizeWindow(wNameSmooth, img_smooth->width, img_smooth->height);
	//cvResizeWindow(wNameGradient, img_gradient->width, img_gradient->height);
	//cvResizeWindow(wNameThreshold, img_threshold->width, img_threshold->height);

	cvShowImage(wName, img_grey);
	//cvShowImage(wNameSmooth, img_smooth);
	//cvShowImage(wNameGradient, img_gradient);
	//cvShowImage(wNameThreshold, img_threshold);

	/************************ Contour search!  ********************************/

	//const char* wName = "Greyscale"; // window name

	//IplImage* img_contour = 0;

	//const char* filepath;
	//filepath = "C:/Users/30330/Documents/Spassere/Project1/contour_test.png";
	//img_contour = cvLoadImage(filepath);


	unsigned char *pic = (unsigned char *) img_grey->imageData; // placeholder for image data
	int B = img_grey->width;
	int end = img_grey->width*img_grey->height;

	int rimx[MAX_RIM], rimy[MAX_RIM];
	//int pos = 259+B*192, newpos, local_tresh = 128, draw_type, count=0;
	int pos = 9 + B * 7, newpos, local_tresh = 128, draw_type, count = 0;
	draw_type = 0;
	newpos = pos; // pos equals the starting position in the image ( = y*Width+x) 

	/* Print a white value */
	printf("White pixel = %d \n", (uint8_t)pic[newpos]);

	while (newpos >= 0L && newpos < end)
	{
		rimx[count] = newpos % B; // save current position in list 
		rimy[count] = newpos / B;
		count++;
		draw_type = (draw_type + 6) % 8; // Select next search direction 

		switch (draw_type) {
		case 0: if (pic[newpos + 1] > local_tresh) { newpos += 1; draw_type = 0; break; }
		case 1: if (pic[newpos + B + 1] > local_tresh) { newpos += B + 1; draw_type = 1; break; }
		case 2: if (pic[newpos + B] > local_tresh) { newpos += B; draw_type = 2; break; }
		case 3: if (pic[newpos + B - 1] > local_tresh) { newpos += B - 1; draw_type = 3; break; }
		case 4: if (pic[newpos - 1] > local_tresh) { newpos -= 1; draw_type = 4; break; }
		case 5: if (pic[newpos - B - 1] > local_tresh) { newpos = B + 1; draw_type = 5; break; }
		case 6: if (pic[newpos - B] > local_tresh) { newpos -= B; draw_type = 6; break; }
		case 7: if (pic[newpos - B + 1] > local_tresh) { newpos -= B - 1; draw_type = 7; break; }

		case 8: if (pic[newpos + 1] > local_tresh) { newpos += 1; draw_type = 0; break; }
		case 9: if (pic[newpos + B + 1] > local_tresh) { newpos += B + 1; draw_type = 1; break; }
		case 10: if (pic[newpos + B] > local_tresh) { newpos += B; draw_type = 2; break; }
		case 11: if (pic[newpos + B - 1] > local_tresh) { newpos += B - 1; draw_type = 3; break; }
		case 12: if (pic[newpos - 1] > local_tresh) { newpos -= 1; draw_type = 4; break; }
		case 13: if (pic[newpos - B - 1] > local_tresh) { newpos = B + 1; draw_type = 5; break; }
		case 14: if (pic[newpos - B] > local_tresh) { newpos -= B; draw_type = 6; break; }
		//default: newpos += 1; break;
		}

		// If we are back at the beginning, we declare success 
		if (newpos == pos) {
			printf("Newpos == pos \n");
			break;
		}
		// Abort if the contour is too complex. 
		if (count >= MAX_RIM) break;
	}



	printf("Count = %d\n", count);



	cvWaitKey(0);

	cvDestroyAllWindows();

	return 0;
}
