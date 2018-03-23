#include<cv.h>  
#include<highgui.h>  
  
int main()  
{  
    IplImage* src = NULL;  
    IplImage* dst = NULL;  
    IplImage* color = NULL;  
  
    src = cvLoadImage ("test.jpg", 1);  
    dst = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);  
    if (src->nChannels == 1)  
    {  
        dst = cvCloneImage (src);  
    }  
    else  
    {  
        cvCvtColor (src, dst, CV_RGB2GRAY);  
    }  
  
    CvMemStorage* storage = cvCreateMemStorage (0);  
    cvSmooth (dst, dst, CV_GAUSSIAN, 5, 5);  
      
    CvSeq* circles = cvHoughCircles (dst, storage, CV_HOUGH_GRADIENT, 2, dst->width /3, 300, 100, 0, 200);  
    color = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 3);  
    cvCvtColor (dst, color, CV_GRAY2RGB);  
    for (int i = 0; i < circles->total; i++)  
    {  
        float* p = (float*)cvGetSeqElem (circles, i);  
        CvPoint pt = cvPoint (cvRound(p[0]), cvRound(p[1]));  
        cvCircle (color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 3, 8, 0);  
    }  
  
    cvNamedWindow ("src", 1);  
    cvShowImage ("src", src);  
    cvNamedWindow ("circle", 1);  
    cvShowImage ("circle", color);  
  
    cvWaitKey (0);  
  
    cvReleaseMemStorage (&storage);  
    cvReleaseImage (&src);  
    cvReleaseImage (&dst);  
    cvReleaseImage (&color);  
  
    return 0;  
}  