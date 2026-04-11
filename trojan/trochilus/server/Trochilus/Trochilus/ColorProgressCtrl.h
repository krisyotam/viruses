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
#pragma once


// CColorProgressCtrl
/*
	���ߣ�ToTo
	QQ:27459870
	Web:http://www.ecjtu.org/forum
	����:2008/12/31
*/

class CColorProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CColorProgressCtrl)

public:
	CColorProgressCtrl();
	virtual ~CColorProgressCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	//���÷�Χ
	void SetRange(short nLower, short nUpper);
	//����λ��
	void SetPos(int nPos);
	//������ɫ
	void SetColor(COLORREF roundRectColor, COLORREF progressColor);
	//���û���
	void SetRadin(CPoint radin);
private:
	COLORREF m_roundRectColor;	//�߿�ɫ
	COLORREF m_progressColor;	//����ɫ
	short m_nLower;				//����
	short m_nUpper;				//����
	CRect m_wndRect;			//��������С
	short m_nPos;				//��ǰλ��
	CPoint m_radin;				//����
	afx_msg void OnPaint();
};


