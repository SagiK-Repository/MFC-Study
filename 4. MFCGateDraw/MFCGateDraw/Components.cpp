#include "pch.h"
#include "Pin.h"
#include "Components.h"


Components::Components()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	showNumber = true;
	pins = nullptr;
}


Components::~Components()
{
}


int Components::processPin(Pin* self)
{
	
	return 0;
}

void Components::drawStateLine(CPaintDC* pDC, int x1, int x2, int y1, int y2, int h, bool isInput, bool isLeft, bool state, bool isShow, bool isAbove) {

	COLORREF PenColor;
	if (!isInput)
		PenColor = RGB(0, 0, 0);
	else
		PenColor = RGB(127, 127, 127);
	CPen pen(PS_SOLID, 1, PenColor);
	CPen* oldpen = pDC->SelectObject(&pen);
	CFont font; font.CreatePointFont(h * 5, _T("System"));
	CFont* oldFont = pDC->SelectObject(&font);

	POINT points1[] = { {x1,y1},{x2,y2} };
	pDC->Polyline(points1, 2);

	if (isShow) {
		CString text;
		COLORREF textColor;
		int refY;
		int topY, botY, flag;
		flag = 0;

		if (isLeft) refY = y1; else refY = y2;

		if (isAbove) {
			topY = refY - h;
			botY = refY - 1;
			flag |= DT_BOTTOM;
		}
		else {
			topY = refY + 1;
			botY = refY + h;
			flag |= DT_TOP;
		}

		if (isLeft) { flag |= DT_LEFT; x1 += 1;}
		else { flag |= DT_RIGHT; x2 -= 1; }

		if (state) {
			text = CString("1");
			textColor = RGB(255, 0, 0);
		}
		else {
			text = CString("0");
			textColor = RGB(0, 0, 0);
		}
		pDC->SetTextColor(textColor);

		if (abs(x1 - x2) < 15) x2 = x1 + 15;
		if (topY < min(y1, y2)) { int dif = min(y1, y2) - topY; topY += dif; botY += dif; } // Text Out of Area calibration.

		CRect rect;
		rect = CRect(min(x1,x2), topY,
			max(x2,x1), botY);
		pDC->DrawText(text, &rect, flag | DT_SINGLELINE);
	}

	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldFont);
}
void Components::drawStateLine(CPaintDC* pDC, int x1, int x2, int y1, int y2, int h,Pin* pio,bool isLeft, bool isShow, bool isAbove) {
	drawStateLine(pDC, x1, x2, y1, y2, h, pio->isSource, isLeft, pio->PinState, isShow, isAbove);

	int refX, refY;
	if (isLeft) refX = min(x1,x2); else refX = max(x1,x2);
	if (isLeft) refY = (x1<x2?y1:y2); else refY = (x1<x2?y2:y1);

	pio->pinX = refX;
	pio->pinY = refY;
}