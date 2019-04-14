#include "StdAfx.h"
#include "BaseGisTool.h"


CBaseGisTool::CBaseGisTool(void)
{
}


CBaseGisTool::~CBaseGisTool(void)
{
}

int CBaseGisTool::LButtonDown (CDC *pDC,UINT nFlags, CPoint point)
{
	return (0);
}
int CBaseGisTool::MouseMove (CDC *pDC,UINT nFlags, CPoint point)
{
	return (0);
}

int CBaseGisTool::RButtonUp (CDC *pDC,UINT nFlags, CPoint point)
{
	return (0);
}
int CBaseGisTool::LButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	return (1);
}
void CBaseGisTool::Draw(GeoPoint &point,CDC *pDC)
{

}

void CBaseGisTool::Draw(GeoLine &line,CDC *pDC)
{
}


void CBaseGisTool::DrawBuffer(CDC *pDC) {

}

void CBaseGisTool::Draw(GeoCircle &circle,CDC *pDC){

}

void CBaseGisTool::Draw(GeoNote &note,CDC *pDC){


}
void CBaseGisTool::Zoomin(CDC *pDC){
	if(m_startp.x!=0&&m_startp.y!=0&&m_lastp.x!=0&&m_lastp.y!=0&&m_startp.x!=m_lastp.x)
	{
		int i,j;
		CPoint in,in1;
		in.x=long((m_startp.x+m_lastp.x)/2);
		in.y=long((m_startp.y+m_lastp.y)/2);
		in1.x=long(in.x/1.3);
		in1.y=long(in.y/1.3);
	    CSize offset(in-in1);
		for(i=0;i<s_point.getSize();i++)
		{
			s_point.elements[i].mpoint.x=long(s_point.elements[i].mpoint.x/1.3)+offset.cx;
			s_point.elements[i].mpoint.y=long(s_point.elements[i].mpoint.y/1.3)+offset.cy;
			Operation.Connectiondb();
			Operation.modifyPoint(s_point.elements[i]);
		}
		for(i=0;i<s_line.getSize();i++)
		{
			for(j=0;j<s_line.elements[i].getSize();j++)
			{
				s_line.elements[i].data[j].x=long(s_line.elements[i].data[j].x/1.3)+offset.cx;
				s_line.elements[i].data[j].y=long(s_line.elements[i].data[j].y/1.3)+offset.cy;
				Operation.Connectiondb();
				Operation.modifyLine(s_line.elements[i]);
			}
		}
		for(i=0;i<s_Circle.getSize();i++)
		{
			for(j=0;j<s_Circle.elements[i].getSize();j++)
			{
				s_Circle.elements[i].data[j].x=long(s_Circle.elements[i].data[j].x/1.3)+offset.cx;
				s_Circle.elements[i].data[j].y=long(s_Circle.elements[i].data[j].y/1.3)+offset.cy;
				Operation.Connectiondb();
				Operation.modifyCircle(s_Circle.elements[i]);
			}
		
		}
		for(i=0;i<s_note.getSize();i++)
		{
			s_note.elements[i].mpoint.x=long(s_note.elements[i].mpoint.x/1.3)+offset.cx;
			s_note.elements[i].mpoint.y=long(s_note.elements[i].mpoint.y/1.3)+offset.cy;
			Operation.Connectiondb();
			Operation.modifyNote(s_note.elements[i]);
		}
	}
}

void CBaseGisTool::Zoomout(CDC *pDC){
	if(m_startp.x!=0&&m_startp.y!=0&&m_lastp.x!=0&&m_lastp.y!=0&&m_startp.x!=m_lastp.x)
	{
		int i,j;
		CPoint in,in1;
		in.x=long((m_startp.x+m_lastp.x)/2);
		in.y=long((m_startp.y+m_lastp.y)/2);
		in1.x=long(in.x*1.3);
		in1.y=long(in.y*1.3);
	    CSize offset(in-in1);
		for(i=0;i<s_point.getSize();i++)
		{
			s_point.elements[i].mpoint.x=long(s_point.elements[i].mpoint.x*1.3)+offset.cx;
			s_point.elements[i].mpoint.y=long(s_point.elements[i].mpoint.y*1.3)+offset.cy;
			Operation.Connectiondb();
			Operation.modifyPoint(s_point.elements[i]);
		}
		for(i=0;i<s_line.getSize();i++)
		{
			for(j=0;j<s_line.elements[i].getSize();j++)
			{
				s_line.elements[i].data[j].x=long(s_line.elements[i].data[j].x*1.3)+offset.cx;
				s_line.elements[i].data[j].y=long(s_line.elements[i].data[j].y*1.3)+offset.cy;
				Operation.Connectiondb();
				Operation.modifyLine(s_line.elements[i]);
			}
		}
		for(i=0;i<s_Circle.getSize();i++)
		{
			for(j=0;j<s_Circle.elements[i].getSize();j++)
			{
				s_Circle.elements[i].data[j].x=long(s_Circle.elements[i].data[j].x*1.3)+offset.cx;
				s_Circle.elements[i].data[j].y=long(s_Circle.elements[i].data[j].y*1.3)+offset.cy;
				Operation.Connectiondb();
				Operation.modifyCircle(s_Circle.elements[i]);
			}
		
		}
		for(i=0;i<s_note.getSize();i++)
		{
			s_note.elements[i].mpoint.x=long(s_note.elements[i].mpoint.x*1.3)+offset.cx;
			s_note.elements[i].mpoint.y=long(s_note.elements[i].mpoint.y*1.3)+offset.cy;
			Operation.Connectiondb();
			Operation.modifyNote(s_note.elements[i]);
		}
	}
}

void CBaseGisTool::OnMove(CDC *pDC){
	if(m_startp.x!=0&&m_startp.y!=0&&m_lastp.x!=0&&m_lastp.y!=0&&m_startp.x!=m_lastp.x)
	{
		int i,j;
	    CSize offset(m_lastp-m_startp);
		for(i=0;i<s_point.getSize();i++)
		{
			s_point.elements[i].mpoint=s_point.elements[i].mpoint+offset;

		}
		for(i=0;i<s_line.getSize();i++)
		{
			for(j=0;j<s_line.elements[i].getSize();j++)
			{
				s_line.elements[i].data[j]=s_line.elements[i].data[j]+offset;

			}
		}
		for(i=0;i<s_Circle.getSize();i++)
		{
			for(j=0;j<s_Circle.elements[i].getSize();j++)
			{
				s_Circle.elements[i].data[j]=s_Circle.elements[i].data[j]+offset;
			}
		
		}
		for(i=0;i<s_note.getSize();i++)
		{
			s_note.elements[i].mpoint=s_note.elements[i].mpoint+offset;
		}
	}
}

void CBaseGisTool::OnReset(CRect rect,CDC *pDC){
	int i=0,j=0;
	long max_x=0,max_y=0;
	long min_x=1366,min_y=768;
	double Hei=rect.Height();
	double Wid=rect.Width();
	for(i=0;i<s_point.getSize();i++)
	{
		if(max_x<s_point.elements[i].mpoint.x)
            max_x=s_point.elements[i].mpoint.x;
		if(max_y<s_point.elements[i].mpoint.y)
			max_y=s_point.elements[i].mpoint.y;
        if(min_x>s_point.elements[i].mpoint.x)
            min_x=s_point.elements[i].mpoint.x;
		if(min_y>s_point.elements[i].mpoint.y)
			min_y=s_point.elements[i].mpoint.y;
	}
	for(i=0;i<s_line.getSize();i++)
	{
		for(j=0;j<s_line.elements[i].getSize();j++)
		{
			if(max_x<s_line.elements[i].data[j].x)
				max_x=s_line.elements[i].data[j].x;
			if(max_y<s_line.elements[i].data[j].y)
				max_y=s_line.elements[i].data[j].y;
			if(min_x>s_line.elements[i].data[j].x)
				min_x=s_line.elements[i].data[j].x;
			if(min_y>s_line.elements[i].data[j].y)
			    min_y=s_line.elements[i].data[j].y;
		}
	}
	for(i=0;i<s_Circle.getSize();i++)
	{
		for(j=0;j<s_Circle.elements[i].getSize();j++)
		{
			if(max_x<s_Circle.elements[i].data[j].x)
				max_x=s_Circle.elements[i].data[j].x;
			if(max_y<s_Circle.elements[i].data[j].y)
				max_y=s_Circle.elements[i].data[j].y;
			if(min_x>s_Circle.elements[i].data[j].x)
				min_x=s_Circle.elements[i].data[j].x;
			if(min_y>s_Circle.elements[i].data[j].y)
				min_y=s_Circle.elements[i].data[j].y;
		}
	}
	for(i=0;i<s_note.getSize();i++)
	{
		if(max_x<s_note.elements[i].mpoint.x)
			max_x=s_note.elements[i].mpoint.x;
		if(max_y<s_note.elements[i].mpoint.y)
			max_y=s_note.elements[i].mpoint.y;
        if(min_x>s_note.elements[i].mpoint.x)
			min_x=s_note.elements[i].mpoint.x;
		if(min_y>s_note.elements[i].mpoint.y)
			min_y=s_note.elements[i].mpoint.y;
	}
	if(max_x!=0&&max_y!=0){
		m_startp.x=(min_x+max_x)/2;
		m_startp.y=(min_y+max_y)/2;
		m_lastp.x=long(Wid/2);
		m_lastp.y=long(Hei/2);
		OnMove(pDC);
	}
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