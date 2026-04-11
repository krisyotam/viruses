; ------------------------------------------------------------
; name      Win32
; type      engine
; cve       —
; year      unknown
; os        Multi
; authors   unknown
; source    vxunderground
; archived  vxunderground, krisyotam (2026)
; notes     —
; ------------------------------------------------------------

;::::::::::::::::::::::::::::::::::::::::::::::::::::::
;                Simple Morpher v.0.1                 :
;                                                     :
;                    x0man � 2008                     :
;                                                     :
;               http://www.virustech.org/             :
;::::::::::::::::::::::::::::::::::::::::::::::::::::::
;-----------------------------------------------------------------------------------------:
;                                                                                         :
;� ������ �������� ��������, ������� � ���� ����������.                                   :
;                                                                                         :
;���� ������ � ������� ��������� ������ � �����������                                     :
;����� ���������� ������� ��������:                                                       :
;                                                                                         :
;_OPCODE struct;                                                                          :
;	dwOldAddress	dd	?	; ������ ����� ���������� (�� ��������)               :
;	dwNewAddress	dd	?	; ����� ����� ����������  (����� ��������)            :
;	dwJumpAddress	dd	?	; ����� ���� ������ ��������� ������(��� �����)       :
;                                   ; (���� ���������� �� ��������)                       :
;	dwLength		dd	?	; � ������ ������� ��� ���������� �� ������������     :
;	 					; ������� ��� ��� ����������� ������ ��� ��� :)       :
;_OPCODE ends                                                                             :
;                                                                                         :
;� "���" ������ ���� ������                                                               :
;  1. ������� ����, � ��������� �� ������ ���������� ������                               :
;     ��������� �������, �������� ������ � ��������� _OPCODE.                             :
;  2. ���������� ���� ��� ������� ��������� (������ �������� ������� �� �������)          :
;  3. ���� ���������� �������� ������� ��� �������, ��� �����                             :
;     ���������� ������ ��� EIP ��� ���������� ����.                                      :
;  4. � ������������ ����������� ���� (����������� NOP)                                   :
;                                                                                         :
;������ ����                                                                              :
;  1. ���������� �� ������� � ���������� ����������                                       :
;  2. ���� ���������� �������� �������, �� ��������� �������� � ������                    :
;    ��� ������, � ������ ��� �� ����������(��� � ���������� ����).                       :
;                                                                                         :
;                                                                                         :
;����� �� ��... ��� ����� ������ �������� ������� ���!                                   :
;                                                                                         :
;������������ ����� ���������� � ���� Catchy_32, ������� ����� ������� �                  :
; http://www.wasm.ru, �� ����� ����������� � ���������� � ����������.                     :
;                                                                                         :
;GreeTz:                                                                                  :
;        Osen                                                                             :
;        izee [ EOF-Project ] http://eof-project.net/                                     :
;                                                                                         :
;  tPORt  (http://www.tport.org/)                                                         :
;  REVENGE(http://www.revenge-crew.com/)                                                  :
;  TLG    (http://tlg.astalavista.ms/)                                                    :
;  TSRh   (http://tsrh.org.ua/)                                                           :
;  TPOC   (http://vx.netlux.org/tpoc/)                                                    :
;                                                                                         :
;                                                                                         :
;  ������� �� ��������!                                                                   :
;                                                                                         :
;                                                                  10.05.2008             :
;                                                           x0man [VirusTech]             :
;                                                    http://www.virustech.org             :
;-----------------------------------------------------------------------------------------:

	.386
	.model flat, stdcall
	option casemap :none

	include \MASM32\INCLUDE\windows.inc
	include \MASM32\INCLUDE\kernel32.inc
	include \MASM32\INCLUDE\user32.inc
	
	includelib \MASM32\LIB\kernel32.lib
	includelib \MASM32\LIB\user32.lib
		
; #########################################################################

_OPCODE struct
	dwOldAddress	dd	?	; ������ ����� ���������� (�� ��������)
	dwNewAddress	dd	?	; ����� ����� ����������  (����� ��������)
	dwJumpAddress	dd	?	; ����� ���� ������ ��������� ������(��� �����)
						; (���� ���������� �� ��������)
	dwLength		dd	?	; � ������ ������� ��� ���������� �� ������������
	 					; ������� ��� ��� ����������� ������ ��� ��� :)
_OPCODE ends
	
; #########################################################################

.code

;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; ��� ��� ����� :)
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
test_code:
	@@:
	jmp @F
	mov eax, edx
	pop eax
	push eax
	call @F
	cmp eax, 0
	jne @B
	jmp @B
	add ecx, edx
	add eax, edx
	xchg edx, ecx
	call @B
	jne @F
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	db	0,0,0,0,0,0,0,0,0,0
	jne @B
	ret
	@@:
	ret
	int 3
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::




;::::::::::::::::::::::::::::::::::
; ��������� ������ ����� ����������
include Catchy32\Catchy32.inc



;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
; ������� ��� �������� �����, ���� ������ ��������� ������|
; ������: dwCurrentAddress - ��������� �� ���             |
;                                                         |
;                     00000000: 74 30  JE imm8            |
;  ��� ������� ����������� "imm8"                         |
;  � ����� ������� imm8 = 00000000 + 30 + 2 = 00000032    |
;   �.�.                                                  |
;   00000000 - ������� �����                              |
;         30 - ��������                                   |
;          2 - ������ ���������� JE imm8                  |
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
;                     00000000: 74 30  JE 00000032 --.    |
;                     00000002:                      |    |
;                                                    |    |
;                     00000032:                <-----�    |
; ��� �������� ��� "�������������" �������                |
; ��� �������������, ���������� ��������� ����            |
;                                ��� �� ������ ;-)        |
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|:::|
; IN  dwCurrentAddress : ������� ����� ��������������� ������ |
; OUT EAX              : ����� ���� ������ ���������          |
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
get_jump_address proc dwCurrentAddress : DWORD

	push ecx
	push edi

	mov edi, dwCurrentAddress
	mov al, byte ptr [edi]
	
	;:::::::::::::::::::::::::::::::::::::
	; XX imm8
	cmp al, 070h
	jl @F
	cmp al, 07Fh
	jna @_jump_imm8_
	
@@:
	;:::::::::::::::::::::::::::::::::::::
	cmp al, 0EBh
	je @_jump_uncond_imm8_
	;:::::::::::::::::::::::::::::::::::::
	; 0F XX imm32
	cmp al, 00Fh
	jne @F
	mov ah, byte ptr [edi + 1]
	cmp ah, 080h
	jl @F
	cmp ah, 08Fh
	jna @_jump_imm32_
	;:::::::::::::::::::::::::::::::::::::

@@:	
	;:::::::::::::::::::::::::::::::::::::
	; JMP imm32
	cmp al, 0E9h
	je @_jump_uncond_imm32_
	

	;:::::::::::::::::::::::::::::::::::::
	; CALL
	cmp al, 0E8h
	je @_call_imm32_
	

	;:::::::::::::::::::::::::::::::::::::
	jmp @_exit_
	;:::::::::::::::::::::::::::::::::::::
	
@_jump_imm8_:
@_jump_uncond_imm8_:
	;:::::::::::::::::::::::::::::::::::::
	; �������� ������
	movzx eax, byte ptr [edi + 1]
	mov cl, al
	test cl, 10000000b ; isNegative?
	
	jnz @_neg_1
		add edi, eax
		add edi, 2
		xchg eax, edi
		jmp @_exit_
	
	@_neg_1:
		neg al
		sub al, 2
		sub edi, eax
		xchg eax, edi
		jmp @_exit_	

	
@_jump_imm32_:
	;:::::::::::::::::::::::::::::::::::::
	; ������� ������
	mov eax, dword ptr [edi + 2]
	mov ecx, eax
	shr ecx, 24d
	test ecx, 10000000b ; isNegative?
	
	jnz @_neg_2
		add eax, edi
		add eax, 6
		jmp @_exit_
		
	@_neg_2:
		neg eax
		sub eax, 6
		sub edi, eax
		xchg eax, edi
		jmp @_exit_
	;:::::::::::::::::::::::::::::::::::::
	

		
@_jump_uncond_imm32_:
@_call_imm32_:
	;:::::::::::::::::::::::::::::::::::::
	; JMP imm32 & CALL imm32
	mov eax, dword ptr [edi + 1]
	mov ecx, eax
	shr ecx, 24d
	test ecx, 10000000b ; isNegative?
	
	jnz @_neg_3
		add edi, eax
		add edi, 5
		xchg eax, edi
		jmp @_exit_
		
	@_neg_3:
		neg eax
		sub eax, 5
		sub edi, eax
		xchg eax, edi
	;///////////////////////////////////////
@_exit_:
	
	pop edi
	pop ecx

	ret
get_jump_address endp


;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
; ������� ��� ������ � ������� �������� ����������             |
; ������ ������ ��� ������....                                 |
;                                                              |
; IN  dwAddress - ����� ������                                 |
; IN  pOpcodes  - ��������� �� ������ � ���������� �������     |
; OUT EAX       - ����� ����� ������...                        |
;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
get_new_jump_address proc dwAddress:DWORD, pOpcodes : DWORD
	push ecx
	
	assume ecx : ptr _OPCODE
	mov ecx, pOpcodes
	mov eax, dwAddress
	
	@@:
	cmp [ecx].dwOldAddress, eax
	je @F
	add ecx, sizeof _OPCODE
	cmp [ecx].dwOldAddress, 0
	jne @B
	xor eax, eax
	@@:
	mov eax, [ecx].dwNewAddress
	
	pop ecx
	ret
get_new_jump_address endp


;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
; ������� ���������� ����������� ���, ����������� NOP            |
; �����! ��� ������ ������������� ������� 0CCh                    |
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
; IN  dwCodeAddress  - ����� ���� ��� ��������                    |
; IN  dwOutputBuffer - ����� ���� ����� ������ ������������� ��� |
; OUT EAX            - ������ �������������� ����                 |
;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|
MorphCode proc dwCodeAddress	: DWORD, dwOutputBuffer : DWORD
local pOpcodes			: DWORD
local dwTotalCodeSize		: DWORD

	;::::::::::::::::::::::::::::::::::::::::::::::::::
	; pOpcodes       - ��������� �� �������� ������� ::
	; dwOutputBuffer - ������������� ���             ::
	;::::::::::::::::::::::::::::::::::::::::::::::::::
	
	;::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	; ������������� ������ ��� ������� � ��������� ����������
	invoke VirtualAlloc, NULL, 1024*1024, MEM_COMMIT + MEM_RESERVE, PAGE_READWRITE
	mov pOpcodes, eax
	
	;::::::::::::::::::::::::::::::::::::::::::::
	; ������� ���������� � ������� ����� ��������
	; ����� ������ ����
	push 0
	pop dwTotalCodeSize

	;:::::::::::::::::::::::::::::::::::::::::
	; ��� ������������
	assume ecx : ptr _OPCODE
	mov esi, dwCodeAddress	; Code Address
	mov edi, dwOutputBuffer	; New Code Address
	mov ecx, pOpcodes		; array of _OPCODES
	;::::::::::::::::::::::::::::::::::::::::	
	

	
;::::::::::::::::::::::::::::::::::::::::
; ������ ���� :::::::::::::::::::::::::::
;::::::::::::::::::::::::::::::::::::::::

	;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	; ������ ��� ������ ���������� � ����� ����� ��� � EDI
	mov [ecx].dwNewAddress, edi

	;::::::::::::::::::::::::::::::::::::
	; �������� ����
	; Loop 1
	@_loop_1:

	;::::::::::::::::::::::::::::::::::::
	; ������ ������ � ����������
	; IN  ESI == Current Code Offset
	; OUT EAX == Instruction Length
	call c_Catchy

	;:::::::::::::::::::::::::::::::::::::
	; ������ ������ � ������ � ����������
	mov [ecx].dwOldAddress, esi
	mov [ecx].dwLength, eax

	;::::::::::::::::::::::::::::::::::::
	; �������� �������� ������ ������ �� �������	
	; ��� ���������� �� ������� ��������� 00Fh
	; � ������ � +10h � �������� ������ ������
	; ������:
	;    ���� :00000000:     74 30
	;                    0F +10 30 00 00 00
	;    �����:00000000: 0F  84 30 00 00 00
	cmp byte ptr [esi], 070h
	jl @F
	cmp byte ptr [esi], 07Fh
	ja @F
		push eax
		mov al, 00Fh
		stosb
		
		movzx eax, byte ptr [esi]
		add eax, 10h
		stosd	
		
		;:::::::::::::::::::::::::::::::::::::::
		; ���������� ����� ���� ��������� ������
		push esi
		call get_jump_address
		
		;::::::::::::::::::::::::
		; ������ ������ � ������
		mov [ecx].dwJumpAddress, eax
		
		pop eax
		
		;::::::::::::::::::::::::::::::::::::
		; �������� � ������ ������� ����
		; ������ 00Fh XXh imm32, �.�. ����� 6
		; ��� XX � [80h..8Fh]
		add dwTotalCodeSize, 6
	;::::::::::::::::::::::::::::::::::::
	; ��������� ������� ���������� ������
	; ��������� � ��������� ����������
	jmp @_next_inst_	
	
	@@:
	;::::::::::::::::::::::::::::::::::::
	; ������...
	; JMP imm8 -> JMP imm32
	; ������
	; ���� : 00000000: EB 33
	; �����: 00000000: E9 33 00 00 00
	cmp byte ptr [esi], 0EBh
	jne @F
		push eax
		
		mov al, 0E9h
		stosb
		xor eax, eax
		stosd

		;:::::::::::::::::::::::::::::::::::::::
		; ���������� ����� ���� ��������� ������
		push esi
		call get_jump_address
		
		;::::::::::::::::::::::::
		; ������ ������ � ������
		mov [ecx].dwJumpAddress, eax

		pop eax		
		;:::::::::::::::::::::::::::::::
		; �������� � ������ ������� ����
		; ������ E9 imm32, �.�. ����� 5
		add dwTotalCodeSize, 5		
	jmp @_next_inst_
	;::::::::::::::::::::::::::::::::::::
	
	
	@@:
	;::::::::::::::::::::::::::::::::::::
	; �������� �� JMP imm32
	cmp byte ptr [esi], 0E9h
	jne @F

	push eax
	push esi
	call get_jump_address
	mov [ecx].dwJumpAddress, eax
	pop eax
	jmp @_replace_instr_
	;::::::::::::::::::::::::::::::::::::
	
	@@:	
	;::::::::::::::::::::::::::::::::::::
	; �������� �� CALL
	cmp byte ptr [esi], 0E8h
	jne @F
	
	push eax
	push esi
	call get_jump_address
	mov [ecx].dwJumpAddress, eax
	pop eax
	jmp @_replace_instr_
	;::::::::::::::::::::::::::::::::::::
	
	
	@@:
	;::::::::::::::::::::::::::::::::::::
	; 00Fh XX imm32
	cmp byte ptr [esi], 00Fh
	jne @F
	cmp byte ptr [esi + 1], 080h
	jl @F
	cmp byte ptr [esi + 1], 08Fh
	ja @F
		push eax
		push esi
		call get_jump_address
		mov [ecx].dwJumpAddress, eax
		pop eax		
	;::::::::::::::::::::::::::::::::::::

	@@:

@_replace_instr_:
	;::::::::::::::::::::::::::::::::::::::::::
	; ��������� ���������� � ����� ������.
	; ���� ��� ����������� � ��� ������
	; ���� �� �� ������ ������������ ����������
	push esi
	push ecx
	
	mov ecx, eax
	rep movsb
	
	pop ecx
	pop esi
	
	; ������� � ������ ������� ����
	; ������ ������� ����������
	add dwTotalCodeSize, eax

	;::::::::::::::::::::::::::::::::::::
	; ���� ������� ���� �� �������� ������� ���������� �� ����
@_next_inst_:
	;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	; ���������� ��� ����������� NOP
	; ��� ����� ���������� ���
	; ������ "�������" ������������
	; ����:
	;--------------
	;      push eax
	;      pop  eax
	;--------------
	;      mov  eax, eax
	;--------------
	;      � �.�.
	push eax
	mov al, 90h
	stosb
	pop eax
	
	;:::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	; �������� ����� ������ ���� �� 1 (������ ���������� NOP)
	; ��� �� ���� ������ ��������� ���� "������" ���
	; ����� ����� ��������� � dwTotalCodeSize ��� ����� ������(!)
	add dwTotalCodeSize, 1
	
	;::::::::::::::::::::::::::::::::::::
	; ������� � ��������� ����������
	add esi, eax
	
	;::::::::::::::::::::::::::::::::::::
	; ������� � ���������� ��������
	; � ����� ������� � ���������� �������
	add ecx, sizeof _OPCODE
	
	;::::::::::::::::::::::::::::::::::::
	; ������� ����� ����� � ��������� ����������
	mov [ecx].dwNewAddress, edi
	

	;::::::::::::::::::::::::::::::::::::
	; ������� �� int 3
	; ��� ������ ��� ��� ����������....
	; � ������������� ��� ��� ������ ��� ������.
	cmp byte ptr [esi], 0CCh
	jne @_loop_1
	; End Loop 1
	;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

	;::::::::::::::::::::::::::::::::::::
	; ������ ��� ������ � ���������� ����������
	mov [ecx].dwOldAddress, 0




;::::::::::::::::::::::::::::::::::::::::
; ������ ���� :::::::::::::::::::::::::::
;::::::::::::::::::::::::::::::::::::::::
	mov ecx, pOpcodes
	@_loop_2:
	;::::::::::::::::::::::::::::::::::::::::
	; ���� ���������� �������� ������� ��� �������
	; �� dwJumpAddress != 0 (!)
	cmp [ecx].dwJumpAddress, 0
	je @F
	;::::::::::::::::::::::::::::::::::::::::
	; ������� ����� ����� ����� ���� ������
	; ��������� ������ ��� �����
	push pOpcodes
	push [ecx].dwJumpAddress
	call get_new_jump_address
	
	;::::::::::::::::::::::::::::::::::::::::
	; �������� ��������� �� ����.
	; �� ���� ��� �������� ���� �� ������
	; ��� EAX (���� ���� ��� �� ������ dwCodeAddress ��� ����������)
	; ������� �� ����� ��������� ����
	; � ��� 2 ������� ������, �� ��� ����������
	; ������ �� �������� :)))
	cmp eax, 0
	je @F
	;::::::::::::::::::::::::::::::::::::::::
	
	;::::::::::::::::::::::::::::::::
	; �������� ����� ����� ����������
	; ����� �������� �� �����
	mov edx, [ecx].dwNewAddress
	;:::::::::::::::::::::::::
	; ������� �������� ������
	; 00Fh XXh imm32
	cmp byte ptr [edx], 00Fh
	je @_0F_XX_imm32
	;:::::::::::::::::::::::::::
	; ������� ����������� ������
	; JMP imm32
	cmp byte ptr [edx], 0E9h
	je @_XXX_imm32_
	;::::::::::::::::::::::
	; ����� (CALL imm32)
	cmp byte ptr [edx], 0E8h
	je @_XXX_imm32_
	;::::::::::::::::::::::
	jmp @F

	;::::::::::::::::::::::::::::::::::::::
	; 00Fh XXh imm32
	; ��� ����� �������� ������������ imm32
	; ��� ��������� �� �������� [����� ������ + 2]
	; ������:
	;   00Fh 84 imm32   ; JE  imm32
	;   00Fh 85 imm32   ; JNE imm32
@_0F_XX_imm32:
	cmp eax, [ecx].dwNewAddress
	jle @_less_or_equal_1
		push eax
		sub eax, [ecx].dwNewAddress
		sub eax, 6
		mov edx, [ecx].dwNewAddress
		mov dword ptr [edx + 2], eax
		pop eax
		jmp @F

	@_less_or_equal_1:
		push eax
		mov edx, [ecx].dwNewAddress
		sub edx, eax
		neg edx
		sub edx, 6
		mov eax, [ecx].dwNewAddress
		mov dword ptr [eax + 2], edx
		pop eax
		jmp @F
	
	;:::::::::::::::::::::::::::::::::::::::::::::
	; �������� imm32 � ����������� JMP � CALL
	; ���� � ����, ������������� ��� ���������
	; ������ ������ � ��� ����� ������� �����
	; imm32 ��������� �� �������� [����� ������ + 1]
	; ������:
	;   E9 imm32
	;   E8 imm32
	; :)
@_XXX_imm32_:
	cmp eax, [ecx].dwNewAddress
	jle @_less_or_equal_2
		push eax
		sub eax, [ecx].dwNewAddress
		sub eax, 5
		mov edx, [ecx].dwNewAddress
		mov dword ptr [edx + 1], eax
		pop eax
		jmp @F

	@_less_or_equal_2:
		push eax
		mov edx, [ecx].dwNewAddress
		sub edx, eax
		neg edx
		sub edx, 5
		mov eax, [ecx].dwNewAddress
		mov dword ptr [eax + 1], edx
		pop eax
		jmp @F
	;::::::::::::::::::::::::::::::::::::::::
	

	@@:	
	;::::::::::::::::::::::::::::::
	; ������� � ��������� ��������
	; ���������� ������ :)
	add ecx, sizeof _OPCODE

	;:::::::::::::::::::::::::::::::::::::
	; ��������� �� ��� ��� ����
	; �� ��������� �� ����� �������
	; �� ��� ��������� ���� � dwOldAddress
	cmp [ecx].dwOldAddress, 0
	jne @_loop_2

	;::::::::::::::::::::::::::::::::::::::::
	; ��������� ������ ��� ��������
	invoke VirtualFree, pOpcodes, NULL, MEM_RELEASE
	
	@_exit_:

	mov eax, dwTotalCodeSize
	ret
MorphCode endp

.data
	; ����� ���� ������ ������������� ���
	dwOutputBuffer		dd	0
	
	; ������ ������
	dwOutputBufferSize	dd	0
	
	; ���-�� ���� ���������� � ����
	dwBytesWritten		dd	0
	
	; ��� ������� � ������� ������� ������������� ���
	szFileName			db	'morphed_code_dump_raw.bin',0
	
	; ����� ��� MessageBoxA
	szComplete			db	'Complete! :)', 0
.code

start:

	;:::::::::::::::::::::::::::::::::::::::::::::::::::::
	; ������������� ������ ��� �������������� ����
	; ������ ������ ��������� ��������� ����
	; �� ������� �� ���-�� ���� ��� ����������� �������
	invoke VirtualAlloc, NULL, 1024*1024, MEM_COMMIT + MEM_RESERVE, PAGE_READWRITE
	mov dwOutputBuffer, eax

	;::::::::::::::::
	; ������ ���.....
	invoke MorphCode, offset test_code, dwOutputBuffer
	mov dwOutputBufferSize, eax
	
	;::::::::::::::::::::::::::::::::
	; ������ ������������� ��� � ����
	invoke CreateFile, offset szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0
	push eax
	invoke WriteFile, eax, dwOutputBuffer, dwOutputBufferSize, addr dwBytesWritten, NULL
	call CloseHandle
	
	;:::::::::::::::::
	; ��������� ������
	invoke VirtualFree, dwOutputBuffer, NULL, MEM_RELEASE
	
	;:::::::::::::::::
	; ������� :)
	invoke MessageBoxA, 0, offset szComplete, 0, MB_ICONINFORMATION

	;:::::::::::::::::
	; �����)
	xor eax, eax
	ret
end start

; #########################################################################
