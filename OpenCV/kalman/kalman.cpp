#include <stdio.h>  
#include "cv.h"  
#include "highgui.h"  
int main ()  
{  
    cvNamedWindow("Kalman",1);  
    CvRandState random;//创建随机  
    cvRandInit(&random,0,1,-1,CV_RAND_NORMAL);  
    IplImage * image=cvCreateImage(cvSize(600,450),8,3);  
    CvKalman * kalman=cvCreateKalman(4,2,0);//状态变量4维，x、y坐标和在x、y方向上的速度，测量变量2维，x、y坐标  
  
    CvMat * xK=cvCreateMat(4,1,CV_32FC1);//初始化状态变量，坐标为（40,40），x、y方向初速度分别为10、10  
    xK->data.fl[0]=40.;  
    xK->data.fl[1]=40;  
    xK->data.fl[2]=10;  
    xK->data.fl[3]=10;  
  
    const float F[]={1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1};//初始化传递矩阵 [1  0  1  0]  
                                                      //               [0  1  0  1]  
                                                      //               [0  0  1  0]  
                                                      //               [0  0  0  1]  
    memcpy(kalman->transition_matrix->data.fl,F,sizeof(F));  
  
  
  
    CvMat * wK=cvCreateMat(4,1,CV_32FC1);//过程噪声  
    cvZero(wK);  
  
    CvMat * zK=cvCreateMat(2,1,CV_32FC1);//测量矩阵2维，x、y坐标  
    cvZero(zK);  
  
    CvMat * vK=cvCreateMat(2,1,CV_32FC1);//测量噪声  
    cvZero(vK);  
  
    cvSetIdentity( kalman->measurement_matrix, cvScalarAll(1) );//初始化测量矩阵H=[1  0  0  0]  
                                                                //                [0  1  0  0]  
    cvSetIdentity( kalman->process_noise_cov, cvScalarAll(1e-1) );/*过程噪声____设置适当数值， 
                                                                    增大目标运动的随机性， 
                                                                    但若设置的很大，则系统不能收敛， 
                                                                    即速度越来越快*/  
    cvSetIdentity( kalman->measurement_noise_cov, cvScalarAll(10) );/*观测噪声____故意将观测噪声设置得很大， 
                                                                    使之测量结果和预测结果同样存在误差*/  
    cvSetIdentity( kalman->error_cov_post, cvRealScalar(1) );/*后验误差协方差*/  
    cvRand( &random, kalman->state_post );  
  
    CvMat * mK=cvCreateMat(1,1,CV_32FC1);  //反弹时外加的随机化矩阵  
  
  
    while(1){  
        cvZero( image );  
        cvRectangle(image,cvPoint(30,30),cvPoint(570,420),CV_RGB(255,255,255),2);//绘制目标弹球的“撞击壁”  
        const CvMat * yK=cvKalmanPredict(kalman,0);//计算预测位置  
        cvRandSetRange( &random, 0, sqrt( kalman->measurement_noise_cov->data.fl[0] ), 0 );  
        cvRand( &random, vK );//设置随机的测量误差  
        cvMatMulAdd( kalman->measurement_matrix, xK, vK, zK );//zK=H*xK+vK  
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*xK,float,0,0)),cvRound(CV_MAT_ELEM(*xK,float,1,0))),  
            4,CV_RGB(255,255,255),2);//白圈，真实位置  
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*yK,float,0,0)),cvRound(CV_MAT_ELEM(*yK,float,1,0))),  
            4,CV_RGB(0,255,0),2);//绿圈，预估位置  
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*zK,float,0,0)),cvRound(CV_MAT_ELEM(*zK,float,1,0))),  
            4,CV_RGB(0,0,255),2);//蓝圈，观测位置  
  
        cvRandSetRange(&random,0,sqrt(kalman->process_noise_cov->data.fl[0]),0);  
        cvRand(&random,wK);//设置随机的过程误差  
        cvMatMulAdd(kalman->transition_matrix,xK,wK,xK);//xK=F*xK+wK  
      
        if(cvRound(CV_MAT_ELEM(*xK,float,0,0))<30){  //当撞击到反弹壁时，对应轴方向取反外加随机化  
            cvRandSetRange( &random, 0, sqrt(1e-1), 0 );  
            cvRand( &random, mK );  
            xK->data.fl[2]=10+CV_MAT_ELEM(*mK,float,0,0);  
        }  
        if(cvRound(CV_MAT_ELEM(*xK,float,0,0))>570){  
            cvRandSetRange( &random, 0, sqrt(1e-2), 0 );  
            cvRand( &random, mK );  
            xK->data.fl[2]=-(10+CV_MAT_ELEM(*mK,float,0,0));  
        }  
        if(cvRound(CV_MAT_ELEM(*xK,float,1,0))<30){  
            cvRandSetRange( &random, 0, sqrt(1e-1), 0 );  
            cvRand( &random, mK );  
            xK->data.fl[3]=10+CV_MAT_ELEM(*mK,float,0,0);  
        }  
        if(cvRound(CV_MAT_ELEM(*xK,float,1,0))>420){  
            cvRandSetRange( &random, 0, sqrt(1e-3), 0 );  
            cvRand( &random, mK );  
            xK->data.fl[3]=-(10+CV_MAT_ELEM(*mK,float,0,0));  
        }  
  
        printf("%f_____%f\n",xK->data.fl[2],xK->data.fl[3]);  
  
  
        cvShowImage("Kalman",image);  
  
        cvKalmanCorrect( kalman, zK );  
  
  
        if(cvWaitKey(100)=='e'){  
            break;  
        }  
    }  
  
      
    cvReleaseImage(&image);/*释放图像*/  
    cvDestroyAllWindows();  
}  