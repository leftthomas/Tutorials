#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
IplImage *image = 0, *hsv = 0, *hue = 0, *mask = 0, *backproject = 0, *histimg = 0;
CvHistogram *hist = 0;
int backproject_mode = 0;
int select_object = 0;
int track_object = 0;
int show_hist = 1; 
CvPoint origin;
CvRect selection;
CvRect track_window;
CvBox2D track_box; // tracking 返回的区域 box，带角度
CvConnectedComp track_comp;
int hdims = 48;     // 划分HIST的个数，越高越精确
float hranges_arr[] = {0,180};
float* hranges = hranges_arr;
int vmin = 10, vmax = 256, smin = 30;
void on_mouse( int event, int x, int y, int flags )
{
    if( !image )
        return;
    if( image->origin )
        y = image->height - y;
    if( select_object )
    {
        selection.x = MIN(x,origin.x);
        selection.y = MIN(y,origin.y);
        selection.width = selection.x + CV_IABS(x - origin.x);
        selection.height = selection.y + CV_IABS(y - origin.y);
        
        selection.x = MAX( selection.x, 0 );
        selection.y = MAX( selection.y, 0 );
        selection.width = MIN( selection.width, image->width );
        selection.height = MIN( selection.height, image->height );
        selection.width -= selection.x;
        selection.height -= selection.y;
    }
    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = cvPoint(x,y);
        selection = cvRect(x,y,0,0);
        select_object = 1;
        break;
    case CV_EVENT_LBUTTONUP:
        select_object = 0;
        if( selection.width > 0 && selection.height > 0 )
            track_object = -1;
#ifdef _DEBUG
    printf("\n # 鼠标的选择区域："); 
    printf("\n   X = %d, Y = %d, Width = %d, Height = %d",
        selection.x, selection.y, selection.width, selection.height);
#endif
        break;
    }
}

CvScalar hsv2rgb( float hue )
{
    int rgb[3], p, sector;
    static const int sector_data[][3]=
        {{0,2,1}, {1,2,0}, {1,0,2}, {2,0,1}, {2,1,0}, {0,1,2}};
    hue *= 0.033333333333333333333333333333333f;
    sector = cvFloor(hue);
    p = cvRound(255*(hue - sector));
    p ^= sector & 1 ? 255 : 0;
    rgb[sector_data[sector][0]] = 255;
    rgb[sector_data[sector][1]] = 0;
    rgb[sector_data[sector][2]] = p;
#ifdef _DEBUG
    printf("\n # Convert HSV to RGB："); 
    printf("\n   HUE = %f", hue);
    printf("\n   R = %d, G = %d, B = %d", rgb[0],rgb[1],rgb[2]);
#endif
    return cvScalar(rgb[2], rgb[1], rgb[0],0);
}
int main( int argc, char** argv )
{
    CvCapture* capture = 0;
    IplImage* frame = 0;
    
    if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
        capture = cvCaptureFromCAM( argc == 2 ?argv[1][0] - '0' : 0 );
    else if( argc == 2 )
        capture = cvCaptureFromAVI( argv[1] ); 
    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        return -1;
    }
    printf( "Hot keys: \n"
        "\tESC - quit the program\n"
        "\tc - stop the tracking\n"
        "\tb - switch to/from backprojection view\n"
        "\th - show/hide object histogram\n"
        "To initialize tracking, select the object with mouse\n" );
    //cvNamedWindow( "Histogram", 1 );
    cvNamedWindow( "CamShiftDemo", 1 );
    //cvSetMouseCallback( "CamShiftDemo", on_mouse, NULL ); // on_mouse 自定义事件
    cvCreateTrackbar( "Vmin", "CamShiftDemo", &vmin, 256, 0 );
    cvCreateTrackbar( "Vmax", "CamShiftDemo", &vmax, 256, 0 );
    cvCreateTrackbar( "Smin", "CamShiftDemo", &smin, 256, 0 );
    for(;;)
    {
        int i, bin_w, c;
        frame = cvQueryFrame( capture );
        if( !frame )
            break;
        if( !image )
        {
            /* allocate all the buffers */
            image = cvCreateImage( cvGetSize(frame), 8, 3 );
            image->origin = frame->origin;
            hsv = cvCreateImage( cvGetSize(frame), 8, 3 );
            hue = cvCreateImage( cvGetSize(frame), 8, 1 );
            mask = cvCreateImage( cvGetSize(frame), 8, 1 );
            backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
            hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 ); // 计算直方图
            histimg = cvCreateImage( cvSize(320,200), 8, 3 );
            cvZero( histimg );
        }
        cvCopy( frame, image, 0 );
        cvCvtColor( image, hsv, CV_BGR2HSV ); // 彩色空间转换 BGR to HSV 
        if( track_object )
        {
            int _vmin = vmin, _vmax = vmax;
            cvInRangeS( hsv, cvScalar(0,smin,MIN(_vmin,_vmax),0),
                        cvScalar(180,256,MAX(_vmin,_vmax),0), mask ); // 得到二值的MASK
            cvSplit( hsv, hue, 0, 0, 0 ); // 只提取 HUE 分量
            if( track_object < 0 )
            {
                float max_val = 0.f;
                cvSetImageROI( hue, selection ); // 得到选择区域 for ROI
                cvSetImageROI( mask, selection ); // 得到选择区域 for mask
                cvCalcHist( &hue, hist, 0, mask ); // 计算直方图
                cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 ); // 只找最大值
                cvConvertScale( hist->bins, hist->bins, max_val?255. / max_val : 0., 0 ); // 缩放 bin 到区间 [0,255] 
                cvResetImageROI( hue ); // remove ROI
                cvResetImageROI( mask );
                track_window = selection;
                track_object = 1;
                cvZero( histimg );
                bin_w = histimg->width / hdims; // hdims: 条的个数，则 bin_w 为条的宽度
                
                // 画直方图
                for( i = 0; i < hdims; i++ )
                {
                    int val = cvRound( cvGetReal1D(hist->bins,i)*histimg->height/255 );
                    CvScalar color = hsv2rgb(i*180.f/hdims);
                    cvRectangle( histimg, cvPoint(i*bin_w,histimg->height),
                                 cvPoint((i+1)*bin_w,histimg->height - val),
                                 color, -1, 8, 0 );
                }
            }
            cvCalcBackProject( &hue, backproject, hist ); // 使用 back project 方法
            cvAnd( backproject, mask, backproject, 0 );
            
            // calling CAMSHIFT 算法模块
            cvCamShift( backproject, track_window,
                        cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),
                        &track_comp, &track_box );
            track_window = track_comp.rect;
            
            if( backproject_mode )
                cvCvtColor( backproject, image, CV_GRAY2BGR ); // 使用backproject灰度图像
            if( image->origin )
                track_box.angle = -track_box.angle;
            cvEllipseBox( image, track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
        }
        
        if( select_object && selection.width > 0 && selection.height > 0 )
        {
            cvSetImageROI( image, selection );
            cvXorS( image, cvScalarAll(255), image, 0 );
            cvResetImageROI( image );
        }
        cvShowImage( "CamShiftDemo", image );
        cvShowImage( "Histogram", histimg );
        c = cvWaitKey(10);
        if( c == 27 )
            break; // exit from for-loop
        switch( c )
        {
        case 'b':
            backproject_mode ^= 1;
            break;
        case 'c':
            track_object = 0;
            cvZero( histimg );
            break;
        case 'h':
            show_hist ^= 1;
            if( !show_hist )
                cvDestroyWindow( "Histogram" );
            else
                cvNamedWindow( "Histogram", 1 );
            break;
        default:
            ;
        }
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow("CamShiftDemo");
    return 0;
}