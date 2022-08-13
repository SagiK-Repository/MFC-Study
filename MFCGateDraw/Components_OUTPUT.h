#pragma once
#include "Components.h"
class Components_OUTPUT :
	public Components
{
public:
	Components_OUTPUT();
	~Components_OUTPUT();
	int place(int x, int y);
	int processPin(Pin* self) override;
	int draw(CPaintDC* pDC);

	static void drawOUTPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, bool state, bool isInput);
};

