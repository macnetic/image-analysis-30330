#include <stdio.h>
#include <math.h>
#include "cv.h"
#include "highgui.h"
#include "SpasserBib.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	const char* wLeft = "Left"; // window name 
	const char* wRight = "Right"; // window name 
	//cvNamedWindow(wLeft, 0); // create simple window 
	//cvNamedWindow(wRight, 0); // create simple window 


	IplImage* img_Left = 0, *img_Right = 0, *img_Right_G =0, *img_Left_G = 0, *img_LeftRegion = 0, *img_RightRegion = 0;
	img_Left = cvLoadImage("C:/Users/30330/Documents/Exercises/PIC1_L.png");
	img_Right = cvLoadImage("C:/Users/30330/Documents/Exercises/PIC1_R.png");
	//img_Right = cvLoadImage("C:/Users/30330/Documents/Exercises/PIC1_L.png"); //Test that equals the two images. Has to return atleast one 0 value!!!

	img_Left_G = cvCreateImage(cvSize(img_Left->width, img_Left->height), IPL_DEPTH_8U, 1);
	img_Right_G = cvCreateImage(cvSize(img_Right->width, img_Right->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img_Left, img_Left_G, CV_RGB2GRAY);
	cvCvtColor(img_Right, img_Right_G, CV_RGB2GRAY);

	/******** Before function: ********/

	//Corr_Region_Type Corr_Region1;
	//uint16_t xL = 386, yL = 125;
	//initCorrRegion(&Corr_Region1, xL, yL, 10, 10);

	//uint32_t idxL = 0, idxR = 0;
	//uint8_t runFlag = 1, Region_Count = 0;
	//uint64_t threshold = 1400; // MAGIC NUMBER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	////uint64_t Region_Count_TEST = 10000000;
	//

	//for (uint16_t y = 0; (y < img_Right_G->height - Corr_Region1.height) && (Region_Count < MAX_AREAS ); y++) {
	//	for (uint16_t x = 0; (x < img_Right_G->width - Corr_Region1.width) && (Region_Count < MAX_AREAS); x++) {
	//		for (uint8_t l = 0; l < Corr_Region1.height; l++) {
	//			for (uint8_t k = 0; k < Corr_Region1.width; k++) {
	//				idxL = (Corr_Region1.xL + img_Left_G->width * Corr_Region1.yL) + (k + l * img_Right_G->width);
	//				idxR = (x + img_Right_G->width * y) + (k + l * img_Right_G->width);

	//				Corr_Region1.corrMeas[Region_Count] += abs(img_Left_G->imageData[idxL] - img_Right_G->imageData[idxR]);


	//			}
	//		}
	//		/* TEST CODE*/
	//		//if (Corr_Region1.corrMeas[Region_Count] < Region_Count_TEST) {
	//		//	Region_Count_TEST = Corr_Region1.corrMeas[Region_Count];
	//		//	printf("Region_Count_TEST = %ld \n", Region_Count_TEST);
	//		//}

	//		if (Corr_Region1.corrMeas[Region_Count] < threshold) {
	//			Corr_Region1.xR[Region_Count] = x;
	//			Corr_Region1.yR[Region_Count] = y;
	//			printf("x = %d \n", Corr_Region1.xR[Region_Count]);
	//			printf("y = %d \n", Corr_Region1.yR[Region_Count]);
	//			printf("m = %d \n", Corr_Region1.corrMeas[Region_Count]);
	//			Region_Count++;
	//		}
	//		else {
	//			Corr_Region1.corrMeas[Region_Count] = 0;
	//		}

	//	}
	//}

	/***********With function **************/
	//Does currently not work. Does not find correct locations. Looks like X-dir is not explored properly.
	uint64_t threshold = 1350;
	Corr_Region_Type Corr_Region1, Corr_Region2, Corr_Region3;
	initCorrRegion(&Corr_Region1, 386, 125, 10, 10);
	initCorrRegion(&Corr_Region2, 116, 234, 10, 10);
	initCorrRegion(&Corr_Region3, 270, 186, 10, 10);

	CorrSearch(&Corr_Region1, img_Left_G, img_Right_G,  threshold);
	//CorrSearch(&Corr_Region2, img_Left_G, img_Right_G, threshold);
	//CorrSearch(&Corr_Region3, img_Left_G, img_Right_G, threshold);

	cvShowImage(wLeft, img_Left_G);
	cvShowImage(wRight, img_Right_G);

	cvWaitKey(0);

	cvDestroyAllWindows();


	return 0;
}
