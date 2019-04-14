#include "StdAfx.h"
#include "GisTool_Line.h"

extern "C" BOOL WINAPI InputLineDlg(int &mark,int &type,int &width,COLORREF &color);

CGisTool_Line::CGisTool_Line(void)
{
	line.width=1;
	line.color=RGB(0,0,0);
	line.type=0;
	line.layer=-1;
}
CGisTool_Line::CGisTool_Line(CView* ptView)
{
	line.width=1;
	line.color=RGB(0,0,0);
	line.type=0;
	line.layer=-1;
	m_ptView = ptView;
	m_step = 0;
	m_lastStart.x = 0;
	m_lastStart.y = 0;
	m_lastEnd.x = 0;
	m_lastEnd.y = 0;
	if(tag==11)
	{
	int mark;
	InputLineDlg(mark,line.type,line.width,line.color);
	}
}
CGisTool_Line::~CGisTool_Line(void)
{
	m_step = 0;
	m_lastStart.x = 0;
	m_lastStart.y = 0;
	m_lastEnd.x = 0;
	m_lastEnd.y = 0;
}
int CGisTool_Line::LButtonDown(CDC *pDC,UINT nFlags, CPoint point)
{
	CPen pen(line.type,line.width,line.color);
	pOldPen=pDC->SelectObject(&pen);
	switch(tag){
	case 11:
		
		if (m_step!=0)
		{
			
			pDC->MoveTo(m_lastStart);
		    pDC->LineTo(point);
		}
		m_step ++;
		m_lastStart = point;
	    line.Push(m_lastStart);
		break;
	case 22:
		Select(point,pDC);
		break;
	case 33:
		Modify(point,pDC);
		break;
	case 44:
		Move(point,pDC);
		break;
	case 55:
		Delete(point,pDC);
		break;
	case 66:
		Cut(point,pDC);
		break;
	case 77:
		Dlinetopoint(point,pDC);
		break;
	}
	pDC->SelectObject(pOldPen);
	return (1);
}
int CGisTool_Line::LButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag)
	{
			case 44:
				if(m_bLBtnDown) 
            {  
				m_bLBtnDown=false;
				s_line.elements[list]=m_lineMouse;
				Operation.Connectiondb();
				Operation.modifyLine(s_line.elements[list]);
			}
				break;
			case 666:
			m_lastp=point;
		    SquareDelete(pDC);
	}

	return (1);
}
int CGisTool_Line::MouseMove(CDC *pDC,UINT nFlags, CPoint point)
{
	CPen pen(line.type,line.width,line.color);
	pOldPen=pDC->SelectObject(&pen);
	switch(tag)
	{
	case 11:
		if (m_step!=0)
		{
			pDC->SetROP2(R2_NOTXORPEN);
			if (m_lastEnd.x!=0 && m_lastEnd.y!=0)
			{
				pDC->MoveTo(m_lastStart);
				pDC->LineTo(m_lastEnd);
			}
			pDC->MoveTo(m_lastStart);
			pDC->LineTo(point);
			m_lastEnd = point;
		}
		break;
	case 44:
		if(m_bLBtnDown) 
		{
			   GeoLine temp_Line=m_lineMouse;
			   temp_Line.color=RGB(255,255,255);
			   Draw(temp_Line,pDC);
			   CPoint temp_point=m_lastStart;
			   CSize offset(point-temp_point); 
			   for(int i=0;i<m_lineMouse.getSize();i++)
				   m_lineMouse.data[i]+=offset;
			   m_lastStart=point;
			   Draw(m_lineMouse,pDC);
			   selectline=m_lineMouse;  
		}
		break;
				
	}
	pDC->SelectObject(pOldPen);	
	return (1);
}
int CGisTool_Line::RButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag)
	{
	case 11:
		m_step = 0;
	    m_lastStart.x = 0;
     	m_lastStart.y = 0;
	    m_lastEnd.x = 0;
	    m_lastEnd.y = 0;
        line.Push(point);
		line.layer=s_layer.elements[editlayer].id;
		Operation.Connectiondb();
		line.id=Operation.addLine(line);
	    s_line.Push(line);
		line.data.clear();
	    break;
	}
	return (1);
}


void CGisTool_Line::Draw(GeoLine &line,CDC *pDC){

	CPen pen(line.type,line.width,line.color);
	pOldPen=pDC->SelectObject(&pen);
	for(int i=0;i<line.getSize()-1;i++)
	{
		pDC->MoveTo(line.data[i]);
		pDC->LineTo(line.data[i+1]);
	}
	pDC->SelectObject(pOldPen);
}

void CGisTool_Line::Select(CPoint &point,CDC *pDC){
	Isselectline=false;
	int i;
	for(i=0;i<s_line.getSize();i++)
	{
		if(OnMouseSelectLine(point,s_line.elements[i])){
			list=i;
			selectline=s_line.elements[i];
			Isselectline=true;
			break;
		}
	}
	if(Isselectline){
	if(tag_linecut==-1){
		    tag=66;
			AfxMessageBox(_T("线成功选中,请选择剪断处！"));
	}
	else if(tag_Dlinetopoint==-1){
		    tag=77;
			AfxMessageBox(_T("线成功选中,请选择删除处！"));
	}
	}

}

void CGisTool_Line::Modify(CPoint &point,CDC *pDC){
	tag_linecut=1;
	tag_Dlinetopoint=1;
	Select(point,pDC);
	if(Isselectline){
		int temp_type,mark,temp_width;
		COLORREF temp_color;
		InputLineDlg(mark,temp_type,temp_width,temp_color);
		if(mark==0){
			s_line.elements[list].color=RGB(255,255,255);
	    	Draw(s_line.elements[list],pDC);
		    s_line.elements[list].type=temp_type;
			s_line.elements[list].width=temp_width;
		    s_line.elements[list].color=temp_color;
			Operation.Connectiondb();
			Operation.modifyLine(s_line.elements[list]);
		    Draw(s_line.elements[list],pDC); 
			selectline=s_line.elements[list];
		}
	}
}

void CGisTool_Line::Move(CPoint &point,CDC *pDC){
	 tag_linecut=1;
	 tag_Dlinetopoint=1;
	 Select(point,pDC);
	 if(Isselectline)
	 {
		  m_bLBtnDown=true;
		  m_lastStart=point;
          m_lineMouse=s_line.elements[list];
		  s_line.elements[list].color=RGB(255,255,255);
	 }
}

void CGisTool_Line::Delete(CPoint &point,CDC *pDC){
	 tag_linecut=1;
	 tag_Dlinetopoint=1;
	 Select(point,pDC);
	  if(Isselectline)
	 {
         s_line.elements[list].color=RGB(255,255,255);
	     Draw(s_line.elements[list],pDC);
		 Operation.Connectiondb();
	     Operation.deleteLine(s_line.elements[list]);
		 s_line.delete_elements(list);
		 Isselectline=false;
	 }
}

void CGisTool_Line::Cut(CPoint &point,CDC *pDC){
	if(Isselectline)
	{
		bool p=true;
		for (int i=0;i<s_line.elements[list].getSize();i++)
		{   
			rect_point.SetRect((int)s_line.elements[list].data[i].x-4,(int)s_line.elements[list].data[i].y-4,(int)s_line.elements[list].data[i].x+4,(int)s_line.elements[list].data[i].y+4);
			if(rect_point.PtInRect(point)) 
			{  
				GeoLine temp_line;
				temp_line.type=s_line.elements[list].type;
				temp_line.color=s_line.elements[list].color;
				temp_line.width=s_line.elements[list].width;
				for (int j=i;j<s_line.elements[list].getSize();j++)
				{
					temp_line.Push(s_line.elements[list].data[j]);
				}
				Draw(temp_line,pDC);
				Operation.Connectiondb();
				temp_line.layer=s_layer.elements[editlayer].id;
				temp_line.id=Operation.addLine(temp_line);
				s_line.Push(temp_line);
				s_line.elements[list].data.erase(s_line.elements[list].data.begin()+i+1,s_line.elements[list].data.end());
				Operation.Connectiondb();
				Operation.modifyLine(s_line.elements[list]);
				p=false;
				Isselectline=false;
				tag=22;
	            tag_linecut=-1;
				AfxMessageBox(_T("您已经成功剪断该线！"));
				break;
			}
		}
		if(p)
		{
			AfxMessageBox(_T("请重新选择剪断处！"));
		}
	}
}


void CGisTool_Line::Dlinetopoint(CPoint &point,CDC *pDC){
	if(Isselectline)
	{
		bool p=true;
		for (int i=0;i<s_line.elements[list].getSize();i++)
		{   
			rect_point.SetRect((int)s_line.elements[list].data[i].x-4,(int)s_line.elements[list].data[i].y-4,(int)s_line.elements[list].data[i].x+4,(int)s_line.elements[list].data[i].y+4);
			if(rect_point.PtInRect(point)) 
			{  
				GeoLine temp_line=s_line.elements[list];
				temp_line.color=RGB(255,255,255);
				Draw(temp_line,pDC);
				s_line.elements[list].data.erase(s_line.elements[list].data.begin()+i);
				Operation.Connectiondb();
				Operation.modifyLine(s_line.elements[list]);
				Draw(s_line.elements[list],pDC);
				p=false;
				Isselectline=false;
				tag=22;
	            tag_Dlinetopoint=-1;
				AfxMessageBox(_T("您已经成功删除线上的该点！"));
				break;
			}
		}
		if(p)
		{
			AfxMessageBox(_T("请重新选择删除处！"));
		}
	}
}


void CGisTool_Line::DrawBuffer(GeoLine &line,CDC *pDC,int r,COLORREF color) {
	int i,k;
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(color);
	CPen *oldpen;
	CPen pen(PS_SOLID,1,color);
	CPoint* points;
	for (i = 0; i < line.getSize()-1; i++){
	//求出矩形四个顶点：
		points=GetPolygon(line.data[i].x, line.data[i].y, line.data[i + 1].x, line.data[i + 1].y, r);
	//画出线段的多边形缓冲区：
		oldbrush = pDC->SelectObject(&brush);
		pDC->Polygon(points, 4);
		oldpen = pDC->SelectObject(&pen);
		for(k = 0;k < 3; k++){
			pDC->MoveTo(points[k]);
			pDC->LineTo(points[k+1]);
		}
		pDC->MoveTo(points[3]);
		pDC->LineTo(points[0]);
	//画出顶点处的圆形缓冲区;
		oldbrush = pDC->SelectObject(&brush);
		pDC->Ellipse(line.data[i].x - r, line.data[i].y + r, line.data[i].x + r, line.data[i].y - r);
		oldpen = pDC->SelectObject(&pen);
		pDC->Ellipse(line.data[i].x - r, line.data[i].y + r, line.data[i].x + r, line.data[i].y - r);
	}
	oldbrush = pDC->SelectObject(&brush);
	pDC->Ellipse(line.data[i].x - r, line.data[i].y + r, line.data[i].x + r, line.data[i].y - r);
	oldpen = pDC->SelectObject(&pen);
	pDC->Ellipse(line.data[i].x - r, line.data[i].y + r, line.data[i].x + r, line.data[i].y - r);
	delete []points;
	pDC->SelectObject(oldbrush);
}


void CGisTool_Line::SquareDelete(CDC *pDC)
{
	bool t;
	for(int i=0;i<s_line.getSize();i++)
	{
		t=true;
		for(int j=0;j<s_line.elements[i].getSize();j++)
		{
			if(OnMouseDelete(s_line.elements[i].data[j].x,s_line.elements[i].data[j].y,m_startp.x,m_startp.y,m_lastp.x,m_lastp.y))
			{
			   t=false;
			   break;
			}
		}
		if(t)
			{
				 s_line.elements[i].color=RGB(255,255,255);
				 Draw(s_line.elements[i],pDC);
				 Operation.Connectiondb();
				 Operation.deleteLine(s_line.elements[i]);
		         s_line.delete_elements(i);
				 i--;
			}
	}
}
