#include "cv.h"
#include "highgui.h"
#include "math.h"
int main(int argc, char** argv)
{
	IplImage* src=0;
	char*filename="left.jpg";
    src=cvLoadImage(filename);
	IplImage* dst=cvCloneImage(src);
	 int  delta = 1;
     int  angle = 0;
     int opt = 1;   // 1： 旋转加缩放
                    // 0:  仅仅旋转
     double factor;
     cvNamedWindow( "src", 1 );
     cvShowImage( "src", src );
     for(;;)
    {
		float m[6];
        CvMat M = cvMat( 2, 3, CV_32F, m );
        int w = src->width;
        int h = src->height;
        if(opt) // 旋转加缩放
			factor = (cos(angle*CV_PI/180.) + 1.0)*2;
            else //  仅仅旋转
				factor = 1;
		m[0] = (float)(factor*cos(-angle*2*CV_PI/180.));
        m[1] = (float)(factor*sin(-angle*2*CV_PI/180.));
        m[3] = -m[1];
        m[4] = m[0];
        // 将旋转中心移至图像中间
        m[2] = w*0.5f; 
        m[5] = h*0.5f; 
        cvGetQuadrangleSubPix( src, dst, &M);
        cvNamedWindow( "dst", 1 );
        cvShowImage( "dst", dst );
        if( cvWaitKey(1) == 27 )
			break;
        angle =(int) (angle + delta) % 360;
	 }
   return 0;
}