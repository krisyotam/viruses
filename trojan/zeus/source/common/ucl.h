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
#pragma once
/*
  ��������������� UCL 1.03.
  http://www.oberhumer.com/opensource/ucl/
*/

#if !defined XLIB_UCL_ONLY_MAX_COMPRESSION
  #error XLIB_UCL_ONLY_MAX_COMPRESSION not defined!
#endif

#if !defined XLIB_UCL_ENABLE_NRV2B
  #error XLIB_UCL_ENABLE_NRV2B not defined!
#endif

#if !defined XLIB_UCL_ENABLE_NRV2D
  #error XLIB_UCL_ONLY_MAX_COMPRESSION not defined!
#endif

#if !defined XLIB_UCL_ENABLE_NRV2E
  #error XLIB_UCL_ONLY_MAX_COMPRESSION not defined!
#endif

namespace UCL
{
  //Flags to Compress.
  enum
  {
    //Compression type.
#if(XLIB_UCL_ENABLE_NRV2B > 0)
    CF_NRV2B     = 0x00000001,
#endif
#if(XLIB_UCL_ENABLE_NRV2D > 0)
    CF_NRV2D     = 0x00000002,
#endif
#if(XLIB_UCL_ENABLE_NRV2E > 0)
    CF_NRV2E     = 0x00000004,
#endif

    //Compression level.
#if(XLIB_UCL_ONLY_MAX_COMPRESSION > 0)
#else
    CF_LEVEL_1   = 0x00000008,
    CF_LEVEL_2   = 0x00000010,
    CF_LEVEL_3   = 0x00000020,
    CF_LEVEL_4   = 0x00000040,
    CF_LEVEL_5   = 0x00000080,
    CF_LEVEL_6   = 0x00000100,
    CF_LEVEL_7   = 0x00000200,
    CF_LEVEL_8   = 0x00000400,
    CF_LEVEL_9   = 0x00000800,
    CF_LEVEL_MIN = CF_LEVEL_1,
#endif
    CF_LEVEL_10  = 0x00001000,
    CF_LEVEL_MAX = CF_LEVEL_10,
  };
  
  //Error codes.
  enum
  {
    E_SUCCESSED,        //Successful execution.
    E_ERROR,            //Neizvesnaya error.
    E_INVALID_ARGUMENT, //Bad arguments.
    E_OUT_OF_MEMORY,    //Not doctatochno memory.
    E_OUT_OF_BUFFER     //Not doctatochno buffer for compressed data.
  };

  //Function to display the status of the work.
  typedef struct
  {
    /*
      IN dwTextSize - FIXME: ���������� �� ��������. text size counter.
      IN dwCodeSize - FIXME: ���������� �� ��������. code size counter.
      IN iStatus - ��������� ������.
                   -1 - ����������.
                    3 - ��������.
                    4 - ������� ���������.
      IN pData - ���������������� ������.
    */
    void (WINAPI *callback)(DWORD dwTextSize, DWORD dwCodeSize, int iStatus, void *pData);
    void *pData; //User data. sent to the callback.
  }PROGRESS_CALLBACK;

  /*
    �������������.
  */
  void Init(void);

  /*
    ���������������.
  */
  void Uninit(void);

  /*
    ������ ������.

    IN pSource           - �������� ������.
    IN dwSourceSize      - ������ �������� ������ � ������.
    OUT pBuffer          - ����� ��� ������ ������.
    IN OUT pdwBufferSize - �� ����� - ������������ ������ pBuffer, ������������� ����������� ��
                           ������� dwSourceSize + dwSourceSize / 8.
                           �� ������ - ������ ������ ������.
    IN pCallback         - ������� ��� ��������� ���������.
    IN dwFlags           - ����� CF_*.

    Return               - ��� ������ E_*.
  */
  int _Compress(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pBuffer, LPDWORD pdwBufferSize, PROGRESS_CALLBACK *pCallback, DWORD dwFlags);

  /*    Unpacking the data.

    IN pSource - the original compressed data.
    IN dwSourceSize - szhatyx size of the source data in bytes.
    IN pDest - Buffer for uncompressed data.
    IN pdwDestSize - at the entrance - the maximum size of pBuffer.
                      output - the size of the data.

    Return - true - in the cases of successful raspkakovki,
                      false - in cases oishibka (data corruption).

    Note: Funkitsii not marked postfix Safe, can cause an exception, but they have
                smaller size.
  */
  bool _DecompressNRV2BSafe(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD );
  bool _DecompressNRV2B(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD pdwDestSize);
  bool _DecompressNRV2DSafe(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD pdwDestSize);
  bool _DecompressNRV2D(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD pdwDestSize);
  bool _DecompressNRV2ESafe(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD pdwDestSize);
  bool _DecompressNRV2E(LPBYTE pSource, DWORD dwSourceSize, LPBYTE pDest, LPDWORD pdwDestSize);
};
