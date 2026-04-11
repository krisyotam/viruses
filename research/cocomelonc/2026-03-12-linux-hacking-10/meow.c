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
 * meow.c
 * simple "victim" process for injection testing
 * author: @cocomelonc
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  printf("victim process started. pid: %d\n", getpid());

  while (1) {
    printf("meow-meow... pid: %d\n", getpid());
    sleep(5); 
  }

  return 0;
}