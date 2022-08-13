
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Components_INPUT.h"
#include "Components_OUTPUT.h"
#include "Components_Line.h"
#include "Components_AND.h"
#include "Components_Gate.h"


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
	void drawNOT(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawAND(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawOR(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawXOR(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawNAND(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawNOR(CPaintDC* pDC, int x1, int y1, int x2, int y2);
	void drawXNOR(CPaintDC* pDC, int x1, int y1, int x2, int y2);

	void drawStateLine(CPaintDC* pDC, int x1, int x2, int y1,int y2, int h, bool isInput, bool isLeft, bool state, bool isAbove = true);

	void drawJunction(CPaintDC* pDC, int x1, int y1,int size);
	

	bool isSelected;
	Components_Line *lines[128],*selectedLine ,*line1;
	int lineCount;
	Components_Gate *gates[128],*selectedGate;
	int gateCount;
	Components_Gate * and1, * input1, * input2, * output1;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int AddComponent(Components_Gate* newOne);
	int DeleteComponent(Components_Gate* gate);
	int AddLine(Components_Line* newOne);
	int DeleteLine(Components_Line* line);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
};

