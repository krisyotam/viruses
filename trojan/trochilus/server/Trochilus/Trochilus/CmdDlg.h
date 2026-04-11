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
#include "afxwin.h"
#include "mfcresize/Resizer.h"

// CCmdDlg �Ի���

class CCmdDlg : public CDialogEx,public IModule
{
	DECLARE_DYNAMIC(CCmdDlg)

public:
	CCmdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCmdDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CMD };
	static void CALLBACK HandleModuleMsg(LPCTSTR clientid,UINT nMsg, LPVOID lpContext, LPVOID lpParameter);
	void HandleModuleMsgProc(UINT nMsg,LPVOID lpContext,LPVOID lpParameter);

	void EnableButton(BOOL isOpen);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnClose();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditResult();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	BOOL IsDisable(CString strCmd);
	void InitResize();

	void InitDisable();
public:
	CBrush m_bkBrush;
	UINT m_nCurSel;
	CEdit m_editResult;
	CString m_strResult;

	CResizer m_resizer;

	CStringArray m_arrDis;
};
