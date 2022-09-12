#pragma once
#include <afx.h>


class CShapeData : public CObject
{
public :
	bool m_fill;
	int m_thick;
	int m_Type;
	CRect m_rect;
	COLORREF m_color;
	CString m_str;

public:
	DECLARE_SERIAL(CShapeData);
	void Serialize(CArchive& ar);
	CShapeData();
	virtual ~CShapeData();

	void operator = (const CShapeData&);

public:
	enum Type {
		None,
		Line,
		Rectangle,
		Elipse,
		RoundRect,
		Text
	};
//	int rect();
	CRect rect();
};
