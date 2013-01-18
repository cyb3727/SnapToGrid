
// SnapToGrid.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSnapToGridApp:
// See SnapToGrid.cpp for the implementation of this class
//

class CSnapToGridApp : public CWinApp
{
public:
	CSnapToGridApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSnapToGridApp theApp;