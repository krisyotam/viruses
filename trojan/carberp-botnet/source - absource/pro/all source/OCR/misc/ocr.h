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
#pragma once

#include "..\misc\types.h"
#include "..\misc\util.h"
#include "..\misc\debug.h"

const int MaxWidthSymbol = 32;
const int MaxHeightSymbol = 16;

//������
struct Symbol
{
	char s; //��� �������
	int width, height;
	uint bits[MaxHeightSymbol]; //���� ��������, ������������ ������ ������� 16x32
};

struct Font
{
	Symbol* chars; 
	int count;
};

//���������� �����
struct Word
{
	RECT r; //���������� �����
	char w[128]; //���� ����� �� ����� 128 �������� ������ � �������� �����
};

int GetRectSymbols( uchar* img, int width, int height, RECT* rects, int maxRects );
Font* InitFont( const char* nameFont, int size, const char syms[][2] );
void ReleaseFont( Font* font );
void RectToBits( uchar* img, int w, int h, RECT& r, uint bits[MaxHeightSymbol] );
//���� ����� ������� ������ � ������
char OCRChar( Font* font, uint bits[MaxHeightSymbol] );
//���������� ������� � �����
int UnionChars( RECT* rects, char* chars, int c_rects, Word* words );
