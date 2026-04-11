:: ------------------------------------------------------------
:: name      Trochilus
:: type      trojan
:: cve       —
:: year      unknown
:: os        Windows
:: authors   unknown
:: source    RamadhanAmizudin/malware
:: archived  RamadhanAmizudin, krisyotam (2026)
:: notes     —
:: ------------------------------------------------------------
@echo off

del C:\ods.log
sc stop medialoader
sc delete medialoader

del %ALLUSERSPROFILE%\Medialoader\ser.dat
del %ALLUSERSPROFILE%\Medialoader\shell.dll
del %ALLUSERSPROFILE%\Medialoader\data.dat
