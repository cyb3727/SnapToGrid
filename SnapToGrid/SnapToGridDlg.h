
// SnapToGridDlg.h : header file
//

#pragma once

#define MAX_POINT_WIDTH 8
#define MAX_POINT_HEIGHT 5

// CSnapToGridDlg dialog
class CSnapToGridDlg : public CDialogEx
{
// Construction
public:
	CSnapToGridDlg(CWnd* pParent = NULL);	// standard constructor
	~CSnapToGridDlg();

// Dialog Data
	enum { IDD = IDD_SNAPTOGRID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Program data
private:
	BOOL GetNearestPoint(CPoint ptMouse);

	POINT pt[MAX_POINT_WIDTH][MAX_POINT_HEIGHT];
	POINT ptNearest;
	CWnd *pWndPoint;				//Window to hold the circle
	CClientDC *pdcCircle;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);




};
