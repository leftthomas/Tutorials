#include"cv.h"     
#include"highgui.h"     
 
int main()    
{    
    IplImage* src = cvLoadImage ("test.jpg", 1);    
    IplImage* dst = cvCreateImage (cvGetSize(src), IPL_DEPTH_32F, 1);    
    IplImage* canny = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);    
  
    cvCvtColor (src, canny, CV_RGB2GRAY);    
    cvCanny (canny, canny, 100, 200, 3);    
    cvDistTransform (canny, dst, CV_DIST_WELSCH, 3);    
  
    cvNamedWindow ("src", 1);    
    cvShowImage ("src", src);    
    cvNamedWindow ("dist", 1);    
    cvShowImage ("dist", canny);    
  
    cvWaitKey (0);    
  
    cvReleaseImage (&src);    
    cvReleaseImage (&canny);    
    cvReleaseImage (&dst);    
  
    return 0;    
}    