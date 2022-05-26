// TreeCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeCtrl.h"
#include "TreeCtrlDlg.h"
#include "TreeCtrlItem.h"
#include ".\treectrldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTreeCtrlDlg dialog



CTreeCtrlDlg::CTreeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREECTRL, m_treeCtrl);
}

BEGIN_MESSAGE_MAP(CTreeCtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_RCLICK, IDC_TREECTRL, OnNMRclickTreectrl)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_NOWHERE_INSERTROOTITEM, OnNowhereInsertrootitem)
	ON_NOTIFY(TVN_DELETEITEM, IDC_TREECTRL, OnTvnDeleteitemTreectrl)
END_MESSAGE_MAP()


// CTreeCtrlDlg message handlers

BOOL CTreeCtrlDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTreeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeCtrlDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTreeCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString DescribeTVHT(UINT flags)
{
	CString s;

	if (flags & TVHT_ABOVE)
		s += "TVHT_ABOVE ";
	if (flags & TVHT_BELOW)
		s += "TVHT_BELOW ";
	if (flags & TVHT_NOWHERE)
		s += "TVHT_NOWHERE ";
	if (flags & TVHT_ONITEM)
		s += "TVHT_ONITEM ";
	if (flags & TVHT_ONITEMBUTTON)
		s += "TVHT_ONITEMBUTTON ";
	if (flags & TVHT_ONITEMICON)
		s += "TVHT_ONITEMICON ";
	if (flags & TVHT_ONITEMINDENT)
		s += "TVHT_ONITEMINDENT ";
	if (flags & TVHT_ONITEMLABEL)
		s += "TVHT_ONITEMLABEL ";
	if (flags & TVHT_ONITEMRIGHT)
		s += "TVHT_ONITEMRIGHT ";
	if (flags & TVHT_ONITEMSTATEICON)
		s += "TVHT_ONITEMSTATEICON ";
	if (flags & TVHT_TOLEFT)
		s += "TVHT_TOLEFT ";
	if (flags & TVHT_TORIGHT)
		s += "TVHT_TORIGHT ";

	return s;
}

void CTreeCtrlDlg::OnNMRclickTreectrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	// The user has right-clicked on the tree control.
	// Because we don't actually get given the mouse coordinates here (which is a bit stupid),
	// we need to see if the user clicked on anything.
	CPoint ptScreen;
	if (GetCursorPos(&ptScreen))
	{
		CPoint ptClient(ptScreen);
		m_treeCtrl.ScreenToClient(&ptClient);

		UINT flags;
		HTREEITEM hTreeItem = m_treeCtrl.HitTest(ptClient, &flags);
		TRACE("hTreeItem = %p, flags = 0x%08x (%s)\n", hTreeItem, flags, (LPCTSTR)DescribeTVHT(flags));

		// The user's clicked on an item, so display a popup menu.
		if ((hTreeItem != NULL) && (flags & TVHT_ONITEM))
		{
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_POPUP_ONITEM));
			CMenu *popup = menu.GetSubMenu(0);
			ASSERT(popup);
			
			UINT nCode = popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, ptScreen.x, ptScreen.y, this, NULL);
			if (nCode != 0)
			{
				CTreeCtrlItem *pItem = reinterpret_cast<CTreeCtrlItem *>(m_treeCtrl.GetItemData(hTreeItem));
				ASSERT(pItem && pItem->IsKindOf(RUNTIME_CLASS(CCmdTarget)));
				pItem->OnCmdMsg(nCode, CN_COMMAND, NULL, NULL);
			}
		}

		// The user hasn't clicked on any item, so show a different popup menu.
		if (hTreeItem == NULL)
		{
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_POPUP_NOWHERE));
			CMenu *popup = menu.GetSubMenu(0);
			ASSERT(popup);
			VERIFY(popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptScreen.x, ptScreen.y, this, NULL));
		}
	}
}

void CTreeCtrlDlg::OnAppAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTreeCtrlDlg::OnNowhereInsertrootitem()
{
	CTreeCtrlItem *pItem = new CTreeCtrlItem;
	LPARAM lParam = reinterpret_cast<LPARAM>(pItem);
	HTREEITEM hTreeItem = m_treeCtrl.InsertItem(TVIF_TEXT | TVIF_PARAM, "Root Item", 0, 0, 0, 0, lParam, TVI_ROOT, TVI_LAST);
	if (hTreeItem)
		pItem->Attach(&m_treeCtrl, hTreeItem);
	else
		delete pItem;
}

void CTreeCtrlDlg::OnTvnDeleteitemTreectrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	LPARAM lParam = pNMTreeView->itemOld.lParam;
	if (lParam)
	{
		CTreeCtrlItem *pItem = reinterpret_cast<CTreeCtrlItem *>(lParam);
		delete pItem;
	}

	*pResult = 0;
}
