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
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#endif

#include <afx.h>
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
// Windows ͷ�ļ�:
#include <windows.h>

#define MAKE_PAIR(_a,b,c) _a::value_type((b),(c))

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "tstring.h"
#include "CommonDefines.h"
#include "AutoCleanup.h"

#include "ods.h"
#include "master.h"
#include "midutils.h"
#include "Exports.h"

#pragma comment(lib,"midutils.lib")

#define OUTPUT_LOG

#ifdef OUTPUT_LOG
#	define errorLogE ErrorODSE
#	define errorLog ErrorODS
#	define infoLogE InfoODSE
#	define infoLog InfoODS
#	define debugLogE DebugODSE
#	define debugLog DebugODS
#else
#	define errorLogE 
#	define errorLog 
#	define infoLogE 
#	define infoLog 
#	define debugLogE 
#	define debugLog 
#endif

#ifndef _DEBUG
#	define DATMODULE
#endif

#define TCPMSGSIZE	(64 * 1024)
