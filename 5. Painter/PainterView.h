
// PainterView.h : interface of the CPainterView class
//

#pragma once


class CPainterView : public CView
{
protected: // create from serialization only
	CPainterView() noexcept;
	DECLARE_DYNCREATE(CPainterView)

// Attributes
public:
	CPainterDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	int DrawObj(CDC* pDC, CShapeData& data);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	bool isDrawing;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	enum PlaceType {
		None,
		Line,
		Rect,
		RoundRect,
		Eclipse,
		Text,
		Erase
	} drawtype;
	bool drawFill;
	enum PlaceColor {
		Black,
		Red,
		Green,
		Blue
	} drawcolor;

	enum PlaceSize {
		SMALL, // 1
		MEDIUM,// 5
		LARGE  // 10
	} drawsize;
	CShapeData* selectedShape;

	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnRect();
	afx_msg void OnUpdateRect(CCmdUI* pCmdUI);
	afx_msg void OnRoundRect();
	afx_msg void OnUpdateRoundRect(CCmdUI* pCmdUI);
	afx_msg void OnEclipse();
	afx_msg void OnUpdateEclipse(CCmdUI* pCmdUI);
	afx_msg void OnText();
	afx_msg void OnUpdateText(CCmdUI* pCmdUI);
	afx_msg void OnFill();
	afx_msg void OnUpdateFill(CCmdUI* pCmdUI);
	afx_msg void OnBlack();
	afx_msg void OnUpdateBlack(CCmdUI* pCmdUI);
	afx_msg void OnRed();
	afx_msg void OnUpdateRed(CCmdUI* pCmdUI);
	afx_msg void OnBlue();
	afx_msg void OnUpdateBlue(CCmdUI* pCmdUI);
	afx_msg void OnGreen();
	afx_msg void OnUpdateGreen(CCmdUI* pCmdUI);
	afx_msg void OnSizeSmall();
	afx_msg void OnUpdateSizeSmall(CCmdUI* pCmdUI);
	afx_msg void OnSizeMedium();
	afx_msg void OnUpdateSizeMedium(CCmdUI* pCmdUI);
	afx_msg void OnSizeLarge();
	afx_msg void OnUpdateSizeLarge(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in PainterView.cpp
inline CPainterDoc* CPainterView::GetDocument() const
   { return reinterpret_cast<CPainterDoc*>(m_pDocument); }
#endif

