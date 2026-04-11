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
#include "afxcmn.h"
#include "mfcresize/Resizer.h"
#include "FileMgrDlg.h"
#include "TransferDlg.h"
#include "CmdDlg.h"
// CPanelDlg �Ի���



class CFilePanelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilePanelDlg)

public:
	CFilePanelDlg(CWnd* pParent = NULL);
	virtual ~CFilePanelDlg();
	// �Ի�������
	enum { IDD = IDD_DIALOG_PANEL };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

public:
	//��ʼ������͹���״̬
	void InitView();
	void InitTab();
	virtual BOOL OnInitDialog();

	void InitResize();
	CResizer m_resizer;

	//����ģ��״̬��Ϣ
	void HandleMsgNotify(UINT nType, LPCTSTR lpContext);

	//��Tab��ѡ��ı�
	afx_msg void OnTcnSelchangeTabPanel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//���ÿͻ���ID
	void SetClientID(LPCTSTR clientid)
	{
		m_clientid = clientid;
		
		m_FileMgr.InitModule(clientid);
		m_TransInfo.InitModule(clientid);

	}

private:

	friend CFileMgrDlg;

	CTabCtrl m_TabCtrl;

	typedef std::map<tstring,tstring> ModuleCallBack;
	ModuleCallBack m_moduleinfo;

	CString m_clientid;
	CriticalSection m_csModuleMap;

	CFileMgrDlg m_FileMgr;
	CTransferDlg m_TransInfo;

public:
	afx_msg void OnClose();
};
