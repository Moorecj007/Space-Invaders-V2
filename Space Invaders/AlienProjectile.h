/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : PlayerProjectile.h
* Description : Header file for the PlayerProjectile class
* Author :	Jc Fowles
* Mail :	JC.Fowles@mediadesign.school.nz
*/

#pragma once

#if !defined(__ALIENPROJECTILE_H__)

#define __ALIENPROJECTILE_H__
// Library Includes

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

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	float GetVelocity() const;
    void SetVelocity(float _fY);

	void SetDestroyed(bool _bDestroy);
	bool GetDestroyed();

private:
	
	CAlienProjectile(const CAlienProjectile& _kr);
	CAlienProjectile& operator= (const CAlienProjectile& _kr);

protected:
	float m_fVelocity;
	bool m_bFired;

	bool m_bDestroy;

	int m_iNumFrames;

	float m_fTimeElapsed;
	float m_fLastMove;

};

#endif //__ALIENPROJECTILE_H__