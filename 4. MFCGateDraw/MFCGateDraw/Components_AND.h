#pragma once
#include "Components.h"
class Components_AND :
	public Components
{
public:
	Components_AND();
	~Components_AND();
	int place(int x, int y);
	int processPin(Pin* self) override;
	int draw(CPaintDC* pDC);

	static void drawAND(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* pins);
};

