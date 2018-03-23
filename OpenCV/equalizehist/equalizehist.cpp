#include "highgui.h"  
#include "cv.h"  
  
int main(int argc, char** argv)  
{  
    int i;  
    IplImage* src = cvLoadImage("test.jpg", 1 );  
    IplImage* imgChannel[4] = { 0, 0, 0, 0 };  
    IplImage* dst = cvCreateImage( cvGetSize( src ), IPL_DEPTH_8U, 3 );  
  
    if( src )  
    {  
        for( i = 0; i < src -> nChannels; i++ )  
        {  
            imgChannel[i] = cvCreateImage( cvGetSize( src ), IPL_DEPTH_8U, 1 );  //要求单通道图像才能直方图均衡化  
        }  
        //通道分离  
        cvSplit( src, imgChannel[0], imgChannel[1], imgChannel[2], imgChannel[3] );//BGRA  
        for( i = 0; i < dst -> nChannels; i++ )  
        {  
            //直方图均衡化，原始图像和目标图像必须是单通道  
            cvEqualizeHist( imgChannel[i], imgChannel[i] );  
        }  
  
        //通道组合  
        cvMerge( imgChannel[0], imgChannel[1], imgChannel[2], imgChannel[3], dst );  
        cvNamedWindow( "src", 1 );  
        cvShowImage( "src", src );  
        cvNamedWindow( "Equalize", 1 );  
        cvShowImage( "Equalize", dst );  
  
        cvWaitKey(0);  
        //释放资源  
        for( i = 0; i < src -> nChannels; i++ )  
        {  
            if( imgChannel[i] )  
            {  
                cvReleaseImage( &imgChannel[i] );  
                //imgChannel[i] = 0;  
            }  
        }  
        cvReleaseImage( &dst );  
    }  
  
    return 0;  
}  