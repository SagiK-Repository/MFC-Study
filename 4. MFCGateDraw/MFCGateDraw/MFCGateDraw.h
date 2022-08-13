
// MFCGateDraw.h : main header file for the MFCGateDraw application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCGateDrawApp:
// See MFCGateDraw.cpp for the implementation of this class
//

class CMFCGateDrawApp : public CWinApp
{
public:
	CMFCGateDrawApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCGateDrawApp theApp;
