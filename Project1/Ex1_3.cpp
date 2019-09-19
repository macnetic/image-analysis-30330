// opencv_helloworld.cpp : Defines the entry point for the console application. 

#include <stdio.h> 
#include "cv.h" 
#include "cxcore.h" 
#include "highgui.h" 
#include <conio.h>
#include "SpasserBib.h"

int main(int argc, char* argv[]) {
	const char* wName = "Image!"; // window name    
	const char* wNameHist = "Histogram"; // window name
	cvNamedWindow(wNameHist, 0);
	cvNamedWindow(wName, 0); // create simple window 


	CvCapture *capture = 0;

	double capProp = 0;

	IplImage *frame, *frame_copy = 0, *imgHist = 0; // pointers to images


	capture = cvCaptureFromCAM(0); // initialize capture device 

	//cvGetCaptureProperty(capture, )
	//cvSetCaptureProperty(capture, CV_CAP_PROP_BRIGHTNESS, 255.0);
	



	if (capture){
		for (;;) {
			if (!cvGrabFrame(capture))
				break;
			frame = cvRetrieveFrame(capture);
			//frame = cvLoadImage("C:/Users/30330/Documents/Spassere/Project1/RGB_test.png"); //Only for testing purpose!!!

			if (!frame)
				break;
			if (!frame_copy) {
				printf("Frame settings:\n Width: %d\n Height: %d\n", frame->width, frame->height);
				frame_copy = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, frame->nChannels);
				cvResizeWindow(wName, frame->width, frame->height);
			}
			if (frame->origin == IPL_ORIGIN_TL) //Test if origo is top-left, if not, flip below.
				cvCopy(frame, frame_copy, 0);
			else
				cvFlip(frame, frame_copy, 0);
			// Extract a color channel
			enum BGR_channel { B, G, R };
			int channel_offset = B;
			IplImage* channel = cvCreateImage(cvSize(frame_copy->width, frame_copy->height), IPL_DEPTH_8U, 1);

			for (int i = 0; i < frame_copy->width * frame_copy->height; i++)
			{
				channel->imageData[i] = frame_copy->imageData[i * 3 + channel_offset];
			}

			//--------------------
			cvShowImage(wName, channel);

			imgHist = histogram(frame_copy, channel_offset);
			cvShowImage(wNameHist, imgHist);

			while (1) {
				if (cvWaitKey(0) > 0)
					break;
			}
			
			if (cvWaitKey(100) > 0)
				break;
			
		}
	}
	
	cvReleaseImage(&frame_copy);
	//cvDestroyWindow("Hello World");
	cvDestroyAllWindows();
	
	

	return 0;
}