/*
  name      Mirai
  type      botnet
  cve       —
  year      unknown
  os        Linux
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

#include "includes.h"

struct resolv_entries {
    uint8_t addrs_len;
    ipv4_t *addrs;
};

void resolv_domain_to_hostname(char *, char *);
struct resolv_entries *resolv_lookup(char *);
void resolv_entries_free(struct resolv_entries *);
