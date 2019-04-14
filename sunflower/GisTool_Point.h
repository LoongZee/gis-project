#pragma once

#include "basegistool.h"
class CGisTool_Point :
	public CBaseGisTool
{
public:
	CGisTool_Point(void);
	CGisTool_Point(CView* ptView);
	virtual ~CGisTool_Point(void);
public:
	void Draw(GeoPoint &point,CDC *pDC);
	void Select(GeoPoint &point,CDC *pDC);
	void Modify(GeoPoint &point,CDC *pDC);
	void Move(GeoPoint &point,CDC *pDC);
	void Delete(GeoPoint &point,CDC *pDC);
	void SquareDelete(CDC *pDC);
	void DrawBuffer(GeoPoint &point,CDC *pDC,int r,COLORREF color);
	int LButtonDown(CDC *pDC,UINT nFlags, CPoint point);
	int LButtonUp(CDC *pDC,UINT nFlags, CPoint point);
	int MouseMove(CDC *pDC,UINT nFlags, CPoint point);
	int RButtonUp(CDC *pDC,UINT nFlags, CPoint point);
private:
	GeoPoint p;
};

