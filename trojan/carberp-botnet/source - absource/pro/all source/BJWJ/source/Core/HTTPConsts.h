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

//-----------------------------------------------------------------------------
//  HTTPConsts -  ������ ����������� �������� ��� ������ � HTTP ����������
//
//  ������ 1.0
//  ����: ���� 2012
//-----------------------------------------------------------------------------
#ifndef HTTPConstsH
#define HTTPConstsH
//-----------------------------------------------------------------------------


const char HTTPProtocolDelimeter[] = "://";
const char HTTPParamsDelimeter[] = "?";
const char HTTPSlash[] = "/";

const DWORD HTTPPort  = 80;
const DWORD HTTPSPort = 443;

const PCHAR ProtocolHTTP  = "http";
const PCHAR ProtocolHTTPS = "https";

//-----------------------------------------------------------------------------
#endif