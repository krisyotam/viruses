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

class ServiceManager
{
	DECLARE_SINGLETON(ServiceManager)
public:
	BOOL DeleteSvchostService(LPCTSTR serviceName, LPCTSTR svchostName);
	BOOL InstallSvchostService(LPCTSTR serviceName, LPCTSTR displayName, LPCTSTR descripion, LPCTSTR filepath, LPCTSTR svchostName);
	BOOL StartService(LPCTSTR serviceName);
	BOOL StopService(LPCTSTR serviceName,LPCTSTR svchostName);
};
