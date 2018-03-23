#include "cv.h"  
#include "highgui.h"  
int main(int argc, char** argv)  
{  
        IplImage *src;  
		src=cvLoadImage("test.jpg",1);
        IplImage* dst = cvCreateImage( cvSize(256,256), 8, 3 );  
        IplImage* src2 = cvCreateImage( cvGetSize(src), 8, 3 );  
        cvLogPolar( src, dst, cvPoint2D32f(src->width/2,src->height/2),  
            40, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );  
        cvLogPolar( dst, src2, cvPoint2D32f(src->width/2,src->height/2),  
            40, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP );  
        cvNamedWindow( "src", 1 );  
        cvShowImage( "src", src );  
        cvNamedWindow( "log-polar", 1 );  
        cvShowImage( "log-polar", dst );  
        cvNamedWindow( "inverse log-polar", 1 );  
        cvShowImage( "inverse log-polar", src2 );  
        cvWaitKey(0);  
} 