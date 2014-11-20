/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : AlienProjectile.cpp 
* Description : Implementaion file for the AlienProjectile Class
* Author :	JC Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz 
*/

// This Include
#include "AlienProjectile.h"

/***********************
* CAlienProjectile: Contructor for the AlienProjectile class
* @author: Jc Fowles
********************/
CAlienProjectile::CAlienProjectile(void)
{
	m_fVelocity = (500.0f);
	m_iNumFrames = 1;
}

/***********************
* ~CAlienProjectile: Destructor for the AlienProjectile class
* @author: Jc Fowles
********************/
CAlienProjectile::~CAlienProjectile(void)
{
}

/***********************
* Initialise: Initialises the projectile and it's member variables
* @author: Jc Fowles
* @return: bool : True if successful
********************/
bool CAlienProjectile::Initialise(float _fPosX, float _fPosY, float _fVelocity)
{
	VALIDATE(CEntity::Initialise(IDB_SPRITEA_BOLT , IDB_MASKA_BOLT, m_iNumFrames));

	// Set Initial Positioning
	m_fX = _fPosX;
    m_fY = _fPosY;

	// Set initial velocity
    m_fVelocity = _fVelocity;

	return (true);
}

/***********************
* Draw: Draws the Sprite using Entities Draw function
* @author: JC Fowles
* @return: void
********************/
void CAlienProjectile::Draw()
{
	CEntity::Draw();
}

/***********************
* Process: Process the changes to the projectile for the current delta tick
* @author: Jc Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CAlienProjectile::Process(float _fDeltaTick)
{
	// Set the new Y coordinate of the Projectile
	m_fY += m_fVelocity * _fDeltaTick;
	CEntity::Process(_fDeltaTick);
}

/***********************
* GetVelocity: Gets the Alien Projectilee speed
* @author: Jc Fowles
* @return: float: the speed the projectile moves
********************/
float CAlienProjectile::GetVelocity() const
{
    return (m_fVelocity);
}

/***********************
* SetVelocity: Sets the Alien ships projectile speed
* @author: Jc Fowles
* @parameter: _fSpeed: The speed the projectile moves
* @return: void
********************/
void CAlienProjectile::SetVelocity(float _fY)
{
    m_fVelocity = _fY;
}

/***********************
* SetDestroy: Sets the projectile to be destroyed or not
* @author: Jc Fowles
* @parameter: _bDestroy: True if to be destroyed
* @return: void
********************/
void CAlienProjectile::SetDestroyed(bool _bDestroy)
{
	m_bDestroy = _bDestroy;
}

/***********************
* GetDestroyed: Retrieves whether the projectile is to be destroyed or not
* @author: Jc Fowles
* @parameter: _bDestroy: True if to be destroyed
* @return: bool; true if the projectile is to be destroyed
********************/
bool CAlienProjectile::GetDestroyed()
{
	return m_bDestroy;
}