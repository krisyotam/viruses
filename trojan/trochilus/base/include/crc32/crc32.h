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
#ifndef CRC32_INC_
#define CRC32_INC_

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

unsigned int crc32(unsigned int CRC, const void *pvBuf, unsigned int nLen);

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////

#endif  // CRC32_INC_
