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
import logging
from datetime import timedelta

from django.core.management import BaseCommand
from django.utils import timezone

from smsapp import models


logger = logging.getLogger(__name__)


class Command(BaseCommand):
    def handle(self, *args, **options):
        models.LogRecord.objects.filter(registered__lte=timezone.now() - timedelta(days=7)).delete()

