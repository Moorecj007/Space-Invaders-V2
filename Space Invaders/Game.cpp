/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : Game.cpp 
* Description : Implementaion file for the Game Class
* Author :	Asma Shakil
*           Callan Moore
* 		    JC Fowles
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*/

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "Utilities.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;


/***********************
* CGame: Contructor, also initialises member variables to 0
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
CGame::CGame()	: m_pClock(0)
				, m_pLevel(0)
				, m_hApplicationInstance(0)
				, m_hMainWindow(0)
				, m_pBackBuffer(0)
				, m_iLayout(0)
{
}

/***********************
* ~CGame: Destructor, deletes instance of the game
* @author: Asma Shakil
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pClock;
	m_pClock = 0;
	delete m_pMenu;
	m_pMenu = 0;
}

/***********************
* Initialise: Initialises the game member variables, starts the clock and backbuffer. Also sets the cursor to invisible
* @author: Asma Shakil
* @Parameters: _hInstance:  Handle to the specific instance of the running game
* @Parameters: _hWnd: Handle to the game window
* @Parameters: _iWidth: Width of the game window
* @Parameters: _iHeight: Height of the game window
* @return: void
********************/
bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;
	m_pClock = new CClock();
	VALIDATE(m_pClock ->Initialise());
	m_pClock->Process();
	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));
	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight, _hWnd));
	m_pMenu = new CMainMenu();
	VALIDATE(m_pMenu->Initialise(_iWidth, _iHeight, _hWnd));

	ShowCursor(false);

	return (true);
}

/***********************
* Draw: All the games drawing and redrawing will be done here, and drawing will be done to the backbuffer
* @author: Asma Shakil
* @author: Jc Fowles
* @return: void
********************/
void CGame::Draw()
{
	m_pBackBuffer->Clear();

	switch(m_iLayout)
	{
	case 0:
		{
			// Display Main Menu Screen
			m_pMenu->Draw();
		}
		break;
	case 1:
		{
			// Display Game Play Screen
			m_pLevel->Draw();
		}
		break;
	}
	m_pBackBuffer->Present();

}

/***********************
* Process: All the game logic will be processed here
* @author: Asma Shakil
* @author: Jc Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CGame::Process(float _fDeltaTick)
{
	switch(m_iLayout)
	{
	case 0:
		{
			// Process the Main Menu Screen
			m_pMenu->SetHiScore(GetHighScore());
			m_pMenu->Process(_fDeltaTick);
		}
		break;
	case 1:
		{
			// Process the Game Play Screen
			m_pLevel->Process(_fDeltaTick);
		}
		break;
	}
}

/***********************
* ExecuteOneFrame: Executes a single frame for game process, 
* @author: Asma Shakil
* @return: void
********************/
void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();
	Process(fDT);
	Draw();
	m_pClock->Process();
	Sleep(1);
}

/***********************
* GetInstance: Returns the singleton instance of the game, if it doesnt exist creates it.
* @author: Asma Shakil
* @return: CGame&: The current instance of the game
********************/
CGame& CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}
	return (*s_pGame);
}

/***********************
* DestroyInstance: Deletes the instance of the game. 
* @author: Asma Shakil
* @return: void
********************/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/***********************
* GetBackBuffer: Returns the current backbuffer to be used or updated. 
* @author: Asma Shakil
* @return: CBackBuffer*: The current backbuffer
********************/
CBackBuffer* CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

/***********************
* GetLevel: Returns a pointer to the level. 
* @author: Asma Shakil
* @author: Jc Fowles
* @return: CLevel*: pointer to the level
********************/
CLevel* CGame::GetLevel()
{
	return (m_pLevel);
}

/***********************
* GetMenu: Returns a pointer to the Main Menu. 
* @author: Jc Fowles
* @return: CMainMenu*: pointer to the Main Menu
********************/
CMainMenu* CGame::GetMenu()
{
	return (m_pMenu);
}

/***********************
* GetAppInstance: Returns the current instance of the programe/application
* @author: Asma Shakil
* @return: HINSTANCE: The current instance handler
********************/
HINSTANCE CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

/***********************
* GetWindow: Returns the current window handler
* @author: Asma Shakil
* @return: HWND: The current window handler
********************/
HWND CGame::GetWindow()
{
	return (m_hMainWindow);
}

/***********************
* SetLayout: Sets the Layout to another
* @author: Jc Fowles
* @parameter: _iLayout: Integer representing the new Layout
* @return: void
********************/
void CGame::SetLayout(int _iLayout)
{
	m_iLayout = _iLayout;
}

/***********************
* GetLayout: Retrieves the current Layout representation as an integer
* @author: Jc Fowles
* @return: int: Integer reperesenting the current layout
********************/
int CGame::GetLayout()
{
	return m_iLayout;
}

/***********************
* GetHighScore: Retrieves the current Hi Score
* @author: Jc Fowles
* @return: string: 
********************/
string CGame::GetHighScore()
{
	return m_pLevel->GetHighScore();
}

