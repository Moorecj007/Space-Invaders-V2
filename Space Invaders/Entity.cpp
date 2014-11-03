/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Entity.cpp
* Description : Implementation file for the Entity class
* Author :	Asma Shakil
*			Callan Moore
*			JC Fowles
* Mail :	Asma.shakil@mediadesign.school.nz
*			Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz		
*/

// This Include
#include "entity.h"

/***********************
* CEntity: Contructor for the Entity class
* @author: Asma Shakil
********************/
CEntity::CEntity()	: m_fX(0.0f)
					, m_fY(0.0f)
{
}

/***********************
* ~CEntity: Destructor for the Entity class
* @author: Asma Shakil
********************/
CEntity::~CEntity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

/***********************
* Initialise: Initialises the entity and creates its sprite (image)
* @author: Asma Shakil
* @author: Callan Moore
* @parameter: _kiSpriteID: Integer value used to locate the sprites image when initialising the sprite
* @parameter: _kiMaskID: Integer value to locate the sprites mask when initialising the sprite
* @parameter: _iMaxFrames: The The maximum number of frames for the sprite to have
* @return: bool: always returns true
********************/
bool CEntity::Initialise(const int _kiSpriteID, const int _kiMaskID, int _iNumFrames)
{
	m_pSprite = new CSprite();
	VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID, _iNumFrames));
	return (true);
}

/***********************
* Draw: Calls the entities sprites draw function
* @author: Asma Shakil
* @return: void
********************/
void CEntity::Draw()
{
	m_pSprite->Draw();
}

/***********************
* Process: Process the changes to the entity for the current delta tick
* @author: Asma Shakil
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CEntity::Process(float _fDeltaTick)
{
	m_pSprite->SetX(static_cast<int>(m_fX));
	m_pSprite->SetY(static_cast<int>(m_fY));
	m_pSprite->Process(_fDeltaTick);
}

/***********************
* GetX: Retrieves the Entities X value
* @author: Asma Shakil
* @return: float: The X value
********************/
float CEntity::GetX() const
{
	return (m_fX);
}

/***********************
* GetY: Retrieves the Entities Y value
* @author: Asma Shakil
* @return: float: The Y value
********************/
float CEntity::GetY() const
{
	return (m_fY);
}

/***********************
* GetWidth: Retrieves the Sprites width that is owned by the Entity
* @author: Asma Shakil
* @return: float: The Sprites width
********************/
float CEntity::GetWidth() const
{
	return (static_cast<float>(m_pSprite->GetWidth()));
}

/***********************
* GetHeight: Retrieves the Sprites height that is owned by the Entity
* @author: Asma Shakil
* @return: float: The Sprites height
********************/
float CEntity::GetHeight() const
{
	return (static_cast<float>(m_pSprite->GetHeight()));
}

/***********************
* SetX: Sets the X value of the Entity to the input value
* @author: Asma Shakil
* @parameter: _f: The new X value
* @return: void
********************/
void CEntity::SetX(float _f)
{
	m_fX = _f;
}

/***********************
* SetY: Sets the Y value of the Entity to the input value
* @author: Asma Shakil
* @parameter: _f: The new Y value
* @return: void
********************/
void CEntity::SetY(float _f)
{
	m_fY = _f;
}