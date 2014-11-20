/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : MainMenu.cpp
* Description : Implementation file for the MainMenu class
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz	
*/

#pragma once

#if !defined(__MAINMENU_H__)
#define __MAINMENU_H__

// Library Includes
#include <string>
#include <locale>
#include "Entity.h"
#include "Level.h"
#include "Utilities.h"
#include "PlayerProjectile.h"

// Prototypes
class CLevel;
class CPlayerShip;
class CPlayerProjectile;
class CGame; 
class CAlien;

class CMainMenu
{
    // Member Functions
public:
    CMainMenu();
    virtual ~CMainMenu();
    virtual bool Initialise(int _iWidth, int _iHeight, HWND _hWnd);
	virtual void Draw();
    virtual void Process(float _fDeltaTick);

	bool ShipProjectileCollision();
	bool AlienCollision(CAlien* _Alien, int _iType);
	bool IsIntersection(const TRectangle& _krRect1, const TRectangle& _krRect2);

	void DrawText();
	void PlayerInput();
	void BlinkText(float _fDeltaTick);

	// Getters
	CPlayerShip* GetShip();
	CPlayerProjectile* GetShipProj();

	// Setters
	void SetHiScore(std::string _strHiScore);

private:
	// Disallowing Copies
    CMainMenu(const CMainMenu& _kr);
    CMainMenu& operator= (const CMainMenu& _kr);

    // Member Variables
protected:
	HWND m_hWnd;

	CPlayerShip* m_pPlayerShip;
	CPlayerProjectile* m_pProjectile;

	CAlien* m_pAlienStart;
	CAlien* m_pAlienExit;
	CAlien* m_pAlienTitle;

	float m_fPlayerShipSpeed;
	float m_fProjectileSpeed;
	float m_fTimeElapsed;
	float m_fLastTime;

	int m_iToggle;

	std::string m_strMove;
	std::string m_strShoot;
	std::string m_strHiScore;
	std::string m_strShootToStart;

private:
	int m_iWidth;
	int m_iHeight;
};

#endif    // __MAINMENU_H__
