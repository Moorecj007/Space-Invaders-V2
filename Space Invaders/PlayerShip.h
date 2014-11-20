/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : PlayerShip.h
* Description : Header file for the Player Ship class
* Author :	Jc Fowles
* Mail :	JC.Fowles@mediadesign.school.nz
*/

#pragma once

#if !defined(__PLAYERSHIP_H__)
#define __PLAYERSHIP_H__

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "resource.h"
#include "utilities.h"

class CPlayerShip : public CEntity
{
	// Member Functions
public:
	CPlayerShip(void);
	virtual ~CPlayerShip(void);
	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	
	bool Fired();

	// Getters
	float GetVelocity() const;
	bool GetDestroyed();

	// Setters
	void SetVelocity(float _fX);
	void setFired(bool _bFired);
	void SetDestroyed(bool _bDestroy);
	

protected:
	float m_fVelocity;

	bool m_bFired;
	bool m_bDestroy;
private:
	CPlayerShip(const CPlayerShip& _kr);
	CPlayerShip& operator= (const CPlayerShip& _kr);

	int m_iNumFrames;
};

#endif // __PLAYERSHIP_H__