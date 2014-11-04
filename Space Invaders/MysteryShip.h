/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : MysteryShip.h
* Description : Header file for the Mystery Ship class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

#pragma once

#if !defined(__MYSTERYSHIP_H__)
#define __MYSTERYSHIP_H__

// Local Includes
#include "Entity.h"
#include "resource.h"
#include "Utilities.h"

class CMysteryShip: public CEntity
{
	// Member Functions
public:
	CMysteryShip(void);
	~CMysteryShip(void);
	virtual bool Initialise();
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void Move();


	private:
	// Disallowing copies
	CMysteryShip(const CMysteryShip& _kr);
	CMysteryShip& operator= (const CMysteryShip& _kr);

	// Member Variables
private:
	int m_iBasePointValue;
	int m_iPointValue;
	int m_iMaskID;
	int m_iSpriteID;
	int m_iNumFrames;
};

#endif // __MYSTERYSHIP_H__

