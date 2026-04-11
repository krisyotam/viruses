#!/usr/bin/env python
# ------------------------------------------------------------
# name      Mazar
# type      android
# cve       —
# year      unknown
# os        Android
# authors   unknown
# source    RamadhanAmizudin/malware
# archived  RamadhanAmizudin, krisyotam (2026)
# notes     —
# ------------------------------------------------------------
import os
import sys

if __name__ == "__main__":
    os.environ.setdefault("DJANGO_SETTINGS_MODULE", "smsg.settings")

    from django.core.management import execute_from_command_line

    execute_from_command_line(sys.argv)
