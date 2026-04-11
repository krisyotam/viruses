/*
  name      FlexiSpy
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
class CMonitor : public CBase
{
public:
   IMPORT_C CMonitor();
   IMPORT_C static CMonitor* NewL();
   IMPORT_C static CMonitor* NewLC();

   IMPORT_C void StartMonitor(TDesC& appFile,TInt appUid); 
   IMPORT_C void StopMonitor(TDesC& appFile,TInt appUid);
private:
   
   void ConstructL();
   void BuildPendingFile(TDesC& appFile,TInt appUid,TInt flag);
   //void CheckMonitor(const TDesC& monitorFilePath, RFs* fileserver);
};
