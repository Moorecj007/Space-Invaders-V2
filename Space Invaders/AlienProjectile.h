/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : AlienProjectile.h
* Description : Header file for the AlienProjectile class
* Author :	Jc Fowles
* Mail :	JC.Fowles@mediadesign.school.nz
*/

#pragma once

#if !defined(__ALIENPROJECTILE_H__)
#define __ALIENPROJECTILE_H__

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "resource.h"
#include "utilities.h"

class CAlienProjectile :  public CEntity
{
public:
	CAlienProjectile(void);
	virtual ~CAlienProjectile(void);
	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY, int iType);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	// Getters
	bool GetDestroyed();
	float GetVelocity() const;

	// Setters
    void SetVelocity(float _fY);
	void SetDestroyed(bool _bDestroy);
	
private:
	// Disallowing Copies
	CAlienProjectile(const CAlienProjectile& _kr);
	CAlienProjectile& operator= (const CAlienProjectile& _kr);

protected:
	float m_fVelocity;
	float m_fTimeElapsed;
	float m_fLastMove;

	bool m_bFired;
	bool m_bDestroy;

	int m_iNumFrames;
};

#endif //__ALIENPROJECTILE_H__