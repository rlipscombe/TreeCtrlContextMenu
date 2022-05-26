
#pragma once


// CTreeCtrlItem command target

class CTreeCtrlItem : public CCmdTarget
{
	CTreeCtrl *m_treeCtrl;
	HTREEITEM m_hTreeItem;

	DECLARE_DYNAMIC(CTreeCtrlItem)

public:
	CTreeCtrlItem();
	virtual ~CTreeCtrlItem();

	void Attach(CTreeCtrl *pTreeCtrl, HTREEITEM hTreeItem)
	{
		m_treeCtrl = pTreeCtrl;
		m_hTreeItem = hTreeItem;
	}

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnOnitemInsertchilditem();
};
