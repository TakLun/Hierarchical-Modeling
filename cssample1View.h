// cs560sample3View.h : interface of the CCs560sample3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CS560sample3VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
#define AFX_CS560sample3VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCssample1View : public CView
{
protected: // create from serialization only
	CCssample1View();
	DECLARE_DYNCREATE(CCssample1View)

// Attributes
public:
	CCssample1Doc* GetDocument();

// Operations
public:

	int m_GLPixelIndex;	
	HDC m_hDC;
	HGLRC m_hRC;

	GLdouble m_ytheta;
	GLdouble m_xtheta;
	GLdouble u, v, n;
	bool rotate_pos, rotate_neg;
	GLfloat left_cone_angle;
	GLfloat right_cone_angle;
	GLfloat left_cylinder_angle;
	GLfloat right_cylinder_angle;
	CPoint m_LDownPos;
	BOOL m_LButtonDown;

	int w, h;
	int view_option;
	// Setup GL view/projection matrices for window size.
    void SizeGL1(int w, int h);
    // Setup default params (lighting, etc...) for GL.
    void SetupGL();
    // Render scene using OpenGL.
    void RenderGLScene(int base_radius, int top_radius, int height);
	void RenderGLScene_Lever();
	void projection(int width, int height, int perspective);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCs560sample3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawGround();
	virtual ~CCssample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCs560sample3View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnIncX();
	afx_msg void OnDecX();
	afx_msg void OnDecY();
	afx_msg void OnIncY();
	afx_msg void OnViewOrtho();
	afx_msg void OnViewPerspective();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnCameraPitchdown();
	afx_msg void OnCameraPitchup32792();
	afx_msg void OnCameraRolldown();
	afx_msg void OnCameraRollup32794();
	afx_msg void OnCameraSliden32795();
	afx_msg void OnCameraSlidep();
	afx_msg void OnCameraYawdown32797();
	afx_msg void OnCameraYawup32798();
	afx_msg void OnLeverRotation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:


};

#ifndef _DEBUG  // debug version in cs560sample3View.cpp
inline CCssample1Doc* CCssample1View::GetDocument()
   { return (CCssample1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CS560sample3VIEW_H__72070A70_2B2E_4625_A38B_3C3967F61AFB__INCLUDED_)
