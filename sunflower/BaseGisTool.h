#pragma once
class CBaseGisTool
{
public:
	CBaseGisTool(void);
	virtual ~CBaseGisTool(void);
public:
	void Zoomin(CDC *pDC);
	void Zoomout(CDC *pDC);
	void OnMove(CDC *pDC);
	void OnReset(CRect rect,CDC *pDC);
	virtual void Draw(GeoPoint &point,CDC *pDC);
	virtual void Draw(GeoLine &line,CDC *pDC);
	virtual void Draw(GeoCircle &circle,CDC *pDC);
	virtual void Draw(GeoNote &note,CDC *pDC);
	virtual void DrawBuffer(CDC *pDC);
	virtual int LButtonDown(CDC *pDC,UINT nFlags, CPoint point);
	virtual int LButtonUp(CDC *pDC,UINT nFlags, CPoint point);
	virtual int MouseMove(CDC *pDC,UINT nFlags, CPoint point);
	virtual int RButtonUp(CDC *pDC,UINT nFlags, CPoint point);
public:
	CView*	m_ptView;
};

