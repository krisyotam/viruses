; ------------------------------------------------------------
; name      Disassembler
; type      research
; cve       —
; year      unknown
; os        Multi
; authors   unknown
; source    vxunderground
; archived  vxunderground, krisyotam (2026)
; notes     —
; ------------------------------------------------------------
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                  ;
;                                                                                  ;
;                                                                      ###         ;
;                                                                        ###       ;
;             ###        ####################################################      ;
;             ###        ####################################################      ;
;             ###                      	 ###                             ###       ;
;             ###             ###    	 ###           #########       ###         ;
;             ###             ###    	 ###          ###########                  ;
;             ###                    	 ###         ##         ##                 ;
;             ###             ###    	 ###         ##         ##                 ;
;             ###             ###    	 ###         ##         ##                 ;
;             ###      ###    ###    	 ###         ##         ##                 ;
;             ###      ###    ###    	 ###         ##         ##                 ;
;             ############    ###    	 ###          ###########                  ;
;       ################################################################	   ;            
;                                                                                  ;
;                                                                                  ;                                                                          
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                  ;
;             		Advanced Length dIsassembler moTOr:)                       ;
;                                                                                  ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                  ; 
;                                   ����� 2.1					   ;                                                
;                                                                                  ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;�㭪�� _LiTo_                                                                    ;
;�����ᥬ���஢���� ��設��� �������						   ;
;��।������ ����� ��設��� �������                                                ;
;�室:                                                                             ;
;esi - ���� ࠧ��ࠥ��� ��設��� �������                                          ;
;edi - 㪠��⥫� �� ��室��� �������� (��� ����) (������� �� INSTR:)		   ;
;��室:                                                                            ;
;� eax - ����� ��設��� �������.                                                   ;
;����⪨:                                                                          ;
;(x) ��室��� ������� (��� ����) ���������� � ����� �����ᥬ���஢����      ;
;������樨 � ������ �।�⠢���� ᮡ�� ᫥���饥:                                 ;
;                                                                                  ;
;	INSTR1	struct                                                             ;
;	(+ 00) len_com		db 00h 	      ;	- ����� �������;                   ;
;	(+ 01) flags		dd 00h 	      ;	- ���⠢����� 䫠��               ;
;	(+ 05) seg		db 00h 	      ;	- ᥣ���� (�᫨ ����);             ;
;	(+ 06) repx		db 00h 	      ;	- ��䨪� (0F2h/0F3h) (�᫨ ����); ;
;	(+ 07) len_offset	db 00h 	      ;	- ࠧ��� ᬥ饭��;                 ;
;	(+ 08) len_operand	db 00h 	      ;	- ࠧ��� ���࠭��;                 ;
;	(+ 09) opcode 		db 00h 	      ;	- ����� (�᫨ �����=0Fh, ⮣��     ;
;					      ;	  � ��࠭���� 2-�� �����, �   ;
;					      ;	  ��⠭���������� 䫠� B_OPCODE2); ;
;	(+ 10) modrm		db 00h 	      ;	- ���� MODRM (⠪��, �᫨ ����)    ;
;	(+ 11) sib		db 00h 	      ;	- ���� SIB                         ;
;	(+ 12) offset		db 8 dup (00h);	- ᬥ饭�� ������樨              ;
;	(+ 20) operand		db 8 dup (00h);	- ���࠭�  ������樨              ;
;	INSTR1	ends                                                               ;
;                                                                                  ;
;(�) ���������� (����) ⮫쪮 general purpose & fpu instructions                   ;
;    (��⠫�� - � ⮯��:)!                                                       ;
;(�) ��� �஢�ન �� ���ᨬ����� ����� ������樨 (15 ����) (���७)              ;
;(�) ��� ����஥�� �� ⠡��窨:                                                   ;
;	����� ������: ⠪ ��� � �⮬ ����ᬥ �ᯮ������� 䫠�� � �᫮��    	   ;
;	������祭��� <=8, � ��� ������ 䫠�� �����筮 ���� � �������� ����    ;
;	(���ᨬ��쭮� �᫮ =8 (B_PREFIX6X) - � ����筮� �।�⠢����� =1000b).    ;
;	���� ��, ���� �㯮 � ���� ���� ����娢��� 2 䫠�� - ��� � ��. �����    ;
;	��ࠧ��, ������ ⠡��窠 � 256 ���� �१����� �� 128.                      ;                            
;(�) ��� 32-��⭮�� �ᯮ��塞��� ����.						   ;
;(�) �� ���, ����� ��䨣 ᠬ � �������� ��⠫�� ������� � ��直� ⠬         ;
;    �஢�ન.                                                                     ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
                                                                                   ;
                                                                                   ;
                                                                                   ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;				����:                                              ;
;(+) ����������ᨬ����								   ;
;(+) 㯠������� ⠡��窨							   ;                                           
;                                                                                  ;
;(-) ���୮ ��������� ���� ������樨						   ;                                                                                                                                                   
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
                                                                                   ;
                                                                                   ;
                                                                                   ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;				�������������:                                     ;
;1)������祭��:                                                                    ;
;	lito.asm                                                                   ;
;2)�맮�:(�ਬ��)                                                                  ;
;	lea	esi,XXXXXXXXh	;���� �������, ��� ����� ���� 㧭���		   ;              
;	lea	edi,XXXXXXXXh	;lea edi,INSTR1					   ;
;	call	LiTo                                                               ;                                                                                                                  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
                                                                                   

									;m1x
							           ;pr0mix@mail.ru	

_LiTo_:
	pushad
	call	_delta_lito_
;===================================================================================

;��ப� ��䨪ᮢ
pfx:
db 2Eh,36h,3Eh,26h,64h,65h,0F2h,0F3h,0F0h,66h,67h

SizePfx		equ $-pfx					;����� pfx

;===================================================================================

;⠡��� 䫠��� ��� ���������� �������
TableFlags1:

;  01  23  45  67  89  AB  CD  EF
db 11h,11h,28h,00h,11h,11h,28h,00h	;00
db 11h,11h,28h,00h,11h,11h,28h,00h      ;01
db 11h,11h,28h,00h,11h,11h,28h,00h      ;02
db 11h,11h,28h,00h,11h,11h,28h,00h      ;03
db 00h,00h,00h,00h,00h,00h,00h,00h	;04
db 00h,00h,00h,00h,00h,00h,00h,00h	;05
db 00h,11h,00h,00h,89h,23h,00h,00h	;06
db 22h,22h,22h,22h,22h,22h,22h,22h	;07
db 39h,33h,11h,11h,11h,11h,11h,11h	;08
db 00h,00h,00h,00h,00h,0C0h,00h,00h	;09
db 88h,88h,00h,00h,28h,00h,00h,00h	;0A
db 22h,22h,22h,22h,88h,88h,88h,88h	;0B
db 33h,40h,11h,39h,60h,40h,02h,00h	;0C
db 11h,11h,22h,00h,11h,11h,11h,11h	;0D
db 22h,22h,22h,22h,88h,0C2h,00h,00h	;0E
db 00h,00h,00h,11h,00h,00h,00h,11h	;0F


;===================================================================================

;⠡��� 䫠��� ��� ���塠���� �������
TableFlags2:

;  01  23  45  67  89  AB  CD  EF
db 11h,11h,00h,00h,00h,00h,01h,00h	;00
db 00h,00h,00h,00h,00h,00h,00h,01h	;01
db 11h,11h,00h,00h,00h,00h,00h,00h	;02
db 00h,00h,00h,00h,00h,00h,00h,00h	;03
db 11h,11h,11h,11h,11h,11h,11h,11h	;04
db 00h,00h,00h,00h,00h,00h,00h,00h	;05
db 00h,00h,00h,00h,00h,00h,00h,00h	;06
db 00h,00h,00h,00h,00h,00h,00h,00h	;07
db 88h,88h,88h,88h,88h,88h,88h,88h	;08
db 11h,11h,11h,11h,11h,11h,11h,11h	;09
db 00h,01h,31h,00h,00h,01h,31h,01h	;0A
db 11h,11h,11h,11h,00h,31h,11h,11h	;0B
db 11h,00h,00h,01h,00h,00h,00h,00h	;0C
db 00h,00h,00h,00h,00h,00h,00h,00h	;0D
db 00h,00h,00h,00h,00h,00h,00h,00h	;0E
db 00h,00h,00h,00h,00h,00h,00h,00h	;0F   
;===================================================================================

SizeTbl		equ $-pfx
;===================================================================================
;䫠��
;-----------------------------------------------------------------------------------
B_NONE		equ	00h		;xex
B_MODRM		equ	01h             ;present byte MODRM
B_DATA8		equ	02h             ;present imm8,rel8, etc
B_DATA16	equ	04h             ;present imm16,rel16, etc
B_PREFIX6X	equ	08h             ;present imm16/imm32 (� ����ᨬ��� �� ������ ��䨪� 0x66 (0x67 ��� ������� 0xA0-0xA3))
B_SEG		equ	10h             ;present segment (�ਬ��: 0x2e,0x3E, etc)
B_PFX66		equ	20h             ;present byte 0x66
B_PFX67		equ	40h             ;present byte 0x67
B_LOCK		equ	80h             ;present byte LOCK (0xF0)
B_REP		equ	100h            ;present byte rep[e/ne]
B_OPCODE2	equ	200h            ;present second opcode (first opcode=0x0F)
B_SIB		equ	400h		;present byte SIB
B_RELX		equ	800h		;present jxx/jmp/call (rel8,rel16,rel32)
;===================================================================================

_delta_lito_:
	pop	ebp
	cld
	xor	eax,eax
	xor	ebx,ebx
	cdq				        		;� edx: dl(0/1) - ���/���� ��䨪� 0x66
	                                                        ;	dh(0/1) - ���/���� ��䨪� 0x67
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxBEG ���� ��䨪ᮢxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
_nextpfx_:					
	lodsb                                			;����砥� ��।��� ���� �������
	push	edi
	lea	edi,[ebp+(pfx-_delta_lito_+SizeTbl)]            ;� edi - ���� ��ப� ��䨪ᮢ
	db	6Ah,SizePfx
	pop	ecx
	repne	scasb                                           ;���� �� � ࠧ��ࠥ��� ������� ��䨪��?
	pop	edi
	jne	_endpfx_                                        ;���? - �� ��室
	cmp	ecx,5
	jl	_lock_
	or	bl,B_SEG
	mov	byte ptr [edi+05h],al				;seg
_lock_:
	cmp	al,0F0h
	jne	_rep_
	or	bl,B_LOCK
_rep_:
	mov	ch,al
	and	ch,0FEh
	cmp	ch,0F2h
	jne	_66_
	or	bx,B_REP
	mov	byte ptr [edi+06h],al				;rep
_66_:
	cmp	al,66h                                          ;���� ᬮ�ਬ, �� 0x66?
	jne	_67_
	mov	dl,1
	or	bl,B_PFX66
_67_:
	cmp	al,67h                                          ;����, �� 0x67?
	jnz	_nextpfx_                                       ;�᫨ ���, � �饬 ��㣨� ��䨪��
	mov	dh,1
	or	bl,B_PFX67
	jmp	_nextpfx_                                       ;�த������ ����
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxEND ���� ��䨪ᮢxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
_endpfx_:
_search_jxx_call_jmp_:
	mov	ch,al
	and	ch,0FEh
	cmp	ch,0E8h
	je	_jxxok_		
	mov	ch,al
	and	ch,11110000b
	cmp	ch,70h
	je	_jxxok_
	cmp	al,0EBh
	je	_jxxok_
	cmp	al,0Fh                                        	;����� ��⮨� �� 2-� ����?
	jne	_opcode_
	lodsb                                                   ;�᫨ ��, � ��६ 2-�� ���� ������
	mov	cl,80h                                          ;� 㢥��稢��� cl=80h
	or	bx,B_OPCODE2
	mov	ch,al
	and	ch,11110000b
	cmp	ch,80h
	jne	_opcode_
_jxxok_:
	or	bx,B_RELX

;-----------------------------------------------------------------------------------
_opcode_:
	xor	ch,ch
        mov	byte ptr [edi+09h],al				;save first opcode
	lea	ebp,[ebp+ecx+(TableFlags1-_delta_lito_+SizeTbl)];� edi - ���� �㦭�� ⠡���� 䫠���(��-�)
	cmp	al,0A0h                                         ;�᫨ �����>=0xA0 � �����<=A3,
	jl	_01_;jb                                            ;
	cmp	al,0A3h
	jg	_01_
	test	cl,cl
	jne	_01_;je                                 	;� dl=dh
	mov	dl,dh						;mov	dl,dh
;-----------------------------------------------------------------------------------
_01_:
	push	eax
	shr	eax,1
	mov	cl,byte ptr [ebp+eax]				;� cl - 䫠�� �������
	jc	_noCF_
	shr	cl,4
_noCF_:
        and	cl,0Fh
	xor	ebp,ebp				        	;� ebp - �㤥� �࠭����� ����� ᬥ饭��(offset)

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxBEG ࠧ��� MODRMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

        or	ecx,ebx
	pop	ebx						;bl=opcode
	test	cl,B_MODRM                                      ;��������� �� ���� modrm?
	je	_endmodrm_                                      ;���? �� ��室
	lodsb                 	  				;al=modrm
	mov	byte ptr [edi+10],al				;MODRM
	mov	ah,al
;-----------------------------------------------------------------------------------
	shr	ah,6   						;ah=mod
;-----------------------------------------------------------------------------------	
	test	al,38h    					;����� ᬮ�ਬ, ࠢ�� �� ���� reg==0?
	jne	_03_
	sub	bl,0F6h                                         ;�᫨ ��, � ᬮ�ਬ �� �����:
	jne	_02_                                            ;ࠢ�� �� �� 0xF6 ��� 0xF7(test)?
	or	cl,B_DATA8                                      ;�᫨ ��, � ��⠭�������� �㦭� 䫠�
_02_:
	dec	ebx
	jne	_03_
	or	cl,B_PREFIX6X
;-----------------------------------------------------------------------------------	
_03_:
	and	al,07h
	xor	ebx,ebx                                         ;bl �⢥砥� �� ������⢨� ���� sib
	mov	bh,ah                                           ;bh=mod
	cmp	dh,1                                      	;���� �� � ࠧ��ࠥ��� ������� ��䨪� 0x67?                            		
	je	_mod00_                                         ;�᫨ ��, � ���᪠������
	cmp	al,4                                            ;���� �஢��塞,ࠢ�� �� ���� rm==4?
	jne	_mod00_
	inc	ebx                                             ;�᫨ ��, � �������� ���� sib
;-----------------------------------------------------------------------------------
_mod00_:
	test	ah,ah                                           ;���� mod==0?
	jne	_mod01_
	dec	dh                                      	;ᮤ�ন� �� ������� 0x67?						
	jne	_nop67_	                                        ;���? ���᪠������
	cmp	al,6                                            ;�᫨ ��, � rm==6?
	jne	_sib_
	inc	ebp                                             ;�᫨ ��, � ����� ᬥ饭��=2(16 bit)
	inc	ebp
_nop67_:
	cmp	al,5                                            ;����, rm==5?
	jne	_sib_
	add	ebp,4                                           ;�᫨ ��, � ����� �����=4 (32 bit)
	jmp	_sib_                                           ;���� �����
;-----------------------------------------------------------------------------------		
_mod01_:		                                        ;mod==1?
	dec	ah                                              
	jne	_mod02_
	inc	ebp                                             ;��? ⮣�� ebp=1
	jmp	_sib_		
;-----------------------------------------------------------------------------------	                        
_mod02_:                                    			;mod==2?
	dec	ah
	jne	_mod03_
	inc	ebp             				;ebp=2
	inc	ebp
	dec	dh                                      	;�᫨ ���� ��䨪� 0x67, ���᪠������ �����
	je	_sib_
	inc	ebp                                             ;� ebp+=2
	inc	ebp          	
	inc	ebx
;-----------------------------------------------------------------------------------
_mod03_:                                                        ;mod==3?
        dec	bl                                              ;�᫨ ��, ⮣�� sib'� �筮 ���!
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxEND ࠧ��� MODRMxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxBEG ����祭�� SIBxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
_sib_:
	dec	bl                                              ;���� �� ���� sib?
	jne	_endmodrm_
	or	cx,B_SIB
	lodsb                                                   ;�᫨ ��, � � al ⥯��� ����� sib(al=sib) 
	mov	byte ptr [edi+11],al				;SIB
	and	al,7                                            ;�����, 
	cmp	al,5                                            ;al==5?
	jne	_endmodrm_
	test	bh,bh                                           ;�᫨ ��, � ᬮ�ਬ, ���� mod==0?
	jne	_endmodrm_
	push	4                                               ;�᫨ ��, � ���� 4-���⮢�� ᬥ饭��
	pop	ebp
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxEND ����祭�� SIBxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxBEG 䫠��xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
_endmodrm_:
        xor	ebx,ebx
	test	cl,B_DATA8                                  	;���� �� �������⮢�� ᬥ饭��?
	je	_nf1_
	inc	ebx
_nf1_:
	test	cl,B_DATA16                                     ;���� �� ���塠�⮢�� ᬥ饭��?
	je	_nf2_
	inc	ebx
	inc	ebx
_nf2_:
	test	cl,B_PREFIX6X                                   ;���� �� � ������� �����।�⢥���� ���祭��?
	je	_endflag_
	dec	dl					;���� �� 0x66(0x67 ��� [0xA0,0xA3]) � ࠧ��ࠥ��� �������?                                              
	je	_okp66_
	inc	ebx
	inc	ebx
_okp66_:
        inc	ebx
        inc	ebx
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxEND 䫠��xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
_endflag_:
        push	ecx
        push	edi
        mov	ecx,ebp
        add	edi,12
        rep	movsb	
        sub	edi,ebp
        add	edi,8
        mov	ecx,ebx
        rep	movsb
        pop	edi
	pop	dword ptr [edi+1]
	sub	esi,dword ptr [esp+4];eax
	xchg	esi,eax
	mov	byte ptr [edi+0],al
	mov	dword ptr [esp+7*4],eax                         ;��࠭塞 ࠧ��� � ���
	xchg	ebp,eax
	mov	byte ptr [edi+7],al
	mov	byte ptr [edi+8],bl	
	popad
	ret	                                               	;��室��:)
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� �㭪樨 _LiTo_                                                              ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


SizeOfLiTo	equ $-_LiTo_					;ࠧ��� �㭪樨 _LiTo_
