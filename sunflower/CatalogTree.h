#pragma once


// CCatalogTree
#include "Resource.h"
#include "InputLayerDlg.h"

class CCatalogTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CCatalogTree)

public:
	CCatalogTree();
	virtual ~CCatalogTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void ToggleItemState(HTREEITEM hti);
	BOOL IsItemChecked(HTREEITEM hItem);
	HTREEITEM GetFirstCheckedItem();
	HTREEITEM GetNextCheckedItem(HTREEITEM hItem);
	HTREEITEM GetPrevCheckedItem(HTREEITEM hItem);
	void SetChecked(HTREEITEM hItem);
	HTREEITEM GetNextItem(HTREEITEM hItem);
	HTREEITEM GetPrevItem(HTREEITEM hItem);
	void State();
	void edit();
	void Sendmess();
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddLayer();
	afx_msg void OnImportLayer();
	afx_msg void OnAllLayerVisible();
	afx_msg void OnNoLayerVisible();
	afx_msg void OnRemoveLayer();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditLayer();
	afx_msg void OnDeleteLayer();
};


