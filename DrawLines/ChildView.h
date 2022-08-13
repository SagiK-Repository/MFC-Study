
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	static float a(float x);
	static float b(float x);
	static float c(float x);
	static float d(float x);
	int paintFunction(CPaintDC* dc, CRect rect, POINTF minXY, POINTF maxXY, float (*func)(float x));
	void PaintGrid(CPaintDC* dc, CRect rect, POINTF minXY, POINTF maxXY, POINTF stepXY, POINTF midXY, float (*func)(float x));
	float translateFloat(float max, float min, float v);
	POINT translateXY(CRect rect, float x, float y);

};

