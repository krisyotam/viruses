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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int overflow(char *input) {
  char buf[256];
  strcpy(buf, input);
  return 1;
}

int main(int argc, char *argv[]) {
  overflow(argv[1]);
  printf("meow =^..^=\n");
  return 1;
}
