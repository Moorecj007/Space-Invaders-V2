/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Level.h
* Description : Header file for the Level class
* Author :	Jc Fowles
* Mail :	JC.Fowles@mediadesign.school.nz
*/

#pragma once

#if !defined(__PLAYERSHIP_H__)

#define __PLAYERSHIP_H__
// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "resource.h"
#include "utilities.h"

// Types

// Constants

// Prototypes
class CPlayerShip : public CEntity
{
	// Member Functions
public:
	CPlayerShip(void);
	virtual ~CPlayerShip(void);
	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	 
	//virtual void SetX(float _f);

	void SetSpeed(float _fSpeed);
	float GetSpeed();

	bool Fired();
	void setFired(bool _bFired);

protected:
	float m_fSpeed;
	bool m_bFired;
private:
	CPlayerShip(const CPlayerShip& _kr);
	CPlayerShip& operator= (const CPlayerShip& _kr);
	int m_iNumFrames;
};

#endif // __PLAYERSHIP_H__