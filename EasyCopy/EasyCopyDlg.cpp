// EasyCopyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EasyCopy.h"
#include "EasyCopyDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BIF_USENEWUI                0x0050
/*static const CString StrCopyFile = 
"*.c;*.cpp;*.h;*.inc;*.hi;*.config;*.component;*.feature;*.domain;*.resource;*.ti;*.txt;*.gz;*.vsd;*.xml;*.sx;*.sxdef";*/
static const int iItemFileWidch = 100;
static const int iItemFilePathWidch = 500;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyCopyDlg dialog

CEasyCopyDlg::CEasyCopyDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CEasyCopyDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CEasyCopyDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEasyCopyDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEasyCopyDlg)
	DDX_Control(pDX, IDC_EDIT_EXCEPT, m_ExceptFiles);
    DDX_Control(pDX, IDC_STATIC_TIME, m_Static_Time);
    DDX_Control(pDX, IDC_STATIC_FILENUMBER, m_Static_Filenumber);
    DDX_Control(pDX, IDC_PROGRESS_COPY, m_Progress_Copy);
    DDX_Control(pDX, IDC_LIST_FILE_INFORMATION, m_DetailList);
    DDX_Control(pDX, IDC_EDIT_CLEW, m_Edit_Clew);
    DDX_Control(pDX, IDC_EDIT_COPYTYPE, m_CopyType);
    DDX_Control(pDX, IDC_BUTTON_BEGIN, m_StartCopy);
    DDX_Control(pDX, IDC_EDIT2, m_DestEdit);
    DDX_Control(pDX, IDC_EDIT1, m_SourceEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEasyCopyDlg, CDialog)
    //{{AFX_MSG_MAP(CEasyCopyDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_DESTPATH, OnButtonDestpath)
    ON_BN_CLICKED(IDC_BUTTON_SOURCEPATH, OnButtonSourcepath)
    ON_BN_CLICKED(IDC_BUTTON_BEGIN, OnButtonBegin)
    ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyCopyDlg message handlers

BOOL CEasyCopyDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    // TODO: Add extra initialization here
    CString StrCopyFile,strCludeFile;
    StrCopyFile.LoadString(IDS_STRING_COPY_TYPE);
    m_CopyType.SetWindowText(StrCopyFile);

    strCludeFile.LoadString(IDS_STRING_EXCLUDE_FILE);
    m_ExceptFiles.SetWindowText(strCludeFile);
    
    m_SourceEdit.SetFocus();

    CString filename,filesource,filedestination;
    filename.LoadString(IDS_STRING_FILENAME);
    filesource.LoadString(IDS_STRING_FILEPLACE);
    filedestination.LoadString(IDS_STRING_DESTINATION_FILE);

    DWORD oldStyle = m_DetailList.GetExtendedStyle();
    m_DetailList.SetExtendedStyle(oldStyle |LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);
    m_DetailList.InsertColumn(0,filename,       LVCFMT_LEFT,iItemFileWidch,0);
    m_DetailList.InsertColumn(1,filesource,     LVCFMT_LEFT,iItemFilePathWidch,0);
    m_DetailList.InsertColumn(2,filedestination,LVCFMT_LEFT,iItemFilePathWidch,0);
    m_Progress_Copy.ShowWindow(FALSE);
    
    return FALSE;  // return TRUE  unless you set the focus to a control
}

void CEasyCopyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEasyCopyDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEasyCopyDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CEasyCopyDlg::OnButtonDestpath() 
{
    // TODO: Add your control notification handler code here
    AddFold(m_DestEdit);
}

void CEasyCopyDlg::OnButtonSourcepath() 
{
    // TODO: Add your control notification handler code here
    AddFold(m_SourceEdit);
}

int CALLBACK CEasyCopyDlg::SetSelProc(HWND hWnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED)
        ::SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData);

    return 0;
}

void CEasyCopyDlg::AddFold(CEdit & edit)
{
    CString cItemName;//项目名    
    CString cSelectFold;
    BROWSEINFO bi;         
    TCHAR Dir[MAX_PATH];
    ITEMIDLIST * pidl;
    
    edit.GetWindowText(cItemName);//获得commbox控件中的内容
    
    cSelectFold.LoadString(IDS_STRING_SELECTFOLD);
    
    bi.hwndOwner        = this->GetSafeHwnd();
    bi.pidlRoot         = NULL;
    bi.pszDisplayName   = Dir; 
    bi.lpszTitle        = cSelectFold;//"选择目录并按下[确定]按钮"; //选择目录
    bi.ulFlags          = BIF_USENEWUI;//BIF_RETURNONLYFSDIRS ; 
    bi.lpfn             = SetSelProc;
    bi.lParam           = (LPARAM)(LPCTSTR)cItemName;
    bi.iImage           = 0; 
    pidl                = SHBrowseForFolder(&bi);
    
    if (pidl == NULL) 
        memset(Dir,0,sizeof(MAX_PATH));
    if (SHGetPathFromIDList(pidl,Dir))/*Retrieve folder name from ITEMLIST structure.*/ 
    {
        edit.SetWindowText(Dir);
    }
}
BOOL CEasyCopyDlg::GetCopyFileType(void)
{
    int iSpace;
    CString cSingleFileType,cClew,cResult;
    
    ListCopyFileType.RemoveAll();
    m_CopyType.GetWindowText(cCopyType);
    if (cCopyType == "")
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_CLEW_1);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        return FALSE;
    }

    bCopyEveryType = FALSE;
    if (cCopyType.Find(EVERYFILETYPE) != -1)
    {
        bCopyEveryType = TRUE;
        return TRUE;        
    }

    while (1)
    {
        iSpace = cCopyType.Find(SPACESIGN);
        if (iSpace == -1)
        {
            cSingleFileType = cCopyType.Right(cCopyType.GetLength() - 2);
            ListCopyFileType.AddHead(cSingleFileType);
            break;
        }
        cSingleFileType = cCopyType.Left(iSpace);
        cCopyType       = cCopyType.Right(cCopyType.GetLength() - iSpace - 1);
        cSingleFileType = cSingleFileType.Right(cSingleFileType.GetLength() - 2);
        ListCopyFileType.AddHead(cSingleFileType);
    }
    return TRUE;
}

BOOL CEasyCopyDlg::GetExceptFiles(void)
{
    int iSpace;
    CString cSingleFile;

    ListExcpetCopyFile.RemoveAll();
    bHaveExceptFile = FALSE;
    
    if (cExceptFiles == "")
    {
        return TRUE;
    }

    if (cExceptFiles.Right(1) == SPACESIGN)
    {
        cExceptFiles = cExceptFiles.Left(cExceptFiles.GetLength() - 1);
    }
    while (1)
    {
        iSpace = cExceptFiles.Find(SPACESIGN);
        if (iSpace == -1)
        {
            ListExcpetCopyFile.AddHead(cExceptFiles);
            break;
        }
        cSingleFile  = cExceptFiles.Left(iSpace);
        cExceptFiles = cExceptFiles.Right(cExceptFiles.GetLength() - iSpace - 1);
        ListExcpetCopyFile.AddHead(cSingleFile);
    }
    bHaveExceptFile = TRUE;
    return TRUE;
}

void CEasyCopyDlg::ThreadExit(void)
{
    CString cClew,StartText,cSuspend,cCause;
    CWaitCursor wait;

    if (CopyStatus != COPYFILEING)
        return;
    
    Sleep(500);//不加这句话的话有可能导致调用SuspendThread之后出现异常
    KillTimer(SCANING_TIMER);
    m_nTimer = NULL;
    
    cClew.LoadString(IDS_STRING_CLEW);
    if (SuspendThread(hThread) == 0xFFFFFFFF)
    {
        cSuspend.LoadString(IDS_STRING_SUSPENDTHREADERROR);            
        MessageBox(cSuspend,cClew,MB_ICONINFORMATION|MB_OK);//线程中止异常
    }
    cCause.LoadString(IDS_STRING_PAUSECLEW);
    if (MessageBox(cCause,cClew, MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) == IDNO)//是否中止操作?
    {
        m_nTimer = SetTimer(SCANING_TIMER, 1000, NULL);//打开计时器显示时间
        ResumeThread(hThread);
        return;
    }
    CopyStatus = STOPFILECOPY;
    CloseHandle(hThread);
    
    StartText.LoadString(IDS_STRING_START);
    m_StartCopy.SetWindowText(StartText);
    m_Progress_Copy.ShowWindow(FALSE);
}

void CEasyCopyDlg::OnButtonBegin() 
{
    // TODO: Add your control notification handler code here
    DWORD dThread;//线程号
    CString StopText,StartText,SearchingText,cClew,cResult;

    if (CopyStatus == COPYFILEING)
    {
        ThreadExit();
        return;
    }
    m_SourceEdit.GetWindowText(cSourcePath);
    m_DestEdit.GetWindowText(cDestPath);
    m_CopyType.GetWindowText(cCopyType);
    m_ExceptFiles.GetWindowText(cExceptFiles);
    
    if (cSourcePath == "")
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_CLEW3);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        m_SourceEdit.SetFocus();
        return;
    }
    if (cDestPath == "")
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_CLEW4);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        m_DestEdit.SetFocus();
        return;
    }
    if (cSourcePath == cDestPath)
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_ERROR1);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        return;
    }
    if (!PathIsValid(cSourcePath))
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_SOURCEPATH_ERROR);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        m_SourceEdit.SetFocus();
        return;
    }
    if (!PathIsValid(cDestPath))
    {
        cClew.LoadString(IDS_STRING_CLEW);
        cResult.LoadString(IDS_STRING_DESTINATIONPATH_ERROR);
        MessageBox(cResult,cClew,MB_ICONERROR|MB_OK);
        m_DestEdit.SetFocus();
        return;
    }

    if (cSourcePath.Right(1) == FOLDSPACESIGN)
    {
        cSourcePath = cSourcePath.Left(cSourcePath.GetLength() - 1);
    }
    if (cDestPath.Right(1) == FOLDSPACESIGN)
    {
        cDestPath = cDestPath.Left(cDestPath.GetLength() - 1);
    }
    if (cCopyType.Right(1) == SPACESIGN)
    {
        cCopyType = cCopyType.Left(cCopyType.GetLength() - 1);
    }

    if (!GetCopyFileType())
    {
        return;
    }

    GetExceptFiles();//get the don't copy files name.

    StopText.LoadString(IDS_STRING_STOP);
    SearchingText.LoadString(IDS_STRING_CLEW2);
    
    m_StartCopy.SetWindowText(StopText);
    m_StartCopy.EnableWindow(FALSE);

    m_Static_Filenumber.SetWindowText(SearchingText);

    iUsedSecond = 0;//扫描计时器清零
    iUsedMinute = 0;
    iUsedHour   = 0;
    m_nTimer    = SetTimer(SCANING_TIMER, 1000, NULL);//Begin to count the file number
    
    hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)EasyCopyThread_SearchFile,this,0,&dThread);
}
UINT CEasyCopyDlg::EasyCopyThread_SearchFile(LPVOID lpvData)
{
    CEasyCopyDlg   *pThis = (CEasyCopyDlg*)lpvData;
    CStringList     listPaths;
    CString         strPath,strFilePath,filename,cExpend,StopText,cResult,cFilenumber,StartText;
    CString         destinationfile,destinationfolder,cCopyFileNumber,cCopyFileResult,displayfilename;
    int             iExpend,iPreFoldSpace,itemp;
    BOOL            bWorking,bNeedCopy;
    CFileFind       find;

    pThis->CopyStatus = SEARCHINGFILE;
    pThis->dCopyFileNumber = 0;
    listPaths.RemoveAll();
    pThis->m_DetailList.DeleteAllItems();
    strPath = pThis->cSourcePath + STR_STRING1;
    cCopyFileNumber.LoadString(IDS_STRING_COPYING_FILEINFO);

    do 
    {
        bWorking = find.FindFile(strPath);
        while (bWorking && pThis->CopyStatus == SEARCHINGFILE)
        {
            bWorking    = find.FindNextFile();
            strFilePath = find.GetFilePath();
            
            if (find.IsDots())
                continue;
            
            if (find.IsDirectory())
            {
                listPaths.AddHead(strFilePath);
                continue;
            }
            else
            {
                filename = find.GetFilePath();//获得文件名(包括路径)
                itemp    = filename.ReverseFind('\\');
                iExpend  = filename.ReverseFind('.');//获得扩展名左边的"."
                /*path: path.path\makefile        */
                pThis->m_Edit_Clew.SetWindowText(filename);
                if (iExpend != -1 && iExpend > itemp)//fine the extend file.
                {
                    cExpend = filename.Right(filename.GetLength() - iExpend - 1);//获得扩展名
                    cExpend.MakeLower();

                    if (pThis->IsInListFileTypes(cExpend) && !pThis->IsInExceptFileList(filename))
                    {
                        pThis->dCopyFileNumber++;
                    }
                }
                else if (!pThis->IsInExceptFileList(filename))//Copy the file without extend filename.
                {
                    pThis->dCopyFileNumber++;
                }
            }
        }
        if(listPaths.IsEmpty())
        {
            cFilenumber.LoadString(IDS_STRING_FILENUMBERCLEW);
            cResult.Format(cFilenumber,pThis->dCopyFileNumber);
            pThis->m_Edit_Clew.SetWindowText(cResult);

            pThis->CopyStatus = STOPSEARCHFILE;
            break;
        }
        strPath = listPaths.RemoveHead() + STR_STRING1;//"\\*.*"
        find.Close();
    } while(pThis->CopyStatus == SEARCHINGFILE);
    //////////////////////////////////////////////////////////////////////////
    //Begin copy file!
    //////////////////////////////////////////////////////////////////////////
    listPaths.RemoveAll();
    pThis->m_DetailList.DeleteAllItems();
	pThis->m_Progress_Copy.ResetProgressData();
    pThis->m_Progress_Copy.ShowWindow(TRUE);
    pThis->m_Progress_Copy.SetRange(0,pThis->dCopyFileNumber);
    pThis->m_Progress_Copy.SetPos(0);
    pThis->m_Progress_Copy.SetStep(1);
    pThis->m_Progress_Copy.SetProgressFillColor(RGB(255,0,0));
    pThis->m_Progress_Copy.SetProgressTextColor(RGB(0,0,255));
    pThis->m_Progress_Copy.ShowPreText(TRUE);

    pThis->dCopyFileCount       = pThis->dCopyFileNumber;
    pThis->dCopyFileNumber      = 0;
    pThis->dCopyFailureNumber   = 0;
    strPath                     = pThis->cSourcePath + STR_STRING1;
    pThis->CopyStatus           = COPYFILEING;

    StopText.LoadString(IDS_STRING_STOP);
    pThis->m_StartCopy.SetWindowText(StopText);
    pThis->m_StartCopy.EnableWindow(TRUE);

    iPreFoldSpace = pThis->cSourcePath.ReverseFind(CH_SLASH1);//'\\'
    do 
    {
        bWorking = find.FindFile(strPath);
        while (bWorking && pThis->CopyStatus == COPYFILEING)
        {
            bWorking    = find.FindNextFile();
            strFilePath = find.GetFilePath();

            if (find.IsDots())
                continue;
            
            if (find.IsDirectory())
            {
                listPaths.AddHead(strFilePath);
                continue;
            }
            else
            {
                bNeedCopy = FALSE;
                filename  = find.GetFilePath();//获得文件名(包括路径)
                itemp     = filename.ReverseFind('\\');
                iExpend   = filename.ReverseFind('.');//获得扩展名左边的"."
                pThis->m_Edit_Clew.SetWindowText(filename);
                if (iExpend != -1 && iExpend > itemp)//fine the extend file.
                {
                    cExpend = filename.Right(filename.GetLength() - iExpend - 1);//获得扩展名
                    cExpend.MakeLower();

                    if (pThis->IsInListFileTypes(cExpend) && !pThis->IsInExceptFileList(filename))
                    {
                        bNeedCopy = TRUE;
                    }
                }
                else if (!pThis->IsInExceptFileList(filename))
                {
                    bNeedCopy = TRUE;
                }
                if (bNeedCopy && iPreFoldSpace != -1)
                {
                    destinationfile = pThis->cDestPath + FOLDSPACESIGN + //"\\"
                        filename.Right(filename.GetLength() - iPreFoldSpace - 1);

                    pThis->CreateDirectoryFromString(destinationfile);
                    if (!CopyFile(filename,destinationfile,FALSE))
                    {
                        destinationfolder = strFilePath.Left(strFilePath.ReverseFind(CH_SLASH1));
                        displayfilename   = filename.Right(filename.GetLength() - filename.ReverseFind(CH_SLASH1) - 1);

                        pThis->SaveCopyFailFile(displayfilename,destinationfolder);

                        pThis->dCopyFailureNumber++;
                    }
                    pThis->dCopyFileNumber++;

                    pThis->m_Progress_Copy.SetPos(pThis->dCopyFileNumber);
                    cCopyFileResult.Format(cCopyFileNumber,pThis->dCopyFileNumber,pThis->dCopyFileCount);
                    pThis->m_Static_Filenumber.SetWindowText(cCopyFileResult);
                }
            }
        }
        if(listPaths.IsEmpty())
        {
            cFilenumber.LoadString(IDS_STRING_COPYFAIL_NUM);
            StartText.LoadString(IDS_STRING_START);
            cResult.Format(cFilenumber,pThis->dCopyFileNumber,pThis->dCopyFailureNumber);

            pThis->m_StartCopy.SetWindowText(StartText);
            pThis->m_StartCopy.EnableWindow(TRUE);

            pThis->m_Edit_Clew.SetWindowText(cResult);
            pThis->m_Progress_Copy.ShowWindow(FALSE);

            pThis->CopyStatus = STOPFILECOPY;
            pThis->KillTimer(pThis->m_nTimer);
            break;
        }
        strPath = listPaths.RemoveHead() + STR_STRING1;//"\\*.*"
        find.Close();
    }while(pThis->CopyStatus == COPYFILEING);
    return 0;
}
void CEasyCopyDlg::SaveCopyFailFile(CString displayfilename,CString destinationfolder)
{
    CString cFail;
    DWORD ListCount;

    cFail.LoadString(IDS_STRING_COPYFILE_FAIL);
    ListCount = m_DetailList.GetItemCount();

    m_DetailList.InsertItem (ListCount,displayfilename);//add the filename
    m_DetailList.SetItemText(ListCount,1,destinationfolder);//add the path
    m_DetailList.SetItemText(ListCount,2,cFail);//add the path
}
//根据传进来的文件名或者目录名创建所需的目录
BOOL CEasyCopyDlg::CreateDirectoryFromString(CString csPath)
{
    TCHAR CurrentDirectory[MAX_PATH];
    CString singlepath = "";
    int ispace;

    GetCurrentDirectory(sizeof(CurrentDirectory),CurrentDirectory);
    ispace = csPath.Find(FOLDSPACESIGN);

    if (-1 == ispace)
    {
        SetCurrentDirectory(CurrentDirectory);
        return FALSE;
    }
    while (ispace != -1)
    {
        if (singlepath != "")
            singlepath = singlepath + FOLDSPACESIGN + csPath.Left(ispace);//获得某一级目录名"\\"
        else
            singlepath = csPath.Left(ispace);//获得某一级目录名

        if (!SetCurrentDirectory(singlepath))//目录不存在
        {
            if (!CreateDirectory(singlepath,NULL))
            {
                SetCurrentDirectory(CurrentDirectory);
                return FALSE;
            }
        }
        csPath = csPath.Right(csPath.GetLength() - ispace - 1);
        ispace = csPath.Find(FOLDSPACESIGN);
    }
    SetCurrentDirectory(CurrentDirectory);
    return TRUE;
}

BOOL CEasyCopyDlg::IsInListFileTypes(CString FileType)//if the file type is in copy type list
{
    int i,iStringListCount;
    CString csFileType;
    POSITION ps;

    if (bCopyEveryType)
    {
        return TRUE;
    }

    iStringListCount = ListCopyFileType.GetCount();
    ps               = ListCopyFileType.GetHeadPosition();

    FileType.MakeLower();
    for (i = 0;i < iStringListCount;i++)
    {
        csFileType = ListCopyFileType.GetNext(ps);
        csFileType.MakeLower();
        if (FileType == csFileType)
            return TRUE;
    }
    return FALSE;
}

BOOL CEasyCopyDlg::IsInExceptFileList(CString Filename)//if the file is needn't file list.
{
    int i,iStringListCount,ispace;
    CString csFilename;
    POSITION ps;

    if (!bHaveExceptFile)
    {
        return FALSE;
    }
    iStringListCount = ListExcpetCopyFile.GetCount();
    if (iStringListCount == 0)
    {
        return FALSE;
    }
    ispace = Filename.ReverseFind(CH_SLASH1);
    if (ispace == -1)
    {
        return FALSE;
    }
    Filename = Filename.Right(Filename.GetLength() - ispace - 1);
    Filename.MakeLower();

    ps = ListExcpetCopyFile.GetHeadPosition();
    for (i = 0;i < iStringListCount;i++)
    {
        csFilename = ListExcpetCopyFile.GetNext(ps);
        csFilename.MakeLower();
        if (Filename == csFilename)
            return TRUE;
    }
    return FALSE;
}

void CEasyCopyDlg::OnCancel() 
{
    // TODO: Add extra cleanup here
    if (CopyStatus == COPYFILEING)
    {
        ThreadExit();
        return;
    }
    CDialog::OnCancel();
}

void CEasyCopyDlg::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    iUsedSecond++;
    if (iUsedSecond >= 60)
    {
        iUsedMinute++;
        if (iUsedMinute >= 60)
        {
            iUsedMinute = 0;
            iUsedHour++;
        }
        iUsedSecond = 0;
    }
    CString cTime,cScantext;

    cScantext.LoadString(IDS_STRING_SCANINGTIME);
    cTime.Format(cScantext,iUsedHour,iUsedMinute,iUsedSecond);//已经扫描了%02d小时%02d分钟%02d秒
    m_Static_Time.SetWindowText(cTime);

    CDialog::OnTimer(nIDEvent);
}

BOOL CEasyCopyDlg::PathIsValid(const CString path)
{
    TCHAR CurrentDirectory[MAX_PATH];
    BOOL reval;
    GetCurrentDirectory(sizeof(CurrentDirectory),CurrentDirectory);

    reval = SetCurrentDirectory(path);
    SetCurrentDirectory(CurrentDirectory);
    return reval;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
