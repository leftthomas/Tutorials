#include"cv.h"  
#include"highgui.h"  
#include<stdlib.h>  

#define ARRAY 0  
  
int main()  
{  
    IplImage* img = cvCreateImage (cvSize(500, 500), 8, 3);  
    cvNamedWindow ("hull", 1);  
  
#if ! ARRAY  
    CvMemStorage* storage = cvCreateMemStorage (0);  
#endif  
    int i;  
    int contour = rand() % 100 + 1;  
    int hullcontour;  
    CvPoint pt0;  
#if ! ARRAY  
    CvSeq* ptseq = cvCreateSeq (CV_SEQ_KIND_GENERIC | CV_32SC2, sizeof(CvContour), sizeof(CvPoint), storage);  
    CvSeq* hull;  
    for (i = 0; i < contour; i++)  
    {  
        pt0.x = rand() % (img->width / 2) + img->width / 4;  
        pt0.y = rand() % (img->height / 2) + img->height / 4;  
        cvSeqPush (ptseq, &pt0);  
    }  
    hull = cvConvexHull2 (ptseq, 0, CV_CLOCKWISE, 0);  
    /*hull = cvConvexHull2 (ptseq, 0, CV_CLOCKWISE, 1);*/  
    hullcontour = hull->total;  
#else  
    CvPoint* points = (CvPoint*)malloc(contour * sizeof(points[0]));  
    int* hull = (int*)malloc(contour * sizeof(hull[0]));  
    CvMat point_mat = cvMat (1, contour, CV_32SC2, points);  
    CvMat hull_mat = cvMat (1, contour, CV_32SC1, hull);  
    for (i = 0; i < contour; i++)  
    {  
        pt0.x = rand() % (img->width / 2) + img->width / 4;  
        pt0.y = rand() % (img->height / 2) + img->height / 4;  
        points[i] = pt0;  
    }  
    cvConvexHull2 (&point_mat, &hull_mat, CV_CLOCKWISE, 0);  
    hullcontour = hull_mat.cols;  
#endif  
    cvZero (img);  
    for (i = 0; i < contour; i++)  
    {  
#if ! ARRAY  
        pt0 = * CV_GET_SEQ_ELEM(CvPoint, ptseq, i);  
        /*pt0 = ** CV_GET_SEQ_ELEM(CvPoint*, ptseq, i);*/  
#else  
        pt0 = points[i];  
#endif  
        cvCircle (img, pt0, 2, CV_RGB(255, 0, 0), CV_FILLED);  
    }  
#if ! ARRAY  
    pt0 = ** CV_GET_SEQ_ELEM(CvPoint*, hull, hullcontour - 1);  
    /*pt0 = * CV_GET_SEQ_ELEM(CvPoint, hull, hullcontour - 1);*/  
#else  
    pt0 = points[hull[hullcontour - 1]];  
#endif  
  
    for (i = 0; i < hullcontour; i++)  
    {  
#if ! ARRAY  
        CvPoint pt = **CV_GET_SEQ_ELEM(CvPoint*, hull, i);  
        /*CvPoint pt = *CV_GET_SEQ_ELEM(CvPoint, hull, i);*/  
#else  
        CvPoint pt = points[hull[i]];  
#endif  
        cvLine (img, pt0, pt, CV_RGB(255, 0, 0));  
        pt0 = pt;  
    }  
  
    cvShowImage ("hull", img);  
  
    cvWaitKey (0);  
  
#if ! ARRAY   
    cvClearMemStorage (storage);  
#else  
    free (points);  
    free (hull);  
#endif  
  
    return 0;  
}  