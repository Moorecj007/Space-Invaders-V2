/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Alien.cpp
* Description : Implementation file for the Alien class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

// This Includes
#include "Alien.h"

/***********************
* CAlien: Contructor for the Alien class
* @author: Callan Moore
********************/
CAlien::CAlien(void)
{
	m_bAlive = true;
	m_iNumFrames = 1;
}

/***********************
* ~CAlien: Destructor for the Alien class
* @author: Callan Moore
********************/
CAlien::~CAlien(void)
{
}

/***********************
* Initialise: Initialise the Alien using Entities Initialise with the its Sprite and Mask IDs
* @author: Callan Moore
* @parameter: _iType: Integer representing the type of Alien to initialise
* @return: bool: Always returns true
********************/
bool CAlien::Initialise(int _iType)
{
	switch(_iType)
	{
	case (1):
		{
			m_iMaskID = IDB_MASKA_ALIEN1;
			m_iSpriteID = IDB_SPRITEA_ALIEN1;
			m_iPointValue = 1000;
		}
		break;
	case (2):
		{
			m_iMaskID = IDB_MASKA_ALIEN2;
			m_iSpriteID = IDB_SPRITEA_ALIEN2;
			m_iPointValue = 2000;
		}
		break;
	case (3):
		{
			m_iMaskID = IDB_MASKA_ALIEN3;
			m_iSpriteID = IDB_SPRITEA_ALIEN3;
			m_iPointValue = 4000;
		}
		break;
	default: {}
	} // End Switch

	VALIDATE(CEntity::Initialise(m_iSpriteID, m_iMaskID, m_iNumFrames));
	return (true);
}

/***********************
* Draw: Draws the Sprite using Entities Draw function only if the Alien is alive
* @author: Callan Moore
* @return: void
********************/
void CAlien::Draw()
{
	if (m_bAlive)
	{
		CEntity::Draw();
	}
}

/***********************
* Process: Process the changes to the Alien for the current delta tick if the Alien is alive
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CAlien::Process(float _fDeltaTick)
{
	if (m_bAlive)
	{	
		CEntity::Process(_fDeltaTick);
	}
}

/***********************
* SetAlive: Sets the Aliens Alive state to the input state
* @author: Callan Moore
* @parameter: _bAlive: boolean value to set the state of the Alien (alive of dead)
* @return: void
********************/
void CAlien::SetAlive(bool _bAlive)
{
	m_bAlive = _bAlive;
}

/***********************
* IsAlive: Returns true or false dependent on whether the Alien is alive
* @author: Callan Moore
* @return: bool: Returns true if the Alien is alive
********************/
bool CAlien::IsAlive() const
{
	return m_bAlive;
}

/***********************
* Move: Moves the Alien in its current direction. Drops down and reverses direction if at screen edge
* @author: Callan Moore
* @parameter: _rbDirection: Movement direction of the Aliens
* @return: void
********************/
void CAlien::Move(bool& _rbDirection)
{
	if( m_bAlive)
	{
		if(_rbDirection == RIGHT)
		{
			CEntity::m_fX += 10;
		}
		else
		{
			CEntity::m_fX += (-10);
		}
	}
}

/***********************
* MoveDown: Moves the Alien down
* @author: Callan Moore
* @return: void
********************/
void CAlien::MoveDown()
{
	if( m_bAlive)
	{
		CEntity::m_fY += 10;
	}
}

/***********************
* ToggleAnimation: Toggles between the Aliens two animations
* @author: Callan Moore
* @return: void
********************/
void CAlien::ToggleAnimation()
{
	(*CEntity::m_pSprite).SetFrame( ((*CEntity::m_pSprite).GetFrame() + 1) % m_iNumFrames);
}

/***********************
* BelowLoseThreshold: Check if the Alien below the lose threshold (At the planet)
* @author: Callan Moore
* @return: bool: True if the Alien is below the threshold
********************/
bool CAlien::BelowLoseThreshold()
{
	if( CEntity::GetY() > 610)
	{
		return true;
	}
	return false;
}

/***********************
* GetPoints: Retrieves the points to award the player with
* @author: Callan Moore
* @return: int: The points to award the player
********************/
int CAlien::GetPoints()
{
	return (m_iPointValue);
}