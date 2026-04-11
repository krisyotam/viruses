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
#include "tstring.h"
#include "../../../common/CommData.h"

//��ȡ��������ĳ��ģ�������Ŀ¼������ֵ��\��β
tstring GetModFilePath(LPCTSTR moduleName);

//��ȡservant.dll����Ŀ¼������ֵ��\��β
LPCTSTR GetBinFilepath();

//���ӽ���
BOOL XorFibonacciCrypt(const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1);

//��ʽ����С
tstring FormatSizeWithUnit(UINT64 size);

//ʹ�ö��Ž��д�С��ʽ��
tstring FormstSizeWithComma(UINT64 size);

//��ȡ�ļ���data��
BOOL ReadDataFile(LPCTSTR datafile, CommData& data);

//ת������
tstring TransferLanguage(DWORD cid);