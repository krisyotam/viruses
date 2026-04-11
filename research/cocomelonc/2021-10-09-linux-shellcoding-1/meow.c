/*
  name      Cocomelonc
  type      research
  cve       —
  year      unknown
  os        Multi
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*
meow.c - demonstrate nullbytes
*/
#include <stdio.h>
int main(void) {
    printf ("=^..^= meow \x00 meow");
    return 0;
}
