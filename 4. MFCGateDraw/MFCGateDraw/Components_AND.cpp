#include "pch.h"
#include "Components_AND.h"


Components_AND::Components_AND()
{
	w = 200;
	h = 140;
	pins = (Pin*)malloc(sizeof(Pin)*3);
	pins[0] = Pin(this);
	pins[0].isSource = false;

	pins[1] = Pin(this);
	pins[1].isSource = false;

	pins[2] = Pin(this);
	pins[2].isSource = true;
}


Components_AND::~Components_AND()
{
	free(pins);
}

int Components_AND::draw(CPaintDC* pDC)
{
	drawAND(pDC, x - w / 2, y - h / 2, x + w / 2, y + h / 2,pins);
	return 0;
}


int Components_AND::place(int x, int y)
{
	this->x = x;
	this->y = y;
	return 0;
}
int Components_AND::processPin(Pin* selected)
{
	if (selected == &pins[0] || selected == &pins[1])
		if (selected->pinFrom != nullptr) {
			selected->PinState = selected->pinFrom->PinState;

			pins[2].PinState = pins[0].PinState && pins[1].PinState;
			if (pins[2].pinTo != nullptr) {
				pins[2].pinTo->processPin();
			}
		}

	return 0;
}

#define rateOfP1P2(p1,w,rate) ((int)(p1+w*rate))
void Components_AND::drawAND(CPaintDC* pDC, int x1, int y1, int x2, int y2,Pin* pins)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.3), rateOfP1P2(y1, height, 0.3), height / 4, pins[0].isSource, true, pins[0].PinState);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.7), rateOfP1P2(y1, height, 0.7), height / 4, pins[1].isSource, true, pins[1].PinState);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.65), rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, pins[2].isSource, true, pins[2].PinState);

	POINT points5[] = { {rateOfP1P2(x1,width,0.35),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.35),rateOfP1P2(y1,height,1.0)} };
	pDC->Polyline(points5, 4);

	//0.625 0.5
	pDC->Arc(rateOfP1P2(x1, width, 0.05)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.65)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.35)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.35)
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}