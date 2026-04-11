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

namespace LnkUtils
{
	BOOL CreateLnk( LPCWSTR lpFilepath, LPCWSTR lnkFilepath ,LPCWSTR lpArgument =_T("") );
	BOOL IsLnkFile( LPCTSTR lpFileName );
	BOOL QueryLnk( LPCTSTR lpLinkPath, tstring& strExePath, tstring& strExeParam );
};
