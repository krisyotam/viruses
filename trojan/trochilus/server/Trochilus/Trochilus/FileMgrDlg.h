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
#include "IModule.h"
#include "resource.h"
#include "mfcresize/Resizer.h"

class CFileMgrDlg : public CDialogEx, public IModule
{
	DECLARE_DYNAMIC(CFileMgrDlg)

public:
	CFileMgrDlg(CWnd* pParent = NULL);
	virtual ~CFileMgrDlg();

	enum { IDD = IDD_DIALOG_FILE };

	//����ģ����Ϣ
	static void CALLBACK HandleModuleMsg(LPCTSTR clientid,UINT nMsg, LPVOID lpContext, LPVOID lpParameter);
	void HandleModuleMsgProc(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);


	//��ʼ������ؼ�������
	virtual BOOL OnInitDialog();
	void InitView();
	void InitData();
	void InitResize();

	//���öԻ����ֶ���
	void SetColumn(CListCtrl* list,LPTSTR text,int nCol,int nWidth);

	//���������ݲ����ļ��б�
	void InsertFileList( char* lpJson,BOOL isRemote);

	//�õ�Զ���ļ��б�
	void GetRemoteList(CString strPath);

	//�õ������ļ��б�
	void GetLocalList(CString strPath);

	//�õ��ļ�ͼ����
	HICON GetFileIcon(CString strPath);

	//���������ļ��б�
	void HandleLocalFile(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);

	//����Զ���ļ��б�
	void HandleRemoteFile(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);

	BOOL IsEquPath(LPCTSTR filename,BOOL isRemote);
	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_rDicList;
	CListCtrl m_rFileList;
	CListCtrl m_lDicList;
	CListCtrl m_lFileList;

	CString m_rCurDir;
	CString m_lCurDir;

	CriticalSection m_csList;
	CImageList m_ImageList;

	CResizer m_resizer;

	LPVOID m_panel;
private:
	//Զ��Ŀ¼�б�˫��
	afx_msg void OnNMDblclkListRdic(NMHDR *pNMHDR, LRESULT *pResult);
	//����Ŀ¼�б�˫��
	afx_msg void OnNMDblclkListLdic(NMHDR *pNMHDR, LRESULT *pResult);
	//Զ���Ϸ�Ŀ¼��ť
	afx_msg void OnBnClickedButtonRupdic();
	//�����Ϸ�Ŀ¼��ť
	afx_msg void OnBnClickedButtonLupdic();
	//Զ��Ŀ¼ˢ��
	afx_msg void OnBnClickedButtonRrefresh();
	//����Ŀ¼ˢ��
	afx_msg void OnBnClickedButtonLrefresh();
	//�ϴ��ļ���ť
	afx_msg void OnBnClickedButtonUpload();
	//�����ļ���ť
	afx_msg void OnBnClickedButtonDown();
public:
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMRClickListRfile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickDownFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
