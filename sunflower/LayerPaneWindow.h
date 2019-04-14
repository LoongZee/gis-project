#pragma once

#include "CatalogTree.h"
// CLayerPaneWindow

class CLayerPaneWindow : public CDockablePane
{
	DECLARE_DYNAMIC(CLayerPaneWindow)

public:
	CLayerPaneWindow();
	virtual ~CLayerPaneWindow();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CCatalogTree m_wndTree;
	CImageList m_imageState;
	CImageList m_imageList;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


