
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
	CBitmap m_bitmap;
	BITMAP m_bmpinfo;
	int m_xpos;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	short* tile;
	SIZE boardSize;
	SIZE bitmapSize;
	int cursor;
//	int boardHeight;
	int flipTiles(POINT tile1, POINT tile2);
	int flipTiles(int tile1, int tile2);
	int blitTile(CPaintDC* pDC, CDC* pmemDC, POINT position, int tileNum);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

