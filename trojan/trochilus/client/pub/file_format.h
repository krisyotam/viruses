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

#define MAX_BUFFER_SIZE 512*1024
//�ļ�ͷ
typedef struct
{
	UINT64 nFileSize; 							//�ļ���С
	int nNodeNum;						//�ֿ�����
	WCHAR szFileName[MAX_PATH];//�ļ���
	WCHAR szMD5[255];					//У��MD5ֵ
}FILE_HEAD,*PFILE_HEAD;

//���ݽڵ�
typedef struct
{
	int nNodeSize;						//�ڵ��С
	int nOffset;								//�ڵ��ļ�ƫ��
}FILE_NODE,*PFILE_NODE;

//...N�����ݽڵ�