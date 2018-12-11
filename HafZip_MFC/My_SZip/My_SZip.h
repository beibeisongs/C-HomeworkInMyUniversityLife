
// My_SZip.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy_SZipApp:
// See My_SZip.cpp for the implementation of this class
//

class CMy_SZipApp : public CWinApp
{
public:
	CMy_SZipApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy_SZipApp theApp;