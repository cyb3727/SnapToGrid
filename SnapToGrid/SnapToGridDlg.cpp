
// SnapToGridDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SnapToGrid.h"
#include "SnapToGridDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIDTH						420	//The width of point matrix
#define HEIGHT						300	//The height of point matrix
#define RANGE						50	//The distance between two points
#define NEAREST_RANGE					250	//Defined to judge whether the mouse is within the range
#define R_CIRCLE					6	//The width of the window to hold the point


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSnapToGridDlg dialog




CSnapToGridDlg::CSnapToGridDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnapToGridDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	pWndPoint = new CWnd;					//Alloacte the subwindow

	//Initiate the point matrix
	for(int i=0; (i+1)*RANGE<WIDTH; i++)
			for(int j=0; (j+1)*RANGE<HEIGHT; j++)
			{
				pt[i][j].x = (i+1)*RANGE;
				pt[i][j].y = (j+1)*RANGE;
			}
}
CSnapToGridDlg::~CSnapToGridDlg()
{
	delete pWndPoint;
	delete pdcCircle;
}

void CSnapToGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSnapToGridDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSnapToGridDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSnapToGridDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CSnapToGridDlg message handlers

BOOL CSnapToGridDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	pWndPoint->Create(NULL, L"WND_POINT", WS_CHILD | WS_VISIBLE, 
		CRect(-R_CIRCLE, -R_CIRCLE, R_CIRCLE, R_CIRCLE), this, WND_POINT);

	pdcCircle = new CClientDC(pWndPoint);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSnapToGridDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSnapToGridDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		pdcCircle->Ellipse(0, 0, R_CIRCLE, R_CIRCLE);			//Draw the circle
		
		//Draw the point matrix
		CClientDC dc(this);
		for(int i=0; (i+1)*RANGE<WIDTH; i++)
			for(int j=0; (j+1)*RANGE<HEIGHT; j++)
			{
				dc.SetPixel(pt[i][j].x, pt[i][j].y, RGB(0, 0, 0));
			}


		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSnapToGridDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSnapToGridDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CSnapToGridDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void CSnapToGridDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	CDialogEx::OnClose();
}


void CSnapToGridDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	PostQuitMessage(1);
}


inline int RoundTo(double x)
{
	return (int)(x+0.5);
}
inline int Squre(int x)
{
	x = abs(x);
	return x * x;
}

//Get the nearst point near the mouse
BOOL CSnapToGridDlg::GetNearestPoint(CPoint ptMouse)
{
	//Get the subscript of the point in the matrix
	int m = RoundTo(1.0 * ptMouse.x / RANGE) - 1;
	int n = RoundTo(1.0 * ptMouse.y / RANGE) - 1;

	if(
		(0 <= m && m < MAX_POINT_WIDTH)
		&& (0 <= n && n < MAX_POINT_HEIGHT)		//Whether within the range of matrix
		&& (ptMouse != pt[m][n])			//Ignore if mouse is on the point to reduce the usage of CPU
		&& (Squre(ptMouse.x - pt[m][n].x) + Squre(ptMouse.y - pt[m][n].y)< NEAREST_RANGE)
	)
	{
		//Nearest point found
		ptNearest = pt[m][n];

		return TRUE;
	}
	else
	{
		//Nearest point not found
		return FALSE;
	}
}


void CSnapToGridDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if(GetNearestPoint(point))
	{
		//If nearest point found, move the circle to the point
		pWndPoint->MoveWindow(ptNearest.x - R_CIRCLE/2, ptNearest.y - R_CIRCLE/2, R_CIRCLE, R_CIRCLE);
	}
	else
	{
		//If not found, move the circle to follow mouse
		pWndPoint->MoveWindow(point.x - R_CIRCLE/2, point.y - R_CIRCLE/2, R_CIRCLE, R_CIRCLE);
	}
	

	CDialogEx::OnMouseMove(nFlags, point);	
}

