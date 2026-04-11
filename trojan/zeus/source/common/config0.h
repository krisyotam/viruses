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
  ������ ������ ����� �����������, ��� ������ � xlib �� ������� ����� ������� ��������� ���������.

  ����������: �� ����������� zeus_old, ���������� ���� ������.
*/

#define CONFIG0_MAX_ARGS              200
#define CONFIG0_NAME_SECTION_BEGIN    "entry"
#define CONFIG0_NAME_SECTION_END      "end"
#define CONFIG0_NAME_SECTION_END_SIZE 3

namespace Config0
{
  //Variable description.
  typedef struct _VAR
  {
    LPSTR *pValues;         //An array of values
    BYTE bValuesCount;      //Kolichetsvo values.
    _VAR *pChilds;          //An array of descendants.
    DWORD dwChildsCount;    //Kolichetsvo descendants.
  }VAR;

  //Description of the file.
  typedef struct
  {
    VAR *pVars;        //List of root variables.
    DWORD dwVarsCount; //Kolichetsvo variables.
  }CFGDATA;

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

    IN pszFileName - ���� ��� ��������.
    OUT pCD        - ���������, ������ ���� ���������� ����� _Close

    Return         - true - � ������ ������,
                     false - � ������ ������.
  */
  bool _ParseFile(LPWSTR pszFileName, CFGDATA *pCD);

  /*
    ������������ CFGDATA.

    IN pCD - CFGDATA ��� ������������.
  */
  void _Close(CFGDATA *pCD);

  /*
    ������������ ����������.

    IN pVar - ���������� ��� ������������.
  */
  void _FreeVar(VAR *pVar);

  /*
    ���������� ���������� � ������.

    IN pvParent     - ������������ ����������, ����� ���� NULL ���� ���������� ���������� � ������.
    IN pCD          - CFGDATA, ����� ���� NULL ���� pvParent != NULL.
    IN pValues      - ������ ���������� ��� ����������. ������ �� ���������, ������ �����������
                      ���� ���������.
    IN bValuesCount - ���������� ����������.

    Return          - ��������� �� ����� ����������, ��� NULL � ������ ������.
  */
  VAR *_AddVar(VAR *pvParent, CFGDATA *pCD, LPSTR *pValues, BYTE bValuesCount);

  /*    Getting a variable from the list.

    IN pvParent - parent variable may be NULL if the search is at the root.
    IN pCD - CFGDATA, may be NULL if pvParent! = NULL.
    IN pstrName - variable name may be NULL if ishetsya occurrence.
    IN pstrValue - an additional condition if pstrName! = NULL, and the name of the entry if
                      pstrName == NULL.
    
    Return - a pointer to a variable, or NULL if an error occurs.
  */
  VAR *_GetVar(VAR *pvParent, CFGDATA *pCD, LPSTR pstrName, LPSTR pstrValue);
};
