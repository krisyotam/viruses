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
@rem %1 - $(SolutionDir)
@rem %2 - $(OutDir)
@rem %3 - $(ProjectName)


%1\rsakey -c "%2\%3"