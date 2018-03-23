#include "cv.h"
#include "highgui.h"
/*
  src and dst are grayscale, 8-bit images;
  Default input value: 
           [low, high] = [0,1];  X-Direction
           [bottom, top] = [0,1]; Y-Direction
           gamma ;
  if adjust successfully, return 0, otherwise, return non-zero.
*/
int ImageAdjust(IplImage* src, IplImage* dst, 
           double low, double high,   // X方向：low and high are the intensities of src
           double bottom, double top, // Y方向：mapped to bottom and top of dst
           double gamma )
{
if(   low<0 && low>1 && high <0 && high>1&&
bottom<0 && bottom>1 && top<0 && top>1 && low>high)
        return -1;
    double low2 = low*255;
    double high2 = high*255;
    double bottom2 = bottom*255;
    double top2 = top*255;
    double err_in = high2 - low2;
    double err_out = top2 - bottom2;
 
    int x,y;
    double val;
 
    // intensity transform
    for( y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            val = ((uchar*)(src->imageData + src->widthStep*y))[x]; 
            val = pow((val - low2)/err_in, gamma) * err_out + bottom2;
            if(val>255) val=255; if(val<0) val=0; // Make sure src is in the range [low,high]
            ((uchar*)(dst->imageData + dst->widthStep*y))[x] = (uchar) val;
        }
    }
    return 0;
}
 
int main( int argc, char** argv ) 
{
    IplImage *src = 0, *dst = 0;
    src=cvLoadImage("test.jpg");
    
    cvNamedWindow( "src", 1 );
    cvNamedWindow( "result", 1 );
    
    // Image adjust
    dst = cvCloneImage(src);
    // 输入参数 [0,0.5] 和 [0.5,1], gamma=1
if( ImageAdjust( src, dst, 0, 0.5, 0.5, 1, 1)!=0) return -1;
    
    cvShowImage( "src", src );
    cvShowImage( "result", dst );
    cvWaitKey(0);
 
    cvDestroyWindow("src");
    cvDestroyWindow("result");
    cvReleaseImage( &src );
    cvReleaseImage( &dst );
    
    return 0;
}