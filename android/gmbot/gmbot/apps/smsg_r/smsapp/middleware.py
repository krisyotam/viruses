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
from .models import SysUser


def app_context_processor(request):
    """
    @type request: HttpRequest
    """
    if request.user.id is None:
        return {}
    try:
        SysUser.objects.get(pk=request.user.id)
        return {'IS_SYSUSER': True, 'SITE_NAME': "GM BOT"}
    except SysUser.DoesNotExist:
        return {'IS_SYSUSER': False}
