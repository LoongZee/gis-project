#include "StdAfx.h"
#include "GisTool_Circle.h"

extern "C" BOOL WINAPI InputCircleDlg(int &mark,int &type,COLORREF &color);

CGisTool_Circle::CGisTool_Circle(void)
{
	circle.color=RGB(0,0,0);
	circle.type=0;
	circle.layer=-1;
}
CGisTool_Circle::CGisTool_Circle(CView* ptView)
{
	circle.color=RGB(0,0,0);
	circle.type=0;
	circle.layer=-1;
	m_ptView = ptView;
	m_step = 0;
	m_startPnt.x = 0;
	m_startPnt.y = 0;
	m_lastPnt.x = 0;
	m_lastPnt.y = 0;
	if(tag==111)
	{
		int mark;
		InputCircleDlg(mark,circle.type,circle.color);
	}
}


CGisTool_Circle::~CGisTool_Circle(void)
{
	m_step = 0;
	m_startPnt.x = 0;
	m_startPnt.y = 0;
	m_lastPnt.x = 0;
	m_lastPnt.y = 0;
}

int CGisTool_Circle::LButtonDown(CDC *pDC,UINT nFlags, CPoint point)
{
	CBrush brush(circle.color);
	CPen pen(PS_SOLID,1,circle.color);
	pOldBrush=pDC->SelectObject(&brush);
	switch(tag)
	{
	case 111:
		if (m_step!=0&&circle.type==0)
		{
			m_step=m_startPnt.x=m_startPnt.y=m_lastPnt.x=m_lastPnt.y = 0;
		}
		else if(m_step!=0&&circle.type==1)
		{
			m_step=m_startPnt.x=m_startPnt.y=m_lastPnt.x=m_lastPnt.y = 0;
		}
		else if(m_step!=0&&circle.type==2)
		{
			pOldPen=pDC->SelectObject(&pen);
			pDC->MoveTo(m_startPnt);
		    pDC->LineTo(point);
		}
		m_step ++;
		m_startPnt = point;
	    circle.Push(m_startPnt);
	break;
	case 222:
		Select(point,pDC);
		break;
	case 333:
		Modify(point,pDC);
		break;
	case 444:
		Move(point,pDC);
		break;
	case 555:
		Delete(point,pDC);
		break;
	}
	pDC->SelectObject(pOldBrush);
	return (1);
}

int CGisTool_Circle::LButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag)
	{
	case 111:
		if(m_step!=0&&(circle.type==0||circle.type==1)&&point.x!=m_startPnt.x&&point.y!=m_startPnt.y)
		{
			circle.Push(point);
			circle.layer=s_layer.elements[editlayer].id;
			Operation.Connectiondb();
			circle.id=Operation.addCircle(circle);
			s_Circle.Push(circle);
			circle.data.clear();
           	m_step=m_startPnt.x=m_startPnt.y=m_lastPnt.x=m_lastPnt.y = 0;
		}
		else if(m_step!=0&&(circle.type==0||circle.type==1)&&point.x==m_startPnt.x&&point.y==m_startPnt.y)
		{
			circle.data.clear();
           	m_step=m_startPnt.x=m_startPnt.y=m_lastPnt.x=m_lastPnt.y = 0;
		}
		break;
	case 444:
		if(m_bLBtnDown) 
		{  
			m_bLBtnDown=false;
			s_Circle.elements[list]=m_circleMouse;
			Operation.Connectiondb();
			Operation.modifyCircle(s_Circle.elements[list]);
		}
		break;
	case 666:
		m_lastPnt=point;
		SquareDelete(pDC);
		break;
	}
	return (1);
}

int CGisTool_Circle::MouseMove(CDC *pDC,UINT nFlags, CPoint point)
{
	
	CBrush brush(circle.color);
	CPen pen(PS_SOLID,1,circle.color);
	pOldBrush=pDC->SelectObject(&brush);
	switch(tag)
	{
	case 111:	
		if (m_step!=0&&circle.type==0)
		{
			pDC->SetROP2(R2_NOTXORPEN);
			if (m_lastPnt.x!=0 && m_lastPnt.y!=0)
				pDC->Ellipse(m_startPnt.x, m_startPnt.y, m_lastPnt.x, m_lastPnt.y);
			pDC->Ellipse(m_startPnt.x, m_startPnt.y, point.x, point.y);
			m_lastPnt = point;
		}
		else if (m_step!=0&&circle.type==1)
		{
			pDC->SetROP2(R2_NOTXORPEN);
			if (m_lastPnt.x!=0 && m_lastPnt.y!=0)
				pDC->Rectangle(m_startPnt.x, m_startPnt.y, m_lastPnt.x, m_lastPnt.y);
			pDC->Rectangle(m_startPnt.x, m_startPnt.y, point.x, point.y);
			m_lastPnt = point;
		}
		else if (m_step!=0&&circle.type==2)
		{
			pOldPen=pDC->SelectObject(&pen);
			pDC->SetROP2(R2_NOTXORPEN);
			if (m_lastPnt.x!=0 && m_lastPnt.y!=0)
			{
				pDC->MoveTo(m_startPnt);
				pDC->LineTo(m_lastPnt);
			}
			pDC->MoveTo(m_startPnt);
			pDC->LineTo(point);
			m_lastPnt = point;
		}
		break;
	case 444:
		if(m_bLBtnDown) 
		{
			   GeoCircle temp_Circle=m_circleMouse;
			   temp_Circle.color=RGB(255,255,255);
			   Draw(temp_Circle,pDC);
			   CPoint temp_point=m_startPnt;
			   CSize offset(point-temp_point); 
			   for(int i=0;i<m_circleMouse.getSize();i++)
				   m_circleMouse.data[i]+=offset;
			   m_startPnt=point;
			   Draw(m_circleMouse,pDC);
			   selectcircle=m_circleMouse;  
		}
		break;
	}
	pDC->SelectObject(pOldBrush);
	return (1);
}

int CGisTool_Circle::RButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	CBrush brush(circle.color);
	CPen pen(PS_SOLID,1,circle.color);
	pOldBrush=pDC->SelectObject(&brush);
	switch(tag)
	{
	case 111:
		if(circle.type==2){
			pOldPen=pDC->SelectObject(&pen);
			m_step=m_startPnt.x=m_startPnt.y=m_lastPnt.x=m_lastPnt.y=0;
			int i;
			circle.Push(point);
			if(circle.getSize()>2){
			pDC->BeginPath();
			pDC->MoveTo(circle.data[0]);
			pDC->LineTo(circle.data[1]);
			for(i=1;i<circle.getSize()-1;i++)
			{
				pDC->LineTo(circle.data[i]);
			    pDC->LineTo(circle.data[i+1]);

			}
			pDC->LineTo(circle.data[i]);
			pDC->LineTo(circle.data[0]);
			pDC->EndPath();
			CRgn rgn;
			rgn.CreateFromPath(pDC);
			pOldBrush=pDC->SelectObject(&brush);
		    pDC->FillRgn(&rgn,&brush);
			circle.layer=s_layer.elements[editlayer].id;
			Operation.Connectiondb();
			circle.id=Operation.addCircle(circle);
			s_Circle.Push(circle);
			}
			circle.data.clear();
		}
	    break;
	}
	pDC->SelectObject(pOldBrush);
	return (1);
}


void CGisTool_Circle::Draw(GeoCircle &circle,CDC *pDC)
{
	CBrush brush(circle.color);
	CPen pen(PS_SOLID,1,circle.color);
	switch(circle.type)
	{
	case 0:
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Ellipse(circle.data[0].x, circle.data[0].y, circle.data[1].x, circle.data[1].y);
		pOldPen=pDC->SelectObject(&pen);
		pDC->Ellipse(circle.data[0].x, circle.data[0].y, circle.data[1].x, circle.data[1].y);
		break;
	case 1:
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Rectangle(circle.data[0].x, circle.data[0].y, circle.data[1].x, circle.data[1].y);
		pOldPen=pDC->SelectObject(&pen);
		pDC->Rectangle(circle.data[0].x, circle.data[0].y, circle.data[1].x, circle.data[1].y);
		break;
	case 2:
		int i;
		pOldPen=pDC->SelectObject(&pen);
		pDC->BeginPath();
		pDC->MoveTo(circle.data[0]);
		pDC->LineTo(circle.data[1]);
		for(i=1;i<circle.getSize()-1;i++)
		{
			pDC->LineTo(circle.data[i]);
			pDC->LineTo(circle.data[i+1]);
		}
		pDC->LineTo(circle.data[i]);
		pDC->LineTo(circle.data[0]);
		pDC->EndPath();
		CRgn rgn;
		rgn.CreateFromPath(pDC);
		pOldBrush=pDC->SelectObject(&brush);
		pDC->FillRgn(&rgn,&brush);
		break;
	}
	pDC->SelectObject(pOldBrush);
}


void CGisTool_Circle::Select(CPoint &point,CDC *pDC)
{
	Isselectcircle=false;
	int i;
	for(i=0;i<s_Circle.getSize();i++)
	{
		if(s_Circle.elements[i].type==0||s_Circle.elements[i].type==1)
		{
			if(OnMouseSelectcircle01(point.x,point.y,s_Circle.elements[i].data[0].x,s_Circle.elements[i].data[0].y,s_Circle.elements[i].data[1].x,s_Circle.elements[i].data[1].y))
			{
				list=i;
			    selectcircle=s_Circle.elements[i];
			    Isselectcircle=true;
			    break;
			}
		}
		else if(s_Circle.elements[i].type==2)
		{
			if(OnMouseSelectcircle2(s_Circle.elements[i].getSize(),s_Circle.elements[i],point.x,point.y))
			{
				list=i;
			    selectcircle=s_Circle.elements[i];
			    Isselectcircle=true;
			    break;
			}
		}
	}
}


void CGisTool_Circle::Modify(CPoint &point,CDC *pDC){
	Select(point,pDC);
	if(Isselectcircle){
		int temp_type,mark;
		COLORREF temp_color;
		InputCircleDlg(mark,temp_type,temp_color);
		if(mark==0){
			s_Circle.elements[list].color=RGB(255,255,255);
	    	Draw(s_Circle.elements[list],pDC);
	  //    s_Circle.elements[list].type=temp_type;
		    s_Circle.elements[list].color=temp_color;
			Operation.Connectiondb();
			Operation.modifyCircle(s_Circle.elements[list]);
		    Draw(s_Circle.elements[list],pDC); 
			selectcircle=s_Circle.elements[list];
		}
	}
}

void CGisTool_Circle::Move(CPoint &point,CDC *pDC){
	 Select(point,pDC);
	 if(Isselectcircle)
	 {
		  m_bLBtnDown=true;
		  m_startPnt=point;
          m_circleMouse=s_Circle.elements[list];
		  s_Circle.elements[list].color=RGB(255,255,255);  
	 }
}

void CGisTool_Circle::Delete(CPoint &point,CDC *pDC){
	 Select(point,pDC);
	  if(Isselectcircle)
	 {
         s_Circle.elements[list].color=RGB(255,255,255);
	     Draw(s_Circle.elements[list],pDC);
		 Operation.Connectiondb();
		 Operation.deleteCircle(s_Circle.elements[list]);
		 s_Circle.delete_elements(list);
		 Isselectcircle=false;
	 }
}

void CGisTool_Circle::SquareDelete(CDC *pDC)
{
	bool t;
	for(int i=0;i<s_Circle.getSize();i++)
	{
		t=true;
		for(int j=0;j<s_Circle.elements[i].getSize();j++)
		{
			if(OnMouseDelete(s_Circle.elements[i].data[j].x,s_Circle.elements[i].data[j].y,m_startp.x,m_startp.y,m_lastPnt.x,m_lastPnt.y))
			{
			   t=false;
			   break;
			}
		}
		if(t)
			{
				 s_Circle.elements[i].color=RGB(255,255,255);
				 Draw(s_Circle.elements[i],pDC);
				 Operation.Connectiondb();
		         Operation.deleteCircle(s_Circle.elements[i]);
		         s_Circle.delete_elements(i);
				 i--;
			}
	}
}


void CGisTool_Circle::DrawBuffer(GeoCircle &circle,CDC *pDC,int r,COLORREF color)
{
	int i, k;
	CBrush brush;
	brush.CreateSolidBrush(color);
	CPen *oldpen;
	CPen pen(PS_SOLID, 1, color);
	if (circle.type == 0)
	{
		pOldBrush = pDC->SelectObject(&brush);
		pDC->Ellipse(circle.data[0].x - r, circle.data[0].y - r, circle.data[1].x + r, circle.data[1].y + r);
	}
	else if (circle.type == 1)
	{
		pOldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(circle.data[0].x - r, circle.data[0].y - r, circle.data[1].x + r, circle.data[1].y + r);
	}

	else {
		for (i = 0; i < circle.getSize() - 1; i++){
			pOldBrush = pDC->SelectObject(&brush);
			CPoint * points;
			//求出矩形四个顶点：
			points = GetPolygon(circle.data[i].x, circle.data[i].y, circle.data[i + 1].x, circle.data[i + 1].y, r);
			//画出线段的多边形缓冲区：
			pDC->Polygon(points, 4);
			oldpen = pDC->SelectObject(&pen);
			for (k = 0; k < 3; k++){
				pDC->MoveTo(points[k]);
				pDC->LineTo(points[k + 1]);
			}
			pDC->MoveTo(points[3]);
			pDC->LineTo(points[0]);
			//画出顶点处的圆形缓冲区;
			pDC->Ellipse(circle.data[i].x - r, circle.data[i].y + r, circle.data[i].x + r, circle.data[i].y - r);
			oldpen = pDC->SelectObject(&pen);
			pDC->Ellipse(circle.data[i].x - r, circle.data[i].y + r, circle.data[i].x + r, circle.data[i].y - r);
			delete[]points;
		}
		pDC->Ellipse(circle.data[i].x - r, circle.data[i].y + r, circle.data[i].x + r, circle.data[i].y - r);
		oldpen = pDC->SelectObject(&pen);
		pDC->Ellipse(circle.data[i].x - r, circle.data[i].y + r, circle.data[i].x + r, circle.data[i].y - r);
		CPoint * points;
		int m = circle.getSize() - 1;
		points = GetPolygon(circle.data[m].x, circle.data[m].y, circle.data[0].x, circle.data[0].y, r);
		pDC->Polygon(points, 4);
		oldpen = pDC->SelectObject(&pen);
		for (k = 0; k < 3; k++){
			pDC->MoveTo(points[k]);
			pDC->LineTo(points[k + 1]);
		}
		pDC->MoveTo(points[3]);
		pDC->LineTo(points[0]);
		delete[] points;
	}	
}
