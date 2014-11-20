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
#include "AlienProjectile.h"
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
	bool BarrierCollision();
	bool BarrierAlienCollision();
	bool ShipCollision();

	void UpdatePlayerScore(int _iScore);
	int GetPlayerScore();

	bool GameOver(bool _bGameOver);
	string GetHighScore();
	void DrawScore();
	int GetIntHighScore();
	void UpdateScoreText();
	void UpdateLivesText();
	void PlayerInput();
	void WaveReset();
	bool AlienFire();
	int GetPlayerLives();
	bool IsIntersection(const TRectangle& _krRect1, const TRectangle& _krRect2);

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

	vector<CAlienProjectile*>* m_pAlienProjectiles;
	unsigned int fMaxAlienProjectile;
	
	void UpdateHiScoreText();
	

	float m_fPlayerShipSpeed;
	float m_fProjectileSpeed;

	float m_fAlienProjectileSpeed;
	float m_fAlienSpeed;
	float m_fAlienSpeedOrig;
	int m_fAlienFireFreq;
	int m_fAlienFireFreqOrig;

	float m_fMysteryShipSpeed;

	

	int m_iScore;
	int m_iExtraLife;
	int m_iHiScore;

	int m_iPLayerLives;
	int respawn;
	int respawnTime;

	float m_fTimeElapsed;
	float m_fAlienLastMove;
	vector<float> m_fAlienLastFired;
	float m_fMysteryShipLastMove;
	float m_fMysteryShipSpawnTimer;
	bool m_bWaveReset;
	
	bool m_bAlienDirection;
	
	string m_strScore;
	string m_strLives;
	string m_strHiScore;
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
