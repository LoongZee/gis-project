
// sunflowerView.cpp : CsunflowerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "sunflower.h"
#endif

#include "sunflowerDoc.h"
#include "sunflowerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" BOOL WINAPI InputBufferDlg(int &mark,int &rad,COLORREF &color);
// CsunflowerView

IMPLEMENT_DYNCREATE(CsunflowerView, CView)

BEGIN_MESSAGE_MAP(CsunflowerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CsunflowerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CsunflowerView::OnCreatePoint)
	ON_COMMAND(ID_32772, &CsunflowerView::OnSelectPoint)
	ON_COMMAND(ID_32773, &CsunflowerView::OnModifyPoint)
	ON_COMMAND(ID_32774, &CsunflowerView::OnMovePoint)
	ON_COMMAND(ID_32775, &CsunflowerView::OnDeletePoint)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32776, &CsunflowerView::OnCreateLine)
	ON_COMMAND(ID_32777, &CsunflowerView::OnSelectLine)
	ON_COMMAND(ID_32778, &CsunflowerView::OnModifyLine)
	ON_COMMAND(ID_32779, &CsunflowerView::OnMoveLine)
	ON_COMMAND(ID_32780, &CsunflowerView::OnDeleteLine)
	ON_COMMAND(ID_32783, &CsunflowerView::OnCut)
	ON_COMMAND(ID_32784, &CsunflowerView::OnDlinetopoint)
	ON_COMMAND(ID_32785, &CsunflowerView::OnCreateLBuffer)
	ON_COMMAND(ID_32786, &CsunflowerView::OnCreateCircle)
	ON_COMMAND(ID_32787, &CsunflowerView::OnSelectCircle)
	ON_COMMAND(ID_32788, &CsunflowerView::OnModifyCircle)
	ON_COMMAND(ID_32789, &CsunflowerView::OnMoveCircle)
	ON_COMMAND(ID_32790, &CsunflowerView::OnDeleteCircle)
	ON_COMMAND(ID_32791, &CsunflowerView::OnSquareDeleteCircle)
	ON_COMMAND(ID_32792, &CsunflowerView::OnCreateNote)
	ON_COMMAND(ID_32793, &CsunflowerView::OnSelectNote)
	ON_COMMAND(ID_32794, &CsunflowerView::OnModifyNote)
	ON_COMMAND(ID_32795, &CsunflowerView::OnMoveNote)
	ON_COMMAND(ID_32796, &CsunflowerView::OnDeleteNote)
	ON_COMMAND(ID_32797, &CsunflowerView::OnSquareDeletePoint)
	ON_COMMAND(ID_32798, &CsunflowerView::OnSquareDeleteNote)
	ON_COMMAND(ID_32799, &CsunflowerView::OnSquareDeleteLine)
	ON_COMMAND(ID_Refresh, &CsunflowerView::OnRefresh)
	ON_COMMAND(ID_Reset, &CsunflowerView::OnReset)
	ON_COMMAND(ID_Zoomin, &CsunflowerView::OnZoomin)
	ON_COMMAND(ID_Zoomout, &CsunflowerView::OnZoomout)
	ON_COMMAND(ID_Move, &CsunflowerView::OnMove)
	ON_WM_COPYDATA()
	ON_UPDATE_COMMAND_UI(ID_32771, &CsunflowerView::OnUpdatePoint)
	ON_UPDATE_COMMAND_UI(ID_32772, &CsunflowerView::OnUpdateSelectPoint)
	ON_UPDATE_COMMAND_UI(ID_32773, &CsunflowerView::OnUpdateModifyPoint)
	ON_UPDATE_COMMAND_UI(ID_32774, &CsunflowerView::OnUpdateMovePoint)
	ON_UPDATE_COMMAND_UI(ID_32775, &CsunflowerView::OnUpdateDeletePoint)
	ON_UPDATE_COMMAND_UI(ID_32797, &CsunflowerView::OnUpdateSquareDeletePoint)
	ON_UPDATE_COMMAND_UI(ID_32776, &CsunflowerView::OnUpdateCreateLine)
	ON_UPDATE_COMMAND_UI(ID_32777, &CsunflowerView::OnUpdateSelectLine)
	ON_UPDATE_COMMAND_UI(ID_32778, &CsunflowerView::OnUpdateModifyLine)
	ON_UPDATE_COMMAND_UI(ID_32779, &CsunflowerView::OnUpdateMoveLine)
	ON_UPDATE_COMMAND_UI(ID_32780, &CsunflowerView::OnUpdateDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_32783, &CsunflowerView::OnUpdateCut)
	ON_UPDATE_COMMAND_UI(ID_32784, &CsunflowerView::OnUpdateDlinetopoint)
	ON_UPDATE_COMMAND_UI(ID_32799, &CsunflowerView::OnUpdateSquareDeleteLine)
	ON_UPDATE_COMMAND_UI(ID_32786, &CsunflowerView::OnUpdateCreateCircle)
	ON_UPDATE_COMMAND_UI(ID_32787, &CsunflowerView::OnUpdateSelectCircle)
	ON_UPDATE_COMMAND_UI(ID_32788, &CsunflowerView::OnUpdateModifyCircle)
	ON_UPDATE_COMMAND_UI(ID_32789, &CsunflowerView::OnUpdateMoveCircle)
	ON_UPDATE_COMMAND_UI(ID_32790, &CsunflowerView::OnUpdateDeleteCircle)
	ON_UPDATE_COMMAND_UI(ID_32791, &CsunflowerView::OnUpdateSquareDeleteCircle)
	ON_UPDATE_COMMAND_UI(ID_32792, &CsunflowerView::OnUpdateCreateNote)
	ON_UPDATE_COMMAND_UI(ID_32793, &CsunflowerView::OnUpdateSelectNote)
	ON_UPDATE_COMMAND_UI(ID_32794, &CsunflowerView::OnUpdateModifyNote)
	ON_UPDATE_COMMAND_UI(ID_32795, &CsunflowerView::OnUpdateMoveNote)
	ON_UPDATE_COMMAND_UI(ID_32796, &CsunflowerView::OnUpdateDeleteNote)
	ON_UPDATE_COMMAND_UI(ID_32798, &CsunflowerView::OnUpdateSquareDeleteNote)
END_MESSAGE_MAP()

// CsunflowerView 构造/析构
CsunflowerView::CsunflowerView()
{
	// TODO: 在此处添加构造代码
	m_ptBaseGisTool = NULL;

}

CsunflowerView::~CsunflowerView()
{
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
}

BOOL CsunflowerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CsunflowerView 绘制
int rad;
COLORREF color;
void CsunflowerView::OnDraw(CDC* pDC)
{
	CsunflowerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
   
	CGisTool_Point Point;
	CGisTool_Line Line;
	CGisTool_Circle Circle;
	CGisTool_Note Note;
	int i=0;
	int j=0;
	for(i=0;i<s_point.getSize();i++)  // for 循环在屏幕上调用数组里的点
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_point.elements[i].layer!=-1&&s_point.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Point.Draw(s_point.elements[i],pDC);
		}
	}
	for(i=0;i<s_line.getSize();i++)   // for 循环在屏幕上调用数组里的线
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_line.elements[i].layer!=-1&&s_line.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Line.Draw(s_line.elements[i],pDC);
		}
	}
	for(i=0;i<s_Circle.getSize();i++)   // for 循环在屏幕上调用数组里的面
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_Circle.elements[i].layer!=-1&&s_Circle.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Circle.Draw(s_Circle.elements[i],pDC);
		}
	}
	for(i=0;i<s_note.getSize();i++)   // for 循环在屏幕上调用数组里的注记
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_note.elements[i].layer!=-1&&s_note.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Note.Draw(s_note.elements[i],pDC);
		}
	}

	if(tag==123456)
	{
	for(i=0;i<s_point.getSize();i++)  // for 循环在屏幕上调用数组里的点
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_point.elements[i].layer!=-1&&s_point.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Point.DrawBuffer(s_point.elements[i],pDC,rad,color);
		}
	}
	for(i=0;i<s_line.getSize();i++)   // for 循环在屏幕上调用数组里的线
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_line.elements[i].layer!=-1&&s_line.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Line.DrawBuffer(s_line.elements[i],pDC,rad,color);
		}
	}
	for(i=0;i<s_Circle.getSize();i++)   // for 循环在屏幕上调用数组里的面
	{
		for(j=0;j<s_layer.getSize();j++) 
		{
			if(s_Circle.elements[i].layer!=-1&&s_Circle.elements[i].layer==s_layer.elements[j].id&&s_layer.elements[j].isshow)
				Circle.DrawBuffer(s_Circle.elements[i],pDC,rad,color);
		}
	}
	}

}


// CsunflowerView 打印


void CsunflowerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CsunflowerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CsunflowerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CsunflowerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

//void CsunflowerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CsunflowerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CsunflowerView 诊断

#ifdef _DEBUG
void CsunflowerView::AssertValid() const
{
	CView::AssertValid();
}

void CsunflowerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsunflowerDoc* CsunflowerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsunflowerDoc)));
	return (CsunflowerDoc*)m_pDocument;
}
#endif //_DEBUG


// CsunflowerView 消息处理程序


void CsunflowerView::OnCreatePoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=1;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);
	
}


void CsunflowerView::OnSelectPoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=2;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);	
}


void CsunflowerView::OnModifyPoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=3;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);	
}


void CsunflowerView::OnMovePoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=4;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);	
}


void CsunflowerView::OnDeletePoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=5;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);	
}




void CsunflowerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
	if (m_ptBaseGisTool!=NULL){
		if(tag==2||tag==3||tag==4){
			KillTimer(1);
	        KillTimer(2);
			m_ptBaseGisTool->Draw(s_point.elements[list],pDC);
			SetTimer(1,200,NULL);
			SetTimer(2,250,NULL);
		}
		else if(tag==5){
			KillTimer(1);
	        KillTimer(2);
			m_ptBaseGisTool->Draw(s_point.elements[list],pDC);
		}
		else if(tag==22||tag==33||tag==44){
			KillTimer(3);
	        KillTimer(4);
			m_ptBaseGisTool->Draw(s_line.elements[list],pDC);
			SetTimer(3,200,NULL);
			SetTimer(4,250,NULL);
		}
		else if(tag==55){
			KillTimer(3);
	        KillTimer(4);
			m_ptBaseGisTool->Draw(s_line.elements[list],pDC);
		}
		else if(tag==222||tag==333||tag==444){
			KillTimer(5);
	        KillTimer(6);
			m_ptBaseGisTool->Draw(s_Circle.elements[list],pDC);
			SetTimer(5,200,NULL);
			SetTimer(6,250,NULL);
		}
		else if(tag==555){
			KillTimer(5);
	        KillTimer(6);
			m_ptBaseGisTool->Draw(s_Circle.elements[list],pDC);
		}
		else if(tag==666||tag==99999||tag==88888){
			  m_startp=point;
			  CRectTracker Tracker;  
			  if (Tracker.TrackRubberBand(this,point,TRUE))  
			  {  
				  CRect rt;  
				  // 获取所拉的矩形  
				  Tracker.GetTrueRect(&rt);  
				  // 获取鼠标左键弹起的那个坐标点  
				  CPoint UpPt = GetOtherPoint(rt,point);  
				  LPARAM lp = MAKELPARAM(UpPt.x,UpPt.y);  
				  // 发送左键弹起消息  
				  this->SendMessage(WM_LBUTTONUP,NULL,lp);  
			  }  
		}
		else if(tag==2222||tag==3333||tag==4444)
		{
			KillTimer(7);
	        KillTimer(8);
			m_ptBaseGisTool->Draw(s_note.elements[list],pDC);
			SetTimer(7,200,NULL);
			SetTimer(8,250,NULL);
		}
		else if(tag==5555){
			KillTimer(7);
	        KillTimer(8);
			m_ptBaseGisTool->Draw(s_note.elements[list],pDC);
		}
		else if(tag==77777){
			 m_startp=point;
			 SetCursor(LoadCursor(NULL, IDC_SIZEALL));
			  m_bLBtnDown=true;
		}
		m_ptBaseGisTool->LButtonDown(pDC,nFlags,point);
	}
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}


void CsunflowerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
	if (m_ptBaseGisTool!=NULL){
		OnDraw(pDC);
		m_ptBaseGisTool->MouseMove(pDC,nFlags,point);
		if(tag==77777)
		{
			if(m_bLBtnDown) 
            {  
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
			OnRefresh();
			m_lastp=point;
			m_ptBaseGisTool->CBaseGisTool::OnMove(pDC);
			m_startp=m_lastp;
			}
		}
	}
	ReleaseDC(pDC);
	CView::OnMouseMove(nFlags, point);
}


void CsunflowerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
	if (m_ptBaseGisTool!=NULL){
		if(tag==2||tag==3){
			KillTimer(1);
	        KillTimer(2);
			m_ptBaseGisTool->Draw(s_point.elements[list],pDC);
			Isselectpoint=false;
			Isselectline=false;
			Isselectcircle=false;
			Isselectnote=false;
		}
		else if(tag==22||33){
			KillTimer(3);
	        KillTimer(4);
			m_ptBaseGisTool->Draw(s_line.elements[list],pDC);
			Isselectpoint=false;
			Isselectline=false;
			Isselectcircle=false;
			Isselectnote=false;
		}
		else if(tag==66){
			KillTimer(3);
	        KillTimer(4);
		    tag_linecut=1;
			m_ptBaseGisTool->Draw(s_line.elements[list],pDC);
			Isselectpoint=false;
			Isselectline=false;
			Isselectcircle=false;
			Isselectnote=false;
		}
		else if(tag==77){
			KillTimer(3);
	        KillTimer(4);
		    tag_Dlinetopoint=1;
			m_ptBaseGisTool->Draw(s_line.elements[list],pDC);
			Isselectpoint=false;
			Isselectline=false;
			Isselectcircle=false;
			Isselectnote=false;
		}
		else if(tag==222||333){
			KillTimer(5);
	        KillTimer(6);
			m_ptBaseGisTool->Draw(s_Circle.elements[list],pDC);
			Isselectline=false;
		}
		m_ptBaseGisTool->RButtonUp(pDC,nFlags,point);
	}
	ReleaseDC(pDC);
	CView::OnRButtonUp(nFlags, point);
}


void CsunflowerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 1:
		{
			if(Isselectpoint)
			{
				CDC *pDC=GetDC();
				GeoPoint temp=selectpoint;
				temp.color=RGB(0,0,255);
				m_ptBaseGisTool->Draw(temp,pDC);
				ReleaseDC(pDC);
				break;
			}
		}
		case 2:
		{
			if(Isselectpoint)
			{
				CDC *pDC=GetDC();
				GeoPoint temp=selectpoint;
			    temp.color=RGB(255,0,0);
			    m_ptBaseGisTool->Draw(temp,pDC);
				ReleaseDC(pDC);
			    break;
			}
		}
		case 3:
		{
			if(Isselectline)
			{
				CDC *pDC=GetDC();
				GeoLine temp=selectline;
			    temp.color=RGB(0,0,255);
			    m_ptBaseGisTool->Draw(temp,pDC); 
				ReleaseDC(pDC);
			    break;
			}
		}
		case 4:
		{
			if(Isselectline)
			{
				CDC *pDC=GetDC();
				GeoLine temp=selectline;
			    temp.color=RGB(255,0,0);
			    m_ptBaseGisTool->Draw(temp,pDC); 
				ReleaseDC(pDC);
			    break;
			}
		}
		case 5:
		{
			if(Isselectcircle)
			{
				CDC *pDC=GetDC();
				GeoCircle temp=selectcircle;
			    temp.color=RGB(0,0,255);
			    m_ptBaseGisTool->Draw(temp,pDC);
				ReleaseDC(pDC);
			    break;
			}
		}
		case 6:
		{
			if(Isselectcircle)
			{
				CDC *pDC=GetDC();
				GeoCircle temp=selectcircle;
			    temp.color=RGB(255,0,0);
			    m_ptBaseGisTool->Draw(temp,pDC); 
				ReleaseDC(pDC);
			    break;
			}
		}
		case 7:
		{
			if(Isselectnote)
			{
				CDC *pDC=GetDC();
				GeoNote temp=selectnote;
			    temp.color=RGB(0,0,255);
			    m_ptBaseGisTool->Draw(temp,pDC); 
				ReleaseDC(pDC);
			    break;
			}
		}
		case 8:
		{
			if(Isselectnote)
			{
				CDC *pDC=GetDC();
				GeoNote temp=selectnote;
			    temp.color=RGB(255,0,0);
			    m_ptBaseGisTool->Draw(temp,pDC); 
				ReleaseDC(pDC);
			    break;
			}
		}
	}
	CView::OnTimer(nIDEvent);
}


void CsunflowerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC=GetDC();
	if (m_ptBaseGisTool!=NULL){
		if(tag==99999)
		{
			m_lastp=point;
   			m_ptBaseGisTool->CBaseGisTool::Zoomin(pDC);
			OnRefresh();
		}
		else if(tag==88888)
		{
			m_lastp=point;
   			m_ptBaseGisTool->CBaseGisTool::Zoomout(pDC);
			OnRefresh();
		}
		else if(tag==77777){
			if(m_bLBtnDown) 
            {  
				int i,j;
				m_bLBtnDown=false;
				for(i=0;i<s_point.getSize();i++)
				{
					Operation.Connectiondb();
					Operation.modifyPoint(s_point.elements[i]);
				}
				for(i=0;i<s_line.getSize();i++)
				{
					for(j=0;j<s_line.elements[i].getSize();j++)
					{
						Operation.Connectiondb();
						Operation.modifyLine(s_line.elements[i]);
					}
				}
				for(i=0;i<s_Circle.getSize();i++)
				{
					for(j=0;j<s_Circle.elements[i].getSize();j++)
					{
						Operation.Connectiondb();
						Operation.modifyCircle(s_Circle.elements[i]);
					}
				}
				for(i=0;i<s_note.getSize();i++)
				{
					Operation.Connectiondb();
					Operation.modifyNote(s_note.elements[i]);
				}
			}
		}
		else 
		{
			m_ptBaseGisTool->LButtonUp(pDC,nFlags,point);
		}
	}
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}



void CsunflowerView::OnCreateLine()
{
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=11;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
}


void CsunflowerView::OnSelectLine()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=22;
	tag_linecut=1;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
}


void CsunflowerView::OnModifyLine()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=33;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
}


void CsunflowerView::OnMoveLine()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=44;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
}


void CsunflowerView::OnDeleteLine()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=55;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
}


void CsunflowerView::OnCut()
{
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=22;
	tag_linecut=-1;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
	// TODO: 在此添加命令处理程序代码
}


void CsunflowerView::OnDlinetopoint()
{
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=22;
	tag_Dlinetopoint=-1;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);	
	// TODO: 在此添加命令处理程序代码
}


void CsunflowerView::OnCreateLBuffer()
{
	// TODO: 在此添加命令处理程序代码
	
	if (m_ptBaseGisTool != NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
    int mark;
	InputBufferDlg(mark,rad,color);
	if(rad==0){
		rad=5;
	}
	if(mark==0){
		tag=123456;
	}
	OnRefresh();
}


void CsunflowerView::OnCreateCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=111;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);	
}


void CsunflowerView::OnSelectCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=222;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);	
}


void CsunflowerView::OnModifyCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=333;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);	
}


void CsunflowerView::OnMoveCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=444;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);	
}


void CsunflowerView::OnDeleteCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=555;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);	
}


void CsunflowerView::OnSquareDeleteCircle()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=666;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Circle(this);
}


void CsunflowerView::OnCreateNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=1111;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);
	
}


void CsunflowerView::OnSelectNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=2222;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);	
}


void CsunflowerView::OnModifyNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=3333;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);	
}


void CsunflowerView::OnMoveNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=4444;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);	
}


void CsunflowerView::OnDeleteNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=5555;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);	
}


void CsunflowerView::OnSquareDeletePoint()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=666;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Point(this);
}


void CsunflowerView::OnSquareDeleteNote()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=666;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Note(this);
}


void CsunflowerView::OnSquareDeleteLine()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=666;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CGisTool_Line(this);
}


void CsunflowerView::OnRefresh()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}


void CsunflowerView::OnReset()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	CDC *pDC=GetDC();
	tag=666666;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CBaseGisTool();
	CRect rect;
	GetWindowRect(&rect);
	m_ptBaseGisTool->CBaseGisTool::OnReset(rect,pDC);
	OnRefresh();
	ReleaseDC(pDC);
}


void CsunflowerView::OnZoomin()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=99999;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CBaseGisTool();
}


void CsunflowerView::OnZoomout()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=88888;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CBaseGisTool();
}


void CsunflowerView::OnMove()
{
	// TODO: 在此添加命令处理程序代码
	if (m_ptBaseGisTool!=NULL)
	{
		delete m_ptBaseGisTool;
		m_ptBaseGisTool = NULL;
	}
	tag=77777;
	Isselectpoint=false;
	Isselectline=false;
	Isselectcircle=false;
	Isselectnote=false;
	m_ptBaseGisTool = new CBaseGisTool();
}


BOOL CsunflowerView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 if (pCopyDataStruct != NULL)  
	 {  

        LPCTSTR pszText = (LPCTSTR)(pCopyDataStruct->lpData);  
		editlayer=_ttoi(pszText);
		OnRefresh();
	 }  
	return 1;
}


void CsunflowerView::OnUpdatePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSelectPoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateModifyPoint(CCmdUI *pCmdUI)
{
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateMovePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateDeletePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSquareDeletePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==0)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateCreateLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSelectLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateModifyLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateMoveLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateDeleteLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateCut(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateDlinetopoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSquareDeleteLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==1)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateCreateCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
    if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSelectCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateModifyCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);

}


void CsunflowerView::OnUpdateMoveCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateDeleteCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSquareDeleteCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==2)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateCreateNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSelectNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateModifyNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateMoveNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateDeleteNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}


void CsunflowerView::OnUpdateSquareDeleteNote(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(s_layer.elements[editlayer].mtype==3)
		pCmdUI->Enable(TRUE);
	else 
		pCmdUI->Enable(FALSE);
}
