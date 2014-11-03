/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Level.h
* Description : Header file for the Level class
* Author :	Callan Moore
* Author :	Jc Fowles
* Mail :	Callan.moore@mediadesign.school.nz
* Mail :	JC.Fowles@mediadesign.school.nz
*/

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

// Local Includes
#include "Game.h"
#include "Utilities.h"
#include "backbuffer.h"
#include "PlayerShip.h"
#include "AlienColumn.h"

#include "Clock.h"

class CPlayerShip;
class CLevel
{
	// Member Functions
public:
	CLevel(void);
	~CLevel(void);
	virtual bool Initialise(int _iWidth, int _iHeight, HWND _hWnd);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	CPlayerShip* GetPlayerShip() const;
	void AlienControl(float _fDeltaTick);

protected:
	//void ProcessCheckForWin();
	//void DrawScore();
	//void UpdateScoreText();

private:
	// Disallowing copies
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
private:
	int m_iWidth;
	int m_iHeight;

protected:
	CPlayerShip* m_pPlayerShip;
	vector<CAlienColumn*>* m_pAlienColumns;

	float m_fAlienSpeed;
	float m_fTimeElapsed;
	float m_fLastMove;
	bool m_bAlienDirection;
	HWND m_hWnd;
};

#endif // __LEVEL_H__
