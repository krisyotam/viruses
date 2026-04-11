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

#include "..\misc\types.h"
#include "..\misc\util.h"
#include "..\misc\debug.h"
#include "..\misc\ocr.h"

//����������� ���� �������� � ������� bmp
void ParseImage( const char* nameFile );
