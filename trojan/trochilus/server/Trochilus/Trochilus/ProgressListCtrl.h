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
#include "ColorProgressCtrl.h"
#include <vector>

// CProgressListCtrl
#define IDC_PROGRESS WM_USER + 100
class CProgressListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CProgressListCtrl)

public:
	CProgressListCtrl();
	virtual ~CProgressListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	std::vector<CColorProgressCtrl*> m_vProgress;
	void DeleteProgress();
};


