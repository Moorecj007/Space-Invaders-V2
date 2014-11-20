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
* CPlayerProjectile: Contructor, also initialises member variables to 0
* @author: Jc Fowles
* @return: void
********************/
CPlayerProjectile::CPlayerProjectile(void) 
{
	m_fVelocity = (0.0f);
	m_bFired = false;
	m_iNumFrames = 1;
}

/***********************
* ~CPlayerProjectile: Destructor, deletes the player projectile
* @author: Jc Fowles
* @return: void
********************/
CPlayerProjectile::~CPlayerProjectile(void)
{

}

/***********************
* Initialise: Initialises the projectile and it's member variables
* @author: Jc Fowles
* @return: bool : True if successful
********************/
bool CPlayerProjectile::Initialise(float _fPosX, float _fPosY, float _fVelocity)
{
	VALIDATE(CEntity::Initialise(IDB_SPRITE_PROJECTILE, IDB_MASK_PROJECTILE, m_iNumFrames));

	// Starting coordinates
	m_fX = _fPosX;
    m_fY = _fPosY;

	// Starting velocity
    m_fVelocity = _fVelocity;

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
		// Only draw if it has been fired
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
	m_fY += m_fVelocity * _fDeltaTick;
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
* DestroyInstance: Destroys the singleton instance of the player projectile
* @author: JC Fowles
* @return: void
********************/
void CPlayerProjectile::DestroyInstance()
{
	delete s_pProjectile;
	s_pProjectile = 0;
}

/***********************
* Fired: Checks to see if the player has fired the projectile 
* @author: Jc Fowless
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

/***********************
* GetVelocity: Gets the player ships projectile speed
* @author: Jc Fowles
* @return: float: The speed the projectile moves
********************/
float CPlayerProjectile::GetVelocity() const
{
    return (m_fVelocity);
}

/***********************
* SetVelocity: Sets the player ships projectile speed
* @author: Jc Fowles
* @parameter: _fSpeed: The speed the projectile moves
* @return: void
********************/
void CPlayerProjectile::SetVelocity(float _fY)
{
    m_fVelocity = _fY;
}

