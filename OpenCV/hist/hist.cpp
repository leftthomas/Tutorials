#include "cv.h" 
#include "highgui.h" 
#include <stdio.h> 
#include <ctype.h> 

int main( )  
{  
    IplImage * src= cvLoadImage("test.jpg");  
    IplImage* gray_plane = cvCreateImage(cvGetSize(src),8,1);  
    cvCvtColor(src,gray_plane,CV_BGR2GRAY);  
  
    int hist_size = 256;    //直方图尺寸  
    int hist_height = 256;  
    float range[] = {0,255};  //灰度级的范围  
    float* ranges[]={range};  
    //创建一维直方图，统计图像在[0 255]像素的均匀分布  
    CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
    //计算灰度图像的一维直方图  
    cvCalcHist(&gray_plane,gray_hist,0,0);  
    //归一化直方图  
    cvNormalizeHist(gray_hist,1.0);  
  
    int scale = 2;  
    //创建一张一维直方图的“图”，横坐标为灰度级，纵坐标为像素个数（*scale）  
    IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale,hist_height),8,3);  
    cvZero(hist_image);  
    //统计直方图中的最大直方块  
    float max_value = 0;  
    cvGetMinMaxHistValue(gray_hist, 0,&max_value,0,0);  
      
    //分别将每个直方块的值绘制到图中  
    for(int i=0;i<hist_size;i++)  
    {  
        float bin_val = cvQueryHistValue_1D(gray_hist,i); //像素i的概率  
        int intensity = cvRound(bin_val*hist_height/max_value);  //要绘制的高度  
        cvRectangle(hist_image,  
            cvPoint(i*scale,hist_height-1),  
            cvPoint((i+1)*scale - 1, hist_height - intensity),  
            CV_RGB(255,255,255));    
    }  
    cvNamedWindow( "GraySource", 1 );  
    cvShowImage("GraySource",gray_plane);  
    cvNamedWindow( "H-S Histogram", 1 );  
    cvShowImage( "H-S Histogram", hist_image );  
  
    cvWaitKey(0);  
}  