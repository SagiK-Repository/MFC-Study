#pragma once
#include "Pin.h"
class Components
{
public:
	Components();
	~Components();
	int x;
	int y;
	int w;
	int h;
	bool showNumber;
	Pin* pins;
	virtual int processPin(Pin* self);

	static void drawStateLine(CPaintDC* pDC, int x1, int x2, int y1, int y2, int h, bool isInput, bool isLeft, bool state, bool isShow = true, bool isAbove=1);
};

