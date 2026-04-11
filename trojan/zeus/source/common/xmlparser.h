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
/*
  ������ � XML �������, ������� MsXml, ��������� ComLibrary.

  ����������: �� ������������� �������� ���������� ������� �� ������� ���������.
*/
#pragma once

namespace XmlParser
{
  //Data on errors.
  typedef struct
  {
    int line;       //Line number.
    int errorCode;  //Error code.
    LPWSTR reason;  //The text of the error.
  }XMLERRORDATA;

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� XML �����.

    IN file   - ��� ����� ��� ��������.
    OUT error - ���������� �� ������, ��� �� ��������������. ����� ���� NULL.
                � ������ ������������� ������, ��� ��������� ������ ���� ����������� �����
                freeXmlErrorData.

    Return    - � ������ ������ ������ XML �����, ������� ������ ���� ������� ����� CloseFile.
                � ������ ������ NULL.
  */
  IXMLDOMDocument *_openFile(const LPWSTR file, XMLERRORDATA *error);

  /*
    �������� XML �����.

    IN doc - ��������� �� ������ ����� ��� ��������.
  */
  void _closeFile(IXMLDOMDocument *doc);

  /*
    ������������ ��������� XMLERRORDATA.

    IN pError - ��������� ��� ������������.
  */
  void _freeXmlErrorData(XMLERRORDATA *pError);

  /*
    ��������� ����������� ��������.

    IN root - ������� ������������� ��������� ���������� ����� node.
    IN node - ������� ��� ����� � XPath. �� ����� ���� NULL.

    Return  - ����� � ������ ������ (����� ���������� ����� _freeBstr()),
              ��� NULL � ������ ������.
  */
  BSTR _getNodeTextOfElement(IXMLDOMElement *root, const BSTR node);
  
  /*
    ��������� ����������� ��������.

    IN root - ������� ������������� ��������� ���������� ����� node.
    IN node - ������� ��� ����� � XPath. �� ����� ���� NULL.

    Return  - ����� � ������ ������ (����� ���������� ����� _freeBstr()),
              ��� NULL � ������ ������.
  */
  BSTR _getNodeTextOfNode(IXMLDOMNode *root, const BSTR node);

  /*    Exemption BSTR through SysFreeString ().

    IN OUT string - string.
  */
  void _freeBstr(BSTR string);
};
