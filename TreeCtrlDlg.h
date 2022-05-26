// TreeCtrlDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CTreeCtrlDlg dialog
class CTreeCtrlDlg : public CDialog
{
// Construction
public:
	CTreeCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TREECTRL_DIALOG };

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
private:
	CTreeCtrl m_treeCtrl;
public:
	afx_msg void OnNMRclickTreectrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAppAbout();
	afx_msg void OnNowhereInsertrootitem();
	afx_msg void OnTvnDeleteitemTreectrl(NMHDR *pNMHDR, LRESULT *pResult);
};
