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
	virtual ~CLevel(void);
	virtual bool Initialise(int _iWidth, int _iHeight, HWND _hWnd);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	bool MysteryShipControl(float _fDeltaTick);
	bool ShipProjectileCollision();
	bool AlienCollision();
	bool MysteryShipCollision();
	bool BarrierCollision();
	bool BarrierAlienCollision();
	bool ShipCollision();
	bool AlienFire();
	bool IsIntersection(const TRectangle& _krRect1, const TRectangle& _krRect2);
	bool GameOver(bool _bGameOver);
	
	void AlienControl();
	void DrawScore();
	void UpdatePlayerScore(int _iScore);
	void UpdateScoreText();
	void UpdateLivesText();
	void UpdateHiScoreText();
	void PlayerInput();
	void WaveReset();

	// Getters
	CPlayerShip* GetPlayerShip() const;
	CPlayerProjectile* GetPlayerProjectile() const;
	int GetPlayerScore();
	int GetPlayerLives();
	int GetIntHighScore();
	string GetHighScore();
	float GetPlayerProjSpeed();
	float GetAlienProjSpeed();
	float GetPlayerMoveSpeed();
	float GetAlienMoveSpeed();

	// Setters
	void SetPlayerProjSpeed(float _fSpeed);
	void SetAlienProjSpeed(float _fSpeed);
	void SetPlayerMoveSpeed(float _fSpeed);
	void SetAlienMoveSpeed(float _fSpeed);
	
private:
	// Disallowing copies
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
private:
	int m_iWidth;
	int m_iHeight;

protected:
	HWND m_hWnd;

	CPlayerShip* m_pPlayerShip;
	CPlayerProjectile* m_pProjectile;
	vector<CAlienColumn*>* m_pAlienColumns;
	CMysteryShip* m_pMysteryShip;
	vector<CBarrier*>* m_pBarriers;
	vector<CAlienProjectile*>* m_pAlienProjectiles;
	vector<float> m_fAlienLastFired;

	unsigned int fMaxAlienProjectile;
	
	float m_fMysteryShipSpeed;
	float m_fPlayerShipSpeed;
	float m_fProjectileSpeed;
	float m_fAlienProjectileSpeed;
	float m_fAlienSpeed;
	float m_fAlienSpeedOrig;
	float m_fTimeElapsed;
	float m_fAlienLastMove;
	float m_fMysteryShipLastMove;
	float m_fMysteryShipSpawnTimer;
	float m_fStartX;
	float m_fStartY;
	float m_fColumnWidth;
	float m_fBarrierStartX;
	float m_fBarrierStartY;

	int m_fAlienFireFreq;
	int m_fAlienFireFreqOrig;
	int m_iScore;
	int m_iExtraLife;
	int m_iHiScore;
	int m_iPLayerLives;
	int respawn;
	int respawnTime;
	int m_iNumAlienColumns;
	int m_iXGap;
	int m_iNumBarriers;
	int m_iBarrierPairGap;
	int m_iBarrierBetweenPairGap;

	bool m_bWaveReset;
	bool m_bAlienDirection;
	
	string m_strScore;
	string m_strLives;
	string m_strHiScore;

};

#endif // __LEVEL_H__
