#pragma once
#include "basegistool.h"
class CGisTool_Note :
	public CBaseGisTool
{
public:
	CGisTool_Note(void);
	CGisTool_Note(CView* ptView);
	virtual ~CGisTool_Note(void);
public:
	void Draw(GeoNote &note,CDC *pDC);
	void Select(GeoNote &note,CDC *pDC);
	void Modify(GeoNote &note,CDC *pDC);
	void Move(GeoNote &note,CDC *pDC);
	void Delete(GeoNote &note,CDC *pDC);
	void SquareDelete(CDC *pDC);
	int LButtonDown(CDC *pDC,UINT nFlags, CPoint point);
	int LButtonUp(CDC *pDC,UINT nFlags, CPoint point);
	int MouseMove(CDC *pDC,UINT nFlags, CPoint point);
	int RButtonUp(CDC *pDC,UINT nFlags, CPoint point);
private:
	GeoNote note;
};

