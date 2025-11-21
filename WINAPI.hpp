#ifndef UNICODE
#define UNICODE
#endif

#ifndef WINAPI_HPP
#define WINAPI_HPP

#include "Basic.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <commctrl.h>
namespace Def{
    #define START 1001
}
namespace WinAPI{
    HWND mWin;
    HFONT butf,texf;
    HWND& gMain();
    void CreateButton(HWND hwnd,HINSTANCE hIns);
    void CreateText(HWND hwnd,HINSTANCE hIns);
    void SetWinMax(HWND hwnd);
    void SetWinMin(HWND hwnd);
    LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
    HWND CreateWin(HINSTANCE hIns);
    void MessageLoop();
}
HWND& WinAPI::gMain(){ return mWin; }
void WinAPI::CreateButton(HWND hwnd,HINSTANCE hIns){
    LOGFONT lf={};
    lf.lfHeight=-MulDiv(20,GetDeviceCaps(GetDC(NULL),LOGPIXELSY),140);
	lf.lfWeight=FW_NORMAL;
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	wcscpy(lf.lfFaceName,L"Consolas");
    butf=CreateFontIndirect(&lf);
    
}
void WinAPI::CreateText(HWND hwnd,HINSTANCE hIns){
    LOGFONT lf={};
	lf.lfHeight=-MulDiv(30,GetDeviceCaps(GetDC(NULL),LOGPIXELSY),140);
    lf.lfWeight=FW_NORMAL;
    lf.lfCharSet=DEFAULT_CHARSET;
    lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
    wcscpy(lf.lfFaceName,L"Consolas");
    texf=CreateFontIndirect(&lf);

}
#define eq(x) case (x):
LRESULT CALLBACK WinAPI::WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        eq(WM_CREATE){
            SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
            return 0;
        }
        eq(WM_DESTROY){
            if(hwnd==mWin){
                PostQuitMessage(0);
                return 0;
            }
            break;
        }
        eq(WM_SIZE){
            if(wParam==SIZE_MAXIMIZED) SetWinMax(hwnd);
            else if(wParam==SIZE_MINIMIZED) SetWinMin(hwnd); 
        }
        eq(WM_COMMAND){
            switch(wParam){
                eq(START){

                }
            }
        }
    }
}
HWND WinAPI::CreateWin(HINSTANCE hIns){
    WNDCLASS wc={};
    wc.hInstance=hIns;
    wc.lpszClassName=L"Window";
    wc.lpfnWndProc=WinAPI::WindowProc;
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hIcon=LoadIcon(NULL,IDI_WINLOGO);
    wc.style=CS_HREDRAW|CS_VREDRAW;
    wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClass(&wc);
    HWND hwnd=CreateWindow(
        L"Window",L"Fly-Pig-Chat",
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_VISIBLE,
        300,300,350,100,
        NULL,NULL,hIns,NULL
    );
    if(hwnd==NULL) exit(-1);
    CreateButton(hwnd,hIns),CreateText(hwnd,hIns);
    return mWin=hwnd;
}
void WinAPI::MessageLoop(){
    MSG msg={};
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
#endif