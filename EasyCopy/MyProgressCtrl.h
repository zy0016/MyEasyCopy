#if !defined(AFX_MYPROGRESSCTRL_H__E59ED7C7_B805_4C50_929C_47E5EF0A67ED__INCLUDED_)
#define AFX_MYPROGRESSCTRL_H__E59ED7C7_B805_4C50_929C_47E5EF0A67ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgressCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyProgressCtrl window

class CMyProgressCtrl : public CProgressCtrl
{
private:
	DWORD iPos;	// The current position
	DWORD iLower;
	DWORD iUpper;
	DWORD iStep;

	CRect rFresh;//��Ҫˢ�µ�����
	CRect rFillin;//��������������
	CRect rctxt;//��ʾ���ֵ�����

	DWORD iRectFillRight;//ˢ�º�������right
	DWORD iOldPre;//����ԭ���İٷֱ�����,���û�и��µĻ��Ͳ�������ʾ
	COLORREF crFillColor;
	COLORREF crTextColor;
	BOOL bShowPre;//�Ƿ���ʾ�ٷֱ�
// Construction
public:
	CMyProgressCtrl();

// Attributes
public:
	DWORD SetPos( DWORD nPos );
	void SetRange( DWORD nLower, DWORD nUpper );
	DWORD SetStep( DWORD nStep );
	void SetProgressFillColor(COLORREF crColor);
	void SetProgressTextColor(COLORREF crColor);
	void ShowPreText(BOOL bShow);
	void ResetProgressData(void);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyProgressCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESSCTRL_H__E59ED7C7_B805_4C50_929C_47E5EF0A67ED__INCLUDED_)