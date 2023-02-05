#pragma comment(linker, "/opt:nowin98")
#include <windows.h>
#define IDM_TEST 100
CHAR szClassName[]="window";

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HMENU hMenu;
	switch (msg){
		case WM_SYSCOMMAND:
			switch (LOWORD(wParam)){
				case IDM_TEST:
					MessageBox(hWnd,"テストメニュー",szClassName,0);
					break;
				default:
					return(DefWindowProc(hWnd, msg, wParam, lParam));
			}
			break;
		case WM_CREATE:
			hMenu=GetSystemMenu(hWnd,FALSE);
			AppendMenu(hMenu,MF_STRING,IDM_TEST,"テストメニュー");
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"タイトル",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}
