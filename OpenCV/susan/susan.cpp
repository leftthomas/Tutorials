  //可以检测眼睛动态匹配轮廓的susan角点检测算法，准确率98   
#include<math.h>  
#include<stdlib.h>  
#include<stdio.h>  
#include "cv.h"  
#include "highgui.h"  
int main( int argc, char** argv )  
{  
    int height ,width ,step ,channels ;  
    int i,j,k,same ,max,min,sum;  
    float thresh;  
    uchar *data0,*data1 ;  
    IplImage* Img, *nimg;
    //载入图像  
    Img=cvLoadImage( "susan.jpg",0);  
    cvNamedWindow( "Images", 2); //创建窗口  
    cvShowImage( "Images", Img ); //显示图像  
    nimg=cvCreateImage(cvGetSize(Img),8,1);  
    height=Img->height;  
    width=Img->width;  
    step=Img->widthStep/sizeof(uchar);  
    channels=Img->nChannels;  
    data0=(uchar*)Img->imageData;  
    data1=(uchar*)nimg->imageData;  
    printf("Processing a %d X %d image with %d channels\n",width,height,channels);  
    int OffSetX[37] =   
    { 
		-1, 0, 1,  
        -2,-1, 0, 1, 2,  
        -3,-2,-1, 0, 1, 2, 3,  
        -3,-2,-1, 0, 1, 2, 3,  
        -3,-2,-1, 0, 1, 2, 3,  
        -2,-1, 0, 1, 2,  
        -1, 0, 1
	};  
    int OffSetY[37] =   
    {   
        -3,-3,-3,  
        -2,-2,-2,-2,-2,  
        -1,-1,-1,-1,-1,-1,-1,  
        0, 0, 0, 0, 0, 0, 0,  
        1, 1, 1, 1, 1, 1, 1,  
        2, 2, 2, 2, 2,  
        3, 3, 3   
    };  
    max = min = data0[0];  
    for(i=3;i<height-3;i++)  
        for(j=3;j<width-3;j++)  
        {  
            same =0;  
            sum = 0;  
            for(k=0;k<37;k++)  
            {  
                sum+=data0[(i+OffSetY[k])*step+(j+OffSetX[k])];  
                thresh = (float)sum/37;  
                float data_fabs;  
                data_fabs= (float)(data0[(i+OffSetY[k])*step+(j+OffSetX[k])]-data0[i*step+j]);  
                if(fabs( data_fabs)<=thresh)  
                    same++;  
            }  
            if(same<18)  
                nimg->imageData[i*step+j] = 255;  
            else  
                nimg->imageData[i*step+j]  = 0;  
            printf("same = %d\n", same);  
        }  
        cvNamedWindow( "Image", 2); //创建窗口  
        cvShowImage( "Image", nimg ); //显示图像  
        cvWaitKey(0); //等待按键  
        cvDestroyWindow( "Image" );//销毁窗口  
        cvReleaseImage( &Img ); //释放图像  
        cvReleaseImage( &nimg );  
        return 0;  
}  