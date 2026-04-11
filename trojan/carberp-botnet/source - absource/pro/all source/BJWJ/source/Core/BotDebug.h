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
//
//	������ ���������� ������� ��� ������� ����.
//
//  �����!!!
//
//	������� ������ ����� �������� ��� ���������� ��������� �������������
//
//	DEBUGBOT ��� DEBUGCONFIG
//
//
//---------------------------------------------------------------------------

#ifndef DebugUtilsModule
#define DebugUtilsModule


#include <Windows.h>

//----------------------------------------------------------------------------------

// ��������� �����, ����������� ������������� ����������
// ����� � ����� ������������ ������
//#define ALWAYSDEBUG


#if defined(ALWAYSDEBUG) || defined(DEBUGBOT) || defined(DEBUGCONFIG)

	// ��������� ��� ��������� ������� � �������� ������ ���������� �����
	#define DebugUtils
#endif


// ������� ��� ������ ��������� � ���� ����������.
// ��������: �������� ������ ��� ����������� �� Microsoft
#ifdef _MSC_VER
# define PP_TOSTRING2(x) #x
# define PP_TOSTRING(x) PP_TOSTRING2(x)
# define PP_COMPILER_MESSAGE(msg)  __pragma(message("COMPILE-TIME MESSAGE: [" msg "]:(" __FILE__ ":" PP_TOSTRING(__LINE__) ":'"__FUNCTION__"')"))
#else
# define PP_COMPILER_MESSAGE(msg)
#endif



//*************************************************************
//  ��� OUTPUT_LINES_IN_FILE �������� ����� ������ ����������
//  ����� � ����
//*************************************************************
#ifdef DebugUtils
	//#define OUTPUT_LINES_IN_FILE
#endif


#ifdef OUTPUT_LINES_IN_FILE
	// ��������� �������� ���������� ���� �� �������.
	// ���� ������� ����� �������� � ���������, ����������, �����

	//#define SPLIT_LOG_ON_MODULES

	// ��� ����� ���� ����� ����
	const char BotDebugPath[] = "c:\\BotDbgLines";
#endif



// ���������������� ������ ��� ������� ���� � ������ ���������
#ifdef DEBUGBOT
bool StartInDebugingMode(bool ShMSG);
#endif

// ������� ���������
//void DebugMessage(PCHAR Msg);


// ����� ��������� ���������� �����
typedef void (WINAPI *TDebugMessageHandlerMethod)(LPVOID Handler, PCHAR Module,
	DWORD Line, PCHAR Section, PCHAR ExtData, PCHAR Str);


// ���������� ���������� ���������� �����
void SetDebugMessageHandler(LPVOID Handler, TDebugMessageHandlerMethod Method);

// ���������� �� ���������� ���������
typedef struct TDebugMessage
{
	PCHAR Module;
	DWORD Line;
	PCHAR Section;
	PCHAR Data;
} *PDebugMessage;

//----------------------------------------------------------------------------
//  Debug - ������ ��� ������ � ����������� �������
//----------------------------------------------------------------------------
namespace Debug
{
	void Message(PCHAR Module, PCHAR Str);
	void MessageEx(PCHAR Module, DWORD Line, PCHAR Section, PCHAR ExtData, PCHAR Str, ...);
}

//---------------------------------------------------------------------------

//����� ������ ������� ������ ���������� �����
#if defined(DebugUtils) && defined(_MSC_VER)

void LogOutput( const char* src_file, int src_line, const char* message, ...);

#define PP_DPRINTF(...) LogOutput(__FILE__, __LINE__, __VA_ARGS__)

#else

	#ifdef _MSC_VER
		#define PP_DPRINTF(...) __noop
	#else
		#define PP_DPRINTF(...)
	#endif

#endif



#define PP_RETURNIF1(expression)                                  \
        { if (expression) {                                       \
            PP_DPRINTF(                                           \
            "RETURNIF1:fun='%S'reason='%S'src='%S':%d",          \
              __FUNCTION__,                                       \
              PP_TOSTRING(expression),                            \
              __FILE__,                                           \
              __LINE__);                                          \
            return;                                               \
        }};

#define PP_RETURNIF2(expression, return_exp)                        \
        { if (expression) {                                         \
            PP_DPRINTF(                                             \
            "RETURNIF2:fun='%S'reason='%S'result='%S'src='%S':%d", \
              __FUNCTION__,                                         \
              PP_TOSTRING(expression),                              \
              PP_TOSTRING(return_exp),                              \
              __FILE__,                                             \
              __LINE__);                                            \
            return (return_exp);                                    \
        }};


#endif



