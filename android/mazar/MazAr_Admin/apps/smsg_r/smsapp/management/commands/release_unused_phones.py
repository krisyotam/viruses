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
import logging

from django.core.management import BaseCommand

from smsapp import commands


logger = logging.getLogger(__name__)


class Command(BaseCommand):
    def handle(self, *args, **options):
        commands.cleanup_rented_phones()
