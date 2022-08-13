
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "DrawLines.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//클라이언트 영역의 좌표를 얻는다.
	CRect rect;
	GetClientRect(&rect);

	PaintGrid(&dc, CRect(rect.right * 0.05, rect.bottom * 0.05, rect.right * 0.45, rect.bottom * 0.45), { -180.f,-2.f }, { 180.f,2.f }, { 30.f,0.25f }, { 0.f,0.f }, this->a);
	PaintGrid(&dc, CRect(rect.right * 0.55, rect.bottom * 0.05, rect.right * 0.95, rect.bottom * 0.45), { -180.f,-2.f }, { 180.f,2.f }, { 30.f,0.25f }, { 0.f,0.f }, this->b);
	PaintGrid(&dc, CRect(rect.right * 0.05, rect.bottom * 0.55, rect.right * 0.45, rect.bottom * 0.95), { -180.f,-10.f }, { 180.f,10.f }, { 30.f,1.f }, { 0.f,0.f }, this->c);
	PaintGrid(&dc, CRect(rect.right * 0.55, rect.bottom * 0.55, rect.right * 0.95, rect.bottom * 0.95), { -4.f,-2.f }, { 4.f,2.f }, { 0.5f,0.2f }, { 0.f,0.f }, this->d);

	// Do not call CWnd::OnPaint() for painting messages
}

float CChildView::a(float x) {
	return sinf(x * (3.14159265f / 180.f));
}

float CChildView::b(float x) {
	return cosf(x * (3.14159265f / 180.f));
}
float CChildView::c(float x) {
	return tanf(x * (3.14159265f / 180.f));
}
float CChildView::d(float x) {
	return 1.f* sinf(1.f * x) + 1/3.f * sinf(3.f * x) + 1/5.f* sinf(5.f * x) + 1/7.f * sinf(7.f * x) + 1 / 9.f * sinf(9.f * x) + 1 / 11.f * sinf(11.f * x) + 1 / 13.f * sinf(13.f * x);
}

POINT CChildView::translateXY(CRect rect, float x, float y) {
	POINT point;

	point.x = rect.left + int(rect.Width() * x);
	point.y = rect.top + int(rect.Height() * y);
	return point;
}
float CChildView::translateFloat(float max, float min, float v) {
	return (v - min) / (max - min);
}

void CChildView::PaintGrid(CPaintDC * dc, CRect rect, POINTF minXY, POINTF maxXY, POINTF stepXY, POINTF midXY, float (*func)(float)) {

	//박스 그리기
	CPen OutlinePen, ZeroPen, GridPen, LinePen;
	OutlinePen.CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
	ZeroPen.CreatePen(PS_SOLID, 4, RGB(127, 127, 127));
	GridPen.CreatePen(PS_SOLID, 2, RGB(64, 64, 64));
	LinePen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	CPen* pOldPen = dc->SelectObject(&OutlinePen);

	POINT points[] = { translateXY(rect,0,0),translateXY(rect,1,0) ,translateXY(rect,1,1) ,translateXY(rect,0,1), translateXY(rect,0,0) };
	dc->Polyline(points, 5);

	dc->SelectObject(&GridPen);
	int grid_per_stepX = int((maxXY.x - minXY.x) / (stepXY.x * 2));
	int vertical_lines = 2 * grid_per_stepX + 1;
	for (int i = 0; i < vertical_lines; i++) {
		float grid_x = midXY.x + (i - grid_per_stepX) * stepXY.x;

		if (grid_x == maxXY.x || grid_x == minXY.x)
			continue;

		if (grid_x == 0.f)
			dc->SelectObject(&ZeroPen);

		float trans_grid_x = translateFloat(maxXY.x, minXY.x, grid_x);
		dc->MoveTo(translateXY(rect, trans_grid_x, 1));
		dc->LineTo(translateXY(rect, trans_grid_x, 0));

		POINT textXY = translateXY(rect, trans_grid_x, 1);
		CString text = TEXT("");
		text.Format(TEXT("%g"), grid_x);
		dc->TextOutW(textXY.x, textXY.y, text);

		if (grid_x == 0.f)
			dc->SelectObject(&GridPen);
	}

	int grid_per_stepY = int((maxXY.y - minXY.y) / (stepXY.y * 2));
	vertical_lines = 2 * grid_per_stepY + 1;
	for (int i = 0; i < vertical_lines; i++) {
		float grid_y = midXY.y + (i - grid_per_stepY) * stepXY.y;

		if (grid_y == maxXY.y || grid_y == minXY.y)
			continue;
		if (grid_y == 0.f)
			dc->SelectObject(&ZeroPen);

		float trans_grid_y = translateFloat(minXY.y, maxXY.y, grid_y);
		dc->MoveTo(translateXY(rect, 0, trans_grid_y));
		dc->LineTo(translateXY(rect, 1, trans_grid_y));

		POINT textXY = translateXY(rect, 1, trans_grid_y);
		CString text = TEXT("");
		text.Format(TEXT("%g"), grid_y);
		dc->TextOutW(textXY.x, textXY.y, text);

		if (grid_y == 0.f)
			dc->SelectObject(&GridPen);
	}

	dc->SelectObject(&LinePen);
	int count = paintFunction(dc, rect, minXY, maxXY, func);

	POINT textXY = translateXY(rect, 1, 1);
	CString text = TEXT("");
	text.Format(TEXT("%d"), count);
	dc->TextOutW(textXY.x, textXY.y, text);

	dc->SelectObject(pOldPen);
	OutlinePen.DeleteObject();
}

int CChildView::paintFunction(CPaintDC * dc, CRect rect, POINTF minXY, POINTF maxXY, float (*func)(float)) {
	float x = minXY.x;
	float width = maxXY.x - minXY.x;
	float height = maxXY.y - minXY.y;
	int res = 400;

	float nextX = width / res;
	float deltaX = 0.001f;


	float prevY = NAN;
	int count = 0;
	BOOL isOut = TRUE;
	while (x < maxXY.x) {
		count++;
		float y = func(x);

		float printx = translateFloat(maxXY.x, minXY.x, x);
		float printy = translateFloat(minXY.y, maxXY.y, y);

		if (isOut == FALSE && (y > maxXY.y || y < minXY.y || y != y)) { // y == y : false if y==Nan
			isOut = TRUE; 
			if (y != y)
				dc->LineTo(translateXY(rect, printx, translateFloat(minXY.y, maxXY.y, prevY)));
			else if (y > maxXY.y)
				dc->LineTo(translateXY(rect, printx, 0));
			else if(y < minXY.y)
				dc->LineTo(translateXY(rect, printx, 1));

		}
		else if (isOut == TRUE && (minXY.y < y && y < maxXY.y)) {
			isOut = FALSE;
			if (prevY != prevY)
				dc->MoveTo(translateXY(rect, printx, printy));
			else if (prevY > maxXY.y)
				dc->MoveTo(translateXY(rect, printx, 0));
			else if(prevY < minXY.y)
				dc->MoveTo(translateXY(rect, printx, 1));
		}


		if (isOut == FALSE) {
			dc->LineTo(translateXY(rect, printx, printy));


			float deltaF = (func(x + deltaX) - func(x)) / deltaX * (width / height);
			float deltaS_X = sqrtf(deltaF * deltaF + 1);

			if (deltaS_X != deltaS_X)// deltaS_X == Nan
				deltaS_X = 1;
			x += nextX / deltaS_X;
		}
		else if(y == y){// y ! Nan

			float deltaF = (func(x + deltaX) - func(x)) / deltaX * (width/ height);
			float deltaS_X = sqrtf(deltaF * deltaF + 1);

			float factor = 1.f;
			factor = factor * 0.001f + 1 / deltaS_X;

			x += nextX * factor;
		}
		else {
			x += nextX*0.1f;
		}
		prevY = y;

		float deltaF = (func(x + deltaX) - func(x)) / deltaX * (width / height);
		float deltaS_X = sqrtf(deltaF * deltaF + 1);

		float factor = 1.f;
		factor = factor * 0.001f + 1 / deltaS_X;

		float xx = factor;
		//x의 증분 : (dx/dS에 비례)
	}
	return count;
}
