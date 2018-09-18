// EasyCopy.h : main header file for the EASYCOPY application
//

#if !defined(AFX_EASYCOPY_H__B5A627C6_F6E3_4EE6_90E9_A5C924B316B9__INCLUDED_)
#define AFX_EASYCOPY_H__B5A627C6_F6E3_4EE6_90E9_A5C924B316B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyCopyApp:
// See EasyCopy.cpp for the implementation of this class
//

class CEasyCopyApp : public CWinApp
{
public:
	CEasyCopyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyCopyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyCopyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYCOPY_H__B5A627C6_F6E3_4EE6_90E9_A5C924B316B9__INCLUDED_)
