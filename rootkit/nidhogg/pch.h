/*
  name      Nidhogg
  type      rootkit
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <bcrypt.h>
#include <ntstrsafe.h>
