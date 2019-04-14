// LayerPaneWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "sunflower.h"
#include "LayerPaneWindow.h"


// CLayerPaneWindow

IMPLEMENT_DYNAMIC(CLayerPaneWindow, CDockablePane)

CLayerPaneWindow::CLayerPaneWindow()
{

}

CLayerPaneWindow::~CLayerPaneWindow()
{
}


BEGIN_MESSAGE_MAP(CLayerPaneWindow, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CLayerPaneWindow 消息处理程序




int CLayerPaneWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	DWORD tree_style=WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_DISABLEDRAGDROP |TVS_CHECKBOXES ;
	m_wndTree.Create(tree_style,CRect(0,0,100,100),this,0);
	m_imageState.Create(IDB_BITMAP2,13,1,RGB(255,255,255));
	m_imageList.Create(IDB_BITMAP3,13,1,RGB(255,255,255));
	m_wndTree.SetImageList(&m_imageState,TVSIL_STATE);
	m_wndTree.SetImageList(&m_imageList,TVSIL_NORMAL);
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent=NULL;
	tvinsert.hInsertAfter=TVI_ROOT;
    tvinsert.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_STATE;
	tvinsert.item.state=INDEXTOSTATEIMAGEMASK(1);
	tvinsert.item.stateMask=TVIS_STATEIMAGEMASK;
	tvinsert.item.iImage=4;
	tvinsert.item.iSelectedImage=4;
	tvinsert.item.hItem=NULL;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.cChildren=0;
	tvinsert.item.lParam=0;
	tvinsert.item.pszText=_T("新地图");
	HTREEITEM hRoot=m_wndTree.InsertItem(&tvinsert);
	return 0;
}


void CLayerPaneWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(GetSafeHwnd()==NULL)
	{
		return;
	}
	m_wndTree.SetWindowPos(this,0,0,cx,cy-1,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTree.ShowWindow(SW_SHOW);
}


void CLayerPaneWindow::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}



