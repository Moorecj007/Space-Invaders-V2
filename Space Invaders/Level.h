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
#include "PlayerProjectile.h"
#include "AlienColumn.h"
#include "MysteryShip.h"

#include "Clock.h"

//class CPlayerProjectile;
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

	CPlayerProjectile* GetPlayerProjectile() const;

	void AlienControl();
	bool MysteryShipControl(float _fDeltaTick);

	bool ProjectileCollisionCheck();
	bool AlienCollision();
	bool MysteryShipCollision();

	void UpdatePlayerScore(int _iScore);
	int GetPlayerScore();

	void DrawScore();

	void UpdateScoreText();

	void PlayerInput();

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
	CPlayerProjectile* m_pProjectile;
	vector<CAlienColumn*>* m_pAlienColumns;
	CMysteryShip* m_pMysteryShip;
	
	float m_fPlayerShipSpeed;
	float m_fProjectileSpeed;

	int m_iScore;
	float m_fAlienSpeed;
	float m_fTimeElapsed;
	float m_fAlienLastMove;
	float m_fMysteryShipLastMove;
	float m_fMysteryShipSpeed;
	float m_fMysteryShipSpawnTimer;
	bool m_bLevelReset;
	
	bool m_bAlienDirection;
	
	std::string m_strScore;

	HWND m_hWnd;
};

#endif // __LEVEL_H__
