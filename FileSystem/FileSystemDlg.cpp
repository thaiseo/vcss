
// FileSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileSystem.h"
#include "FileSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileSystemDlg dialog



CFileSystemDlg::CFileSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILESYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_myListControl);
	DDX_Control(pDX, IDC_EDIT2, m_CEditFile);
	DDX_Control(pDX, IDC_EDIT1, m_CEditPath);
}

BEGIN_MESSAGE_MAP(CFileSystemDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFileSystemDlg::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CFileSystemDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CFileSystemDlg message handlers

BOOL CFileSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	
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
	// Add List Control


	m_myListControl.InsertColumn(0,L"File Name ", LVCFMT_LEFT,200);
	m_myListControl.InsertColumn(1, L"Size", LVCFMT_LEFT,100);
	m_myListControl.InsertColumn(2, L"Path", LVCFMT_LEFT, 400);
	m_myListControl.InsertColumn(3, L"Date Modified", LVCFMT_LEFT, 150);
	m_myListControl.InsertColumn(4, L"Created", LVCFMT_LEFT, 150);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CFileSystemDlg::PreTranslateMessage(MSG* pMsg) {	
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			OnBnClickedButton1();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CFileSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileSystemDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFileSystemDlg::AddItem(CString fileName, CString size, CString filePath, CString dataModified, CString created) {
	int idxItem ;
	idxItem  = m_myListControl.InsertItem(0, fileName);
	m_myListControl.SetItemText(idxItem, 1, size);
	m_myListControl.SetItemText(idxItem, 2, filePath);
	m_myListControl.SetItemText(idxItem, 3, dataModified);
	m_myListControl.SetItemText(idxItem, 4, created);
}

void CFileSystemDlg::RecursiveDirectory(CString path,CString fileName) {
	ULONGLONG sizeFile;
	CTime createdTime, dateModifiedTime;
	CFileFind finder;
	BOOL bWorking = finder.FindFile(path + CString("\\*.*"));
	CString timeFmt = CString("%d/%m/%y %R %p");


	while (bWorking) {
		bWorking = finder.FindNextFileW();
		CString fName = finder.GetFileName();
		if (fName != L"." && fName != L"..") {
			if (finder.IsDirectory()) {
				RecursiveDirectory(finder.GetFilePath(), fileName);
			}
			else {
				if (fName.Find(fileName) != -1) {
					finder.GetCreationTime(createdTime);
					finder.GetLastWriteTime(dateModifiedTime);
					sizeFile = finder.GetLength();
					CString szStr;
					szStr.Format(CString("%llu KB"), sizeFile);
					AddItem(finder.GetFileName(), szStr, finder.GetFilePath(), createdTime.Format(timeFmt), dateModifiedTime.Format(timeFmt));
				}
			}
		}
	}
	finder.Close();
}

void CFileSystemDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int pathLen = m_CEditPath.GetWindowTextLengthW();
	int nameLen = m_CEditFile.GetWindowTextLengthW();
	CString strPathValue, strNameValue;

	m_CEditPath.GetWindowTextW(strPathValue);
	m_CEditFile.GetWindowTextW(strNameValue);
	m_myListControl.DeleteAllItems();

	RecursiveDirectory(strPathValue, strNameValue);
}


void CFileSystemDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
