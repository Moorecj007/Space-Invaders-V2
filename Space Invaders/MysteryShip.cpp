/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : MysteryShip.cpp
* Description : Implementation file for the Mystery Ship class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

// Local Includes
#include "resource.h"
#include "Utilities.h"

// This Includes
#include "MysteryShip.h"

/***********************
* CMysteryShip: Contructor for the Mystery Ship class
* @author: Callan Moore
********************/
CMysteryShip::CMysteryShip(void)
{
	m_iBasePointValue = 50;
	m_iNumFrames = 1;
}

/***********************
~CMysteryShip: Destructor for the Mystery Ship class
* @author: Callan Moore
********************/
CMysteryShip::~CMysteryShip(void)
{

}

/***********************
* Initialise: Initialise the Mystery Ship using Entities Initialise with the its Sprite and Mask IDs
* @author: Callan Moore
* @return: bool: Always returns true
********************/
bool CMysteryShip::Initialise()
{
	// Selects the Mask and Sprite Resource IDs
	m_iMaskID = IDB_MASKA_MYSSHIP;
	m_iSpriteID = IDB_SPRITEA_MYSSHIP;

	// Generate the point value to award player if destroyed
	int iPointMultiplier = (rand() % 6);
	m_iPointValue = 50 * iPointMultiplier;

	VALIDATE(CEntity::Initialise(m_iSpriteID, m_iMaskID, m_iNumFrames));

	// Set starting coordinates slightly off the screen
	CEntity::SetX(-1*GetHeight());
	CEntity::SetY(90);
	return (true);
}

/***********************
* Draw: Draws the Sprite using Entities Draw function
* @author: Callan Moore
* @return: void
********************/
void CMysteryShip::Draw()
{
	CEntity::Draw();
}

/***********************
* Process: Process the changes to the Mystery Ship for the current delta tick
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CMysteryShip::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

/***********************
* Move: Moves the Mystery Ship across the screen
* @author: Callan Moore
* @return: void
********************/
void CMysteryShip::Move()
{
	CEntity::m_fX += 10;
}

/***********************
* GetPoints: Retrieves the points to award the player with
* @author: Callan Moore
* @return: int: The points to award the player
********************/
int CMysteryShip::GetPoints()
{
	int iMultiplier = rand() % 6 + 1;
	return ( iMultiplier * m_iBasePointValue);
}