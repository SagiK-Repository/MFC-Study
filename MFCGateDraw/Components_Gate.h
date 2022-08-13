#pragma once
#include "Components.h"
enum GateType {
	AND = 0,
	OR,
	XOR,
	NOT,
	NAND,
	NOR,
	XNOR,
	JUNCTION,
	Gate_INPUT,
	Gate_OUTPUT,
	TEXT,
	NONE
};

class Components_Gate :
	public Components
{
public:
	Components_Gate();
	Components_Gate(GateType type);
	~Components_Gate();
	void setGateType(GateType type);
	int place(int x, int y);
	int processPin(Pin* self) override;
	int draw(CPaintDC* pDC);
	int isClick(int mouseX, int mouseY);

	CString text;
	GateType gate_type;
	void (*drawGate)(CPaintDC*, int, int, int, int,Pin*,bool);

	static void drawNOT(CPaintDC* pDC, int x1, int y1, int x2, int y2,Pin* ports,bool drawpin);
	static void drawAND(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawOR(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawXOR(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawNAND(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawNOR(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawXNOR(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawJunction(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawINPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawOUTPUT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	static void drawTEXT(CPaintDC* pDC, int x1, int y1, int x2, int y2, Pin* ports, bool drawpin);
	CRect getRect(int offset = 0);
	bool isBound();
};

