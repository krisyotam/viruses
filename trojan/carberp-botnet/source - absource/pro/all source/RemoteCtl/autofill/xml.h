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
#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED

typedef struct _PARAM
{
    _PARAM *next;
    _PARAM *prev;
    PCHAR			name;
    int           dwnamehash;
    PCHAR			value;
} PARAM,*PPARAM;

typedef struct _NODE
{
    _NODE	*next;
    _NODE	*prev;
    _NODE	*child;
    _PARAM			*param;
    PCHAR			name;
    int           dwnamehash;
    PCHAR			value;
    BOOLEAN			simply;
} NODE,*PNODE;

// [in] data - ��������� �� ������ � xml-����
// [in] len - ������ data
// [out] *handle - ��������� � ������� ������� �����
ULONG XmlParse(PCHAR data, ULONG len,PNODE* handle);

// [in] node - ����� ���������� � XmlParse
void XmlFree(PNODE *pnode);

PNODE XmlDuplicateNode(PNODE node);

char *XmlGetSubNodeValueByName(PNODE node, char *name);
PNODE XmlGetSubNodeByName(PNODE node, char *name);
PNODE XmlGetNextSubNodeByName(PNODE node, char *name);
PNODE XmlEnumerateSubNodes(PNODE node, unsigned long idx);
char *XmlGetValueByParameterName(PNODE node, char *name);

void *xalloc(size_t size);
void xfree(void *mem);

#endif // XML_H_INCLUDED
