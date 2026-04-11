/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#pragma once


// NameOfRunQuest dialog

class NameOfRunQuest : public CDialog
{
	DECLARE_DYNAMIC(NameOfRunQuest)

public:
	NameOfRunQuest(CWnd* pParent = NULL);   // standard constructor
	virtual ~NameOfRunQuest();

// Dialog Data
//	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
};
