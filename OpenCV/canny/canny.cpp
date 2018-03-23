#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
int main( int argc, char** argv )  
{   
    IplImage* img = NULL;  
    IplImage* cannyImg = NULL;  
    char *filename;  
    filename="test.jpg";  
    img=cvLoadImage(filename,1);  
    //载入图像，强制转化为Gray  
    if((img = cvLoadImage(filename, 0)) != 0 )  
    {  
        //为canny边缘图像申请空间  
        cannyImg = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);  
        //canny边缘检测  
        cvCanny(img, cannyImg, 50, 150, 3);  
        //创建窗口  
        cvNamedWindow("src", 1);  
        cvNamedWindow("canny",1);  
        //显示图像  
        cvShowImage( "src", img );  
        cvShowImage( "canny", cannyImg );  
        cvWaitKey(0); //等待按键  
        //销毁窗口  
        cvDestroyWindow( "src" );  
        cvDestroyWindow( "canny" );  
        //释放图像  
        cvReleaseImage( &img );  
        cvReleaseImage( &cannyImg );  
        return 0;  
    }  
    return -1;  
} 