#include "pch.h"
#include "Components_Line.h"


Components_Line::Components_Line()
{
	pins = (Pin*)malloc(sizeof(Pin)*2);
	pins[0] = Pin(this);
	pins[0].isSource = false;// input

	pins[1] = Pin(this);
	pins[1].isSource = true;//output

	size = 5;
	point = (POINT*)malloc(sizeof(POINT)*size);
	len = 0;
}


Components_Line::~Components_Line()
{
	free(pins);
	free(point);
}

int Components_Line::draw(CPaintDC* pDC)
{
	if (len == 1) {
		drawStateLine(pDC, x, x, y, y, 40, false, true, pins[0].PinState, showNumber);
		drawStateLine(pDC, x + w, x + w, y + h, y + h, 40, true, false, pins[0].PinState, showNumber);
	}
	else if (len == 2) {
		drawStateLine(pDC, point[0].x, point[1].x/2+ point[0].x/2, point[0].y, point[1].y/2+ point[0].y/2, 40, false, true, pins[0].PinState, showNumber);
		drawStateLine(pDC, point[1].x/2+ point[0].x/2, point[0].y, point[1].x/2+ point[0].x/2, point[1].y, 40, true, false, pins[0].PinState, showNumber);
	}
	else if(len > 2){
		drawStateLine(pDC, point[0].x, point[1].x, point[0].y, point[1].y, 40, false, true, pins[0].PinState, showNumber);
		pDC->Polyline(point+1, len-1);
		drawStateLine(pDC, point[len-2].x, point[len-1].x, point[len-2].y, point[len-1].y, 40, true, false, pins[0].PinState, showNumber);
	}
	return 0;
}


int Components_Line::place(int x1, int x2,int y)
{
	x = x1;
	this->y = y;
	w = x2 - x1;
	h = 1;
	len = 1;
	addPoint(x, y);
	return 0;
}
int Components_Line::processPin(Pin* selected)
{
	if (selected == &pins[0])
		if (selected->pinFrom != nullptr) {
			pins[0].PinState = selected->pinFrom->PinState;
			pins[1].PinState = pins[0].PinState;

			if (pins[1].pinTo != nullptr) {
				pins[1].pinTo->processPin();
			}
		}

	return 0;
}


int Components_Line::setLastPoint(int x, int y)
{
	if (len == 0)return 1;
	point[len - 1].x = x;
	point[len - 1].y = y;
	return 0;
}


POINT Components_Line::getLastPoint()
{
	return point[len-1];
}


int Components_Line::addPoint(int x, int y)
{
	POINT pointNew = {x, y};
	
	if (size <= len) {
		POINT* allocate = (POINT*)malloc(sizeof(POINT) * size * 2);
		if (allocate == nullptr)return 2;
		memcpy(allocate, point, sizeof(POINT) * size);
		size *= 2;
		free(point);
		point = allocate;
	}
	point[len++] = pointNew;
	return 0;
}


int Components_Line::deletePoint(POINT* pin)
{
	for (int i = 0; i < len; i++) {
		if (point+i == pin) {
			POINT* allocate = (POINT*)malloc(sizeof(POINT) * (len-i-1));
			if(allocate == nullptr)return 2;
			memcpy(allocate, point+i+1, len-i-1);
			memcpy(point+i, allocate, len-i-1);
			free(allocate);
			return 0;
		}
	}
	return 1;
}
