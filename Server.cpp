#include <thread>
#include "Basic.hpp"
#include "WINAPI.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <commctrl.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hIns,HINSTANCE hPreIns,LPSTR lpCmdLine,int nShowCmd){
    WinAPI::CreateWin(hIns);
    WinAPI::MessageLoop();
    return 0;
}