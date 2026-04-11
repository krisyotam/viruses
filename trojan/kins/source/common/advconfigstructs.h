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

namespace AdvancedConfigStructures
{
  
# pragma pack(push, 1)
  typedef struct
  {
    WORD size;              //Size of structure.
    WORD urlHostMask;       //Referrer host mask position.
    WORD urlCaptcha;        //Captcha image mask.
  }CAPTCHAENTRY;
# pragma pack(pop)

};