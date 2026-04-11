/*
  name      Zeus
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
  
  //marker - proizvolny marker to indicate the end of the data.
  //within these blocks are located arbitrary data,
  arg1 arg2
  [marker

  marker]
  
  ...
*/

namespace Config1
{
  //Variable description.
  typedef struct _VAR
  {
    DWORD dwSourceLine;  //Position variable in the source file.
    LPWSTR *ppstrValues; //Arguments variable.
    DWORD dwValuesCount; //Kolichetsvo argumenov.
    
    _VAR *pvChilds;      //An array of child elements.
    DWORD dwChildsCount; //Kolichetsvo children.
  }VAR;

  //File koniguratsii.
  typedef struct
  {
    VAR *pvVars;        //Array permennyh.
    DWORD dwVarsCount;  //Kolichetsvo variables.
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

  /*    Closure of the configuration file and release memory.

    IN pcf - file for processing.
  */
  void _CloseFile(CONFIGFILE *pcf);
};
