
// DesignView.cpp : CDesignView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Design.h"
#endif

#include "DesignDoc.h"
#include "DesignView.h"
#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
#include <math.h>
#include <ctype.h>
#include "windows.h"
#include <time.h>
#include <string.h>
#include <legacy/legacy.hpp>
#ifdef _DEBUG
#define new DEBUG_NEW
#define max_corners 124 
#define ARRAY 0 
#define NUMBER 100
#define DELAY 5
#endif


// CDesignView

IMPLEMENT_DYNCREATE(CDesignView, CView)

BEGIN_MESSAGE_MAP(CDesignView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Canny, &CDesignView::OnCanny)
	ON_COMMAND(ID_Corner, &CDesignView::OnCorner)
	ON_COMMAND(ID_rotate, &CDesignView::Onrotate)
	ON_COMMAND(ID_zoom, &CDesignView::Onzoom)
	ON_COMMAND(ID_Log, &CDesignView::OnLog)
	ON_COMMAND(ID_Gauss, &CDesignView::OnGauss)
	ON_COMMAND(ID_Sobel, &CDesignView::OnSobel)
	ON_COMMAND(ID_Laplace, &CDesignView::OnLaplace)
	ON_COMMAND(ID_Prewitt, &CDesignView::OnPrewitt)
	ON_COMMAND(ID_pyramid, &CDesignView::Onpyramid)
	ON_COMMAND(ID_Erode, &CDesignView::OnErode)
	ON_COMMAND(ID_Dilate, &CDesignView::OnDilate)
	ON_COMMAND(ID_Open, &CDesignView::OnOpen)
	ON_COMMAND(ID_Close, &CDesignView::OnClose)
	ON_COMMAND(ID_Gray, &CDesignView::OnGray)
	ON_COMMAND(ID_Reverse, &CDesignView::OnReverse)
	ON_COMMAND(ID_Brightness, &CDesignView::OnBrightness)
	ON_COMMAND(ID_Hist, &CDesignView::OnHist)
	ON_COMMAND(ID_Hist, &CDesignView::OnHist)
	ON_COMMAND(ID_Equalize, &CDesignView::OnEqualize)
	ON_COMMAND(ID_HoughLines, &CDesignView::OnHoughlines)
	ON_COMMAND(ID_HoughCircles, &CDesignView::OnHoughcircles)
	ON_COMMAND(ID_Distancetransform, &CDesignView::OnDistancetransform)
	ON_COMMAND(ID_Hull, &CDesignView::OnHull)
	ON_COMMAND(ID_Delaunay, &CDesignView::OnDelaunay)
	ON_COMMAND(ID_Tone, &CDesignView::OnTone)
	ON_COMMAND(ID_Drawing, &CDesignView::OnDrawing)
	ON_COMMAND(ID_Laplacecam, &CDesignView::OnLaplacecam)
	ON_COMMAND(ID_Bkgrd, &CDesignView::OnBkgrd)
	ON_COMMAND(ID_OpenCam, &CDesignView::OnOpencam)
	ON_COMMAND(ID_Susan, &CDesignView::OnSusan)
	ON_COMMAND(ID_Kalman, &CDesignView::OnKalman)
END_MESSAGE_MAP()

// CDesignView 构造/析构

CDesignView::CDesignView()
{
	// TODO: 在此处添加构造代码

}

CDesignView::~CDesignView()
{
}

BOOL CDesignView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDesignView 绘制

void CDesignView::OnDraw(CDC* /*pDC*/)
{
	CDesignDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDesignView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDesignView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDesignView 诊断

#ifdef _DEBUG
void CDesignView::AssertValid() const
{
	CView::AssertValid();
}

void CDesignView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDesignDoc* CDesignView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDesignDoc)));
	return (CDesignDoc*)m_pDocument;
}
#endif //_DEBUG


// CDesignView 消息处理程序


void CDesignView::OnCanny()//Canny算法
{
	IplImage* img = NULL;  
    IplImage* cannyImg = NULL;  
    char *filename;  
    filename="Canny.jpg";  
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
	}
}


void CDesignView::OnCorner()//角点检测
{
	int cornerCount=max_corners;  
    CvPoint2D32f corners[max_corners];  
    double qualityLevel = 0.05;  
    double minDistance = 5;  
    IplImage *srcImage = 0, *grayImage = 0, *corners1 = 0, *corners2 = 0;  
    int i;  
    CvScalar color = CV_RGB(255,0,0);  
    cvNamedWindow( "Corner", 2); //创建显示窗口  
    //加载一副图片  
    srcImage = cvLoadImage("Corner.png", 1);  
    grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);  
    //将原图灰度化  
    cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);  
    corners1= cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_32F, 1);  
    corners2= cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_32F, 1);  
    cvGoodFeaturesToTrack (grayImage, corners1, corners2, corners,&cornerCount, qualityLevel, minDistance, 0);   
    if(cornerCount>0)  
    {  
        for (i = 0; i < cornerCount; ++i)  
        {  
            cvCircle(srcImage, cvPoint((int)(corners[i].x), (int)(corners[i].y)), 6, color, 2, CV_AA, 0);  
        }  
    }  
    cvShowImage("Corner", srcImage);  
    cvWaitKey(0);  
    cvReleaseImage(&srcImage);  
    cvReleaseImage(&grayImage);  
    cvReleaseImage(&corners1);  
    cvReleaseImage(&corners2);  
}


void CDesignView::Onrotate()//图像旋转
{
	IplImage* src=0;
	char*filename="rotate.jpg";
    src=cvLoadImage(filename);
	IplImage* dst=cvCloneImage(src);
	int  delta = 1;
    int  angle = 0;
    double factor;
    cvNamedWindow( "src", 1 );
    cvShowImage( "src", src );
	for(;;)
	{
		float m[6];
        CvMat M = cvMat( 2, 3, CV_32F, m );
        int w = src->width;
        int h = src->height;
		factor = 1;
		m[0] = (float)(factor*cos(-angle*2*CV_PI/180.));
        m[1] = (float)(factor*sin(-angle*2*CV_PI/180.));
        m[3] = -m[1];
        m[4] = m[0];
        // 将旋转中心移至图像中间
        m[2] = w*0.5f; 
        m[5] = h*0.5f; 
        cvGetQuadrangleSubPix( src, dst, &M);
        cvNamedWindow( "rotate", 1 );
        cvShowImage( "rotate", dst );
        if( cvWaitKey(1) == 27 )
			break;
        angle =(int) (angle + delta) % 360;
	 }
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "rotate" );  
}


void CDesignView::Onzoom()//旋转与缩放
{
	IplImage* src=0;
	char*filename="zoom.jpg";
    src=cvLoadImage(filename);
	IplImage* dst=cvCloneImage(src);
	int  delta = 1;
    int  angle = 0;
    double factor;
    cvNamedWindow( "src", 1 );
    cvShowImage( "src", src );
    for(;;)
	{
		float m[6];
        CvMat M = cvMat( 2, 3, CV_32F, m );
        int w = src->width;
        int h = src->height;
		factor = (cos(angle*CV_PI/180.) + 1.0)*2;
		m[0] = (float)(factor*cos(-angle*2*CV_PI/180.));
        m[1] = (float)(factor*sin(-angle*2*CV_PI/180.));
        m[3] = -m[1];
        m[4] = m[0];
        // 将旋转中心移至图像中间
        m[2] = w*0.5f; 
        m[5] = h*0.5f; 
        cvGetQuadrangleSubPix( src, dst, &M);
        cvNamedWindow( "zoom", 1 );
        cvShowImage( "zoom", dst );
        if( cvWaitKey(1) == 27 )
			break;
        angle =(int) (angle + delta) % 360;
	 }
	cvReleaseImage(&src);  
    cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "zoom" );  
}


void CDesignView::OnLog()//Log_Polar极坐标变换
{
	IplImage *src;  
	src=cvLoadImage("Log.jpg",1);
    IplImage* dst = cvCreateImage( cvSize(256,256), 8, 3 );  
    IplImage* src2 = cvCreateImage( cvGetSize(src), 8, 3 );  
    cvLogPolar( src, dst, cvPoint2D32f(src->width/2,src->height/2),40,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );  
    cvLogPolar( dst, src2, cvPoint2D32f(src->width/2,src->height/2),40, CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP );  
    cvNamedWindow( "src", 1 );  
    cvShowImage( "src", src );  
    cvNamedWindow( "log-polar", 1 );  
    cvShowImage( "log-polar", dst );  
    cvNamedWindow( "inverse log-polar", 1 );  
    cvShowImage( "inverse log-polar", src2 );  
    cvWaitKey(0);
	cvReleaseImage(&src);  
    cvReleaseImage(&dst);
	cvReleaseImage(&src2);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "log-polar" );
	cvDestroyWindow( "inverse log-polar" );
}


void CDesignView::OnGauss()//Gauss滤波
{
	//变量声明  
    IplImage* src=0,*dst=0;  
	float k[9]={1.f/16,2.f/16,1.f/16,2.f/16,4.f/16,2.f/16,1.f/16,2.f/16,1.f/16};
    CvMat kernel=cvMat(3,3,CV_32FC1,k);
    //载入图像  
    src =cvLoadImage("filter.jpg"); 
	dst=cvCloneImage(src);
    //创建窗口  
    cvNamedWindow("src",0);  
	cvShowImage("src",src);
    //初始化滤波器  
    //滤波处理  
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));  
    cvNamedWindow("Gauss",0);  
	cvShowImage("Gauss",dst);  
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "Gauss" );
}


void CDesignView::OnSobel()//Sobel算法
{
	//变量声明  
    IplImage* src=0,*dst=0;  
	float k[9]={1,2,1,0,0,0,-1,-2,-1};
    CvMat kernel=cvMat(3,3,CV_32FC1,k);
    //载入图像  
    src =cvLoadImage("filter.jpg"); 
	dst=cvCloneImage(src);
    //创建窗口  
    cvNamedWindow("src",0);  
	cvShowImage("src",src);
    //初始化滤波器  
    //滤波处理  
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));  
    cvNamedWindow("Sobel",0);  
	cvShowImage("Sobel",dst);  
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "Sobel" );
}


void CDesignView::OnLaplace()//Laplace算法
{
	//变量声明  
    IplImage* src=0,*dst=0;  
	float k[9]={0,1,0,1,-4,1,0,1,0};
    CvMat kernel=cvMat(3,3,CV_32FC1,k);
    //载入图像  
    src =cvLoadImage("filter.jpg"); 
	dst=cvCloneImage(src);
    //创建窗口  
    cvNamedWindow("src",0);  
	cvShowImage("src",src);
    //初始化滤波器  
    //滤波处理  
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));  
    cvNamedWindow("Laplace",0);  
	cvShowImage("Laplace",dst);  
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "Laplace" );
}


void CDesignView::OnPrewitt()//Prewitt算法
{
	//变量声明  
    IplImage* src=0,*dst=0;  
	float k[9]={1,1,1,0,0,0,-1,-1,-1};
    CvMat kernel=cvMat(3,3,CV_32FC1,k);
    //载入图像  
    src =cvLoadImage("filter.jpg"); 
	dst=cvCloneImage(src);
    //创建窗口  
    cvNamedWindow("src",0);  
	cvShowImage("src",src);
    //初始化滤波器  
    //滤波处理  
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));  
    cvNamedWindow("Prewitt",0);  
	cvShowImage("Prewitt",dst);  
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow( "src" );  
    cvDestroyWindow( "Prewitt" );
}


void CDesignView::Onpyramid()//金字塔图像分割
{
	IplImage*src=0,*dst = 0;
	int threshold1, threshold2;
    int l=1,level = 4;
    int block_size = 1000;
    CvSeq *comp;
    CvMemStorage *storage;
    src =cvLoadImage("pyramid.jpg"); 
    cvNamedWindow("Source", 0);
    cvShowImage("Source", src);
    cvNamedWindow("Segmentation", 0);
    storage = cvCreateMemStorage ( block_size );
    src->width &= -(1<<level);
    src->height &= -(1<<level);
    dst = cvCloneImage(src);
    // 对彩色图像进行分割
    threshold1 =255;
    threshold2 =30;
    cvPyrSegmentation(src, dst, storage, &comp,level, threshold1+1, threshold2+1);
    cvShowImage("Segmentation", dst);
    cvWaitKey(0);
    cvDestroyWindow("Segmentation");
    cvDestroyWindow("Source");
    cvReleaseMemStorage(&storage );
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
}


void CDesignView::OnErode()//腐蚀
{
	IplImage *src=0;  
	IplImage *dst=0;  
	IplConvKernel *element=0;//声明一个结构元素  
    int element_shape=CV_SHAPE_RECT;//长方形形状的元素   
    src =cvLoadImage("morphology.jpg");       
    dst=cvCloneImage(src);      
    element = cvCreateStructuringElementEx(21,21,10,10,element_shape,0);  
    cvErode(src,dst,element,1);
	cvNamedWindow("src",1); 
	cvShowImage("src",src); 
	cvNamedWindow("Erode",1); 
	cvShowImage("Erode",dst);  
    cvWaitKey(0);  
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Erode");
	cvReleaseStructuringElement(&element);  
}


void CDesignView::OnDilate()//膨胀
{
	IplImage *src=0;  
	IplImage *dst=0;  
	IplConvKernel *element=0;//声明一个结构元素  
    int element_shape=CV_SHAPE_RECT;//长方形形状的元素   
    src =cvLoadImage("morphology.jpg");       
    dst=cvCloneImage(src);      
    element = cvCreateStructuringElementEx(21,21,10,10,element_shape,0);  
    cvDilate(src,dst,element,1);
	cvNamedWindow("src",1); 
	cvShowImage("src",src); 
	cvNamedWindow("Dilate",1); 
	cvShowImage("Dilate",dst);  
    cvWaitKey(0);  
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Dilate");
	cvReleaseStructuringElement(&element); 
}


void CDesignView::OnOpen()//开运算
{
	IplImage *src=0;  
	IplImage *dst=0;  
	IplConvKernel *element=0;//声明一个结构元素  
    int element_shape=CV_SHAPE_RECT;//长方形形状的元素   
    src =cvLoadImage("morphology.jpg");       
    dst=cvCloneImage(src);      
    element = cvCreateStructuringElementEx(21,21,10,10,element_shape,0);  
    cvErode(src,dst,element,1);//腐蚀图像  
    cvDilate(dst,dst,element,1);//膨胀图像  
	cvNamedWindow("src",1); 
	cvShowImage("src",src); 
	cvNamedWindow("Open",1); 
	cvShowImage("Open",dst);  
    cvWaitKey(0);  
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Open");
	cvReleaseStructuringElement(&element); 
}


void CDesignView::OnClose()//闭运算
{
	IplImage *src=0;  
	IplImage *dst=0;  
	IplConvKernel *element=0;//声明一个结构元素  
    int element_shape=CV_SHAPE_RECT;//长方形形状的元素   
    src =cvLoadImage("morphology.jpg");       
    dst=cvCloneImage(src);      
    element = cvCreateStructuringElementEx(21,21,10,10,element_shape,0);  
    cvDilate(dst,dst,element,1);//膨胀图像  
    cvErode(src,dst,element,1);//腐蚀图像 
	cvNamedWindow("src",1); 
	cvShowImage("src",src); 
	cvNamedWindow("Close",1); 
	cvShowImage("Close",dst);  
    cvWaitKey(0);  
    cvReleaseImage(&src);  
    cvReleaseImage(&dst);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Close");
	cvReleaseStructuringElement(&element); 
}

void CDesignView::OnGray()//彩色变灰阶
{
	IplImage *srcImage = 0, *grayImage = 0;  
    cvNamedWindow( "src", 2); //创建显示窗口  
    cvNamedWindow( "Gray", 2);
	//加载一副图片  
    srcImage = cvLoadImage("gray.jpg", 1);  
    grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U, 1);  
    //将原图灰度化  
    cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);  
    cvShowImage("src", srcImage); 
	cvShowImage("Gray", grayImage); 
    cvWaitKey(0);  
    cvReleaseImage(&srcImage);  
    cvReleaseImage(&grayImage);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Gray");
}


void CDesignView::OnReverse()//图像反转
{
	IplImage* img=0,*reverse=0;
	int height,width,step,channels;
	UCHAR* data;
	int i,j,k;
	img=cvLoadImage("reverse.jpg");
	reverse=cvCloneImage(img);
	height=reverse->height;
	width=reverse->width;
	step=reverse->widthStep;
	channels=reverse->nChannels;
	data=(UCHAR*)reverse->imageData;
	cvNamedWindow("src",1); 
	cvNamedWindow("Reverse",1); 
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			for(k=0;k<channels;k++)
				data[i*step+j*channels+k]=255-data[i*step+j*channels+k];
	cvShowImage("src",img);
	cvShowImage("Reverse",reverse);
	cvWaitKey(0);
	cvReleaseImage(&img);  
    cvReleaseImage(&reverse);  
	cvDestroyWindow("src"); 
    cvDestroyWindow("Reverse");
}


void CDesignView::OnBrightness()//亮度变换
{
	
    IplImage *src = 0, *dst = 0;
    cvNamedWindow( "src", 1 );
    cvNamedWindow( "Brightness", 1 );
	src=cvLoadImage("Brightness.jpg");
    dst = cvCloneImage(src);
	// Image adjust
    // 输入参数 [0,0.5] 和 [0.5,1], gamma=1
	ImageAdjust( src, dst, 0, 0.5, 0.5, 1,1);
    cvShowImage( "src", src );
    cvShowImage( "Brightness", dst );
    cvWaitKey(0);
    cvDestroyWindow("src");
    cvDestroyWindow("Brightness");
    cvReleaseImage( &src );
    cvReleaseImage( &dst );
}

int CDesignView::ImageAdjust(IplImage* src, IplImage* dst, //亮度变换内调用函数
    double low, double high,   // X方向：low and high are the intensities of src
    double bottom, double top, // Y方向：mapped to bottom and top of dst
    double gamma )
{
	if( low<0 && low>1 && high <0 && high>1&&bottom<0 && bottom>1 && top<0 && top>1 && low>high)
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


void CDesignView::OnHist()//图像直方图
{
    IplImage * src= cvLoadImage("Hist.jpg");  
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
    cvNamedWindow( "src", 1 );  
    cvShowImage("src",src);  
    cvNamedWindow( "Histogram", 1 );  
    cvShowImage( "Histogram", hist_image );  
    cvWaitKey(0); 
	cvReleaseImage( &src ); 
    cvReleaseImage( &gray_plane ); 
    cvDestroyWindow("src");
	cvDestroyWindow("Histogram"); 
}


void CDesignView::OnEqualize()//直方图均衡化
{
	int i;  
    IplImage* src = cvLoadImage("Hist.jpg", 1 );  
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
		cvReleaseImage( &src ); 
        cvReleaseImage( &dst ); 
		cvDestroyWindow("src");
		cvDestroyWindow("Equalize");
    }  
}


void CDesignView::OnHoughlines()//Hough变换检测线段
{
	IplImage *src = cvLoadImage("Houghlines.jpg",1);  
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
        cvNamedWindow("Houghlines");  
        cvShowImage("Houghlines",color_dst);  
        cvWaitKey(0);  
        cvReleaseImage(&src);  
        cvReleaseImage(&dst);  
        cvReleaseImage(&color_dst);  
        cvReleaseMemStorage(&storage);   
        cvDestroyAllWindows();  
    }  
}


void CDesignView::OnHoughcircles()//Hough变换检测圆
{
	IplImage* src = NULL;  
    IplImage* dst = NULL;  
    IplImage* color = NULL;  
    src = cvLoadImage ("Houghcircles.png", 1);  
    dst = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);  
    if (src->nChannels == 1)  
    {  
        dst = cvCloneImage (src);  
    }  
    else  
    {  
        cvCvtColor (src, dst, CV_RGB2GRAY);  
    }  
    CvMemStorage* storage = cvCreateMemStorage (0);  
    cvSmooth (dst, dst, CV_GAUSSIAN, 5, 5);  
    CvSeq* circles = cvHoughCircles (dst, storage, CV_HOUGH_GRADIENT, 2, dst->width /3, 300, 100, 0, 200);  
    color = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 3);  
    cvCvtColor (dst, color, CV_GRAY2RGB);  
    for (int i = 0; i < circles->total; i++)  
    {  
        float* p = (float*)cvGetSeqElem (circles, i);  
        CvPoint pt = cvPoint (cvRound(p[0]), cvRound(p[1]));  
        cvCircle (color, pt, cvRound(p[2]), CV_RGB(255, 0, 0), 3, 8, 0);  
    }  
    cvNamedWindow ("src", 1);  
    cvShowImage ("src", src);  
    cvNamedWindow ("Houghcircles", 1);  
    cvShowImage ("Houghcircles", color);  
    cvWaitKey (0);  
    cvReleaseMemStorage (&storage);  
    cvReleaseImage (&src);  
    cvReleaseImage (&dst);  
    cvReleaseImage (&color);  
    cvDestroyAllWindows();
}


void CDesignView::OnDistancetransform()//距离变换
{
	IplImage* src = cvLoadImage ("Distancetransform.jpg", 1);    
    IplImage* dst = cvCreateImage (cvGetSize(src), IPL_DEPTH_32F, 1);    
    IplImage* canny = cvCreateImage (cvGetSize(src), IPL_DEPTH_8U, 1);    
    cvCvtColor (src, canny, CV_RGB2GRAY);    
    cvCanny (canny, canny, 100, 200, 3);    
    cvDistTransform (canny, dst, CV_DIST_WELSCH, 3);    
    cvNamedWindow ("src", 1);    
    cvShowImage ("src", src);    
    cvNamedWindow ("dist", 1);    
    cvShowImage ("dist", canny);    
    cvWaitKey (0);    
    cvReleaseImage (&src);    
    cvReleaseImage (&canny);    
    cvReleaseImage (&dst);    
    cvDestroyAllWindows();
}


void CDesignView::OnHull()//点集凸包
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
}


void CDesignView::OnDelaunay()//Delaunay三角形
{
	char win[] = "source";
    int i;
    CvRect rect = { 0, 0, 600, 600 };
    CvMemStorage* storage;
    CvSubdiv2D* subdiv;
    IplImage* img;
    CvScalar active_facet_color, delaunay_color, voronoi_color, bkgnd_color;
    active_facet_color = CV_RGB( 255, 0, 0 );
    delaunay_color = CV_RGB( 0,0,0);
    voronoi_color = CV_RGB(0, 180, 0);
    bkgnd_color = CV_RGB(255,255,255);
    img = cvCreateImage( cvSize(rect.width,rect.height), 8, 3 );
    cvSet( img, bkgnd_color, 0 );
    cvNamedWindow( win, 1 );
    storage = cvCreateMemStorage(0);
    subdiv = init_delaunay( storage, rect );
    for( i = 0; i < 200; i++ )
    {
        CvPoint2D32f fp = cvPoint2D32f( (float)(rand()%(rect.width-10)+5),
                                        (float)(rand()%(rect.height-10)+5));
        locate_point( subdiv, fp, img, active_facet_color );
        cvShowImage( win, img );
        if( cvWaitKey( 100 ) >= 0 )
            break;
        cvSubdivDelaunay2DInsert( subdiv, fp );
        cvCalcSubdivVoronoi2D( subdiv );
        cvSet( img, bkgnd_color, 0 );
        draw_subdiv( img, subdiv, delaunay_color, voronoi_color );
        cvShowImage( win, img );
        if( cvWaitKey( 100 ) >= 0 )
            break;
    }
    cvSet( img, bkgnd_color, 0 );
    paint_voronoi( subdiv, img );
    cvShowImage( win, img );
    cvWaitKey(0);
    cvReleaseMemStorage( &storage );
    cvReleaseImage(&img);
    cvDestroyWindow( win );
}

CvSubdiv2D* CDesignView::init_delaunay( CvMemStorage* storage,CvRect rect )//Delaunay三角形内调函数
{
    CvSubdiv2D* subdiv;
    subdiv = cvCreateSubdiv2D( CV_SEQ_KIND_SUBDIV2D, sizeof(*subdiv),sizeof(CvSubdiv2DPoint),sizeof(CvQuadEdge2D),storage );
    cvInitSubdivDelaunay2D( subdiv, rect );
    return subdiv;
}

void CDesignView::draw_subdiv_point( IplImage* img, CvPoint2D32f fp, CvScalar color )//Delaunay三角形内调函数
{
    cvCircle( img, cvPoint(cvRound(fp.x), cvRound(fp.y)), 3, color, CV_FILLED, 8, 0 );
}

void CDesignView::draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, CvScalar color )//Delaunay三角形内调函数
{
    CvSubdiv2DPoint* org_pt;
    CvSubdiv2DPoint* dst_pt;
    CvPoint2D32f org;
    CvPoint2D32f dst;
    CvPoint iorg, idst;
    org_pt = cvSubdiv2DEdgeOrg(edge);
    dst_pt = cvSubdiv2DEdgeDst(edge);
    if( org_pt && dst_pt )
    {
        org = org_pt->pt;
        dst = dst_pt->pt;
        iorg = cvPoint( cvRound( org.x ), cvRound( org.y ));
        idst = cvPoint( cvRound( dst.x ), cvRound( dst.y ));
        cvLine( img, iorg, idst, color, 1, CV_AA, 0 );
    }
}

void CDesignView::draw_subdiv( IplImage* img, CvSubdiv2D* subdiv,CvScalar delaunay_color, CvScalar voronoi_color )//Delaunay三角形内调函数
{
    CvSeqReader reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;
    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
        if( CV_IS_SET_ELEM( edge ))
        {
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge + 1, voronoi_color );
            draw_subdiv_edge( img, (CvSubdiv2DEdge)edge, delaunay_color );
        }
        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
}

void CDesignView::locate_point( CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,CvScalar active_color )//Delaunay三角形内调函数
{
    CvSubdiv2DEdge e;
    CvSubdiv2DEdge e0 = 0;
    CvSubdiv2DPoint* p = 0;
    cvSubdiv2DLocate( subdiv, fp, &e0, &p );
    if( e0 )
    {
        e = e0;
        do
        {
            draw_subdiv_edge( img, e, active_color );
            e = cvSubdiv2DGetEdge(e,CV_NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }
    draw_subdiv_point( img, fp, active_color );
}

void CDesignView::draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge )//Delaunay三角形内调函数
{
    CvSubdiv2DEdge t = edge;
    int i, count = 0;
    CvPoint* buf = 0;
    // count number of edges in facet
    do
    {
        count++;
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    } while (t != edge );
    buf = (CvPoint*)malloc( count * sizeof(buf[0]));
    // gather points
    t = edge;
    for( i = 0; i < count; i++ )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeOrg( t );
        if( !pt ) break;
        buf[i] = cvPoint( cvRound(pt->pt.x), cvRound(pt->pt.y));
        t = cvSubdiv2DGetEdge( t, CV_NEXT_AROUND_LEFT );
    }
    if( i == count )
    {
        CvSubdiv2DPoint* pt = cvSubdiv2DEdgeDst( cvSubdiv2DRotateEdge( edge, 1 ));
        cvFillConvexPoly( img, buf, count, CV_RGB(rand()&255,rand()&255,rand()&255), CV_AA, 0 );
        cvPolyLine( img, &buf, &count, 1, 1, CV_RGB(0,0,0), 1, CV_AA, 0);
        draw_subdiv_point( img, pt->pt, CV_RGB(0,0,0));
    }
    free( buf );
}

void CDesignView::paint_voronoi( CvSubdiv2D* subdiv, IplImage* img )//Delaunay三角形内调函数
{
    CvSeqReader reader;
    int i, total = subdiv->edges->total;
    int elem_size = subdiv->edges->elem_size;
    cvCalcSubdivVoronoi2D( subdiv );
    cvStartReadSeq( (CvSeq*)(subdiv->edges), &reader, 0 );
    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* edge = (CvQuadEdge2D*)(reader.ptr);
        if( CV_IS_SET_ELEM( edge ))
        {
            CvSubdiv2DEdge e = (CvSubdiv2DEdge)edge;
            // left
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 1 ));
            // right
            draw_subdiv_facet( img, cvSubdiv2DRotateEdge( e, 3 ));
        }
        CV_NEXT_SEQ_ELEM( elem_size, reader );
    }
}

void CDesignView::OnTone()//二维色调-饱和度图像
{
	IplImage* src= cvLoadImage ("Tone.jpg", 1);;
	IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* planes[] = { h_plane, s_plane };
    IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
    int h_bins = 30, s_bins = 32;
    int hist_size[] = {h_bins, s_bins};
    float h_ranges[] = { 0, 180 }; /* hue varies from 0 (~0°red) to 180 (~360°red again) */
    float s_ranges[] = { 0, 255 }; /* saturation varies from 0 (black-gray-white) to 255 (pure spectrum color) */
    float* ranges[] = { h_ranges, s_ranges };
    int scale = 10;
    IplImage* hist_img = cvCreateImage( cvSize(h_bins*scale,s_bins*scale), 8, 3 );
    CvHistogram* hist;
    float max_value = 0;
    int h, s;
    cvCvtColor( src, hsv, CV_BGR2HSV );
    cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );
    hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
    cvCalcHist( planes, hist, 0, 0 );
    cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );
    cvZero( hist_img );
    for( h = 0; h < h_bins; h++ )
	{
		for( s = 0; s < s_bins; s++ )
		{
			float bin_val = cvQueryHistValue_2D( hist, h, s );
            int intensity = cvRound(bin_val*255/max_value);
            cvRectangle( hist_img, cvPoint( h*scale, s*scale ),cvPoint( (h+1)*scale - 1, (s+1)*scale - 1),CV_RGB(intensity,intensity,intensity),CV_FILLED );
		}
	}
    cvNamedWindow( "Source", 1 );
    cvShowImage( "Source", src );
    cvNamedWindow( "H-S Histogram", 1 );
    cvShowImage( "H-S Histogram", hist_img );
    cvWaitKey(0);
	cvReleaseImage (&src);    
    cvReleaseImage (&hist_img);       
    cvDestroyAllWindows();
}


void CDesignView::OnDrawing()//画图
{
	char wndname[] = "Drawing Demo";
	int line_type = CV_AA; // change it to 8 to see non-antialiased graphics
    int i;
    CvPoint pt1,pt2; //基于二维整形坐标轴的点
    double angle;
    CvSize sz;   //矩形框大小，以像素为精度
    CvPoint ptt[6];
    CvPoint* pt[2];
    int arr[2];
    CvFont font;
    CvRNG rng;
    int width = 1000, height = 700;
    int width3 = width*3, height3 = height*3;
    CvSize text_size;
    int ymin = 0;
    // Load the source image
    IplImage* image = cvCreateImage( cvSize(width,height), 8, 3 );
    IplImage* image2;
    // Create a window
    cvNamedWindow(wndname, 1 );
    cvZero( image ); //#define cvZero cvSetZero   void cvSetZero( CvArr* arr ); arr 要被清空数组
    cvShowImage(wndname,image);
    rng = cvRNG((unsigned)-1);
    pt[0] = &(ptt[0]);
    pt[1] = &(ptt[3]);
    arr[0] = 3;
    arr[1] = 3;
    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        pt2.x=cvRandInt(&rng) % width3 - width;
        pt2.y=cvRandInt(&rng) % height3 - height;
        cvLine( image, pt1, pt2, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );//绘制连接两个点的线段 
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        pt2.x=cvRandInt(&rng) % width3 - width;
        pt2.y=cvRandInt(&rng) % height3 - height;
        cvRectangle( image,pt1, pt2, random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );//绘制简单、指定粗细或者带填充的矩形
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        sz.width =cvRandInt(&rng)%200;
        sz.height=cvRandInt(&rng)%200;
        angle = (cvRandInt(&rng)%1000)*0.180;
        cvEllipse( image, pt1, sz, angle, angle - 100, angle + 200,
                   random_color(&rng), cvRandInt(&rng)%10-1, line_type, 0 );//函数cvEllipse用来绘制或者填充一个简单的椭圆弧或椭圆扇形
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 0; i< NUMBER; i++)
    {
        pt[0][0].x=cvRandInt(&rng) % width3 - width;
        pt[0][0].y=cvRandInt(&rng) % height3 - height;
        pt[0][1].x=cvRandInt(&rng) % width3 - width;
        pt[0][1].y=cvRandInt(&rng) % height3 - height;
        pt[0][2].x=cvRandInt(&rng) % width3 - width;
        pt[0][2].y=cvRandInt(&rng) % height3 - height;
        pt[1][0].x=cvRandInt(&rng) % width3 - width;
        pt[1][0].y=cvRandInt(&rng) % height3 - height;
        pt[1][1].x=cvRandInt(&rng) % width3 - width;
        pt[1][1].y=cvRandInt(&rng) % height3 - height;
        pt[1][2].x=cvRandInt(&rng) % width3 - width;
        pt[1][2].y=cvRandInt(&rng) % height3 - height;
        cvPolyLine( image, pt, arr, 2, 1, random_color(&rng), cvRandInt(&rng)%10, line_type, 0 );//函数cvPolyLine 绘制一个简单的或多样的多角曲线
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 0; i< NUMBER; i++)
    {
        pt[0][0].x=cvRandInt(&rng) % width3 - width;
        pt[0][0].y=cvRandInt(&rng) % height3 - height;
        pt[0][1].x=cvRandInt(&rng) % width3 - width;
        pt[0][1].y=cvRandInt(&rng) % height3 - height;
        pt[0][2].x=cvRandInt(&rng) % width3 - width;
        pt[0][2].y=cvRandInt(&rng) % height3 - height;
        pt[1][0].x=cvRandInt(&rng) % width3 - width;
        pt[1][0].y=cvRandInt(&rng) % height3 - height;
        pt[1][1].x=cvRandInt(&rng) % width3 - width;
        pt[1][1].y=cvRandInt(&rng) % height3 - height;
        pt[1][2].x=cvRandInt(&rng) % width3 - width;
        pt[1][2].y=cvRandInt(&rng) % height3 - height;
        cvFillPoly( image, pt, arr, 2, random_color(&rng), line_type, 0 );//函数cvFillPoly用于一个单独被多变形轮廓所限定的区域内进行填充
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 0; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        cvCircle( image, pt1, cvRandInt(&rng)%300, random_color(&rng),
                  cvRandInt(&rng)%10-1, line_type, 0 );//函数cvCircle绘制或填充一个给定圆心和半径的圆
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    for (i = 1; i< NUMBER; i++)
    {
        pt1.x=cvRandInt(&rng) % width3 - width;
        pt1.y=cvRandInt(&rng) % height3 - height;
        cvInitFont( &font, cvRandInt(&rng) % 8,(cvRandInt(&rng)%100)*0.05+0.1,(cvRandInt(&rng)%100)*0.05+0.1, (cvRandInt(&rng)%5)*0.1, cvRound(cvRandInt(&rng)%10), line_type );//字体结构初始化。函数 cvRound, cvFloor, cvCeil 用一种舍入方法将输入浮点数转换成整数。 cvRound 返回和参数最接近的整数值
        cvPutText( image, "Northeast Petroleum University!", pt1, &font, random_color(&rng));//在图像中加入文本
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX, 3, 3, 0.0, 5, line_type );
    cvGetTextSize( "Opencv forever!", &font, &text_size, &ymin );//设置字符串文本的宽度和高度
    pt1.x = (width - text_size.width)/2;
    pt1.y = (height + text_size.height)/2;
    image2 = cvCloneImage(image);
    for( i = 0; i < 255; i++ )
    {
        cvSubS( image2, cvScalarAll(i), image, 0 );//函数 cvSubS 从原数组的每个元素中减去一个数量
        cvPutText( image, "Design Your Life!", pt1, &font, CV_RGB(255,i,i));
        cvShowImage(wndname,image);
        cvWaitKey(DELAY);
    }
    // Wait for a key stroke; the same function arranges events processing
    cvWaitKey(0);
    cvReleaseImage(&image);
    cvReleaseImage(&image2);
    cvDestroyWindow(wndname);
}

CvScalar CDesignView::random_color(CvRNG* rng) //函数 cvRNG 初始化随机数生成器并返回其状态，RNG 随机数生成器（Drawing内调函数）
{
    int icolor = cvRandInt(rng); //函数 cvRandInt 返回均匀分布的随机 32-bit 无符号整型值并更新 RNG 状态
    return CV_RGB(icolor&255, (icolor>>8)&255, (icolor>>16)&255); //创建一个色彩值
}


void CDesignView::OnLaplacecam()//动态边缘检测
{
	IplImage* laplace = 0;
    IplImage* colorlaplace = 0;
    IplImage* planes[3] = { 0, 0, 0 }; // 多个图像面
    CvCapture* capture = 0; 
    capture = cvCaptureFromCAM(0);
    cvNamedWindow( "Laplacian", 0 );
	// 循环捕捉，直到用户按键跳出循环体
    for(;;)
    {
        IplImage* frame = 0;
        int i;
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        if( !laplace )
        {
            for( i = 0; i < 3; i++ )
                planes[i] = cvCreateImage( cvSize(frame->width,frame->height), 8, 1 );
			laplace = cvCreateImage( cvSize(frame->width,frame->height),IPL_DEPTH_16S, 1 );
            colorlaplace = cvCreateImage( cvSize(frame->width,frame->height), 8, 3 );
        }
        cvCvtPixToPlane( frame, planes[0], planes[1], planes[2], 0 );
        for( i = 0; i < 3; i++ )
        {
            cvLaplace( planes[i], laplace, 3 ); // 3: aperture_size
            cvConvertScaleAbs( laplace, planes[i], 1, 0 ); // planes[] = ABS(laplace)
        }
        cvCvtPlaneToPix( planes[0], planes[1], planes[2], 0, colorlaplace );
        colorlaplace->origin = frame->origin;
        cvShowImage("Laplacian", colorlaplace );
        if( cvWaitKey(10) >= 0 )
            break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow("Laplacian");
}


void CDesignView::OnBkgrd()//背景建模检测
{
	//声明IplImage指针
	IplImage* pFrame = NULL; 
	IplImage* pFrImg = NULL;
	IplImage* pBkImg = NULL;
	CvMat* pFrameMat = NULL;
	CvMat* pFrMat = NULL;
	CvMat* pBkMat = NULL;
	CvCapture* pCapture = NULL;
	int nFrmNum = 0;
	//创建窗口
	cvNamedWindow("video", 1);
	cvNamedWindow("background",1);
	cvNamedWindow("foreground",1);
	//使窗口有序排列
	cvMoveWindow("video", 30, 0);
	cvMoveWindow("background", 360, 0);
	cvMoveWindow("foreground", 690, 0);
	//打开视频文件
	pCapture = cvCaptureFromFile("globe.avi");
	//逐帧读取视频
	while(pFrame = cvQueryFrame( pCapture ))
    {
      nFrmNum++;
      //如果是第一帧，需要申请内存，并初始化
      if(nFrmNum == 1)
	  {
		  pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),IPL_DEPTH_8U,1);
		  pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),IPL_DEPTH_8U,1);
		  pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
		  pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
		  pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
		  //转化成单通道图像再处理
		  cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);
		  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
		  cvConvert(pFrImg, pFrameMat);
		  cvConvert(pFrImg, pFrMat);
		  cvConvert(pFrImg, pBkMat);
	  }
      else
	  {
		  cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
		  cvConvert(pFrImg, pFrameMat);//先做高斯滤波，以平滑图像
		  //cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
		  //当前帧跟背景图相减
		  cvAbsDiff(pFrameMat, pBkMat, pFrMat);
		  //二值化前景图
		  cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);
          //进行形态学滤波，去掉噪音 
          //cvErode(pFrImg, pFrImg, 0, 1);
          //cvDilate(pFrImg, pFrImg, 0, 1);
          //更新背景
          cvRunningAvg(pFrameMat, pBkMat, 0.003, 0);
          //将背景转化为图像格式，用以显示
          cvConvert(pBkMat, pBkImg);
          //显示图像
          cvShowImage("video", pFrame);
          cvShowImage("background", pBkImg);
          cvShowImage("foreground", pFrImg);
          //如果有按键事件，则跳出循环
          //此等待也为cvShowImage函数提供时间完成显示
          //等待时间可以根据CPU速度调整
          if( cvWaitKey(2) >= 0 )
			  break;
	  } // end of if-else
	} // end of while-loop
    //销毁窗口
    cvDestroyWindow("video");
    cvDestroyWindow("background");
    cvDestroyWindow("foreground");
    //释放图像和矩阵
    cvReleaseImage(&pFrImg);
    cvReleaseImage(&pBkImg);
    cvReleaseMat(&pFrameMat);
    cvReleaseMat(&pFrMat);
    cvReleaseMat(&pBkMat);
}

void CDesignView::OnOpencam()//启动摄像头
{
	IplImage* laplace = 0;
    IplImage* colorlaplace = 0;
    IplImage* planes[3] = { 0, 0, 0 }; // 多个图像面
    CvCapture* capture = 0; 
    capture = cvCaptureFromCAM(0);
    cvNamedWindow( "Cam", 0 );
	// 循环捕捉，直到用户按键跳出循环体
    for(;;)
    {
        IplImage* frame = 0;
        int i;
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        if( !laplace )
        {
            for( i = 0; i < 3; i++ )
                planes[i] = cvCreateImage( cvSize(frame->width,frame->height), 8, 1 );
			laplace = cvCreateImage( cvSize(frame->width,frame->height),IPL_DEPTH_16S, 1 );
            colorlaplace = cvCreateImage( cvSize(frame->width,frame->height), 8, 3 );
        }
        cvCvtPixToPlane( frame, planes[0], planes[1], planes[2], 0 );
        cvCvtPlaneToPix( planes[0], planes[1], planes[2], 0, colorlaplace );
        colorlaplace->origin = frame->origin;
        cvShowImage("Cam", colorlaplace );
        if( cvWaitKey(10) >= 0 )
            break;
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow("Cam");
}

void CDesignView::OnSusan()//Susan算法
{
	int height ,width ,step ,channels ;  
    int i,j,k,same ,max,min,sum;  
    float thresh;  
    uchar *data0,*data1 ;  
    IplImage* Img, *nimg;
    //载入图像  
    Img=cvLoadImage( "susan.jpg",0);  
    cvNamedWindow( "src", 2); //创建窗口  
    cvShowImage( "src", Img ); //显示图像  
    nimg=cvCreateImage(cvGetSize(Img),8,1);  
    height=Img->height;  
    width=Img->width;  
    step=Img->widthStep/sizeof(uchar);  
    channels=Img->nChannels;  
    data0=(uchar*)Img->imageData;  
    data1=(uchar*)nimg->imageData;    
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
        }  
        cvNamedWindow( "Susan", 2); //创建窗口  
        cvShowImage( "Susan", nimg ); //显示图像  
        cvWaitKey(0); //等待按键  
        cvDestroyWindow( "Susan" );
		cvDestroyWindow( "src" );//销毁窗口  
        cvReleaseImage( &Img ); //释放图像  
        cvReleaseImage( &nimg );  
}


void CDesignView::OnKalman()//Kalman算法
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
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*xK,float,0,0)),cvRound(CV_MAT_ELEM(*xK,float,1,0))),4,CV_RGB(255,255,255),2);//白圈，真实位置  
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*yK,float,0,0)),cvRound(CV_MAT_ELEM(*yK,float,1,0))),4,CV_RGB(0,255,0),2);//绿圈，预估位置  
        cvCircle(image,cvPoint(cvRound(CV_MAT_ELEM(*zK,float,0,0)),cvRound(CV_MAT_ELEM(*zK,float,1,0))),4,CV_RGB(0,0,255),2);//蓝圈，观测位置  
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
        cvShowImage("Kalman",image);  
        cvKalmanCorrect( kalman, zK );  
        if(cvWaitKey(100)==27){  
            break;  
        }  
    }   
    cvReleaseImage(&image);/*释放图像*/  
    cvDestroyAllWindows();  
}
