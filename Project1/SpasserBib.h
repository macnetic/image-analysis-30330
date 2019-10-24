#ifndef SPASSERBIB_H
#define SPASSERBIB_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h> 
#include <stdint.h>
#include "cv.h" 
#include "cxcore.h" 
#include "highgui.h" 
#include <conio.h> 
#include <stdlib.h>

/* Defines -----------------------------------------------------------------*/
#define MAX_AREAS 255 //Note should fit in uint8_t!!

typedef struct Corr_Region_Type
{
	uint16_t xL, yL;
	uint16_t xR[MAX_AREAS], yR[MAX_AREAS]; //Defined from upper left corner!
	uint8_t width, height;
	uint64_t corrMeas[MAX_AREAS];
} Corr_Region_Type;


IplImage* histogram(IplImage* img, uint8_t colSel);

int cmpfunc(const void * a, const void * b);

void computeMedian(IplImage* img, IplImage* imgResult);

void initCorrRegion(Corr_Region_Type* CorrRegion, uint16_t xL, uint16_t yL, uint8_t width, uint8_t height);
void CorrSearch(Corr_Region_Type* Corr_Region, IplImage* img_Left_G, IplImage* img_Right_G, uint64_t threshold);
#endif /* SPASSERBIB_H */
