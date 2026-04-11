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
#pragma once

unsigned char* LoadImage( const char* nameFile, int& width, int& height );
bool SaveToBmp(const char* nameFile, unsigned char* image, int width, int height);

