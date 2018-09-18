// EasyCopyDlg.h : header file
//

#if !defined(AFX_EASYCOPYDLG_H__618A32D7_AC9E_4473_86CA_EFA7E4DBF727__INCLUDED_)
#define AFX_EASYCOPYDLG_H__618A32D7_AC9E_4473_86CA_EFA7E4DBF727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEasyCopyDlg dialog
#define SCANING_TIMER		            1000
#define STR_STRING1			_T("\\*.*")
#define CH_SLASH1			_T('\\')
#define SPACESIGN           _T(";")//项目分割符
#define FOLDSPACESIGN       _T("\\")
#define EVERYFILETYPE       _T("*.*")

#include "MyProgressCtrl.h"

class CEasyCopyDlg : public CDialog
{
// Construction

    
public:
	CEasyCopyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEasyCopyDlg)
	enum { IDD = IDD_EASYCOPY_DIALOG };
	CEdit	m_ExceptFiles;
	CStatic	m_Static_Time;
	CStatic	m_Static_Filenumber;
	CMyProgressCtrl	m_Progress_Copy;
	CListCtrl	m_DetailList;
	CEdit	m_Edit_Clew;
	CEdit	m_CopyType;
	CButton	m_StartCopy;
	CEdit	m_DestEdit;
	CEdit	m_SourceEdit;
	//}}AFX_DATA
private:
    typedef enum
	{
        SEARCHINGFILE,
        STOPSEARCHFILE,
		COPYFILEING,//正在拷贝
		STOPFILECOPY//停止拷贝
	}COPYSTATUS;
    COPYSTATUS CopyStatus;//操作状态

    HANDLE hThread;
    CString cSourcePath,cDestPath,cCopyType,cExceptFiles;
    DWORD dCopyFileCount;//For backup
    DWORD dCopyFileNumber;//文件个数
    DWORD dCopyFailureNumber;
    BOOL bCopyEveryType;//True:copy every type file.
    BOOL bHaveExceptFile;//True:need check except file list,false: needn't check it.
    int m_nTimer;
    int iUsedSecond;
    int iUsedMinute;
    int iUsedHour;
    CStringList ListCopyFileType;//copy file type list.
    CStringList ListExcpetCopyFile;//Don't copy files list.

    void AddFold(CEdit & edit);
    BOOL GetCopyFileType(void);
    BOOL GetExceptFiles(void);
    static int CALLBACK SetSelProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
    static UINT EasyCopyThread_SearchFile(LPVOID lpvData);
    BOOL IsInListFileTypes(CString FileType);//该文件类型是否在需要拷贝的类型中
    BOOL IsInExceptFileList(CString Filename);//该文件是否在排除拷贝的列表中
    BOOL CreateDirectoryFromString(CString csPath);
    BOOL PathIsValid(const CString path);
    void ThreadExit(void);
    void SaveCopyFailFile(CString displayfilename,CString destinationfolder);
    // ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyCopyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEasyCopyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonDestpath();
	afx_msg void OnButtonSourcepath();
	afx_msg void OnButtonBegin();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYCOPYDLG_H__618A32D7_AC9E_4473_86CA_EFA7E4DBF727__INCLUDED_)
