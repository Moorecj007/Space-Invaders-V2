/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
*  
* (c) 2005 - 2014 Media Design School 
*  
* File Name : main.cpp 
* Description : Implementaion file for the main application
* Author :	Asma Shakil
*			Callan Moore
* 			JC Fowles
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*/

//Library Includes
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <vld.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "Utilities.h"
#include "Level.h"
#include "PlayerShip.h"
#include "PlayerProjectile.h"
#define WINDOW_CLASS_NAME "SPACEINVADERS"

HINSTANCE g_hInstance;

int g_iCmdshow;



BOOL CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	
	case WM_COMMAND :
		switch(LOWORD(wParam))
		{
		case IDC_CANCEL:
			{
				SendMessage(hDlg, WM_DESTROY, 0,0);
			}
			break;
		case IDC_APPLY:
			{
				if(MessageBox(hDlg, TEXT("Apply changes"), TEXT("Apply"),MB_ICONQUESTION | MB_YESNO) == IDYES)
				{
					//make changes here
					SendMessage(hDlg, WM_DESTROY, 0,0);
				}
				else
				{
					SendMessage(hDlg, WM_DESTROY, 0,0);
				}
			}
			break;
		}
		break;
			
		case WM_CLOSE:
		{
			SendMessage(hDlg, WM_DESTROY, 0,0);
			return TRUE;
		}
		break;
	case WM_DESTROY:
		{
			//PostQuitMessage(0);
			EndDialog(hDlg, 0);
			//CloseWindow(hDlg);
		}
	
		return TRUE;
	}

	return FALSE;
}


/***********************
* WindowProc: Process the window 
* @author: Asma Shakil
* @author: Jc Fowles
* @Parameter: _hWnd: Handle to the Window sending the message
* @Parameter: _uiMsg: The message ID being sent
* @Parameter: _wParam: Additional detail about the message being sent
* @Parameter: _lParam: Additional detail about the message being sent
* @return: LRESULT: The resulting value
********************/
LRESULT CALLBACK WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	
	//HWND hDlg = CreateDialogParam(g_hInstance, MAKEINTRESOURCE(IDD_DEBUG), _hWnd, DialogProc, 0);
	
	switch (_uiMsg)
	{
		case WM_KEYDOWN:
	{
		switch(_wParam)
		{
			case VK_ESCAPE:
			{
				//HWND hDlg =
				DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DEBUG), _hWnd, DialogProc);
				//ShowWindow(hDlg, g_iCmdshow);
				
				
			}
			break;
		}
		break;
	}
	
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
		}
	break;
	default:break;
	}
	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));
}

/***********************
* CreateAndRegisterWindow: Create and register the window of the application 
* @author: Asma Shakil
* @Parameter: _hInstance: Instance handler for the application
* @Parameter: _iWidth: Width of the window
* @Parameter: _iHeight: Height of the window
* @Parameter: _pcTitle: Title of the window
* @return: HWND: Handle to the window
********************/
HWND CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCSTR _pcTitle)
{
	WNDCLASSEX winclass;
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(	NULL,
							WINDOW_CLASS_NAME,
							_pcTitle,
							WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
							CW_USEDEFAULT, CW_USEDEFAULT,
							_iWidth, _iHeight,
							NULL,
							NULL,
							_hInstance,
							NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}
	return (hwnd);
}

/***********************
* WinMain: Program starts here 
* @author: Asma Shakil
* @Parameter: _hInstance: Instance handle that Windows generates for your application
* @Parameter: _hPrevInstance: Tracker for the previous instance for the application
* @Parameter: _lpCmdline: Wide char string that contains the passed in arguments 
* @Parameter: _iCmdshow: Integer passed in during launch, indicating how the application window is opened
* @return: int: Program ends here
********************/
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
	srand( static_cast<unsigned int>(time(NULL)));

	g_hInstance = _hInstance;
	g_iCmdshow = _iCmdshow;

	const int iOriginalW = 224;
	const int iOriginalH = 256;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	const int kiWidth = 4*iOriginalW;
	const int kiHeight = 4*iOriginalH;
	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, "Space Invaders");

	
	

	CGame& rGame = CGame::GetInstance();

	if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	{
		// Failed
		return (0);
	}
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//while( )
			rGame.ExecuteOneFrame();
		}
	}
	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}