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

#include "ReportCtrl.h"
#include "mfcresize/Resizer.h"
#include <map>
#include "HostList.h"
// CHostDlg �Ի���

typedef std::map<CString,CLIENT_INFO> ClientMap;

class CHostDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHostDlg)

public:
	CHostDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHostDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_HOST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	static void CALLBACK ClientInfoNotify(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);
	void CALLBACK ClientInfoNotifyProc(UINT nMsg,CLIENT_INFO* pInfo);

	void InitView();
	void InitResize();
	static void StartPanel(CLIENT_INFO& info,LPVOID lpParameter);

	CImageList m_Imagelist;
	CHostList m_Clientlist;
	CResizer m_resizer;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	ClientMap m_clients;
	CriticalSection m_csClient;
	

};
