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

#if !defined(__PLAYERPROJECTILE_H__)
#define __PLAYERPROJECTILE_H__

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "resource.h"
#include "utilities.h"

class CPlayerProjectile : public CEntity
{
	// Member Functions
public:
	// Singleton Methods
	static CPlayerProjectile& GetInstance();
	static void DestroyInstance();
	
	virtual ~CPlayerProjectile(void);
	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	bool Fired();

	// Getters
	float GetVelocity() const;

	// Setters
    void SetVelocity(float _fY);
	void setFired(bool _bFired);
	
private:
	// Disallowing Copies
	CPlayerProjectile(void);
	CPlayerProjectile(const CPlayerProjectile& _kr);
	CPlayerProjectile& operator= (const CPlayerProjectile& _kr);

	// Member Variables
protected:
	float m_fVelocity;

	bool m_bFired;

	int m_iNumFrames;

	// Singleton Instance
	static CPlayerProjectile* s_pProjectile;
};

#endif //__PLAYERPROJECTILE_H__