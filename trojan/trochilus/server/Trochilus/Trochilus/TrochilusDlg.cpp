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

// TrochilusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Trochilus.h"
#include "TrochilusDlg.h"
#include "FilePanelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CTrochilusDlg �Ի���




CTrochilusDlg::CTrochilusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrochilusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrochilusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CTrochilusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CTrochilusDlg::OnTcnSelchangeTabMain)

	ON_WM_SIZE()
END_MESSAGE_MAP()

void CTrochilusDlg::InitResize()
{

	static CResizer::CBorderInfo s_bi[] = {
		{IDC_TAB_MAIN,    
		{CResizer::eFixed, IDC_MAIN, CResizer::eLeft},
		{CResizer::eFixed, IDC_MAIN, CResizer::eTop},
		{CResizer::eFixed, IDC_MAIN, CResizer::eRight},
		{CResizer::eFixed, IDC_MAIN, CResizer::eBottom}},
		{ID_STATUS_BAR_CTRL,    
		{CResizer::eFixed, IDC_MAIN, CResizer::eLeft},
		{CResizer::eFixed, IDC_MAIN, CResizer::eBottom},
		{CResizer::eFixed, IDC_MAIN, CResizer::eRight},
		{CResizer::eFixed, IDC_MAIN, CResizer::eBottom}}
	};

	const int nSize = sizeof(s_bi)/sizeof(s_bi[0]);
	m_resizer.Init(m_hWnd, NULL, s_bi, nSize);
}

BOOL CTrochilusDlg::InitView()
{
	m_TabCtrl.InsertItem(0,_T("Host"));
	m_TabCtrl.InsertItem(1,_T("Listener"));
	CRect rs;

	m_TabCtrl.GetClientRect(&rs);
	rs.top += 21;

	m_HostDlg.Create(IDD_DIALOG_HOST,&m_TabCtrl);
	m_HostDlg.MoveWindow(&rs);

	m_LisDlg.Create(IDD_DIALOG_LIS,&m_TabCtrl);
	m_LisDlg.MoveWindow(&rs);

	m_HostDlg.ShowWindow(TRUE);
	//��ʼ��״̬��
	CRect rect;
	GetClientRect(rect);
	VERIFY( m_wndStatusBar.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM|SBARS_SIZEGRIP,
		CRect(0,0,0,0), this, ID_STATUS_BAR_CTRL) );        
	//����״̬��λ��
	m_wndStatusBar.GetClientRect(&rect);
	int nWidths[4] ={ 400, 420, rect.right-150,-1};
	VERIFY(m_wndStatusBar.SetParts(4, nWidths));

	//�趨�����ı�
	m_wndStatusBar.SetText(_T("Host: 0"),2,0);
	m_wndStatusBar.SetText(_T("0-0-0 0:0:0"),0,0);
	m_wndStatusBar.SetText(_T("Version 0.0.2 Build 41"),3,0);

	m_timeRepeat.Init(DateRepeatProc,this,_T("time"),0,1);
	m_timeRepeat.Start();

	return TRUE;
}


DWORD WINAPI CTrochilusDlg::DateRepeatProc(LPVOID lpParameter)
{
	CTrochilusDlg* lpDlg = (CTrochilusDlg*)lpParameter;
	SYSTEMTIME sysTime;

	GetLocalTime(&sysTime);

	lpDlg->m_wndStatusBar.SetText(common::FormatSystemTime(sysTime),0,0);
	return 0;
}

BOOL CTrochilusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	if (!InitView())
	{
		ExitProcess(0);
	}

	InitResize();
	return TRUE;
}

void CTrochilusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CTrochilusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CTrochilusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrochilusDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSel = m_TabCtrl.GetCurSel();

	if (nSel == 0)
	{
		m_LisDlg.ShowWindow(FALSE);
		m_HostDlg.ShowWindow(TRUE);
	}
	else if(nSel == 1)
	{
		m_HostDlg.ShowWindow(FALSE);
		m_LisDlg.ShowWindow(TRUE);
	}
}



void CTrochilusDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	CRect rs;
	
	m_resizer.Move();
	
	if (m_TabCtrl.m_hWnd)
	{
		m_TabCtrl.GetClientRect(&rs);
		rs.top += 21;

		m_HostDlg.MoveWindow(rs);
		m_LisDlg.MoveWindow(rs);
	}

}
