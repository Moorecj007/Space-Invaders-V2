/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : PlayerProjectile.cpp 
* Description : Implementaion file for the PlayerProjectile Class
* Author :	JC Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz 
*/

// This Include
#include "PlayerProjectile.h"

// Static Variables
CPlayerProjectile* CPlayerProjectile::s_pProjectile = 0;


/***********************
* CGame: Contructor, also initialises member variables to 0
* @author: Jc Fowles
* @return: void
********************/
CPlayerProjectile::CPlayerProjectile(void) : m_fSpeed(25)
{
	m_fTimeElapsed = 0;
	m_fLastMove = 0;
	m_bFired = false;
	m_iNumFrames = 1;
}

/***********************
* CPlayerShip: destructor, deletes the player projectile
* @author: Jc Fowles
* @return: void
********************/
CPlayerProjectile::~CPlayerProjectile(void)
{

}

/***********************
* Initialise: Initialises the projectile and it's member variables
* @author: Jc Fowles
* @return: bool : check if it initialised properly
********************/
bool CPlayerProjectile::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_SPRITE_PROJECTILE, IDB_MASK_PROJECTILE, m_iNumFrames));
	return (true);
}

/***********************
* Draw: Draws the Sprite using Entities Draw function
* @author: JC Fowles
* @return: void
********************/
void CPlayerProjectile::Draw()
{
	if(m_bFired)
	{
		CEntity::Draw();
	}
}

/***********************
* Process: Process the changes to the projectile for the current delta tick
* @author: Jc Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CPlayerProjectile::Process(float _fDeltaTick)
{
  	m_fTimeElapsed   += _fDeltaTick;
	
	if((m_fTimeElapsed - m_fLastMove) > (0.01))
	{
		fly();
		m_fLastMove = m_fTimeElapsed;
	}
	
	CEntity::Process(_fDeltaTick);
	
}

/***********************
* GetInstance: Returns the singleton instance of the projectile, if it doesnt exist creates it.
* @author: JC Fowles
* @return: CPlayerProjectile&: The current instance of the player projectile
********************/
CPlayerProjectile& CPlayerProjectile::GetInstance()
{
	if (s_pProjectile == 0)
	{
		s_pProjectile = new CPlayerProjectile();
	}
	return (*s_pProjectile);
}

/***********************
* GetInstance: Returns the singleton instance of the projectile, if it doesnt exist creates it.
* @author: JC Fowles
* @return: CPlayerProjectile&: The current instance of the player projectile
********************/
void CPlayerProjectile::DestroyInstance()
{
	delete s_pProjectile;
	s_pProjectile = 0;
}

/***********************
* setSpeed: Sets the players projectile speed
* @author: Jc Fowles
* @parameter: _fSpeed: The speed the projectile moves
* @return: void
********************/
void CPlayerProjectile::SetSpeed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}

/***********************
* getSpeed: Gets the projectile ships speed
* @author: Jc Fowles
* @return: float: the speed the projectile moves
********************/
float CPlayerProjectile::GetSpeed()
{
	return m_fSpeed;
}

/***********************
* fly: Gets the projectile ships speed
* @author: Jc Fowles
* @return: float: the speed the projectile moves
********************/
void CPlayerProjectile::fly()
{
	CEntity::m_fY += (-1);
}


/***********************
* Fired: checks to see if the player has fired the projectile 
* @author: Jc Fowels
* @return: bool: true if fired
********************/
bool CPlayerProjectile::Fired()
{
	return m_bFired;
}

/***********************
* Fired: Sets the is fired boolean
* @author: Jc Fowels
* @return: void
********************/
void CPlayerProjectile::setFired(bool _bFired)
{
	m_bFired = _bFired;
}