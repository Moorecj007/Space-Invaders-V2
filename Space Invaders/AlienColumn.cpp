/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : AlienColumn.cpp
* Description : Implementation file for the AlienColumn class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

// This Includes
#include "AlienColumn.h"

/***********************
* CAlienColumn: Contructor for the AlienColumn class
* @author: Callan Moore
********************/
CAlienColumn::CAlienColumn(void)
{
	m_vecpAliens = new vector<CAlien*>;
}

/***********************
* ~CAlienColumn: Destructor for the AlienColumn class
* @author: Callan Moore
********************/
CAlienColumn::~CAlienColumn(void)
{
	vector<CAlien*>::iterator iterAliens = m_vecpAliens->begin();
	vector<CAlien*>::iterator iterAliensEnd = m_vecpAliens->end();

	while( iterAliens != iterAliensEnd)
	{
		delete (*iterAliens);
		(*iterAliens) = 0;

		iterAliens++;
	}
	delete m_vecpAliens;
	m_vecpAliens = 0;
}

/***********************
* Initialise: Initialise the AlienColumn with all its member variables
* @author: Callan Moore
* @parameter: _fX: The X coordinate that the column starts at
* @parameter: _fY: The Y coordinate that the top of the column starts at
* @return: bool: Always returns true
********************/
bool CAlienColumn::Initialise(float _fX, float _fY)
{
	CAlien* pTempAlien;
	pTempAlien = new CAlien;
	VALIDATE(pTempAlien->Initialise(3));
	m_vecpAliens->push_back(pTempAlien);
	pTempAlien = new CAlien;
	VALIDATE(pTempAlien->Initialise(2));
	m_vecpAliens->push_back(pTempAlien);
	pTempAlien = new CAlien;
	VALIDATE(pTempAlien->Initialise(2));
	m_vecpAliens->push_back(pTempAlien);
	pTempAlien = new CAlien;
	VALIDATE(pTempAlien->Initialise(1));
	m_vecpAliens->push_back(pTempAlien);
	pTempAlien = new CAlien;
	VALIDATE(pTempAlien->Initialise(1));
	m_vecpAliens->push_back(pTempAlien);

	const int kiGap = 16;
	float fCurrentX = _fX;
	float fCurrentY = _fY;

	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		((*m_vecpAliens)[i])->SetX(fCurrentX);
		((*m_vecpAliens)[i])->SetY(fCurrentY);

		fCurrentY += (pTempAlien->GetHeight() + kiGap);
	}

	return (true);
}

/***********************
* Draw: Draws all the Aliens in the column
* @author: Callan Moore
* @author: JC Fowles
* @return: void
********************/
void CAlienColumn::Draw()
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		((*m_vecpAliens)[i])->Draw();
	}
}

/***********************
* Process: Process the changes to the AlienColumn for the current delta tick
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CAlienColumn::Process(float _fDeltaTick)
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		((*m_vecpAliens)[i])->Process(_fDeltaTick);
	}
}

/***********************
* Move: Moves the AlienColumn
* @author: Callan Moore
* @parameter: _rbDirection: Movement direction of the Aliens
* @return: void
********************/
void CAlienColumn::Move(bool& _rbDirection)
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		((*m_vecpAliens)[i])->Move(_rbDirection);
	}
}

/***********************
* MoveDown: Moves the AlienColumn down
* @author: Callan Moore
* @return: void
********************/
void CAlienColumn::MoveDown()
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		((*m_vecpAliens)[i])->MoveDown();
	}
}

/***********************
* IsAlive: Returns true if at least one Alien in the Column is still alive
* @author: Callan Moore
* @return: bool: Whether the Column contains at least one alive Alien
********************/
bool CAlienColumn::IsAlive() const
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		if( (*m_vecpAliens)[i]->IsAlive())
		{
			return true;
		}
	}
	return false;
}

/***********************
* GetAliens: Retrieves the Alien Columns vector of Aliens
* @author: Callan Moore
* @return: vector<CAlien*>*: Pointer to the AlienColumns Aliens
********************/
vector<CAlien*>* CAlienColumn::GetAliens()
{
	return m_vecpAliens;
}

/***********************
* ToggleAnimation: Tells all the Aliens in the Column to toggles between animations
* @author: Callan Moore
* @return: void
********************/
void CAlienColumn::ToggleAnimation()
{
	for( unsigned int i = 0; i < m_vecpAliens->size(); i++)
	{
		if( (*m_vecpAliens)[i]->IsAlive())
		{
			(*m_vecpAliens)[i]->ToggleAnimation();
		}
	}
}

/***********************
* BelowLoseThreshold: Check if the bottom Alien of the column is below the lose threshold (At the planet)
* @author: Callan Moore
* @return: bool: True if the Bottom most Alien is below the threshold
********************/
bool CAlienColumn::BelowLoseThreshold()
{
	// Find the lowest Alien in the column that is still alive
	for( unsigned int i = (m_vecpAliens->size() - 1); i >= 0 ; i--)
	{
		if( (*m_vecpAliens)[i]->IsAlive())
		{
			return (*m_vecpAliens)[i]->BelowLoseThreshold();
			break;
		}
	}
	return false;
}
