:: ------------------------------------------------------------
:: name      Dendroid
:: type      android
:: cve       —
:: year      unknown
:: os        Android
:: authors   unknown
:: source    RamadhanAmizudin/malware
:: archived  RamadhanAmizudin, krisyotam (2026)
:: notes     —
:: ------------------------------------------------------------
@echo off
set PATH=%CD%;%PATH%;
java -jar "%~dp0\apktool.jar" %1 %2 %3 %4 %5 %6 %7 %8 %9
