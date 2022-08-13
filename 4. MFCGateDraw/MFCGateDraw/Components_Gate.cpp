#include "pch.h"
#include "Components_Gate.h"

Components_Gate::Components_Gate() {
	setGateType(NONE);
}
Components_Gate::Components_Gate(GateType type) {
	setGateType(type);
}

void Components_Gate::setGateType(GateType type)
{
	gate_type = type;

	switch (type) {
	case AND:w = 150; h = 80; break;   //IN 0,1 OUT 3
	case OR :w = 150; h = 80; break;   //IN 0   OUT 3
	case XOR:w = 150; h = 80; break;   //IN 0,1 OUT 3
	case NOT:w = 150; h = 80; break;   //IN 0,1 OUT 3
	case NAND:w = 150; h = 80; break;  //IN 0,1 OUT 3
	case NOR :w = 150; h = 80; break;  //IN 0,1 OUT 3
	case XNOR:w = 150; h = 80; break;  //IN 0,1 OUT 3
	case JUNCTION:w = 15; h = 15; break;//IN 0   OUT 3,4,5
	case Gate_INPUT:w = 60; h = 30; break;  //IN     OUT 3
	case Gate_OUTPUT:w = 60; h = 30; break; //IN 0   OUT 
	case TEXT:w = 100; h = 40; break;
	default:gate_type = NONE; w = 0, h = 0; break;
	}
	switch (type) {
	case AND:	  drawGate = drawAND; break;
	case OR :	  drawGate = drawOR; break;
	case XOR:	  drawGate = drawXOR; break;
	case NOT:	  drawGate = drawNOT; break;
	case NAND:	  drawGate = drawNAND; break;
	case NOR:	  drawGate = drawNOR; break;
	case XNOR:	  drawGate = drawXNOR; break;
	case JUNCTION:drawGate = drawJunction; break;
	case Gate_INPUT:drawGate = drawINPUT; break;  //IN     OUT 3
	case Gate_OUTPUT:drawGate = drawOUTPUT; break; //IN 0   OUT 
	case TEXT:	  drawGate = drawTEXT; break;
	default:drawGate = nullptr; break;
	}

	if (gate_type != NONE) {

		pins = (Pin*)malloc(sizeof(Pin) * 6);

		pins[0] = Pin(this);
		pins[0].isSource = false;

		pins[1] = Pin(this);
		pins[1].isSource = false;

		pins[2] = Pin(this);
		pins[2].isSource = false;

		pins[3] = Pin(this);
		pins[3].isSource = true;

		pins[4] = Pin(this);
		pins[4].isSource = true;

		pins[5] = Pin(this);
		pins[5].isSource = true;
	}
}


Components_Gate::~Components_Gate()
{
	for (int i = 0; i < 6; i++){
		if (pins[i].pinFrom != nullptr)
			pins[i].pinFrom->pinTo = nullptr;
		if (pins[i].pinTo != nullptr)
			pins[i].pinTo->pinFrom = nullptr;
	}
	free(pins);
}

#define rateOfP1P2(p1,w,rate) ((int)(p1+w*rate))
void Components_Gate::drawNOT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[0].isSource, true, ports[0].PinState,drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.65) + height / 4, rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[3].isSource, true, ports[3].PinState, drawpin);

	POINT points3[] = { {rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.65),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)} };
	pDC->Polyline(points3, 4);

	//0.625 0.5
	pDC->Ellipse(rateOfP1P2(x1, width, 0.65)
		, rateOfP1P2(y1, height, 0.5) - height / 8
		, rateOfP1P2(x1, width, 0.65) + height / 4
		, rateOfP1P2(y1, height, 0.5) + height / 8);


	pDC->SelectObject(oldpen);
}
void Components_Gate::drawAND(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.3), rateOfP1P2(y1, height, 0.3), height / 4, ports[0].isSource, true, ports[0].PinState,drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.7), rateOfP1P2(y1, height, 0.7), height / 4, ports[1].isSource, true, ports[1].PinState,drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.75), rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[3].isSource, true, ports[3].PinState,drawpin);

	POINT points5[] = { {rateOfP1P2(x1,width,0.35),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.35),rateOfP1P2(y1,height,1.0)} };
	pDC->Polyline(points5, 4);

	//0.625 0.5
	pDC->Arc(rateOfP1P2(x1, width, -0.05)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.75)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.35)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.35)
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}
void Components_Gate::drawOR(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.24), rateOfP1P2(y1, height, 0.3), rateOfP1P2(y1, height, 0.3), height / 4, ports[0].isSource, true, ports[0].PinState,drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.24), rateOfP1P2(y1, height, 0.7), rateOfP1P2(y1, height, 0.7), height / 4, ports[1].isSource, true, ports[1].PinState,drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.75), rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[3].isSource, true, ports[3].PinState,drawpin);

	pDC->Arc(rateOfP1P2(x1, width, 0.05)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.25)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 0.0));

	pDC->Arc(rateOfP1P2(x1, width, -0.45)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.75)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}
void Components_Gate::drawXOR(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

	drawOR(pDC, x1, y1, x2, y2, ports,drawpin);

	CPen* oldpen = pDC->SelectObject(&pen);

	pDC->Arc(rateOfP1P2(x1, width, 0.05) - height / 8
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.25) - height / 8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height / 8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height / 8
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}
void Components_Gate::drawNAND(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.3), rateOfP1P2(y1, height, 0.3), height / 4, ports[0].isSource, true, ports[0].PinState, drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.7), rateOfP1P2(y1, height, 0.7), height / 4, ports[1].isSource, true, ports[1].PinState, drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.65) + height / 4, rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[3].isSource, true, ports[3].PinState, drawpin);

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

	//0.625 0.5
	pDC->Ellipse(rateOfP1P2(x1, width, 0.65)
		, rateOfP1P2(y1, height, 0.5) - height / 8
		, rateOfP1P2(x1, width, 0.65) + height / 4
		, rateOfP1P2(y1, height, 0.5) + height / 8);

	pDC->SelectObject(oldpen);
}
void Components_Gate::drawNOR(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.24), rateOfP1P2(y1, height, 0.3), rateOfP1P2(y1, height, 0.3), height / 4, ports[0].isSource, true, ports[0].PinState, drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.0), rateOfP1P2(x1, width, 0.24), rateOfP1P2(y1, height, 0.7), rateOfP1P2(y1, height, 0.7), height / 4, ports[1].isSource, true, ports[1].PinState, drawpin);
	drawStateLine(pDC, rateOfP1P2(x1, width, 0.65) + height / 4, rateOfP1P2(x1, width, 1.0), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 4, ports[3].isSource, true, ports[3].PinState, drawpin);

	pDC->Arc(rateOfP1P2(x1, width, 0.05)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.25)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 0.0));

	pDC->Arc(rateOfP1P2(x1, width, -0.35)
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.65)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15)
		, rateOfP1P2(y1, height, 0.0));

	//0.625 0.5
	pDC->Ellipse(rateOfP1P2(x1, width, 0.65)
		, rateOfP1P2(y1, height, 0.5) - height / 8
		, rateOfP1P2(x1, width, 0.65) + height / 4
		, rateOfP1P2(y1, height, 0.5) + height / 8);

	pDC->SelectObject(oldpen);
}
void Components_Gate::drawXNOR(CPaintDC * pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

	drawNOR(pDC, x1, y1, x2, y2,ports,drawpin);

	CPen* oldpen = pDC->SelectObject(&pen);

	pDC->Arc(rateOfP1P2(x1, width, 0.05) - height / 8
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.25) - height / 8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height / 8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height / 8
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}
void Components_Gate::drawJunction(CPaintDC * pDC,int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);
	pDC->Ellipse(x1,y1,x2,y2);
	pDC->SelectObject(oldpen);
}
void Components_Gate::drawINPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	bool state = ports[3].PinState, isInput = ports[3].isSource;
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, x2, rateOfP1P2(x1, width, 0.85), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 2, isInput, false, state, true, drawpin);
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
		textColor = RGB(255, 0, 0);
	}
	else {
		text = CString("0");
		textColor = RGB(0, 0, 0);
	}
	pDC->SetTextColor(textColor);
	CRect rect;
	rect = CRect(rateOfP1P2(x1, width, 0.85), rateOfP1P2(y1, height, 0.0),
		rateOfP1P2(x1, width, 0.25), rateOfP1P2(y1, height, 1.0));
	pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(oldpen);
}
void Components_Gate::drawOUTPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	bool state = ports[0].PinState, isInput = ports[0].isSource;
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	drawStateLine(pDC, x1, rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.5), rateOfP1P2(y1, height, 0.5), height / 2, isInput, false, state, true, drawpin);
	//POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.5)},
	//					{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.5)} };
	//pDC->Polyline(points1, 2);

	POINT points3[] = { {rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,0.75),rateOfP1P2(y1,height,0.0)},
						{rateOfP1P2(x1,width,1.00),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,0.75),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,1.0)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.0)} };
	pDC->Polyline(points3, 6);

	CString text;
	COLORREF textColor;
	if (state) {
		text = CString("1");
		textColor = RGB(255, 0, 0);
	}
	else {
		text = CString("0");
		textColor = RGB(0, 0, 0);
	}
	pDC->SetTextColor(textColor);
	CRect rect;
	rect = CRect(rateOfP1P2(x1, width, 0.15), rateOfP1P2(y1, height, 0.0),
		rateOfP1P2(x1, width, 0.75), rateOfP1P2(y1, height, 1.0));
	pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(oldpen);
}
void Components_Gate::drawTEXT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin)
{
	Components_Gate* parent = (Components_Gate*)ports[0].parent;
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);
	CFont font; font.CreatePointFont(height * 5, _T("System"));
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,0));

	POINT points3[] = { {x1,y1},
						{x2,y1},
						{x2,y2},
						{x1,y2},
						{x1,y1}, };
	if(drawpin)
		pDC->Polyline(points3, 5);

	CRect rect = parent->getRect();
	pDC->DrawText(parent->text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldFont);
}


int Components_Gate::draw(CPaintDC* pDC)
{
	if (drawGate != nullptr)
		drawGate(pDC, x - w / 2, y - h / 2, x + w / 2, y + h / 2, pins,showNumber);
	return 0;
}


int Components_Gate::place(int x, int y)
{
	this->x = x;
	this->y = y;
	return 0;
}
int Components_Gate::processPin(Pin* selected)
{
	if (selected >= &pins[0] && selected <= &pins[2])
		if (selected->pinFrom != nullptr) {
			selected->PinState = selected->pinFrom->PinState;

			switch (gate_type) {
			case AND:	  pins[3].PinState = pins[0].PinState & pins[1].PinState; break;
			case OR:	  pins[3].PinState = pins[0].PinState | pins[1].PinState; break;
			case XOR:	  pins[3].PinState = pins[0].PinState ^  pins[1].PinState; break;
			case NOT:	  pins[3].PinState = !pins[0].PinState; break;
			case NAND:	  pins[3].PinState = !(pins[0].PinState & pins[1].PinState); break;
			case NOR:	  pins[3].PinState = !(pins[0].PinState | pins[1].PinState); break;
			case XNOR:	  pins[3].PinState = !(pins[0].PinState ^ pins[1].PinState); break;
			case JUNCTION:pins[3].PinState = pins[0].PinState;pins[4].PinState = pins[0].PinState;pins[5].PinState = pins[0].PinState; break;

			default:return 0;
			}
			
			if (pins[3].pinTo != nullptr)pins[3].pinTo->processPin();
			if (pins[4].pinTo != nullptr)pins[4].pinTo->processPin();
			if (pins[5].pinTo != nullptr)pins[5].pinTo->processPin();
		}
	if (selected >= &pins[3] && selected <= &pins[5]) // OUTPUT pin
		if (selected->pinTo != nullptr) {
			selected->pinTo->processPin();
		}

	return 0;
}

int Components_Gate::isClick(int mouseX, int mouseY)
{
	CRect rect = getRect();
	if (rect.left <= mouseX && mouseX <= rect.right && rect.top <= mouseY && mouseY <= rect.bottom) {
		if (gate_type == Gate_INPUT) {
			pins[3].PinState = !pins[3].PinState;
			processPin(&pins[3]);
		}
		return 1;
	}
	else return 0;
}



CRect Components_Gate::getRect(int offset)
{
	return CRect(x - w / 2 - offset, y - w / 2 - offset, x + w / 2 + offset, y + w / 2 + offset);
}


bool Components_Gate::isBound()
{
	bool res = false;
	for (int i = 0; i < 6; i++)
		res |= pins[i].isBound();
	return res;
}
