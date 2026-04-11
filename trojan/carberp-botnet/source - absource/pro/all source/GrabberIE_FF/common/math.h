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
/*
  �������������� �������.
*/

namespace Math
{
  /*
    �������������.
  */
  void Init(void);

  /*
    ���������������.
  */
  void Uninit(void);

#if !defined _WIN64
  /*
    ������� 64-� ������� ��������� ����� (�������� ����� � Win32).

    IN dwA - �������.
    IN dwB - ��������.

    Return - ���������.
  */
  __int64 __stdcall _divI64(__int64 dwA, __int64 dwB);

  /*
    ������� 64-� ������� ��� ��������� ����� (�������� ����� � Win32).

    IN dwA - �������.
    IN dwB - ��������.

    Return - ���������.
  */
  DWORD64 __stdcall _divU64(DWORD64 dwA, DWORD64 dwB);

  /*
    ��������� ������ �� ������� 64-� ������� ��������� �����.

    IN dwA - �������.
    IN dwB - ��������.

    Return - ���������.
  */
  __int64 __stdcall _modI64(__int64 dwA, __int64 dwB);

  /*
    ��������� ������ �� ������� 64-� ������� ��� ��������� �����.

    IN dwA - �������.
    IN dwB - ��������.

    Return - ���������.
  */
  DWORD64 __stdcall _modU64(DWORD64 dwA, DWORD64 dwB);

  /*
    ��������� 64-� ������� ����� (�������� ����� � Win32).

    IN dwA - ��������.
    IN dwB - ���������.

    Return - ���������.
  */
  DWORD64 __stdcall _mul64(DWORD64 dwA, DWORD64 dwB);

  /*
    ����� ������ 64-� ������� ����� (�������� ����� � Win32).

    IN number - �����.
    IN bits   - ����� ��� ������.

    Return    - ���������.
  */
  DWORD64 __stdcall _shr64(DWORD64 number, BYTE bits);

  /*
    �������������� float � int32  (�������� ����� � Win32).

    IN f   - float.
    Return - int32.
  */
  int __stdcall _ftoi(float f);
#endif

  /*
    ���������� ���������� �������� 32-x ������� �����.

    IN iNumber - �����.

    Return - ���������� ��������.
  */
  int _abs(int iNumber);

  /*
    ���������� ���������� �������� 64-x ������� �����.

    IN iNumber - �����.

    Return - ���������� ��������.
  */
  __int64 _abs64(__int64 iNumber);

  /*
    �������� ����� �� ����� � ������� �����.

    IN d   - �������� �����.
    OUT ip - ����� �����.

    Return - ������� �����.
  */
  double _modf(double d, double *ip);

  /*
    ��������� ����� � ������� �������.

    IN d - �����.

    Return - ���������.
  */
  double _floor(double d);

  /*
    ��������� ����� � ������� �������.

    IN d - �����.

    Return - ���������.
  */
  double _ceil(double d);

  /*
    ������� ��������� ���� �������� �������.

    IN p1  - ������ �������.
    IN p2  - ������ �������.

    Return -  > 0 - ������� p1 ������ p2.
              = 0 - �������� �����.
              < 0 - ������� p1 ������ p2.
  */
  typedef int (*qsortProc)(const void *p1, const void *p2);

  /*
    �������� ������� ���������� ��� �������.

    IN pBase   - ������� ����� �������.
    IN dwCount - ���������� ��������� � �������.
    IN dwWidth - ������ ������ ��������.
    IN pComp   - ������� ���������.
  */
  void _qsort(void *pBase, DWORD dwCount, DWORD dwWidth, qsortProc pComp);
};
