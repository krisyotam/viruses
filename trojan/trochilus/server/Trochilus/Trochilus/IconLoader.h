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
class CIconLoader
{
	DECLARE_SINGLETON(CIconLoader)
public:
	HICON LoadIcon(CString strPath);
private:
	typedef std::map<CString,HICON> IconMap;
	IconMap m_IconMap;
};

