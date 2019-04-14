#pragma once
#include "basegistool.h"
class CGisTool_Circle :
	public CBaseGisTool
{
public:
	CGisTool_Circle(void);
	CGisTool_Circle(CView* ptView);
	virtual ~CGisTool_Circle(void);
public:
	void Draw(GeoCircle &circle,CDC *pDC);
	void Select(CPoint &point,CDC *pDC);
	void Modify(CPoint &point,CDC *pDC);
	void Move(CPoint &point,CDC *pDC);
	void Delete(CPoint &point,CDC *pDC);
	void SquareDelete(CDC *pDC);
	void DrawBuffer(GeoCircle &circle,CDC *pDC,int r,COLORREF color);
	int LButtonDown(CDC *pDC,UINT nFlags, CPoint point);
	int MouseMove(CDC *pDC,UINT nFlags, CPoint point);
	int RButtonUp(CDC *pDC,UINT nFlags, CPoint point);
	int LButtonUp(CDC *pDC,UINT nFlags, CPoint point);
private:
	long	m_step;
	POINT	m_startPnt;
	POINT	m_lastPnt;
	GeoCircle circle;
	CBrush *pOldBrush;
	CPen *pOldPen;
};

