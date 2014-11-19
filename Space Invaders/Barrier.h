/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Barrier.h
* Description : Header file for the Barrier class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

#pragma once

// Library Includes

// Local Includes
#include "Entity.h"

class CBarrier : public CEntity
{
	// Member Functions
public:
	CBarrier(void);
	~CBarrier(void);
	virtual bool Initialise(float _fX, float _fY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void DecreaseHealth();

private:
	// Disallowing copies
	CBarrier(const CBarrier& _kr);
	CBarrier& operator= (const CBarrier& _kr);

	// Member Variables
private:
	int m_iSpriteID;
	int m_iMaskID;

	int m_iHealth;
	int m_iImageIndex;
	int m_iNumFrames;
	bool m_bAlive;
};

