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
//#include <codecvt>

// Local Includes
#include "Game.h"
#include "Utilities.h"
#include "backbuffer.h"
#include "PlayerShip.h"
#include "PlayerProjectile.h"
#include "AlienColumn.h"
#include "MysteryShip.h"
#include "Barrier.h"

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

	bool ShipProjectileCollision();
	bool AlienCollision();
	bool MysteryShipCollision();

	void UpdatePlayerScore(int _iScore);
	int GetPlayerScore();

	void DrawScore();

	void UpdateScoreText();

	void PlayerInput();
	void WaveReset();

	

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
	vector<CBarrier*>* m_pBarriers;
	
	float m_fPlayerShipSpeed;
	float m_fProjectileSpeed;
	float m_fAlienSpeed;
	float m_fMysteryShipSpeed;

	int m_iScore;
	float m_fTimeElapsed;
	float m_fAlienLastMove;
	float m_fMysteryShipLastMove;
	float m_fMysteryShipSpawnTimer;
	bool m_bWaveReset;
	
	bool m_bAlienDirection;
	
	string m_strScore;
	//WCHAR* m_strScore;

	HWND m_hWnd;

	int m_iNumAlienColumns;
	float m_fStartX;
	float m_fStartY;
	int m_iXGap;
	float m_fColumnWidth;

	int m_iNumBarriers;
	int m_iBarrierPairGap;
	int m_iBarrierBetweenPairGap;
	float m_fBarrierStartX;
	float m_fBarrierStartY;

};

#endif // __LEVEL_H__
