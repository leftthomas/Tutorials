
// DesignView.h : CDesignView 类的接口
//

#pragma once

#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
class CDesignView : public CView
{
protected: // 仅从序列化创建
	CDesignView();
	DECLARE_DYNCREATE(CDesignView)

// 特性
public:
	CDesignDoc* GetDocument() const;
	int ImageAdjust(IplImage* src, IplImage* dst,double low, double high,double bottom, double top, double gamma );
	CvSubdiv2D* init_delaunay( CvMemStorage* storage,CvRect rect );
	void draw_subdiv_point( IplImage* img, CvPoint2D32f fp, CvScalar color );
	void draw_subdiv_edge( IplImage* img, CvSubdiv2DEdge edge, CvScalar color );
	void draw_subdiv( IplImage* img, CvSubdiv2D* subdiv,CvScalar delaunay_color, CvScalar voronoi_color );
	void locate_point( CvSubdiv2D* subdiv, CvPoint2D32f fp, IplImage* img,CvScalar active_color );
	void draw_subdiv_facet( IplImage* img, CvSubdiv2DEdge edge );
	void paint_voronoi( CvSubdiv2D* subdiv, IplImage* img );
	CvScalar random_color(CvRNG* rng);
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CDesignView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCanny();
	afx_msg void OnCorner();
	afx_msg void Onrotate();
	afx_msg void Onzoom();
	afx_msg void OnLog();
	afx_msg void OnGauss();
	afx_msg void OnSobel();
	afx_msg void OnLaplace();
	afx_msg void OnPrewitt();
	afx_msg void Onpyramid();
	afx_msg void OnErode();
	afx_msg void OnDilate();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnGray();
	afx_msg void OnReverse();
	afx_msg void OnBrightness();
	afx_msg void OnHist();
	afx_msg void OnEqualize();
	afx_msg void OnHoughlines();
	afx_msg void OnHoughcircles();
	afx_msg void OnDistancetransform();
	afx_msg void OnHull();
	afx_msg void OnDelaunay();
	afx_msg void OnTone();
	afx_msg void OnDrawing();
	afx_msg void OnLaplacecam();
	afx_msg void OnBkgrd();
	afx_msg void OnOpencam();
	afx_msg void OnSusan();
	afx_msg void OnKalman();
};

#ifndef _DEBUG  // DesignView.cpp 中的调试版本
inline CDesignDoc* CDesignView::GetDocument() const
   { return reinterpret_cast<CDesignDoc*>(m_pDocument); }
#endif

