/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
// ColorProgressCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColorProgressCtrl.h"


// CColorProgressCtrl

IMPLEMENT_DYNAMIC(CColorProgressCtrl, CProgressCtrl)

CColorProgressCtrl::CColorProgressCtrl()
{
	m_roundRectColor = RGB(116, 158, 210);	//�߿�ɫ
	m_progressColor = RGB(45, 213,79);		//����ɫ
	m_nLower = 0;							//����
	m_nUpper = 100;							//����
	m_nPos = 0;								//��ǰλ��
	m_radin = CPoint(0, 0);					//����
}

CColorProgressCtrl::~CColorProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CColorProgressCtrl ��Ϣ��������



//���÷�Χ
void CColorProgressCtrl::SetRange(short nLower, short nUpper)
{

}
//����λ��
void CColorProgressCtrl::SetPos(int nPos)
{
	if (nPos < 0 || nPos > m_nUpper)
	{
		return;
	}
	m_nPos = nPos;
	InvalidateRect(m_wndRect);
}
//������ɫ
void CColorProgressCtrl::SetColor(COLORREF roundRectColor, COLORREF progressColor)
{
	m_roundRectColor = roundRectColor;
	m_progressColor = progressColor;
}
//���û���
void CColorProgressCtrl::SetRadin(CPoint radin)
{
	m_radin = radin;
}


void CColorProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴�������Ϣ�����������
	GetClientRect(&m_wndRect);
	//���߿�
	CPen pen1;
	pen1.CreatePen(PS_SOLID, 2, m_roundRectColor);
	CPen *oldPen = dc.SelectObject(&pen1);
	dc.RoundRect(m_wndRect, m_radin);
	dc.SelectObject(oldPen);
	//������
	CRect rectProgress;
	CBrush brush;
	CPen pen2;
	pen2.CreatePen(PS_NULL, 0, m_roundRectColor);
	brush.CreateSolidBrush(m_progressColor);
	rectProgress.bottom = m_wndRect.bottom - 1;
	rectProgress.top = m_wndRect.top + 1;
	rectProgress.left = m_wndRect.left + 1;
	rectProgress.right = m_wndRect.right * (float)m_nPos / (float)m_nUpper - 1;
	dc.SelectObject(pen2);
	dc.SelectObject(brush);
	dc.RoundRect(rectProgress, m_radin);
	// ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()
}
