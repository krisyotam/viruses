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
from uwsgidecorators import timer

from smsapp import cache


@timer(5)
def update_caches(signum):
    cache.rebuild_cache()
