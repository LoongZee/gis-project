// CatalogTree.cpp : 实现文件
//

#include "stdafx.h"
#include "sunflower.h"
#include "CatalogTree.h"


extern "C" BOOL WINAPI AddLayerDlg(int &mark,int &type,CString &name);

// CCatalogTree

IMPLEMENT_DYNAMIC(CCatalogTree, CTreeCtrl)

CCatalogTree::CCatalogTree()
{

}

CCatalogTree::~CCatalogTree()
{
}


BEGIN_MESSAGE_MAP(CCatalogTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CCatalogTree::OnNMRClick)
	ON_COMMAND(ID__32808, &CCatalogTree::OnAddLayer)
	ON_COMMAND(ID__32809, &CCatalogTree::OnImportLayer)
	ON_COMMAND(ID__32810, &CCatalogTree::OnAllLayerVisible)
	ON_COMMAND(ID__32811, &CCatalogTree::OnNoLayerVisible)
	ON_COMMAND(ID__32812, &CCatalogTree::OnRemoveLayer)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_32813, &CCatalogTree::OnEditLayer)
	ON_COMMAND(ID_32814, &CCatalogTree::OnDeleteLayer)
END_MESSAGE_MAP()



// CCatalogTree 消息处理程序




void CCatalogTree::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	UINT nFlags;
	CPoint curPoint;
	GetCursorPos(&curPoint);
	ScreenToClient(&curPoint); //屏幕坐标转换为TREE内坐标
	HTREEITEM hItem = HitTest(curPoint,&nFlags);
	HTREEITEM Root = GetRootItem();
	if (hItem && (TVHT_ONITEM & nFlags)) //判断是否有HTREEITEM
	{
		CCatalogTree::SelectItem(hItem);
		CMenu menu;
		if(hItem == Root)
		{
			menu.LoadMenu(IDR_MENU1);
		}
		else if(hItem != Root)
		{
			menu.LoadMenu(IDR_MENU2);
		}
		CMenu* popup=menu.GetSubMenu(0);
		GetCursorPos(&curPoint);
		popup->TrackPopupMenu(TPM_LEFTBUTTON|TPM_LEFTALIGN,curPoint.x,curPoint.y,this);
	}
	*pResult = 0;
}

void CCatalogTree::OnAddLayer()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetSelectedItem();
	int mark;
	int type;
	bool t=true;
	CString layerName;
	AddLayerDlg(mark,type,layerName);
	for(int i=0;i<s_layer.getSize();i++)
	{
		if(layerName==s_layer.elements[i].Layername)
		{
			t=false;	
			AfxMessageBox(_T("图层名重复！"));
			break;
		}
	}
	if(mark==0&&layerName!=""&&t)
	{
		if(type==0)
			InsertItem(layerName,0,0,hItem);
		else if(type==1)
			InsertItem(layerName,1,1,hItem);
		else if(type==2)
			InsertItem(layerName,2,2,hItem);
		else if(type==3)
			InsertItem(layerName,3,3,hItem);
		GeoLayer layer;
		layer.Layername=layerName;
		layer.mtype=type;
		layer.isshow=false;
		layer.isedit=false;
		Operation.Connectiondb();
		layer.id=Operation.addlayer(layer);
		s_layer.Push(layer);
	}
	Sendmess();
}


void CCatalogTree::OnImportLayer()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetSelectedItem();
    CInputLayerDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(importlayer.Layername!="")
		{
			Operation.Connectiondb();
			Operation.importlayer(importlayer);
			if(importlayer.mtype==0)
				InsertItem(importlayer.Layername,0,0,hItem);
			else if(importlayer.mtype==1)
				InsertItem(importlayer.Layername,1,1,hItem);
			else if(importlayer.mtype==2)
				InsertItem(importlayer.Layername,2,2,hItem);
			else if(importlayer.mtype==3)
				InsertItem(importlayer.Layername,3,3,hItem);
			s_layer.Push(importlayer);
		}
		else AfxMessageBox(_T("未选择图层"));
	}
	Sendmess();
}

void CCatalogTree::OnAllLayerVisible()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetRootItem();
	SetItemState( hItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	if(ItemHasChildren(hItem)){
		HTREEITEM htiChild = this->GetChildItem (hItem);
		if (htiChild&&!IsItemChecked(htiChild))
			 SetItemState( htiChild, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
      else
         return ;
      HTREEITEM htiSibling = GetNextSiblingItem (htiChild);
      while (htiSibling)
      {
		 if (!IsItemChecked(htiSibling))
			 SetItemState( htiSibling, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
         htiSibling = GetNextSiblingItem(htiSibling);
      }
   }
	for(int i=0;i<s_layer.getSize();i++)
	{
		s_layer.elements[i].isshow=true;
		s_layer.elements[i].isedit=false;	
	}
	Sendmess();
}


void CCatalogTree::OnNoLayerVisible()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetRootItem();
	if(ItemHasChildren(hItem)){
		HTREEITEM htiChild = this->GetChildItem (hItem);
		if (htiChild&&IsItemChecked(htiChild))
			 SetItemState( htiChild, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
      else
         return ;
      HTREEITEM htiSibling = GetNextSiblingItem (htiChild);
      while (htiSibling)
      {
		 if (IsItemChecked(htiSibling))
			 SetItemState( htiSibling, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );
         htiSibling = GetNextSiblingItem(htiSibling);
      }
   }
	for(int i=0;i<s_layer.getSize();i++)
	{
		s_layer.elements[i].isshow=false;
		s_layer.elements[i].isedit=false;	
	}
	Sendmess();
}


void CCatalogTree::OnRemoveLayer()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetRootItem();
	while(ItemHasChildren(hItem)){
		HTREEITEM htiChild = this->GetChildItem (hItem);
		if (htiChild)
		{
			DeleteItem(htiChild);
		}
	}
	s_layer.top=-1;
	s_point.top=-1;
	s_line.top=-1;
	s_Circle.top=-1;
	s_note.top=-1;
	Sendmess();
}


void CCatalogTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
   UINT uFlags=0;
   HTREEITEM hti = HitTest(point,&uFlags);

   if( uFlags & TVHT_ONITEMSTATEICON )
   {
        ToggleItemState(hti);
		State();
		edit();
		Sendmess();
		return;
   }
   CTreeCtrl::OnLButtonDown(nFlags, point);
}


void CCatalogTree::ToggleItemState(HTREEITEM hti)
{

   int iImage = GetItemState( hti, TVIS_STATEIMAGEMASK )>>12;
   SetItemState( hti, INDEXTOSTATEIMAGEMASK(iImage == 1 ? 2 : 1), TVIS_STATEIMAGEMASK );
   if(GetRootItem()!=hti){
	   if(IsItemChecked(hti))
	   {
	        SetChecked(GetRootItem());
	   }
   }
   if(!IsItemChecked(hti)&&ItemHasChildren(hti)){
	   HTREEITEM htiSibling = this->GetChildItem (hti);
	   while (htiSibling)
	   {
		   if (IsItemChecked(htiSibling))
		   {
			   ToggleItemState(htiSibling);
		   }
		   htiSibling = GetNextSiblingItem(htiSibling);
      }
   }
   else if (IsItemChecked(hti)&&ItemHasChildren(hti))
   {
      HTREEITEM htiSibling = this->GetChildItem (hti);
      while (htiSibling)
      {
		 if (!IsItemChecked(htiSibling))
			 ToggleItemState(htiSibling);
         htiSibling = GetNextSiblingItem(htiSibling);
      }
   }

}

void CCatalogTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
   UINT uFlags=0;
   HTREEITEM hti = HitTest(point,&uFlags);

   if( uFlags & TVHT_ONITEMSTATEICON )
   {
        ToggleItemState(hti);
		State();
		edit();
		Sendmess();
		return;
   }
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}


BOOL CCatalogTree::IsItemChecked(HTREEITEM hItem)
{
   return GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12 == 2||GetItemState( hItem, TVIS_STATEIMAGEMASK )>>12 == 3;
}



HTREEITEM CCatalogTree::GetFirstCheckedItem()
{
   for ( HTREEITEM hItem = GetRootItem(); 
     hItem!=NULL; hItem = GetNextItem( hItem ) )
      if ( IsItemChecked(hItem) )
         return hItem;

   return NULL;

}

HTREEITEM CCatalogTree::GetNextCheckedItem(HTREEITEM hItem)
{
   for ( hItem = GetNextItem( hItem ); 
     hItem!=NULL; hItem = GetNextItem( hItem ) )
      if ( IsItemChecked(hItem) )
         return hItem;

   return NULL;

}

HTREEITEM CCatalogTree::GetPrevCheckedItem(HTREEITEM hItem)
{
   for ( hItem = GetPrevItem( hItem ); 
     hItem!=NULL; hItem = GetPrevItem( hItem ) )
      if ( IsItemChecked(hItem) )
         return hItem;

   return NULL;

}

void CCatalogTree::SetChecked(HTREEITEM hItem)
{
   SetItemState( hItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );

}
// GetNextItem   - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem      - The reference item

HTREEITEM CCatalogTree::GetNextItem(HTREEITEM hItem)
{

   HTREEITEM   hti;

   if( ItemHasChildren( hItem ) )
      return GetChildItem( hItem ); // return first child
   else{
      // return next sibling item
      // Go up the tree to find a parent's sibling if needed.
      while( (hti = GetNextSiblingItem( hItem )) == NULL ){
         if( (hItem = GetParentItem( hItem ) ) == NULL )
            return NULL;
      }
   }
   return hti;


}

HTREEITEM CCatalogTree::GetPrevItem(HTREEITEM hItem)
{
   HTREEITEM hti;

   // Return a previous sibling item if it exists
   if( hti = GetPrevSiblingItem(hItem) )
      return hti;
   else
      // No sibling, return the parent 
	  return GetParentItem(hItem);
}



void CCatalogTree::OnEditLayer()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = GetRootItem();
	HTREEITEM hItem1 = GetSelectedItem();
	SetItemState( hItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
	if(ItemHasChildren(hItem)){
		HTREEITEM htiSibling = this->GetChildItem (hItem);
		while (htiSibling)
		{
			if (GetItemState( htiSibling, TVIS_STATEIMAGEMASK )>>12 == 3)
			{
				SetItemState( htiSibling, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
				for(int i=0;i<s_layer.getSize();i++)
				{
					if(GetItemText(htiSibling)==s_layer.elements[i].Layername)
					{		
						s_layer.elements[i].isshow=true;
						s_layer.elements[i].isedit=false;
					}
				}
				break;
			}
			htiSibling = GetNextSiblingItem(htiSibling);
		}
	}
	SetItemState( hItem1, INDEXTOSTATEIMAGEMASK(3), TVIS_STATEIMAGEMASK);
	CString strText = GetItemText(hItem1); 
	for(int i=0;i<s_layer.getSize();i++)
	{
		if(strText==s_layer.elements[i].Layername)
		{		
			s_layer.elements[i].isshow=true;
			s_layer.elements[i].isedit=true;
			editlayer=i;
		}
	}
	Sendmess();
}


void CCatalogTree::OnDeleteLayer()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem1 = GetSelectedItem();
	for(int i=0;i<s_layer.getSize();i++)
	{
		if(GetItemText(hItem1)==s_layer.elements[i].Layername)
		{	
			if(s_layer.elements[i].mtype==0)
			{
				int size=s_point.getSize();
				for(int j=0;j<size;j++)
				{
					if(s_point.elements[j].layer==s_layer.elements[i].id)
					{
						s_point.delete_elements(j);
					}
				
				}
			
			}
			else if(s_layer.elements[i].mtype==1)
			{
				int size=s_line.getSize();
				for(int j=0;j<size;j++)
				{
					if(s_line.elements[j].layer==s_layer.elements[i].id)
					{
						s_line.delete_elements(j);
					}
				}
			}
			else if(s_layer.elements[i].mtype==2)
			{
				int size=s_Circle.getSize();
				for(int j=0;j<size;j++)
				{
					if(s_Circle.elements[j].layer==s_layer.elements[i].id)
					{
						s_Circle.delete_elements(j);
					}
				
				}
			}
			else if(s_layer.elements[i].mtype==3)
			{
				int size=s_note.getSize();
				for(int j=0;j<size;j++)
				{
					if(s_note.elements[j].layer==s_layer.elements[i].id)
					{
						s_note.delete_elements(j);
					}
				
				}
			}
			s_layer.delete_elements(i);
			break;
		}
	}
	DeleteItem(hItem1);	
	State();
	Sendmess();
}

void CCatalogTree::State()
{
	HTREEITEM hItem = GetRootItem();
	if(ItemHasChildren(hItem)){
		HTREEITEM htiSibling = this->GetChildItem (hItem);
		while (htiSibling)
		{
			if (GetItemState( htiSibling, TVIS_STATEIMAGEMASK )>>12 == 1)
			{
				for(int i=0;i<s_layer.getSize();i++)
				{
					if(GetItemText(htiSibling)==s_layer.elements[i].Layername)
					{		
						s_layer.elements[i].isshow=false;
						s_layer.elements[i].isedit=false;
					}
				}
			}
			else if (GetItemState( htiSibling, TVIS_STATEIMAGEMASK )>>12 == 2)
			{
				for(int i=0;i<s_layer.getSize();i++)
				{
					if(GetItemText(htiSibling)==s_layer.elements[i].Layername)
					{		
						s_layer.elements[i].isshow=true;
						s_layer.elements[i].isedit=false;
					}
				}
			}
			else if (GetItemState( htiSibling, TVIS_STATEIMAGEMASK )>>12 == 3)
			{
				for(int i=0;i<s_layer.getSize();i++)
				{
					if(GetItemText(htiSibling)==s_layer.elements[i].Layername)
					{		
						s_layer.elements[i].isshow=true;
						s_layer.elements[i].isedit=true;
					}
				}
			}
			htiSibling = GetNextSiblingItem(htiSibling);
		}
	}
}

void CCatalogTree::edit()
{
	bool t=true;
	HTREEITEM hItem = GetRootItem();
	if(ItemHasChildren(hItem)){
		HTREEITEM htiSibling = this->GetChildItem (hItem);
		while (htiSibling)
		{
			if (GetItemState( htiSibling, TVIS_STATEIMAGEMASK )>>12 == 3)
			{
				for(int i=0;i<s_layer.getSize();i++)
				{
					if(GetItemText(htiSibling)==s_layer.elements[i].Layername)
					{		
						editlayer=i;
						t=false;
						break;
					}
				}
			}
			htiSibling = GetNextSiblingItem(htiSibling);
		}
	}
	if(t)
	{
		editlayer=-1;
	}
}

void CCatalogTree::Sendmess()
{
	HWND receiveWindow =  ((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView()->GetSafeHwnd();  
	if (receiveWindow == NULL)  
    return;
	CString sendData;
	sendData.Format(_T("%d"), editlayer);
	COPYDATASTRUCT copyData = { 0 };
	copyData.lpData = sendData.GetBuffer();
	copyData.cbData = sendData.GetLength();
	::SendMessageW(receiveWindow, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&copyData);
	sendData.ReleaseBuffer();
}