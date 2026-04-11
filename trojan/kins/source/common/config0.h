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
  ������ ������ ����� �����������, ��� ������ � xlib �� ������� ����� ������� ��������� ���������.

  ����������: �� ����������� zeus_old, ���������� ���� ������.
*/

#define CONFIG0_MAX_ARGS              200
#define CONFIG0_NAME_SECTION_BEGIN    "entry"
#define CONFIG0_NAME_SECTION_END      "end"
#define CONFIG0_NAME_SECTION_END_SIZE 3

namespace Config0
{
  //�������� ����������.
  typedef struct _VAR
  {
    LPSTR *pValues;         //������ ��������
    BYTE bValuesCount;      //���������� ��������.
    _VAR *pChilds;          //������ ��������.
    DWORD dwChildsCount;    //���������� ��������.
  }VAR;

  //�������� �����.
  typedef struct
  {
    VAR *pVars;        //������ �������� ����������.
    DWORD dwVarsCount; //���������� ����������.
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

  /*
    ��������� ���������� �� ������.

    IN pvParent     - ������������ ����������, ����� ���� NULL ���� ����� ���������� � �����.
    IN pCD          - CFGDATA, ����� ���� NULL ���� pvParent != NULL.
    IN pstrName     - ��� ����������, ����� ���� NULL ���� ������ ���������.
    IN pstrValue    - �������������� ������� ���� pstrName != NULL, � ��� ��������� ����
                      pstrName == NULL.
    
    Return          - ��������� �� ����������, ��� NULL � ������ ������.
  */
  VAR *_GetVar(VAR *pvParent, CFGDATA *pCD, LPSTR pstrName, LPSTR pstrValue);
};
