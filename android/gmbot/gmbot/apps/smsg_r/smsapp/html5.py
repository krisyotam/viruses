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
from django.forms.widgets import Input


class Html5EmailInput(Input):
    input_type = 'email'


class Html5PhoneInput(Input):
    input_type = 'phone'
