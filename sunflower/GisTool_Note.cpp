#include "StdAfx.h"
#include "GisTool_Note.h"

extern "C" BOOL WINAPI InputnoteDlg(int &mark,CString &str,COLORREF &color);

CGisTool_Note::CGisTool_Note(void)
{
	note.color=RGB(0,0,0);
	note.mnote="";
	note.layer=-1;
}

CGisTool_Note::CGisTool_Note(CView* ptView)
{
	note.color=RGB(0,0,0);
	note.mnote="";
	note.layer=-1;
	m_ptView = ptView;
}


CGisTool_Note::~CGisTool_Note(void)
{

}

int CGisTool_Note::LButtonDown(CDC *pDC,UINT nFlags, CPoint point)
{	
	switch(tag){
	case 1111:
		int mark;
		InputnoteDlg(mark,note.mnote,note.color);
		note.mpoint=point;
		Draw(note,pDC);
		note.layer=s_layer.elements[editlayer].id;
		Operation.Connectiondb();
		note.id=Operation.addNote(note);
		s_note.Push(note);
		break;
	case 2222:
		Draw(selectnote,pDC);
		note.mpoint=point;
		Select(note,pDC);
		break;
	case 3333:
		note.mpoint=point;
	    Modify(note,pDC);
		break;
	case 4444:
		note.mpoint=point;
		Move(note,pDC);
		break;
	case 5555:
		note.mpoint=point;
	    Delete(note,pDC);
		break;
		}
	
	return (1);
}

int CGisTool_Note::MouseMove(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag){
			case 4444:
				if(m_bLBtnDown) 
            {  
			   GeoNote temp_note=m_noteMouse;
			   temp_note.color=RGB(255,255,255);
			   Draw(temp_note,pDC);
			   m_noteMouse.mpoint=point;
			   Draw(m_noteMouse,pDC);
			   selectnote=m_noteMouse;
			}
				break;
		}
	
	return (1);
}
int CGisTool_Note::LButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{
	switch(tag)
	{
			case 4444:
				if(m_bLBtnDown) 
            {  
				m_bLBtnDown=false;
				s_note.elements[list]=m_noteMouse;
				Operation.Connectiondb();
			    Operation.modifyNote(s_note.elements[list]);
			}
				break;
			case 666:
				note.mpoint=point;
		        SquareDelete(pDC);
	}
	return (1);
}

int CGisTool_Note::RButtonUp(CDC *pDC,UINT nFlags, CPoint point)
{

	return (1);
}


void CGisTool_Note::Draw(GeoNote &note,CDC *pDC)
{
	pDC->SetTextColor(note.color);
	pDC->TextOut(note.mpoint.x,note.mpoint.y,note.mnote);
}

void CGisTool_Note::Select(GeoNote &note,CDC *pDC)
{
	Isselectnote=false;
	for (int i=0;i<s_note.getSize();i++)
	{   
		CSize size = pDC->GetTextExtent(s_note.elements[i].mnote); 
		rect_note.SetRect((int)s_note.elements[i].mpoint.x,(int)s_note.elements[i].mpoint.y,(int)s_note.elements[i].mpoint.x+size.cx,(int)s_note.elements[i].mpoint.y+size.cy);
		if(rect_note.PtInRect(note.mpoint)) 
		{  
			list=i;
			selectnote=s_note.elements[i];
			Isselectnote=true;
			break;
		}
	}
}

void CGisTool_Note::Modify(GeoNote &note,CDC *pDC)
{
	Select(note,pDC);
	if(Isselectnote){
		int mark;
		CString temp_str;
		COLORREF temp_color;
		InputnoteDlg(mark,temp_str,temp_color);
		if(mark==0){
			s_note.elements[list].color=RGB(255,255,255);
	    	Draw(s_note.elements[list],pDC);
			s_note.elements[list].mnote=temp_str;
		    s_note.elements[list].color=temp_color;
			Operation.Connectiondb();
			Operation.modifyNote(s_note.elements[list]);
		    Draw(s_note.elements[list],pDC); 
			selectnote=s_note.elements[list];
		}
	}
}

void CGisTool_Note::Move(GeoNote &note,CDC *pDC)
{
	 Select(note,pDC);
	 if(Isselectnote)
	 {
		  m_bLBtnDown=true;
          m_noteMouse=s_note.elements[list];
		  s_note.elements[list].color=RGB(255,255,255);
	 }
}

void CGisTool_Note::Delete(GeoNote &note,CDC *pDC){
	 Select(note,pDC);
	  if(Isselectnote)
	 {
         s_note.elements[list].color=RGB(255,255,255);
	     Draw(s_note.elements[list],pDC);
		 Operation.Connectiondb();
		 Operation.deleteNote(s_note.elements[list]);
		 s_note.delete_elements(list);
		 Isselectnote=false;
	 }
}

void  CGisTool_Note::SquareDelete(CDC *pDC){
	bool t;
	
	for(int i=0;i<s_note.getSize();i++)
	{
		CSize size = pDC->GetTextExtent(s_note.elements[i].mnote); 
		t=true;
		if(OnMouseDelete(s_note.elements[i].mpoint.x,s_note.elements[i].mpoint.y,m_startp.x,m_startp.y,note.mpoint.x,note.mpoint.y))
		{
			   t=false;
		}
		if(OnMouseDelete(s_note.elements[i].mpoint.x+size.cx,s_note.elements[i].mpoint.y+size.cy,m_startp.x,m_startp.y,note.mpoint.x,note.mpoint.y))
		{
			   t=false;
		}
		if(OnMouseDelete(s_note.elements[i].mpoint.x,s_note.elements[i].mpoint.y+size.cy,m_startp.x,m_startp.y,note.mpoint.x,note.mpoint.y))
		{
			   t=false;
		}
		if(OnMouseDelete(s_note.elements[i].mpoint.x+size.cx,s_note.elements[i].mpoint.y,m_startp.x,m_startp.y,note.mpoint.x,note.mpoint.y))
		{
			   t=false;
		}
		if(t)
			{
				 s_note.elements[i].color=RGB(255,255,255);
				 Draw(s_note.elements[i],pDC);
				 Operation.Connectiondb();
		         Operation.deleteNote(s_note.elements[i]);
		         s_note.delete_elements(i);
				 i--;
			}
	}
}