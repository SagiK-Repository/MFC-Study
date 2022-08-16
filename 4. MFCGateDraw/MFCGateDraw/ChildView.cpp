
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
	res = AddComponent(new Components_Gate(AND)); gates[res]->place(110, 80 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(OR)); gates[res]->place(110, 160 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(XOR)); gates[res]->place(110, 240 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(NAND)); gates[res]->place(110, 320 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(NOR)); gates[res]->place(110, 400 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(XNOR)); gates[res]->place(110, 480 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(Gate_INPUT)); gates[res]->place(110, 560 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(Gate_OUTPUT)); gates[res]->place(110, 640 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(JUNCTION)); gates[res]->place(110, 720 + 70); gates[res]->showNumber = false;
	res = AddComponent(new Components_Gate(TEXT)); gates[res]->place(110, 800 + 70); gates[res]->w = 150; gates[res]->w = 80; gates[res]->text = _T("Line");
	
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


	for (int i = 0; i < sizeof(lines) / sizeof(*lines); i++) {
		if (lines[i] != nullptr)lines[i]->draw(&dc);
	}

	for (int i = 0; i < sizeof(gates) / sizeof(*gates); i++) {
		if (gates[i] != nullptr)gates[i]->draw(&dc);
	}
	// Do not call CWnd::OnPaint() for painting messages
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
			for (int i = 0; i < line->pinCount; i++) {
				line->pins[i].deletePin();
			}
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
						// Adding gates
						if (gates[i]->gate_type != TEXT) {
							i = AddComponent(new Components_Gate(gates[i]->gate_type));
							if (i < 0)break;
							selectedGate = gates[i];
							selectedGate->place(point.x, point.y);
						}
						else {// Adding Line
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
			else if (selectedLine != nullptr) { // connecting line
				Pin* pinNearest = findNearestPin(gates, point, 30.f);

				if (pinNearest != nullptr) {
					if (selectedLine->len == 0) {// first input

						 // if there's no pins around here
						//cancels the click.

						//if there's pin around here
						int res = selectedLine->ConnectPinAuto(pinNearest);
						if (res != 0) {
							MessageBox(L"Fail. Already Connected or PinType Mismatch.");
						}
						else {
							selectedLine->addPoint(pinNearest->pinX, pinNearest->pinY);

							selectedLine->addPoint(point.x, point.y);
						}
					}
					else // last input(line termination)
					{
						int res = selectedLine->ConnectPinAuto(pinNearest);
						if (res != 0) { // if connect fails
							MessageBox(L"Fail. Already Connected or PinType Mismatch.");
						}
						else {
							selectedLine->setLastPoint(pinNearest->pinX, pinNearest->pinY);
							selectedLine->pins[0].processPin(); // bring the state of input.
							Invalidate();
							selectedLine = nullptr;
							isSelected = false;
						}
					}
				}

				if(selectedLine != nullptr && selectedLine->len > 0 && pinNearest == nullptr)
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
		if (selectedLine != nullptr) { // termination in middle'
			//delete the line.

			DeleteLine(selectedLine);
			selectedLine = nullptr;
			isSelected = false;
			Invalidate();

			/*
			selectedLine->setLastPoint(point.x, point.y);
			
			int i = AddComponent(new Components_Gate(JUNCTION));
			if (i > 0) {
				gates[i]->place(point.x, point.y);
			}
			if (selectedLine->pins[0].pinFrom == nullptr) { // input is empty
				
			}
			else if (selectedLine->pins[1].pinTo == nullptr) {

			}
			else {
				//No pins are remaind. invalid state.
				MessageBox(L"ERROR.");
			}
			selectedLine = nullptr;
			isSelected = false;
			*/
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


Pin* CChildView::findNearestPin(Components_Gate** gates, POINT point, float threshold)
{
	Pin* pinptr = nullptr;
	for (int i = 0; gates[i] != nullptr; i++) {
		for (int j = 0; j < gates[i]->pinCount; j++) {
			if (gates[i]->pins[j].pinX == 0 && gates[i]->pins[j].pinY == 0)continue;

			float dist = sqrtf( powf(point.x-gates[i]->pins[j].pinX,2.f) + powf(point.y-gates[i]->pins[j].pinY,2.f) );
			if (dist < threshold) {
				threshold = dist;
				pinptr = gates[i]->pins + j;
			}
		}
	}

	return pinptr;
}
