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

/***********************
* CPlayerShip: Contructor, also initialises member variables to 0
* @author: Jc Fowles
* @return: void
********************/
CPlayerShip::CPlayerShip(void)
{
	m_fVelocity = 0.0f;
	m_bFired = false;
	m_iNumFrames = 1;
	m_bDestroy = false;
}

/***********************
* CPlayerShip: Destructor, deletes the player Ship
* @author: Jc Fowles
* @return: void
********************/
CPlayerShip::~CPlayerShip(void)
{
}

/***********************
* Initialise: Initialises the playerShip and it's member variables
* @author: Jc Fowles
* @return: bool : true if successful
********************/
bool CPlayerShip::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_SPRITE_PLAYERSHIP, IDB_MASK_PLAYERSHIP, m_iNumFrames));
	return (true);
}

/***********************
* Draw: Draws the Sprite using Entities Draw function
* @author: JC Fowles
* @return: void
********************/
void CPlayerShip::Draw()
{
	CEntity::Draw();
}

/***********************
* Process: Process the changes to the PlayerShip for the current delta tick
* @author: Jc Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CPlayerShip::Process(float _fDeltaTick)
{
	m_fX += m_fVelocity*_fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

/***********************
* Fired: checks to see if the player has fired the projectile 
* @author: Jc Fowels
* @return: bool: true if fired
********************/
bool CPlayerShip::Fired()
{
	return m_bFired;
}

/***********************
* Fired: Sets the is fired boolean
* @author: Jc Fowels
* @return: void
********************/
void CPlayerShip::setFired(bool _bFired)
{
	m_bFired = _bFired;
}

/***********************
* GetVelocity: Gets the players ships speed
* @author: Jc Fowles
* @return: float: the speed the playership moves
********************/
float CPlayerShip::GetVelocity() const
{
    return (m_fVelocity);
}

/***********************
* SetVelocity: Sets the players ships speed
* @author: Jc Fowles
* @parameter: _fSpeed: The speed the playerShip moves
* @return: void
********************/
void CPlayerShip::SetVelocity(float _fX)
{
    m_fVelocity = _fX;
}

/***********************
* SetDestroy: Sets the projectile to be destroyed or not
* @author: Jc Fowles
* @parameter: _bDestroy: True if to be destroyed
* @return: void
********************/
void CPlayerShip::SetDestroyed(bool _bDestroy)
{
	m_bDestroy = _bDestroy;
}

/***********************
* GetDestroyed: Retrieves whether the projectile to be destroyed or not
* @author: Jc Fowles
* @return: bool: True if it is to be destroyed
********************/
bool CPlayerShip::GetDestroyed()
{
	return m_bDestroy;
}