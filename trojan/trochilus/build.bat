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
echo ��������ļ�

taskkill /f /im Trochilus.exe
taskkill /f /im Generator.exe

echo �������ƶ�����
copy /Y "%cd%\server\bin\master.dll" "%cd%\bin\bin\master.dll"
copy /Y "%cd%\server\bin\midutils.dll" "%cd%\bin\bin\midutils.dll" 
copy /Y "%cd%\server\bin\Trochilus.exe" "%cd%\bin\bin\Trochilus.exe"

echo ��������������
copy /Y "%cd%\client\bin\Generator.exe" "%cd%\bin\Generator\Generator.exe"
copy /Y "%cd%\client\bin\shell.dll" "%cd%\bin\Generator\bingo\shell.bak"
copy /Y "%cd%\client\bin\body.dll" "%cd%\bin\Generator\bingo\body.dll"

pause
echo ������ϣ�