
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MFCGateDraw.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

#define rateOfP1P2(p1,w,rate) ((int)(p1+w*rate))

CChildView::CChildView()
{
	for (int i = 0; i < sizeof(lines) / sizeof(*lines); i++)
		lines[i] = nullptr;
	for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
		gates[i] = nullptr;
	isSelected = false;
	gateCount = 0;
	lineCount = 0;

	int res = 0;
	res = AddComponent(new Components_Gate(NOT)); gates[res]->place(110, 0 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(AND)); gates[res]->place(110, 100 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(OR)); gates[res]->place(110, 200 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(XOR)); gates[res]->place(110, 300 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(NAND)); gates[res]->place(110, 400 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(NOR)); gates[res]->place(110, 500 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(XNOR)); gates[res]->place(110, 600 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(JUNCTION)); gates[res]->place(110, 700 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(TEXT)); gates[res]->place(110, 800 + 70); gates[res]->w = 150; gates[res]->w = 80; gates[res]->text = _T("Line");

	res = AddComponent(and1 = new Components_Gate(NOR));
	res = AddComponent(input1 = new Components_Gate(Gate_INPUT));
	res = AddComponent(input2 = new Components_Gate(Gate_INPUT));
	res = AddComponent(output1 = new Components_Gate(Gate_OUTPUT));

	res = AddLine(line1 = new Components_Line());

	input1->place(850-and1->w/2-input1->w/2, rateOfP1P2(200-and1->h/2,and1->h,0.3));
	input2->place(850-and1->w/2-input2->w/2, rateOfP1P2(200-and1->h/2,and1->h,0.7));

	and1->place(850, 200);

	res = Pin::connectPin(&input1->pins[3], &and1->pins[0]);
	res = Pin::connectPin(&input2->pins[3], &and1->pins[1]);

	res = Pin::connectPin(&line1->pins[0], &and1->pins[3]);
	line1->place(850 + and1->w / 2, 1050, 200);
	line1->showNumber = false;
	res = Pin::connectPin(&line1->pins[1], &output1->pins[0]);

	output1->place(1050 + output1->w / 2, 200);
	
	input1->pins[3].processPin();
	input2->pins[3].processPin();

}

CChildView::~CChildView()
{
	for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
		delete gates[i];
	for (int i = 0; i < sizeof(lines) / sizeof(*lines); i++)
		delete lines[i];
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.Rectangle(0, 0, 220, 1000);


	drawStateLine(&dc, 500, 600, 25,50, 24,false, true, 1);
	drawStateLine(&dc, 500, 600, 50,75, 24,true, true, 0,false);
	drawStateLine(&dc, 500, 600, 75,100, 24,true, false, 1);
	drawStateLine(&dc, 500, 600, 100,25, 24,false, false, 0,false);

	drawJunction(&dc, 200, 100, 10);


	for (int i = 0; i < sizeof(lines) / sizeof(*lines); i++) {
		if (lines[i] != nullptr)lines[i]->draw(&dc);
	}

	for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++) {
		if (gates[i] != nullptr)gates[i]->draw(&dc);
	}
	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::drawNOT(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.5)} };
	POINT points2[] = { { rateOfP1P2(x1, width, 0.65) + height / 4,rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,1.0),rateOfP1P2(y1,height,0.5)} };
	pDC->Polyline(points1, 2);
	pDC->Polyline(points2, 2);

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
void CChildView::drawAND(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.3)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.3)} };
	POINT points2[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.7)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.7)} };
	POINT points3[] = { {rateOfP1P2(x1,width,0.65),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,1.0),rateOfP1P2(y1,height,0.5)} };
	pDC->Polyline(points1, 2);
	pDC->Polyline(points2, 2);
	pDC->Polyline(points3, 2);

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
void CChildView::drawOR(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.3)},
						{rateOfP1P2(x1,width,0.24),rateOfP1P2(y1,height,0.3)} };
	POINT points2[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.7)},
						{rateOfP1P2(x1,width,0.24),rateOfP1P2(y1,height,0.7)} };
	POINT points3[] = { {rateOfP1P2(x1,width,0.65),rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,1.0),rateOfP1P2(y1,height,0.5)} };
	pDC->Polyline(points1, 2);
	pDC->Polyline(points2, 2);
	pDC->Polyline(points3, 2);

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


	pDC->SelectObject(oldpen);
}
void CChildView::drawXOR(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

	drawOR(pDC, x1, y1, x2, y2);

	CPen* oldpen = pDC->SelectObject(&pen);

	pDC->Arc(rateOfP1P2(x1, width, 0.05) - height/8
		, rateOfP1P2(y1, height, 0.0)
		, rateOfP1P2(x1, width, 0.25) - height/8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height/8
		, rateOfP1P2(y1, height, 1.0)
		, rateOfP1P2(x1, width, 0.15) - height/8
		, rateOfP1P2(y1, height, 0.0));


	pDC->SelectObject(oldpen);
}
void CChildView::drawNAND(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.3)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.3)} };
	POINT points2[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.7)},
						{rateOfP1P2(x1,width,0.15),rateOfP1P2(y1,height,0.7)} };
	POINT points3[] = { {rateOfP1P2(x1,width,0.65)+height/4,rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,1.0),rateOfP1P2(y1,height,0.5)} };
	pDC->Polyline(points1, 2);
	pDC->Polyline(points2, 2);
	pDC->Polyline(points3, 2);

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
void CChildView::drawNOR(CPaintDC* pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	POINT points1[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.3)},
						{rateOfP1P2(x1,width,0.24),rateOfP1P2(y1,height,0.3)} };
	POINT points2[] = { {rateOfP1P2(x1,width,0.0),rateOfP1P2(y1,height,0.7)},
						{rateOfP1P2(x1,width,0.24),rateOfP1P2(y1,height,0.7)} };
	POINT points3[] = { {rateOfP1P2(x1,width,0.65)+height/4,rateOfP1P2(y1,height,0.5)},
						{rateOfP1P2(x1,width,1.0),rateOfP1P2(y1,height,0.5)} };
	pDC->Polyline(points1, 2);
	pDC->Polyline(points2, 2);
	pDC->Polyline(points3, 2);

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
void CChildView::drawXNOR(CPaintDC * pDC, int x1, int y1, int x2, int y2)
{
	int width = x2 - x1, height = y2 - y1;
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

	drawNOR(pDC, x1, y1, x2, y2);

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
void CChildView::drawStateLine(CPaintDC* pDC, int x1, int x2, int y1,int y2,int h,bool isInput , bool isLeft, bool state, bool isAbove) {
	Components::drawStateLine(pDC, x1, x2, y1,y2, h, isInput, isLeft, state, isAbove);
}
void CChildView::drawJunction(CPaintDC* pDC, int x1, int y1, int size)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);

	pDC->Ellipse(x1 - size
		, y1 - size
		, x1 + size
		, y1 + size);

	pDC->SelectObject(oldpen);
}


int CChildView::AddComponent(Components_Gate* newOne)
{
	if (gateCount > (sizeof(gates) / sizeof(*gates)))return -1;

	for (int i = 0; i < gateCount+1; i++) {
		if (gates[i] == nullptr) {
			gates[i] = newOne;
			gateCount++;
			return i;
		}
	}
	return -2;
}
int CChildView::DeleteComponent(Components_Gate* gate)
{
	for (int i = 0; i < gateCount; i++) {
		if (gates[i] == gate) {
			delete gates[i];
			gates[i] = nullptr;
			return 0;
		}
	}
	return 1;
}
int CChildView::AddLine(Components_Line* newOne)
{
	if (lineCount > sizeof(lines) / sizeof(*lines))return -1;

	for (int i = 0; i < lineCount+1; i++) {
		if (lines[i] == nullptr) {
			lines[i] = newOne;
			lineCount++;
			return i;
		}
	}
	return -2;
}
int CChildView::DeleteLine(Components_Line* line)
{
	for (int i = 0; i < lineCount; i++) {
		if (lines[i] == line) {
			delete lines[i];
			lines[i] = nullptr;
			return 0;
		}
	}
	return 1;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!isSelected) {
		if (point.x < 200) {
			selectedGate = nullptr;
			selectedLine = nullptr;
			for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
				if (gates[i] != nullptr)
					if (gates[i]->isClick(point.x, point.y)) {
						if (gates[i]->gate_type != TEXT) {
							i = AddComponent(new Components_Gate(gates[i]->gate_type));
							if (i < 0)break;
							selectedGate = gates[i];
							selectedGate->place(point.x, point.y);
						}
						else {
							i = AddLine(new Components_Line());
							if (i < 0)break;
							selectedLine = lines[i];
						}
						Invalidate();
						break;
					}
			if (selectedGate != nullptr || selectedLine != nullptr) {
				isSelected = true;
			}
		}


		bool res = false;
		for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
			if (gates[i] != nullptr) res |= gates[i]->isClick(point.x, point.y);
		if (res) Invalidate();
	}
	else {
		if (point.x > 200)
			if (selectedGate != nullptr) {
				selectedGate = nullptr;
				isSelected = false;
				Invalidate();
			}
			else if (selectedLine != nullptr) {
				if(selectedLine->len == 0)
					selectedLine->addPoint(point.x, point.y);

				selectedLine->addPoint(point.x, point.y);
			}
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (isSelected) {
		if (selectedGate != nullptr) {
			InvalidateRect(selectedGate->getRect(max(abs(selectedGate->x - point.x), abs(selectedGate->y - point.y)) + 1));

			selectedGate->place(point.x, point.y);
		}
		else if (selectedLine != nullptr) {
			Invalidate();
			selectedLine->setLastPoint(point.x, point.y);
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!isSelected) {
		if (point.x > 200) {
			selectedGate = nullptr;
			selectedLine = nullptr;
			for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
				if (gates[i] != nullptr)
					if (gates[i]->isClick(point.x, point.y) && !gates[i]->isBound()) {
						selectedGate = gates[i];
						break;
					}
			if (selectedGate != nullptr || selectedLine != nullptr) {
				isSelected = true;
			}
		}


	}
	else {
		if (selectedLine != nullptr) {
			selectedLine->setLastPoint(point.x, point.y);
			int i = AddComponent(new Components_Gate(JUNCTION));
			if (i > 0) {
				gates[i]->place(point.x, point.y);
			}
			selectedLine = nullptr;
			isSelected = false;
			//두 핀을 연결하는 내용을 만든다.
		}
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CChildView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!isSelected) {
		if (point.x > 200) {
			for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++)
				if (gates[i] != nullptr)
					if (gates[i]->isClick(point.x, point.y)) {
						InvalidateRect(gates[i]->getRect(5));
						DeleteComponent(gates[i]);
						break;
					}
		}


	}

	CWnd::OnRButtonDblClk(nFlags, point);
}
