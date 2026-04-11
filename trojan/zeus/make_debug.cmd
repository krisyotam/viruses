:: ------------------------------------------------------------
:: name      Zeus
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

cd make
"..\bin\php\php.exe" -q make.php -b debug debug
cd ..
