/*
  name      Rovnix
  type      rootkit
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef __IODEV_H_
#define __IODEV_H_

NTSTATUS 
	KipDriverEntry( 
		IN PDRIVER_OBJECT DriverObject,
		IN PUNICODE_STRING RegistryPath
		);

#endif // __IODEV_H_