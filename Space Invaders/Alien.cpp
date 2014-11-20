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
* @return: bool: Return true if successful
********************/
bool CAlien::Initialise(int _iType)
{
	switch(_iType)
	{
	case (1):
		{
			// Bottom two rows of Aliens
			m_iMaskID = IDB_MASKA_ALIEN1;
			m_iSpriteID = IDB_SPRITEA_ALIEN1;
			m_iPointValue = 10;
		}
		break;
	case (2):
		{
			// Middle two rows of Aliens
			m_iMaskID = IDB_MASKA_ALIEN2;
			m_iSpriteID = IDB_SPRITEA_ALIEN2;
			m_iPointValue = 20;
		}
		break;
	case (3):
		{
			// Top Single Row of Aliens
			m_iMaskID = IDB_MASKA_ALIEN3;
			m_iSpriteID = IDB_SPRITEA_ALIEN3;
			m_iPointValue = 40;
		}
		break;
	case (4):
		{
			// Menu Start Image
			m_iMaskID = IDB_MASK_START;
			m_iSpriteID = IDB_SPRITE_START;
			m_iPointValue = 0;
		}
		break;
	case (5):
		{
			// Menu Exit Image
			m_iMaskID = IDB_MASK_EXIT;
			m_iSpriteID = IDB_SPRITE_EXIT;
			m_iPointValue = 0;
		}
		break;
	case (6):
		{
			// Menu Title Image
			m_iMaskID = IDB_MASK_TITLE;
			m_iSpriteID = IDB_SPRITE_TITLE;
			m_iPointValue = 0;
		}
		break;
	default: {}
	} // End Switch

	VALIDATE(CEntity::Initialise(m_iSpriteID, m_iMaskID, m_iNumFrames));
	return (true);
}

/***********************
* Draw: Draws the Alien using Entities Draw function only if the Alien is alive
* @author: Callan Moore
* @return: void
********************/
void CAlien::Draw()
{
	// Only draw Alien if it is currently alive
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
	// Only process Alien if it is currently alive
	if (m_bAlive)
	{	
		CEntity::Process(_fDeltaTick);
	}
}

/***********************
* SetAlive: Sets the Aliens Alive state to the input state
* @author: Callan Moore
* @parameter: _bAlive: boolean value to set the state of the Alien (alive or dead)
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
* Move: Moves the Alien in its current direction
* @author: Callan Moore
* @parameter: _rbDirection: Movement direction of the Aliens
* @return: void
********************/
void CAlien::Move(bool& _rbDirection)
{
	// Only move Alien if it is currently alive
	if( m_bAlive)
	{
		if(_rbDirection == RIGHT)
		{
			CEntity::m_fX += 20;
		}
		else
		{
			CEntity::m_fX += (-20);
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
	// Only move Alien if it is currently alive
	if( m_bAlive)
	{
		CEntity::m_fY += 24;
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
* BelowLoseThreshold: Check if the Alien below the lose threshold towards the bottom of the screen
* @author: Callan Moore
* @return: bool: True if the Alien is below the threshold
********************/
bool CAlien::BelowLoseThreshold()
{
	// Only move Alien if it is currently alive
	if( m_bAlive)
	{
		if( CEntity::GetY() > 768)
		{
			return true;
		}
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