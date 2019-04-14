
// sunflowerView.h : CsunflowerView 类的接口
//

#pragma once
#include "BaseGisTool.h"
#include "GisTool_Point.h"
#include "GisTool_Line.h"
#include "GisTool_Circle.h"
#include "GisTool_Note.h"

class CsunflowerView : public CView
{
protected: // 仅从序列化创建
	CsunflowerView();
	DECLARE_DYNCREATE(CsunflowerView)

// 特性
public:
	CsunflowerDoc* GetDocument() const;
	CBaseGisTool*	m_ptBaseGisTool;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CsunflowerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCreatePoint();
	afx_msg void OnSelectPoint();
	afx_msg void OnModifyPoint();
	afx_msg void OnMovePoint();
	afx_msg void OnDeletePoint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCreateLine();
	afx_msg void OnSelectLine();
	afx_msg void OnModifyLine();
	afx_msg void OnMoveLine();
	afx_msg void OnDeleteLine();
	afx_msg void OnCut();
	afx_msg void OnDlinetopoint();
	afx_msg void OnCreateLBuffer();
	afx_msg void OnCreateCircle();
	afx_msg void OnSelectCircle();
	afx_msg void OnModifyCircle();
	afx_msg void OnMoveCircle();
	afx_msg void OnDeleteCircle();
	afx_msg void OnSquareDeleteCircle();
	afx_msg void OnCreateNote();
	afx_msg void OnSelectNote();
	afx_msg void OnModifyNote();
	afx_msg void OnMoveNote();
	afx_msg void OnDeleteNote();
	afx_msg void OnSquareDeletePoint();
	afx_msg void OnSquareDeleteNote();
	afx_msg void OnSquareDeleteLine();
	afx_msg void OnRefresh();
	afx_msg void OnReset();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnMove();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnUpdatePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModifyPoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMovePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeletePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSquareDeletePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModifyLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDlinetopoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSquareDeleteLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModifyCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSquareDeleteCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCreateNote(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectNote(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModifyNote(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveNote(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteNote(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSquareDeleteNote(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // sunflowerView.cpp 中的调试版本
inline CsunflowerDoc* CsunflowerView::GetDocument() const
   { return reinterpret_cast<CsunflowerDoc*>(m_pDocument); }
#endif

