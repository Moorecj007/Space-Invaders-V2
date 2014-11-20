/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Barrier.cpp
* Description : Implementation file for the Barrier class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

// This Include
#include "Barrier.h"

/***********************
* CBarrier: Contructor for the Barrier class
* @author: Callan Moore
********************/
CBarrier::CBarrier(void)
{
	m_iHealth = 24;
	m_iNumFrames = 6;
	m_bAlive = true;
}

/***********************
* ~CBarrier: Destructor for the Barrier class
* @author: Callan Moore
********************/
CBarrier::~CBarrier(void)
{
}

/***********************
* Initialise: Initialise the Barrier with all its member variables
* @author: Callan Moore
* @parameter: _fX: The X coordinate for the centre of the Barrier
* @parameter: _fY: The Y coordinate for the centre of the Barrier
* @return: bool: Return true if successful
********************/
bool CBarrier::Initialise(float _fX, float _fY)
{
	m_iMaskID = IDB_MASK_BARRIER;
	m_iSpriteID = IDB_SPRITE_BARRIER;

	VALIDATE(CEntity::Initialise(m_iSpriteID, m_iMaskID, m_iNumFrames));

	CEntity::m_pSprite->SetFrame(5);
	SetX(_fX);
	SetY(_fY);

	return true;
}

/***********************
* Draw: Draws The Barrier
* @author: Callan Moore
* @return: void
********************/
void CBarrier::Draw()
{
	// Draw only if the Barrier is alive
	if( m_bAlive == true)
	{
		CEntity::Draw();
	}
}

/***********************
* Process: Process the changes to the barrier for the current delta tick
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CBarrier::Process(float _fDeltaTick)
{
	// Process only if the Barrier is alive
	if (m_bAlive)
	{	
		CEntity::Process(_fDeltaTick);
	}
}

/***********************
* DecreaseHealth: Decrease the Health of the barrier by 1 and change the image frame
* @author: Callan Moore
* @return: void
********************/
void CBarrier::DecreaseHealth()
{
	m_iHealth--;

	// Change the image(frame) of the Barrier based upon its remaining health
	if( m_iHealth == 0)
	{
		m_bAlive = false;
	}
	else if( m_iHealth < 4)
	{
		CEntity::m_pSprite->SetFrame(0);
	}
	else if( m_iHealth < 8)
	{
		CEntity::m_pSprite->SetFrame(1);
	}
	else if( m_iHealth < 12)
	{
		CEntity::m_pSprite->SetFrame(2);
	}
	else if( m_iHealth < 16)
	{
		CEntity::m_pSprite->SetFrame(3);
	}
	else if( m_iHealth < 20)
	{
		CEntity::m_pSprite->SetFrame(4);
	}
	else if( m_iHealth < 24)
	{
		CEntity::m_pSprite->SetFrame(5);
	}
}

/***********************
* isAlive: Return if the barrier is alive
* @author: Callan Moore
* @return: void
********************/
bool CBarrier::IsAlive()
{
	return m_bAlive;
}

/***********************
* ResetHealth: Reset the Barrier to initial values
* @author: Callan Moore
* @return: void
********************/
void CBarrier::ResetHealth()
{
	m_iHealth = 24;
	m_bAlive = true;
	CEntity::m_pSprite->SetFrame(5);
}

