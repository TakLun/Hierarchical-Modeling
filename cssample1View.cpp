
#include "stdafx.h"
#include "cssample1.h"

#include "cssample1Doc.h"
#include "cssample1View.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCssample1View

IMPLEMENT_DYNCREATE(CCssample1View, CView)

BEGIN_MESSAGE_MAP(CCssample1View, CView)
	//{{AFX_MSG_MAP(CCssample1View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_INC_X, OnIncX)
	ON_COMMAND(ID_DEC_X, OnDecX)
	ON_COMMAND(ID_DEC_Y, OnDecY)
	ON_COMMAND(ID_INC_Y, OnIncY)
	ON_COMMAND(ID_VIEW_ORTHO, OnViewOrtho)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, OnViewPerspective)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_CAMERA_PITCHDOWN, OnCameraPitchdown)
	ON_COMMAND(ID_CAMERA_PITCHUP32792, OnCameraPitchup32792)
	ON_COMMAND(ID_CAMERA_ROLLDOWN, OnCameraRolldown)
	ON_COMMAND(ID_CAMERA_ROLLUP32794, OnCameraRollup32794)
	ON_COMMAND(ID_CAMERA_SLIDEN32795, OnCameraSliden32795)
	ON_COMMAND(ID_CAMERA_SLIDEP, OnCameraSlidep)
	ON_COMMAND(ID_CAMERA_YAWDOWN32797, OnCameraYawdown32797)
	ON_COMMAND(ID_CAMERA_YAWUP32798, OnCameraYawup32798)
	ON_COMMAND(ID_LEVER_ROTATION, OnLeverRotation)
	
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCssample1View construction/destruction

CCssample1View::CCssample1View()
{
	m_hDC=NULL;
	m_hRC=NULL;
	m_ytheta=m_xtheta=left_cone_angle=right_cone_angle=0; //camera rotation angle
	right_cylinder_angle = 0;
	left_cylinder_angle = 180;
	u = 0.0;
	v = 0.0;
	n = 40.0;
	w=h=0; //width and height of view area
	view_option=1;//perspective by default
}

CCssample1View::~CCssample1View()
{
}

BOOL CCssample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View drawing

void CCssample1View::OnDraw(CDC* pDC)
{
	CCssample1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect rcClient;
	GetClientRect(rcClient);
	
	w=rcClient.Width();
	h=rcClient.Height();

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	wglMakeCurrent(m_hDC,m_hRC);

	if(view_option==1){
	
		//down right view
		glViewport((int)(w/2.0), 0, (int)(w/2.0), (int)(h/2.0));
		projection(w/2, h/2, view_option);

		// Here we define the camera position on a sphere surround the object,
		// with radius 50.0. The camera keep focused on the center of the
		// object, which is position (0, 0, 0).

		gluLookAt(u,v,n, 0.0, 0.0, 0.0, 0, 1, 0);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
		RenderGLScene(5, 5, 30);	
	
		//V2
		//add code to generate the other 3 view
		glViewport(0, 0, (int)(w/2.0), (int)(h/2.0));
		projection(w/2, h/2, view_option);
		gluLookAt(0,40,0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		RenderGLScene_Lever();

		//V3
		glViewport(0, (int)(h/2.0), (int)(w/2.0), (int)(h/2.0));
		projection(w/2, h/2, view_option);
		gluLookAt(40, 0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		RenderGLScene_Lever();

		//V4
		glViewport((int)(w/2.0), (int)(h/2.0), (int)(w/2.0), (int)(h/2.0));
		projection(w/2, h/2, view_option);
		gluLookAt(0,0,40, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		RenderGLScene_Lever();

	
	}
	else{ //implement part 1, draw triangle
		glViewport((int)(w/2.0), 0, (int)(w/2.0), (int)(h/2.0));
		projection(w/2, h/2, view_option);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
		
		// draw triangle ...
	}

	glFlush();

	wglMakeCurrent(m_hDC,NULL);
//	wglMakeCurrent(m_hDC,m_hRC);
    ::SwapBuffers(m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View printing

BOOL CCssample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCssample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

void CCssample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{}

/////////////////////////////////////////////////////////////////////////////
// CCssample1View diagnostics

#ifdef _DEBUG
void CCssample1View::AssertValid() const
{
	CView::AssertValid();
}

void CCssample1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCssample1Doc* CCssample1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCssample1Doc)));
	return (CCssample1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCssample1View message handlers

int CCssample1View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	int nPixelFormat;				
	m_hDC = ::GetDC(m_hWnd);			

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	
		1,									
		PFD_DRAW_TO_WINDOW |			
		PFD_SUPPORT_OPENGL |			
		PFD_DOUBLEBUFFER,				
		PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0,					
		0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 
                PFD_MAIN_PLANE, 0, 0, 0, 0 
	};

    nPixelFormat = ::ChoosePixelFormat(m_hDC, &pfd);
    ::SetPixelFormat(m_hDC, nPixelFormat, &pfd);
    m_hRC = ::wglCreateContext(m_hDC);
    ::wglMakeCurrent(m_hDC,m_hRC);
    SetupGL();
    ::wglMakeCurrent(m_hDC,NULL);
	
	return 0;
}

void CCssample1View::OnDestroy() 
{
	CView::OnDestroy();
	// Clean up rendering context stuff
    ::wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);	
}

void CCssample1View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
		
    ::wglMakeCurrent(m_hDC,m_hRC);
    SizeGL1(cx, cy);
    ::wglMakeCurrent(NULL,NULL);

}

// Setup GL view/projection matrices for window size.
void CCssample1View::SizeGL1(int w, int h)
{
        // Correct for zero dimensions.
        h = h ? h : 1;
        w = w ? w : 1;
 
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, w, 0, h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*		glColor3ub(255, 255, 255);
		glBegin(GL_LINES);
			glVertex2i(w/2,0);
			glVertex2i(w/2,h);
			glVertex2i(0,h/2);
			glVertex2i(w,h/2);
		glEnd();
*/		glFlush();
}

void CCssample1View::SetupGL()
{
        glDepthFunc(GL_LEQUAL);
	    glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
}

void CCssample1View::projection(int width, int height, int perspective)
{
    float ratio = (float)width/height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective)
      gluPerspective(60, ratio, 1, 256);
    else 
      glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Render scene using OpenGL.
void CCssample1View::RenderGLScene(int base_radius, int top_radius, int height)
{
	// draw a cylinder or a sphere, 
	// you will draw more objects in this function
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_LINE);
    //gluSphere (quadObj, 25, 60, 60);              //draw a sphere
 	gluCylinder(quadObj, base_radius, top_radius, height, 25, 25);       //draw a cone shape cylinder
	DrawGround();								  //draw ground lines for reference	
    gluDeleteQuadric(quadObj);
	glFlush();
}

// Render scene using OpenGL.
void CCssample1View::RenderGLScene_Lever()
{
	// draw a cylinder or a sphere, 
	// you will draw more objects in this function
    GLUquadricObj* quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_LINE);

	//Center sphere
	glPushMatrix();
	glRotatef(left_cylinder_angle, 0.0, 1.0, 0.0);
	gluSphere (quadObj, 2, 20, 20);
	glPopMatrix();

	//Center Cylinder Pivot
	glPushMatrix();
	glTranslatef(0.0,-2.0, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadObj, 1, 1, 20, 15, 15);
	glPopMatrix();

	//Left Cylinder
	glPushMatrix();
	glRotatef(left_cylinder_angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0.0,1.5);
	gluCylinder(quadObj, 1, 1, 10, 15, 15);
	glPopMatrix();

	//Right Cylinder
	glPushMatrix();
	glRotatef(right_cylinder_angle, 0.0, 1.0, 0.0);
	glTranslatef(0,0.0,1.5);
	gluCylinder(quadObj, 1, 1, 10, 15, 15);
	glPopMatrix();

	//Left sphere
	glPushMatrix();
	glRotatef(left_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(left_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,0.0,12.5);
	gluSphere (quadObj, 2, 20, 20);
	glPopMatrix();

	//Right Sphere
	glPushMatrix();
	glRotatef(right_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(right_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,0.0,12.5);
	gluSphere (quadObj, 2, 20, 20);
	glPopMatrix();

	//Left Cone
	glPushMatrix();
	glRotatef(left_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(left_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,-2.0,12.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadObj, 0, 1, 10, 15, 15);
	glPopMatrix();

	//Right Cone
	glPushMatrix();
	glRotatef(right_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(right_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,-2.0,12.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluCylinder(quadObj, 0, 1, 10, 15, 15);
	glPopMatrix();

	//Left Large Sphere
	glPushMatrix();
	glRotatef(left_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(left_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,-14.0,12.5);
	gluSphere (quadObj, 4, 20, 20);
	glPopMatrix();

	//Right Large Sphere
	glPushMatrix();
	glRotatef(right_cylinder_angle, 0.0, 1.0, 0.0);
	glRotatef(right_cone_angle, 0.0, 0.0, 1.0);
	glTranslatef(0,-14.0,12.5);
	gluSphere (quadObj, 4, 20, 20);
	glPopMatrix();

	DrawGround(); //draw ground lines for reference	
    gluDeleteQuadric(quadObj);
	glFlush();
}

void CCssample1View::OnIncX() 
{
	m_xtheta+=15.0/360.;
	InvalidateRect(NULL, FALSE);
}

void CCssample1View::OnDecX() 
{
	m_xtheta-=15.0/360.;
	InvalidateRect(NULL, FALSE);	
}

void CCssample1View::OnDecY() 
{
	m_ytheta-=15.0/360.;
	InvalidateRect(NULL, FALSE);	
}

void CCssample1View::OnIncY() 
{
	m_ytheta+=15.0/360.;
	InvalidateRect(NULL, FALSE);	
}

void CCssample1View::OnViewOrtho() 
{
	view_option=0;	
	InvalidateRect(NULL, FALSE);	
}

void CCssample1View::OnViewPerspective() 
{
	view_option=1;
	InvalidateRect(NULL, FALSE);	
}

void CCssample1View::DrawGround()
{
    glBegin(GL_LINES);
	for(int i =-15; i<=15; i++)
	{
		glVertex3f(i*5.f, -10.f, -100.f);
		glVertex3f(i*5.f, -10.f, 100.f);
	}
		for(int j =-15; j<=15; j++)
	{
		glVertex3f(-100.f, -10.f, j*5.f);
		glVertex3f(100.f, -10.f, j*5.f);
	}
	glEnd();
	
}

//for part 1, ortho view triangle
void CCssample1View::OnViewZoomin() 
{
	// TODO: Add your command handler code here
	
}

void CCssample1View::OnViewZoomout() 
{
	// TODO: Add your command handler code here
	
}

//for part 2, perspective view objects rotation
void CCssample1View::OnCameraPitchdown() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	v = cos((10*3.1415926535)/180)*v_temp - sin((10*3.1415926535)/180)*n_temp;
	n = sin((10*3.1415926535)/180)*v_temp + cos((10*3.1415926535)/180)*n_temp;

	InvalidateRect(NULL, FALSE);
	
}

void CCssample1View::OnCameraPitchup32792() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	v = cos((-10*3.1415926535)/180)*v_temp - sin((-10*3.1415926535)/180)*n_temp;
	n = sin((-10*3.1415926535)/180)*v_temp + cos((-10*3.1415926535)/180)*n_temp;

	InvalidateRect(NULL, FALSE);

}

void CCssample1View::OnCameraRolldown() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	u = cos((-10*3.1415926535)/180)*u_temp - sin((-10*3.1415926535)/180)*v_temp;
	v = sin((-10*3.1415926535)/180)*u_temp + cos((-10*3.1415926535)/180)*v_temp;

	InvalidateRect(NULL, FALSE);
	
}

void CCssample1View::OnCameraRollup32794() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	u = cos((10*3.1415926535)/180)*u_temp - sin((10*3.1415926535)/180)*v_temp;
	v = sin((10*3.1415926535)/180)*u_temp + cos((10*3.1415926535)/180)*v_temp;

	InvalidateRect(NULL, FALSE);
	
}

void CCssample1View::OnCameraSliden32795() 
{
	n+=1;
	InvalidateRect(NULL, FALSE);
}

void CCssample1View::OnCameraSlidep() 
{
	n-=1;
	InvalidateRect(NULL, FALSE);
}

void CCssample1View::OnCameraYawdown32797() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	n = cos((-10*3.1415926535)/180)*n_temp - sin((-10*3.1415926535)/180)*u_temp;
	u = sin((-10*3.1415926535)/180)*n_temp + cos((-10*3.1415926535)/180)*u_temp;

	InvalidateRect(NULL, FALSE);
}

void CCssample1View::OnCameraYawup32798() 
{
	double u_temp = u;
	double v_temp = v;
	double n_temp = n;
	n = cos((10*3.1415926535)/180)*n_temp - sin((10*3.1415926535)/180)*u_temp;
	u = sin((10*3.1415926535)/180)*n_temp + cos((10*3.1415926535)/180)*u_temp;

	InvalidateRect(NULL, FALSE);
}

void CCssample1View::OnLeverRotation() 
{
	left_cone_angle+=10;
	right_cone_angle+=10;
	left_cylinder_angle+=10;
	right_cylinder_angle+=10;
	InvalidateRect(NULL, FALSE);
	
}

//mouse handling function not required so far
void CCssample1View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LButtonDown = TRUE;
	m_LDownPos = point;
	CView::OnLButtonDown(nFlags, point);
}

void CCssample1View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_LButtonDown)
	{
		CSize rotate = m_LDownPos - point;
		m_LDownPos = point;
		InvalidateRect(NULL, FALSE);
	}
	
	CView::OnMouseMove(nFlags, point);
}


void CCssample1View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LButtonDown = FALSE;	
	CView::OnLButtonUp(nFlags, point);	
}