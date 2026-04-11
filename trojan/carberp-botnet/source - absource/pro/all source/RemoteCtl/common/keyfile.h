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
#pragma once

class ClientKey
{
public:

	wstring name;
	vector<BYTE> content;
	vector<BYTE> hash;
	vector<BYTE> backhash;

public:

  ClientKey( LPCTSTR _name, bool bCreateBackHash = true );
  bool InitFromString( LPCSTR s );
  bool Load( );
};
