/*
  name      FlexiSpy
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef	__EXTEND_GLOBALS_H__
#define	__EXTEND_GLOBALS_H__

#include <e32std.h>

#define	MAX_LIST_ITEM_TEXT_LENGTH	48
_LIT(KListItemPrefix,"\t");

#ifdef	__SDK_S60_3RD__
_LIT(KMifFileName,"menulist_res.mif");
#endif

#endif