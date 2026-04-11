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
;      xxxxxxxxxxx      xxxxxxxx     xxxx    xxxx     xxxxxxxxxx          xxxxxxxx      xxxxxxxxx        ;  
;      xxxxxxxxxxxx    xxxx  xxxx    xxxx    xxxx    xxxxxxxxxxx         xxxxxxxxxx    xxxxxxxxxxx       ; 
;      xxxx    xxxx   xxxx    xxxx   xxxxx   xxxx   xxxx    xxxx         xxx    xxxx   xxx    xxxx       ;    
;      xxxx    xxxx   xxxx    xxxx   xxxxxx  xxxx   xxxx                        xxxx          xxxx       ;   
;      xxxx    xxxx   xxxx    xxxx   xxxxxxx xxxx   xxxx                   xxxxxxxx     xxxxxxxxxx       ;   
;      xxxxxxxxxxx    xxxx xx xxxx   xxxx xxxxxxx   xxxx                   xxxxxxxx    xxxxxxxxxx        ;  
;      xxxxxxxxxxxx   xxxx xx xxxx   xxxx  xxxxxx   xxxx   xxxxx                xxxx   xxxx              ;     
;      xxxx    xxxx   xxxx    xxxx   xxxx   xxxxx   xxxx    xxxx                xxxx   xxxx    xxx       ;   
;      xxxx    xxxx   xxxx    xxxx   xxxx    xxxx    xxxxxxxxxxx         xxxxxxxxxx    xxxxxxxxxxx       ;   
;      xxxx    xxxx   xxxx    xxxx   xxxx    xxxx     xxxxxxxxxx         xxxxxxxxx     xxxxxxxxxxx       ;   
;                                                                                                        ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                               RAndom Numbers Generator                                                 ; 
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                       :)!                                                              ;
;                                                                                                        ; 
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                   ������� RANG32                                                       ;
;                             ��������� ��������� ����� (���)                                            ;
;                                                                                                        ;
;                                                                                                        ;
;����:                                                                                                   ;
;1 �������� - ����� (N). ����� ���������� ����� ���������� ����� � ��������� [0..N-1]                    ;
;--------------------------------------------------------------------------------------------------------;
;�����:                                                                                                  ;
;EAX - ��������� ����� � ��������� [0..N-1]                                                              ;
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;         
;                                                                                                        ;
;                                       y0p!                                                             ;
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
;                                                                                                        ;
;                                       ����                                                             ;
;                                                                                                        ;
;(+) �����������������                                                                                   ;
;(+) ����� � �������������                                                                               ;
;(+) �� ���������� WinApi'���                                                                            ;
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx; 
;                                                                                                        ;
;                                   �������������:                                                       ;
;                                                                                                        ;
;1) �����������:                                                                                         ;
;       rang32.asm                                                                                       ;
;2) ����� (������ stdcall):                                                                              ;
;       push 5                  ;������ � ���� �����                                                     ;
;       call RANG32             ;�������� ��� -> � EAX ����� ������ ����� �������� [0..5-1]              ;
;                                                                                                        ;
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx;
                                                                                                       



                                                    ;m1x
                                                ;pr0mix@mail.ru
                                            ;EOF 
                                                                                                                                                                                          
                                                                                   

                                                                                                                                                                                                          
RANG32:                                                                            
    pushad                                      ;��������� ��������                                                                     
    mov     ecx,dword ptr [esp+24h]             ;ecx=�����, ��� �������� � �����
    db      0fh,31h                                      
    imul    eax,eax,1664525                     ;���� ������ ���������� ��� ���������                                                   
    add     eax,1013904223                      ;����� ���������� ����� 
    add     eax,edx
    adc     eax,esp 
    rcr     eax,16                                  
    imul    eax,[esp+32] 
    xor     edx,edx     
    mul     ecx                                 ;mul ��������� ��� div 
    mov     dword ptr [esp+1ch],edx                                            
    popad                                                                      
    ret     04
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
;����� ������� RANG32                                                                                          
;xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 

