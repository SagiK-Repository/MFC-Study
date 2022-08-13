#include "pch.h"
#include "Components_INPUT.h"


Components_INPUT::Components_INPUT()
{
	w = 100;
	h = 45;
	pins = (Pin*)malloc(sizeof(Pin));
	pins[0] = Pin(this);
	pins[0].isSource = true;
}


Components_INPUT::~Components_INPUT()
{
	free(pins);
}

#define rateOfP1P2(p1,w,rate) ((int)(p1+w*rate))
void Components_INPUT::drawINPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, bool state, bool isInput)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, x2, rateOfP1P2(x1, width, 0.85), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 2, isInput, false, state, true);
	//POINT points1[] = { {rateOfP1P2(x1,width,1.00),rateOfP1P2(y1,height,0.5)},
	//					{rateOfP1P2(x1,width,0.85),rateOfP1P2(y1,height,0.5)} };
	//pDC->Polyline(points1, 2);

	POINT points3[] = { {rateOfP1P2(x1,width,0.85),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.25),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.00),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,0.25),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.85),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.85),rateOfP1P2(y1,height,0.0)} };
	pDC->Polyline(points3, 6);

	CString text;
	COLORREF textColor;
	if (state) {
		text = CString("1");
		textColor = RGB(0, 0, 0);
	}
	else {
		text = CString("0");
		textColor = RGB(255, 0, 0);
	}
	pDC->SetTextColor(textColor);
	CRect rect;
	rect = CRect(rateOfP1P2(x1, width, 0.85), rateOfP1P2(y1, height, 0.0),
		rateOfP1P2(x1, width, 0.25), rateOfP1P2(y1, height, 1.0));
	pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(oldpen);
}

int Components_INPUT::draw(CPaintDC* pDC)
{
	drawINPUT(pDC, x-w/2, y-h/2, x+w/2, y+h/2, pins[0].PinState,true);
	return 0;
}


int Components_INPUT::place(int x, int y)
{
	this->x = x;
	this->y = y;
	return 0;
}


int Components_INPUT::toggleState()
{
	pins[0].PinState = !pins[0].PinState;
	return 0;
}


int Components_INPUT::isClick(int mouseX, int mouseY)
{
	if(x-w/2 <= mouseX && mouseX <= x+w/2 && y-h/2 <= mouseY && mouseY <= y+h/2){
		toggleState();
		processPin(&pins[0]);
		return 1;
	}else return 0;
}


int Components_INPUT::processPin(Pin* self)
{
	if (self == &self[0] && self->pinTo != nullptr) {
		self->pinTo->processPin();
	}
	return 0;
}
