
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MFCPuzzle.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	srand((unsigned int)(time(NULL)));

	m_xpos = 0;
	m_bitmap.LoadBitmapW(IDB_BITMAP1);
	m_bitmap.GetBitmap(&m_bmpinfo);

	boardSize.cx = 3;
	boardSize.cy = 3;

	bitmapSize.cx = m_bmpinfo.bmWidth;
	bitmapSize.cy = m_bmpinfo.bmHeight;

	cursor = -1;

	//  boardHeight = 0;
	int tilesize = sizeof(*tile) * boardSize.cx * boardSize.cy;
	tile = (short*)malloc(tilesize);

	for (int i = 0; i < boardSize.cx * boardSize.cy; i++)
		tile[i] = i;
	tile[0] = -1;

	//for (int shuffleI = 0; shuffleI < 120; shuffleI++) {
	//	int sourcetile = rand() % (boardSize.cx * boardSize.cy);
	//	int direction = rand() & 0x03;//0:0도 1:90도 2:180도 3:270도

	//	int sourcetileX = sourcetile % boardSize.cx;
	//	int sourcetileY = sourcetile / boardSize.cx;

	//	int destTileX = sourcetileX;
	//	int destTileY = sourcetileY;

	//	switch (direction) {
	//	case 0:destTileY--; break;
	//	case 1:destTileX++; break;
	//	case 2:destTileY++; break;
	//	case 3:destTileX--; break;
	//	}
	//	flipTiles({ sourcetileX,sourcetileY }, { destTileX,destTileY });
	//}
}

CChildView::~CChildView()
{
	free(tile);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_WM_CREATE()
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

	CRect rect;
	dc.SetMapMode(MM_ANISOTROPIC);
	GetClientRect(&rect);
	dc.SetWindowExt(rect.Width()/2,rect.Height()/2);
	dc.SetViewportExt(rect.Width(), rect.Height());
	
	//dc.BitBlt(10, 10, m_bmpinfo.bmWidth, m_bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	int tileW = bitmapSize.cx / boardSize.cx;
	int tileH = bitmapSize.cy / boardSize.cy;

	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&m_bitmap);
	for (int i = 0; i < boardSize.cx * boardSize.cy; i++) {

		int positionX = i % boardSize.cx;
		int positionY = i / boardSize.cx;
		POINT iPoint = { 10 + positionX * (tileW + 5), 10 + positionY * (tileH + 5) };

		blitTile(&dc, &dcmem, iPoint, i);

		//if (cursor == i) {
		//	CPen outlinePen;
		//	outlinePen.CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
		//	CPen* oldPen = dc.SelectObject(&outlinePen);

		//	POINT points[] = { iPoint,{iPoint.x + tileW,iPoint.y},{iPoint.x + tileW,iPoint.y + tileH},{iPoint.x,iPoint.y + tileH},iPoint };
		//	dc.Polyline(points,5);

		//	dc.SelectObject(oldPen);
		//	outlinePen.DeleteObject();
		//}
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	int tileW = bitmapSize.cx / boardSize.cx;
	int tileH = bitmapSize.cy / boardSize.cy;

	int tilepointX = (point.x/2 - 10) / (tileW + 5);
	int tilepointY = (point.y/2 - 10) / (tileH + 5);
	int cursorpoint = tilepointX + tilepointY * boardSize.cx;

	if (tilepointX >= 0 && tilepointX < boardSize.cx && tilepointY >= 0 && tilepointY < boardSize.cy) {
		//if (boardSize.cx*boardSize.cy > cursor && cursor >= 0) {

		//	flipTiles(cursor, cursorpoint);
		//	cursor = -1;
		//}
		//else {
		//	cursor = cursorpoint;
		//}
		//Invalidate();
		int flipPoint = cursorpoint;

		if (cursorpoint + 1 < boardSize.cx* boardSize.cy			 && tile[cursorpoint + 1] == -1) flipPoint = cursorpoint + 1;
		if (cursorpoint - 1 >= 0									 && tile[cursorpoint - 1] == -1) flipPoint = cursorpoint - 1;
		if (cursorpoint + boardSize.cx < boardSize.cx * boardSize.cy && tile[cursorpoint + boardSize.cx] == -1) flipPoint = cursorpoint + boardSize.cx;
		if (cursorpoint - boardSize.cx >= 0							 && tile[cursorpoint - boardSize.cx] == -1) flipPoint = cursorpoint - boardSize.cx;

		flipTiles(cursorpoint, flipPoint);
		Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


int CChildView::flipTiles(POINT tile1, POINT tile2)
{
	if (tile1.x < 0 || tile1.x >= boardSize.cx || tile1.y < 0 || tile1.y >= boardSize.cy
		|| tile2.x < 0 || tile2.x >= boardSize.cx || tile2.y < 0 || tile2.y >= boardSize.cy)
		return 1;

	int tile1position = tile1.x + tile1.y * boardSize.cx;
	int tile2position = tile2.x + tile2.y * boardSize.cx;

	return flipTiles(tile1position, tile2position);
}
int CChildView::flipTiles(int tile1, int tile2)
{
	int tilesize = boardSize.cx * boardSize.cy;
	if (tile1 < 0 || tile1 >= tilesize || tile2 < 0 || tile2 >= tilesize)
		return 1;

	auto swap = tile[tile1];
	tile[tile1] = tile[tile2];
	tile[tile2] = swap;

	return 0;
}


int CChildView::blitTile(CPaintDC* pDC, CDC* pmemDC, POINT position,int tileNum)
{
	int tilesize = boardSize.cx * boardSize.cy;
	if (tileNum < 0 || tileNum >= tilesize)
		return 1;
	int tileX = tile[tileNum] % boardSize.cx;
	int tileY = tile[tileNum] / boardSize.cx;

	int tileW = bitmapSize.cx / boardSize.cx;
	int tileH = bitmapSize.cy / boardSize.cy;
	pDC->BitBlt(position.x, position.y, tileW, tileH, pmemDC, tileW * tileX, tileH * tileY, SRCCOPY);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == 1) {
		
		for (int i = 0; i < (boardSize.cx * boardSize.cy); i++) {
			int sourcetile = rand() % (boardSize.cx * boardSize.cy);
			int direction = rand() & 0x03;//0:0도 1:90도 2:180도 3:270도

			int sourcetileX = sourcetile % boardSize.cx;
			int sourcetileY = sourcetile / boardSize.cx;

			int destTileX = sourcetileX;
			int destTileY = sourcetileY;

			switch (direction) {
			case 0:destTileY--; break;
			case 1:destTileX++; break;
			case 2:destTileY++; break;
			case 3:destTileX--; break;
			}
			flipTiles({ sourcetileX,sourcetileY }, { destTileX,destTileY });
		}
		m_xpos++;
		Invalidate();
		if (m_xpos > 20) KillTimer(1);
	}

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(1, 20, NULL);

	return 0;
}
