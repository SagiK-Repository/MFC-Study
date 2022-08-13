#pragma once
#include "Components.h"
class Components_INPUT :
	public Components
{
public:
	Components_INPUT();
	~Components_INPUT();
	int place(int x, int y);
	int processPin(Pin* self) override;
	int draw(CPaintDC* pDC);
	int toggleState();
	int isClick(int mouseX, int mouseY);

	static void drawINPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, bool state, bool isInput);
};

