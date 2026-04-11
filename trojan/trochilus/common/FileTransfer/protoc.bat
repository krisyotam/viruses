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
%~dp0protoc -I=%~dp0 --cpp_out=%~dp0 %~dp0FileTransfer.proto
move /Y %~dp0FileTransfer.pb.h %1
move /Y %~dp0FileTransfer.pb.cc %1