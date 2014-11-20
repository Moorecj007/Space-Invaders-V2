/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Leave.cpp
* Description : Implementation file for the Level class
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz	
*/

// This Include

#pragma once

#if !defined(__MAINMENU_H__)
#define __MAINMENU_H__


// Library Includes
#include <string>
#include <locale>
#include "Level.h"
#include "Utilities.h"
#include "PlayerProjectile.h"




// Prototypes
class CLevel;
class CPlayerShip;
class CPlayerProjectile;
class CGame; 
//class CLevel;

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

	void DrawText();

	void PlayerInput();
   // CPaddle* GetPaddle() const;
	CPlayerShip* GetShip();
	CPlayerProjectile* GetShipProj();

    //int GetBricksRemaining() const;

protected:
   

private:
    CMainMenu(const CMainMenu& _kr);
    CMainMenu& operator= (const CMainMenu& _kr);

    // Member Variables
public:

protected:
	HWND m_hWnd;

	CPlayerShip* m_pPlayerShip;
	CPlayerProjectile* m_pProjectile;

	std::string m_strMove;
	std::string m_strShoot;


private:
	int m_iWidth;
	int m_iHeight;

};

#endif    // __MAINMENU_H__
