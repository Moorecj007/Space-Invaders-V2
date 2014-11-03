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

// This Include
#include "PlayerShip.h"

CPlayerShip::CPlayerShip(void)
{
	m_fSpeed = 10.0;
	m_iNumFrames = 1;
}


CPlayerShip::~CPlayerShip(void)
{
}

bool CPlayerShip::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_SPRITE_PLAYERSHIP, IDB_MASK_PLAYERSHIP, m_iNumFrames));
	return (true);
}

void CPlayerShip::Draw()
{
	CEntity::Draw();
}

void CPlayerShip::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}


void CPlayerShip::setSpeed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}

float CPlayerShip::getSpeed()
{
	return m_fSpeed;
}


/***********************
* SetX: Sets the X value of the plyerShip 
* @author: Jc Fowels
* @parameter: _f: The new X value
* @return: void
********************/
/*
void CPlayerShip::SetX(float _f)
{
	if((!(_f < GetWidth()/2)) && !(672 - (GetWidth()/2)))
	{
		m_fX = _f;
	}
	
}*/