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
	~CAlien(void);
	virtual bool Initialise(int _iType);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void SetAlive(bool _b);
	bool IsAlive() const;
	void Move(bool& _rbDirection);
	void MoveDown();
	void ToggleAnimation();
	bool BelowLoseThreshold();
	int GetPoints();

private:
	// Disallowing copies
	CAlien(const CAlien& _kr);
	CAlien& operator= (const CAlien& _kr);

	// Member Variables
protected:
	int m_iPointValue;
	bool m_bAlive;
	int m_iMaskID;
	int m_iSpriteID;
	int m_iNumFrames;

};

#endif // __ALIEN_H__
