/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Alien.h
* Description : Header file for the Alien class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

#pragma once

#if !defined(__ALIEN_H__)
#define __ALIEN_H__

// Local Includes
#include "Entity.h"
#include "resource.h"
#include "Utilities.h"

class CAlien : public CEntity
{
	// Member Functions
public:
	CAlien(void);
	virtual ~CAlien(void);
	virtual bool Initialise(int _iType);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void Move(bool& _rbDirection);
	void MoveDown();
	void ToggleAnimation();

	bool IsAlive() const;
	bool BelowLoseThreshold();

	// Getters
	int GetPoints();

	// Setters
	void SetAlive(bool _b);
	
private:
	// Disallowing copies
	CAlien(const CAlien& _kr);
	CAlien& operator= (const CAlien& _kr);

	// Member Variables
protected:
	int m_iPointValue;
	int m_iMaskID;
	int m_iSpriteID;
	int m_iNumFrames;

	bool m_bAlive;
};

#endif // __ALIEN_H__
