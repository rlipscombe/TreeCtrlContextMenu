// TreeCtrlItem.cpp : implementation file
//

#include "stdafx.h"
#include "TreeCtrl.h"
#include "TreeCtrlItem.h"

// CTreeCtrlItem

IMPLEMENT_DYNAMIC(CTreeCtrlItem, CCmdTarget)

CTreeCtrlItem::CTreeCtrlItem()
	: m_treeCtrl(NULL), m_hTreeItem(NULL)
{
}

CTreeCtrlItem::~CTreeCtrlItem()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlItem, CCmdTarget)
	ON_COMMAND(ID_ONITEM_INSERTCHILDITEM, OnOnitemInsertchilditem)
END_MESSAGE_MAP()



// CTreeCtrlItem message handlers

void CTreeCtrlItem::OnOnitemInsertchilditem()
{
	CTreeCtrlItem *pItem = new CTreeCtrlItem;
	LPARAM lParam = reinterpret_cast<LPARAM>(pItem);
	HTREEITEM hTreeItem = m_treeCtrl->InsertItem(TVIF_TEXT | TVIF_PARAM, "Child Item", 0, 1, 0, 0, lParam, m_hTreeItem, TVI_LAST);
	if (hTreeItem)
	{
		pItem->Attach(m_treeCtrl, hTreeItem);
		m_treeCtrl->EnsureVisible(hTreeItem);
	}
	else
		delete pItem;
}
