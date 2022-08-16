#pragma once
#include "Components.h"
class Components_Line :
	public Components
{
public:
	Components_Line();
	~Components_Line();
	int place(int x1, int x2, int y);
	int processPin(Pin* self) override;
	int draw(CPaintDC* pDC);
	POINT* point;
	int len;//filed
	int size;//allocated
	int setLastPoint(int x, int y);
	POINT getLastPoint();
	int addPoint(int x, int y);
	int deletePoint(POINT* pin);
	int ConnectPinAuto(Pin* pin);
};

