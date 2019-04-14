#pragma once
#include "basegistool.h"

class CGisTool_Line :
	public CBaseGisTool
{
public:
	CGisTool_Line(void);
	CGisTool_Line(CView* ptView);
	virtual ~CGisTool_Line(void);
public:
	void Draw(GeoLine &line,CDC *pDC);
	void Select(CPoint &point,CDC *pDC);
	void Modify(CPoint &point,CDC *pDC);
	void Move(CPoint &point,CDC *pDC);
	void Delete(CPoint &point,CDC *pDC);
	void SquareDelete(CDC *pDC);
	void Cut(CPoint &point,CDC *pDC);
	void Dlinetopoint(CPoint &point,CDC *pDC);
	void DrawBuffer(GeoLine &line,CDC *pDC,int r,COLORREF color);
	int LButtonDown(CDC *pDC,UINT nFlags, CPoint point);
	int LButtonUp(CDC *pDC,UINT nFlags, CPoint point);
	int MouseMove(CDC *pDC,UINT nFlags, CPoint point);
	int RButtonUp(CDC *pDC,UINT nFlags, CPoint point);

private:
	GeoLine line;
	short	m_step;
	CPoint	m_lastStart;
	CPoint	m_lastEnd;
	CPen *pOldPen;
};

