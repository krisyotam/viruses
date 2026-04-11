#!/bin/sh
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

source /opt/rh/python27/enable
. /home/admin/virtualenv/django/bin/activate

cd /home/admin/apps/smsg_r
python manage.py check_inactive
python manage.py clean_logs
