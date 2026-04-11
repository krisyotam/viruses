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
gcc -static -O3 -lpthread -pthread src/*.c -o loader
