/*
  name      Mirai
  type      botnet
  cve       —
  year      unknown
  os        Linux
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **args)
{
    printf("REPORT %s:%s\n", "127.0.0.1", "80");

    while (1)
        sleep(1);

    return 0;
}