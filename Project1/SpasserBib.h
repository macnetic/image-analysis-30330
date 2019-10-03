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



IplImage* histogram(IplImage* img, uint8_t colSel);

int cmpfunc(const void * a, const void * b);

void computeMedian(IplImage* img, IplImage* imgResult);

#endif /* SPASSERBIB_H */
