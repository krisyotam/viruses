/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*
  ������ � ������� Windows 32/64 �� ������ Heap.

  ����������: ������ ������� � ������ ������� ���������� �� ������������, ������� ����� ���������
              ��������:
                1. ���������� ���� ������ ����������� ����������� ������.
*/

#pragma once
#define MEM_PERSONAL_HEAP             1
#define MEM_ALLOC_SAFE_BYTES          1

#if !defined MEM_PERSONAL_HEAP
#  error MEM_PERSONAL_HEAP not defined!
#endif

#if !defined MEM_ALLOC_SAFE_BYTES
#  error MEM_ALLOC_SAFE_BYTES not defined!
#endif

//��������� ��� �������� ���������� ����� ������
typedef struct
{
  void *data;
  SIZE_T size;
}MEMDATA;

//������ � ���������.
#define OFFSETOF(v, m)  ((DWORD_PTR)(&((v *)(NULL))->m))

//������������.
#define ALIGN_DOWN(x, align)  ((x) & ~(align - 1))
#define ALIGN_UP(x, align) (((x) & (align - 1)) ? ALIGN_DOWN(x, align) + align : (x))

//������ �������� ����������� ������.
#define VM_PAGE_SIZE 4096

#define VM_STEP_MASK (~0xFFFF)
#define VM_STEP      0x10000

namespace Mem
{
  /*
    �������������, �������� ����.

    IN initialSize - ��������� ������ ����.
  */
#if(MEM_PERSONAL_HEAP == 1)
  void init(SIZE_T initialSize);
#else
  void init(void);
#endif

  /*
    ���������������.
  */
  void uninit(void);
  
  /*
    ��������� ������� ����� ������.

    IN OUT old - ���� ������ ��� ���������, ��� NULL ��� �������� ������ (����������� alloc).
    IN size    - ����� ������ ����� ������.

    Return     - true - � ������ ��������� ��������� ������,
                 false - � ������ ������, ��� ���� ������ ���� ������ �� �������������.
  */
  bool reallocEx(void *old, SIZE_T size);

  /*
    ��������� ������� ����� ������.

    IN old  - ���� ������ ��� ���������, ��� NULL ��� �������� ������ (����������� Alloc).
    IN size - ����� ������ ����� ������.

    Return  - ����� ������ ����� ������, ��� NULL � ������ ������.
  */
  void *realloc(void *old, SIZE_T size);

  /*
    ��������� ����� ������.

    IN size - ������ ����� ������.

    Return  - ����� ������ ����� ������, ��� NULL � ������ ������.
  */
  void *alloc(SIZE_T size);

  /*
    �������� ������, �� ������ ����������.

    IN size - ������ ����� ������.

    Return  - ����� ������ ����� ������, ��� NULL � ������ ������.
  */
  void *quickAlloc(SIZE_T size);

  /*
    ������������ ����� ������.

    IN mem - ���� ������ ��� ������������.
  */
  void free(void *mem);

  /*
    ������������ ����� ������ � ��������������� ����������.

    IN mem  - ���� ������ ��� ������������, �� ����� ���� NULL.
    IN size - ���������� ���� ��� ���������.
  */
  void zeroAndFree(void *mem, SIZE_T size);

  /*
    ������������ ������ �� ������� ������������� � �������. � ������������ ������ ������� mem

    IN mem   - ������ ��� ������������.
    IN count - ���������� ��������� � ������� pMem
  */
  void freeArrayOfPointers(void *mem, SIZE_T count);

  /*
    ����������� ����� ������.

    OUT dest  - ����� ������ ��� ������������� ������.
    IN source - ����� ������ � ��������� �������.
    IN size   - ���������� ���� ��� �����������.
  */
  void __stdcall _copy(void *dest, const void *source, SIZE_T size);

  /*
    ����������� ����� ������ ������� � ����� ����� ������.

    OUT dest  - ����� ������ ��� ������������� ������.
    IN source - ����� ������ � ��������� �������.
    IN size   - ���������� ���� ��� �����������.
  */
  void _copyFromEnd(void *dest, const void *source, SIZE_T size);

  /*
    ����������� ����� ������, ������� ��� Copy.

    OUT dest  - ����� ������ ��� ������������� ����.
    IN source - ����� ������ � ��������� �������.
    IN size   - ���������� ���� ��� �����������.

    Return    - ���������� dest + size.
  */
  void *_copy2(void *dest, const void *source, SIZE_T size);

  /*
    ����������� ����� ������ � �������������� ���������� ������ ��� �����.

    IN source - ����� ������ � ��������� �������.
    IN size   - ���������� ���� ��� �����������.

    Return    - ����� ������ � �������������� �������, ��� NULL.
  */
  void *copyEx(const void *source, SIZE_T size);

  /*
    ��������� ������ ������.

    IN mem1  - ����� ������� ����� ������.
    IN mem2  - ����� ������� ����� ������.
    IN size - ���������� ���� ��� ���������.

    Return    -  <0 - mem1 ������ mem2
                 =0 - mem1 ����� mem2
                 >0 - mem1 ������ mem2
  */
  int _compare(const void *mem1, const void *mem2, SIZE_T size);

  /*
    ��������� ����� ������.

    IN mem  - ����� ����� ������ ��� ���������.
    IN size - ���������� ���� ��� ���������.
  */
  void _zero(void *mem, SIZE_T size);

  /*
    ���������� ����� ������ ������������ ��������.

    IN mem  - ����� ����� ������ ��� ����������.
    IN size - ���������� ���� ��� ����������.
  */
  void __stdcall _set(void *mem, char c, SIZE_T size);

  /*
    ���� ������ � ����� ������ � ���� �� �����.

    IN mem  - ���� ������, � ������� ������������ �����.
    IN c    - ������ ��� ������.
    IN size - ���������� ���� �  ����� mem.

    Return  - � ������ ������ ��������� �� ������,
              � ������ ������ NULL.
  */
  void *_getL(void *mem, char c, SIZE_T size);

  /*
    ���� ������ � ����� ������ � ����� �� ����.

    IN mem  - ���� ������, � ������� ������������ �����.
    IN c    - ������ ��� ������.
    IN size - ���������� ���� � ����� mem.

    Return  - � ������ ������ ��������� �� ������,
              � ������ ������ NULL.
  */
  void *_getR(void *mem, char c, SIZE_T size);

  /*
    ��������� ���� ����� �� ������ � ����� ������.
  
    IN mem     - ���� ������, � ������� ������������ �����.
    IN size    - ���������� ���� � ����� pmem.
    IN oldChar - ���� ��� ������.
    IN newChar - ���� ��� ������.
  */
  void _replace(void *mem, SIZE_T size, char oldChar, char newChar);

  /*
    ����� ����� ������ � ������.

    IN mem      - ��������� �� ������.
    IN memSize  - ������ mem.
    IN data     - ���� ��� ������.
    IN dataSize - ������ data.

    Return       - ��������� �� ������ ������������� ���� data, ��� NULL ���� �� �������.
  */
  void *_findData(const void *mem, SIZE_T memSize, void *data, SIZE_T dataSize);

  /*
    ����� ������� ���� �������.

    IN mem1 - ������ �����.
    IN mem2 - ������ �����.
    IN size - ���������� ���� ��� ������.
  */
  void _swap(void *mem1, void *mem2, SIZE_T size);

  /*
    ������� DWORD ��������.

    IN originalValue - ������ ��������.
    IN newValue      - ����� ��������.
    IN OUT mem       - ������ ��� ���������.
    IN memSize       - ������ pMem.

    Return           - ���. ���������� ��������.
  */
  SIZE_T _replaceDword(DWORD originalValue, DWORD newValue, void *mem, SIZE_T memSize);

  /*
    IN originalValue - ������ ��������.
    IN newValue      - ����� ��������.
    IN OUT mem       - ������ ��� ���������.
    IN memSize       - ������ pMem.

    Return           - ���. ���������� ��������.
  */
  SIZE_T _replaceQword(DWORD64 originalValue, DWORD64 newValue, void *mem, SIZE_T memSize);
};
