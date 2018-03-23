#include"highgui.h"  
#include"cv.h"  
#include<stdio.h>  
int main(int argc,char**argv)  
{  
    //变量声明  
    IplImage* src=0,*dst=0;  
	float k[9]={1.f/16,2.f/16,1.f/16,2.f/16,4.f/16,2.f/16,1.f/16,2.f/16,1.f/16};
    CvMat kernel=cvMat(3,3,CV_32FC1,k);
    //载入图像  
    src =cvLoadImage("test.jpg"); 
	dst=cvCloneImage(src);
    //创建窗口  
    cvNamedWindow("src",0);  
	cvShowImage("src",src);
    //初始化滤波器  
    //滤波处理  
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));  
    cvNamedWindow("filtering",0);  
	cvShowImage("filtering",dst);  
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
    return 0;  
} 