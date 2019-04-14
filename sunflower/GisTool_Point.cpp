#include "StdAfx.h"
#include "GisTool_Point.h"

extern "C" BOOL WINAPI InputPointDlg(int &mark,int &type,COLORREF &color);

CGisTool_Point::CGisTool_Point(void)
{
	p.color=RGB(0,0,0);
	p.layer=-1;
	p.type=0;
}

CGisTool_Point::CGisTool_Point(CView* ptView)
{
	p.color=RGB(0,0,0);
	p.type=0;
	m_ptView = ptView;
	int mark;
	if(tag==1)
	{
		InputPointDlg(mark,p.type,p.color);
	}
}


CGisTool_Point::~CGisTool_Point(void)
{
}

int CGisTool_Point::LButtonDown(CDC *pDC,UINT nFlags, CPoint point)
{	
	switch(tag){
			case 1:
				p.mpoint=point;
				Draw(p,pDC);
				p.layer=s_layer.elements[editlayer].id;
				Operation.Connectiondb();
				p.id=Operation.addPoint(p);
				s_point.Push(p);
				break;
			case 2:
				Draw(selectpoint,pDC);
				p.mpoint=point;
				Select(p,pDC);
				break;
			case 3:
			    p.mpoint=point;
			    Modify(p,pDC);
				break;
			case 4:
			    p.mpoint=point;
			    Move(p,pDC);
				break;
			case 5:
				p.mpoint=point;
			    Delete(p,pDC);
				break;
		}
	return (1);
}

int CGisTool_Point::MouseMove(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag){
			case 4:
				if(m_bLBtnDown) 
            {  
			   GeoPoint temp_point=m_pointMouse;
			   temp_point.color=RGB(255,255,255);
			   Draw(temp_point,pDC);
			   m_pointMouse.mpoint=point;
			   Draw(m_pointMouse,pDC);
			   selectpoint=m_pointMouse;
			}
				break;
		}
	return (1);
}
int CGisTool_Point::LButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag)
	{
			case 4:
				if(m_bLBtnDown) 
            {  
				m_bLBtnDown=false;
				s_point.elements[list]=m_pointMouse;
				Operation.Connectiondb();
				Operation.modifyPoint(s_point.elements[list]);
			}
				break;
			case 666:
				p.mpoint=point;
		        SquareDelete(pDC);
				break;
	}

	return (1);
}

int CGisTool_Point::RButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{

	return (1);
}


void CGisTool_Point::Draw(GeoPoint &point,CDC *pDC)
{
	if(point.type==0)//  当 type==0 绘制方形点
	{
		pDC->SetPixel(point.mpoint.x,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y+1,point.color);
	}
	if(point.type==1)  //当 type==1 绘制三角点
	{
		pDC->SetPixel(point.mpoint.x,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y-2,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x-2,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x+2,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-2,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x+2,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x-3,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x+3,point.mpoint.y+1,point.color);
        pDC->SetPixel(point.mpoint.x-3,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x-2,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x+2,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x+3,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x-4,point.mpoint.y+2,point.color);
		pDC->SetPixel(point.mpoint.x+4,point.mpoint.y+2,point.color);
		}
	if(point.type==2)  //当 type==2 绘制空心点
	{
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y+1,point.color);
		pDC->SetPixel(point.mpoint.x+1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y-1,point.color);
		pDC->SetPixel(point.mpoint.x-1,point.mpoint.y+1,point.color);
	}
}

void CGisTool_Point::Select(GeoPoint &point,CDC *pDC){
	Isselectpoint=false;
	for (int i=0;i<s_point.getSize();i++)
	{   
		rect_point.SetRect((int)s_point.elements[i].mpoint.x-4,(int)s_point.elements[i].mpoint.y-4,(int)s_point.elements[i].mpoint.x+4,(int)s_point.elements[i].mpoint.y+4);
		if(rect_point.PtInRect(point.mpoint)) 
		{  
			list=i;
			selectpoint=s_point.elements[i];
			Isselectpoint=true;
			break;
		}
	}
}

void CGisTool_Point::Modify(GeoPoint &point,CDC *pDC){
	Select(point,pDC);
	if(Isselectpoint){
		int temp_type,mark;
		COLORREF temp_color;
		InputPointDlg(mark,temp_type,temp_color);
		if(mark==0){
			s_point.elements[list].color=RGB(255,255,255);
	    	Draw(s_point.elements[list],pDC);
		    s_point.elements[list].type=temp_type;
		    s_point.elements[list].color=temp_color;
			Operation.Connectiondb();
			Operation.modifyPoint(s_point.elements[list]);
		    Draw(s_point.elements[list],pDC); 
			selectpoint=s_point.elements[list];
		}
	}
}

void CGisTool_Point::Move(GeoPoint &point,CDC *pDC){
	 Select(point,pDC);
	 if(Isselectpoint)
	 {
		  m_bLBtnDown=true;
          m_pointMouse=s_point.elements[list];
		  s_point.elements[list].color=RGB(255,255,255);
	 }
}

void CGisTool_Point::Delete(GeoPoint &point,CDC *pDC){
	 Select(point,pDC);
	  if(Isselectpoint)
	 {
         s_point.elements[list].color=RGB(255,255,255);
	     Draw(s_point.elements[list],pDC);
		 Operation.Connectiondb();
		 Operation.deletePoint(s_point.elements[list]);
		 s_point.delete_elements(list);
		 Isselectpoint=false;
	 }
}



void CGisTool_Point::SquareDelete(CDC *pDC)
{
	bool t;
	for(int i=0;i<s_point.getSize();i++)
	{
		t=true;
		if(OnMouseDelete(s_point.elements[i].mpoint.x,s_point.elements[i].mpoint.y,m_startp.x,m_startp.y,p.mpoint.x,p.mpoint.y))
		{
			   t=false;
		}
		if(t)
			{
				 s_point.elements[i].color=RGB(255,255,255);
				 Draw(s_point.elements[i],pDC);
				 Operation.Connectiondb();
		         Operation.deletePoint(s_point.elements[i]);
		         s_point.delete_elements(i);
				 i--;
			}
	}
}

void CGisTool_Point::DrawBuffer(GeoPoint &point,CDC *pDC,int r,COLORREF color) 
{
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(color);
	CPen *oldpen;
	CPen pen(PS_SOLID,1,color);
	oldbrush = pDC->SelectObject(&brush);
	pDC->Ellipse(point.mpoint.x - r, point.mpoint.y + r, point.mpoint.x + r, point.mpoint.y - r);
	oldpen = pDC->SelectObject(&pen);
	pDC->Ellipse(point.mpoint.x - r, point.mpoint.y + r, point.mpoint.x + r, point.mpoint.y - r);
	pDC->SelectObject(oldbrush);
}