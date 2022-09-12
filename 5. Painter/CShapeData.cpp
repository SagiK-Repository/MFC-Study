#include "pch.h"
#include "CShapeData.h"

IMPLEMENT_SERIAL(CShapeData, CObject, 1);

CShapeData::CShapeData() {
	m_color = RGB(0, 0, 0);
	m_rect = { 0,0,0,0 };
	m_str = _T("");
	m_thick = 1;
	m_Type = None;
}

CShapeData::~CShapeData() {

}

void CShapeData::operator=(const CShapeData& data)
{
	this->m_color = data.m_color;
	this->m_fill = data.m_fill;
	this->m_rect = data.m_rect;
	this->m_str = data.m_str;
	this->m_thick = data.m_thick;
	this->m_Type = data.m_Type;
}

void CShapeData::Serialize(CArchive& ar) {
	CObject::Serialize(ar);

	if (ar.IsStoring()) {
		ar << m_Type << m_thick << m_rect << m_color << m_str << m_fill;
	}
	else {
		ar >> m_Type >> m_thick >> m_rect >> m_color >> m_str >> m_fill;
	}
}

CRect CShapeData::rect()
{
	CRect rect;
	rect.top    = min(m_rect.top, m_rect.bottom);
	rect.bottom = max(m_rect.top, m_rect.bottom);

	rect.left  = min(m_rect.left, m_rect.right);
	rect.right = max(m_rect.left, m_rect.right);
	return rect;
}
