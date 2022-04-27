
// FileSystemDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFileSystemDlg dialog
class CFileSystemDlg : public CDialogEx
{
// Construction
public:
	CFileSystemDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILESYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	void AddItem(CString fileName, CString size, CString filePath, CString dataModified, CString created);
	BOOL PreTranslateMessage(MSG *pMsg);
	void RecursiveDirectory(CString path, CString fileName);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_myListControl;
	CEdit m_CEditFile;
	CEdit m_CEditPath;
};
