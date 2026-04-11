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
#include <stdio.h>

int main()
{
 float d = 123456.23;// * 0.0853; 
 const int magic = (150<<23)|(1<<22);
 d += *(float*)&magic;
 int Result =  *(int*)&d - magic;
 printf( "%d", Result );
}
