
// PainterView.cpp : implementation of the CPainterView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Painter.h"
#endif

#include "CShapeData.h"
#include "PainterDoc.h"
#include "PainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPainterView

IMPLEMENT_DYNCREATE(CPainterView, CView)

BEGIN_MESSAGE_MAP(CPainterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TYPE_LINE, &CPainterView::OnLine)
	ON_UPDATE_COMMAND_UI(ID_TYPE_LINE, &CPainterView::OnUpdateLine)
	ON_COMMAND(ID_RECT, &CPainterView::OnRect)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CPainterView::OnUpdateRect)
	ON_COMMAND(ID_ROUND_RECT, &CPainterView::OnRoundRect)
	ON_UPDATE_COMMAND_UI(ID_ROUND_RECT, &CPainterView::OnUpdateRoundRect)
	ON_COMMAND(ID_ECLIPSE, &CPainterView::OnEclipse)
	ON_UPDATE_COMMAND_UI(ID_ECLIPSE, &CPainterView::OnUpdateEclipse)
	ON_COMMAND(ID_TEXT, &CPainterView::OnText)
	ON_UPDATE_COMMAND_UI(ID_TEXT, &CPainterView::OnUpdateText)
	ON_COMMAND(ID_TYPE_FILL, &CPainterView::OnFill)
	ON_UPDATE_COMMAND_UI(ID_TYPE_FILL, &CPainterView::OnUpdateFill)
	ON_COMMAND(ID_BLACK, &CPainterView::OnBlack)
	ON_UPDATE_COMMAND_UI(ID_BLACK, &CPainterView::OnUpdateBlack)
	ON_COMMAND(ID_RED, &CPainterView::OnRed)
	ON_UPDATE_COMMAND_UI(ID_RED, &CPainterView::OnUpdateRed)
	ON_COMMAND(ID_BLUE, &CPainterView::OnBlue)
	ON_UPDATE_COMMAND_UI(ID_BLUE, &CPainterView::OnUpdateBlue)
	ON_COMMAND(ID_GREEN, &CPainterView::OnGreen)
	ON_UPDATE_COMMAND_UI(ID_GREEN, &CPainterView::OnUpdateGreen)
	ON_COMMAND(ID_SIZE_SMALL, &CPainterView::OnSizeSmall)
	ON_UPDATE_COMMAND_UI(ID_SIZE_SMALL, &CPainterView::OnUpdateSizeSmall)
	ON_COMMAND(ID_SIZE_MEDIUM, &CPainterView::OnSizeMedium)
	ON_UPDATE_COMMAND_UI(ID_SIZE_MEDIUM, &CPainterView::OnUpdateSizeMedium)
	ON_COMMAND(ID_SIZE_LARGE, &CPainterView::OnSizeLarge)
	ON_UPDATE_COMMAND_UI(ID_SIZE_LARGE, &CPainterView::OnUpdateSizeLarge)
END_MESSAGE_MAP()

// CPainterView construction/destruction

CPainterView::CPainterView() noexcept
{
	// TODO: add construction code here
	isDrawing = false;
	drawtype = PlaceType::None; 
	drawFill = false;
	drawsize = PlaceSize::SMALL; 
	drawcolor = PlaceColor::Black;
}

CPainterView::~CPainterView()
{
}

BOOL CPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPainterView drawing

void CPainterView::OnDraw(CDC* pDC)
{
	CPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < pDoc->m_arrData.GetSize(); i++)
		DrawObj(pDC, pDoc->m_arrData.GetAt(i));

	// TODO: add draw code for native data here
}


// CPainterView printing

BOOL CPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPainterView diagnostics

#ifdef _DEBUG
void CPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPainterDoc* CPainterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPainterDoc)));
	return (CPainterDoc*)m_pDocument;
}
#endif //_DEBUG


// CPainterView message handlers


int CPainterView::DrawObj(CDC* pDC, CShapeData& data)
{
	CBrush brush,*oldBrush;
	if (data.m_fill)
		brush.CreateSolidBrush(data.m_color);
	else
		brush.CreateObject();
	oldBrush = pDC->SelectObject(&brush);

	CPen pen,*oldPen;
	pen.CreatePen(PS_SOLID, data.m_thick, data.m_color);
	oldPen = pDC->SelectObject(&pen);

	CFont font;
	font.CreatePointFont(data.m_rect.Height() * 5, _T("±Ã¼­"));
	CFont* oldFont = pDC->SelectObject(&font);

	POINT roundpoint = { data.m_rect.Width() * 0.1,data.m_rect.Height() * 0.1 };
	POINT linepoint[2] = { data.m_rect.TopLeft() ,data.m_rect.BottomRight() };
	switch (data.m_Type)
	{
	case CShapeData::Line:
		pDC->Polygon(linepoint, 2);
		break;

	case CShapeData::Rectangle:
		pDC->Rectangle(data.m_rect);
		break;

	case CShapeData::Elipse:
		pDC->Ellipse(data.m_rect);
		break;

	case CShapeData::RoundRect:
		pDC->RoundRect(data.m_rect, roundpoint);
		break;

	case CShapeData::Text:
		pDC->DrawText(data.m_str,&data.m_rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;

	default:
		break;
	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldFont);
	return 0;
}


void CPainterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (isDrawing) {
		isDrawing = false;
	}
	else {
		if (drawtype != PlaceType::None) {
			isDrawing = true;
			CShapeData data;
			data.m_Type = drawtype;
			data.m_fill = drawFill;

			switch (drawsize)
			{
			case PlaceSize::SMALL:  data.m_thick = 1 ; break;
			case PlaceSize::MEDIUM: data.m_thick = 5 ; break;
			case PlaceSize::LARGE:  data.m_thick = 10; break;
			default: data.m_thick = 1; break;
			}

			switch (drawcolor)
			{
			case PlaceColor::Black: data.m_color = RGB(0,0,0);   break;
			case PlaceColor::Red  : data.m_color = RGB(255,0,0); break;
			case PlaceColor::Green: data.m_color = RGB(0,255,0); break;
			case PlaceColor::Blue : data.m_color = RGB(0,0,255); break;
			default: data.m_color = RGB(0, 0, 0); break;
			}

			data.m_rect.top = point.y;
			data.m_rect.left = point.x;

			CPainterDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if (!pDoc)
				return;
			pDoc->m_arrData.Add(data);
			pDoc->SetModifiedFlag();
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CPainterView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	selectedShape = nullptr;

	int nSize = pDoc->m_arrData.GetCount();
	for (int i = 0; i < nSize; i++) {
		if (pDoc->m_arrData[i].m_Type == PlaceType::Text && pDoc->m_arrData[i].rect().PtInRect(point)) {
			selectedShape = &pDoc->m_arrData[i];
			InvalidateRect(selectedShape->rect());
			break;
		}
	}

	CView::OnRButtonDown(nFlags, point);
}


void CPainterView::OnMouseMove(UINT nFlags, CPoint point)
{
	static POINT prePoint;
	// TODO: Add your message handler code here and/or call default
	if (isDrawing) {
		CPainterDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		pDoc->m_arrData[pDoc->m_arrData.GetCount() - 1].m_rect.bottom = point.y;
		pDoc->m_arrData[pDoc->m_arrData.GetCount() - 1].m_rect.right = point.x;
		CRect rect = pDoc->m_arrData[pDoc->m_arrData.GetCount() - 1].rect();

		long dist = (long)sqrt(pow((double)(point.x - prePoint.x), 2) + pow((double)(point.y - prePoint.y), 2));

		pDoc->SetModifiedFlag();
		rect.InflateRect(dist+5, dist+5, dist+5, dist+5);
		InvalidateRect(&rect);
	}
	prePoint = point;
	CView::OnMouseMove(nFlags, point);
}


void CPainterView::OnLine()
{
	if (drawtype == PlaceType::Line) drawtype = PlaceType::None;
	else drawtype = PlaceType::Line;
	Invalidate();
}
void CPainterView::OnUpdateLine(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawtype == PlaceType::Line);
}
void CPainterView::OnRect()
{
	if (drawtype == PlaceType::Rect) drawtype = PlaceType::None;
	else drawtype = PlaceType::Rect;
	Invalidate();
}
void CPainterView::OnUpdateRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawtype == PlaceType::Rect);
}
void CPainterView::OnRoundRect()
{
	if (drawtype == PlaceType::RoundRect) drawtype = PlaceType::None;
	else drawtype = PlaceType::RoundRect;
	Invalidate();
}
void CPainterView::OnUpdateRoundRect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawtype == PlaceType::RoundRect);
}
void CPainterView::OnEclipse()
{
	if (drawtype == PlaceType::Eclipse) drawtype = PlaceType::None;
	else drawtype = PlaceType::Eclipse;
	Invalidate();
}
void CPainterView::OnUpdateEclipse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawtype == PlaceType::Eclipse);
}
void CPainterView::OnText()
{
	if (drawtype == PlaceType::Text) drawtype = PlaceType::None;
	else drawtype = PlaceType::Text;
	Invalidate();
}
void CPainterView::OnUpdateText(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawtype == PlaceType::Text);
}



void CPainterView::OnFill()
{
	if(drawFill)
		 drawFill = false;
	else drawFill = true;
	Invalidate();
}


void CPainterView::OnUpdateFill(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawFill == true);
}


void CPainterView::OnBlack()
{
	drawcolor = PlaceColor::Black;
	Invalidate();
}


void CPainterView::OnUpdateBlack(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawcolor == PlaceColor::Black);
}


void CPainterView::OnRed()
{
	drawcolor = PlaceColor::Red;
	Invalidate();
}


void CPainterView::OnUpdateRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawcolor == PlaceColor::Red);
}


void CPainterView::OnBlue()
{
	drawcolor = PlaceColor::Blue;
	Invalidate();
}


void CPainterView::OnUpdateBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawcolor == PlaceColor::Blue);
}


void CPainterView::OnGreen()
{
	drawcolor = PlaceColor::Green;
	Invalidate();
}


void CPainterView::OnUpdateGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawcolor == PlaceColor::Green);
}


void CPainterView::OnSizeSmall()
{
	drawsize = PlaceSize::SMALL;
	Invalidate();
}


void CPainterView::OnUpdateSizeSmall(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawsize == PlaceSize::SMALL);
}


void CPainterView::OnSizeMedium()
{
	drawsize = PlaceSize::MEDIUM;
	Invalidate();
}


void CPainterView::OnUpdateSizeMedium(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawsize == PlaceSize::MEDIUM);
}


void CPainterView::OnSizeLarge()
{
	drawsize = PlaceSize::LARGE;
	Invalidate();
}


void CPainterView::OnUpdateSizeLarge(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(drawsize == PlaceSize::LARGE);
}
