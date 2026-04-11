/*
  name      KINS
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
/*
  ������ ����� ������������ #1, ������ ��� Malware, ������ � UTF8.

  //comment
  ;comment
  #comment
  arg1 arg2 argX
  {
    subarg1 subarg2 subargX
  }
  
  //marker - ����������� ������ ��� ����������� ����� ������.
  //������ ����� ������ ���������� ������������ ������,
  arg1 arg2
  [marker

  marker]
  
  ...
*/

namespace Config1
{
  //�������� ����������.
  typedef struct _VAR
  {
    DWORD dwSourceLine;  //������� ���������� � �������� �����.
    LPWSTR *ppstrValues; //��������� ����������.
    DWORD dwValuesCount; //���������� ���������.
    
    _VAR *pvChilds;      //������ �������� ���������.
    DWORD dwChildsCount; //���������� �������� ���������.
  }VAR;

  //���� �����������.
  typedef struct
  {
    VAR *pvVars;        //������ ���������.
    DWORD dwVarsCount;  //���������� ����������.
  }CONFIGFILE;

  /*
    �������������.
  */
  void Init(void);

  /*
    ���������������.
  */
  void Uninit(void);

  /*
    ������� �����.

    IN pstrFile      - ���� ��� ���������.
    OUT pdwErrorLine - ������ �� ������� ��������� ������, � ������ �������� �������� false.
    OUT pcf          - ������ ������������ �����.

    Return           - true - � ������ ������,
                       false - � ������ ������.
  */
  bool _ParseFile(LPWSTR pstrFile, LPDWORD pdwErrorLine, CONFIGFILE *pcf);

  /*
    ���������� ����������.

    IN OUT pvParent  - ������������ ���������� ��� NULL.
    IN OUT pcf       - ���� ������������.
    IN pstrValues    - �������� ����������, ������ ������ ���� ������� ���������� Mem, �����
                       ��������� ���������� ���� �������, ������ ���������� ������ ����� �����,
                       � �� ������ ��������� ��� �������� �� ���.
    IN dwValuesCount - ���������� ��������� � pstrValues.

    Return           - � ������ ������ ��������� �� ����������, �������� � ������������,
                       ��� NULL � ������ ������.
  */
  VAR *_AddVar(VAR *pvParent, CONFIGFILE *pcf, LPWSTR *pstrValues, DWORD dwValuesCount);

  /*
    ��������� ��������� �� �������� ��������.
    
    IN pvParent      - ������������ ���������� ��� NULL.
    IN pcf           - ���� ������������.
    IN pstrValues    - �������� ����������(����� �� �����), ������� ������ ��������� ����������.
    IN dwValuesCount - ���������� ��������� � pstrValues.
    IN bMathCase     - true - � ������ ��������, false - ��� ����� ��������.

    Return           - � ������ ������ ��������� �� ����������, ��� NULL � ������ ������.
  */
  VAR *_GetVar(VAR *pvParent, CONFIGFILE *pcf, LPWSTR *pstrValues, DWORD dwValuesCount, bool bMathCase);
  
  /*
    ������������ ��������� � ���� �� ��������.

    IN pVar - ���������� ��� ���������.
  */
  void _FreeVar(VAR *pvVar);

  /*
    �������� ����� ������������ � ������������ ������.

    IN pcf - ���� ��� ���������.
  */
  void _CloseFile(CONFIGFILE *pcf);
};
