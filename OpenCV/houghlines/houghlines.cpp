#include"cv.h"  
#include"highgui.h"  
#include<math.h>  
  
int main(void)  
{  
    IplImage *src = cvLoadImage("test.jpg",0);  
    if (src)  
    {  
        IplImage *dst = cvCreateImage(cvGetSize(src),8,1);  
        IplImage *color_dst = cvCreateImage(cvGetSize(src),8,3);  
        CvMemStorage *storage = cvCreateMemStorage();  
        CvSeq *lines = 0;  
        int i ;  
        cvCanny(src,dst,50,200,3);  
      
        cvCvtColor(dst,color_dst,CV_GRAY2BGR);  
    #if 0  
        lines = cvHoughLines2(dst,storage,CV_HOUGH_STANDARD,1,CV_PI/180,150,0,0);  
          
        for (i=0;i<lines->total;i++)  
        {  
            float *line = (float *)cvGetSeqElem(lines,i);  
            float rho = line[0];  
            float theta = line[1];  
            CvPoint pt1,pt2;  
            double a = cos(theta);  
            double b = sin(theta);  
            if (fabs(a)<0.001)  
            {  
                pt1.x = pt2.x = cvRound(rho);  
                pt1.y = 0;  
                pt2.y = color_dst->height;  
            }  
            else if (fabs(b)<0.001)  
            {  
                pt1.y = pt2.y = cvRound(rho);  
                pt1.x = 0;  
                pt2.x = color_dst->width;  
            }  
            else  
            {  
                pt1.x = 0;  
                pt1.y = cvRound(rho/b);  
                pt2.x = cvRound(rho/a);  
                pt2.y = 0;  
            }  
  
            cvLine(color_dst,pt1,pt2,CV_RGB(255,0,0),1,8);  
        }  
    #else  
        lines = cvHoughLines2(dst,storage,CV_HOUGH_PROBABILISTIC,1,CV_PI/180,80,30,5);  
        for (i=0;i<lines->total;i++)  
        {  
            CvPoint *line = (CvPoint *)cvGetSeqElem(lines,i);  
            cvLine(color_dst,line[0],line[1],CV_RGB(255,0,0),1,CV_AA);  
        }  
    #endif  
        cvNamedWindow("Source");  
        cvShowImage("Source",src);  
  
        cvNamedWindow("Hough");  
        cvShowImage("Hough",color_dst);  
  
        cvWaitKey(0);  
  
        cvReleaseImage(&src);  
        cvReleaseImage(&dst);  
        cvReleaseImage(&color_dst);  
        cvReleaseMemStorage(&storage);  
          
        cvDestroyAllWindows();  
          
        return 1;  
    }  
}  