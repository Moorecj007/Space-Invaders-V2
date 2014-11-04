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
	m_fSpeed = 10.0;
	m_bFired = false;
	m_iNumFrames = 1;
}

/***********************
* CPlayerShip: destructor, deletes the playerShip
* @author: Jc Fowles
* @return: void
********************/
CPlayerShip::~CPlayerShip(void)
{
}

/***********************
* Initialise: Initialises the playerShip and it's member variables
* @author: Jc Fowles
* @return: bool : check if it initialesed properly
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
	CEntity::Process(_fDeltaTick);
}

/***********************
* setSpeed: Sets the players ships speed
* @author: Jc Fowles
* @parameter: _fSpeed: The speed the playerShip moves
* @return: void
********************/
void CPlayerShip::SetSpeed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}

/***********************
* getSpeed: Gets the players ships speed
* @author: Jc Fowles
* @return: float: the speed the playership moves
********************/
float CPlayerShip::GetSpeed()
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