/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Leave.cpp
* Description : Implementation file for the Level class
* Author :	Callan Moore
* Author :	Jc Fowles
* Mail :	Callan.moore@mediadesign.school.nz	
* Mail :	Jc.Fowles@mediadesign.school.nz	
*/

// This Include
#include "Level.h"

/***********************
* CLevel: Contructor for the Level class
* @author: Callan Moore
********************/
CLevel::CLevel()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_pPlayerShip = 0;
	m_pAlienColumns = new vector<CAlienColumn*>;

	m_fTimeElapsed = 0;
	m_fAlienLastMove = 0;
	m_fMysteryShipLastMove = 0;
	m_bAlienDirection = RIGHT;
}

/***********************
* ~CLevel: Destructor for the Level class
* @author: Callan Moore
********************/
CLevel::~CLevel()
{

}

/***********************
* Initialise: Initialise all the member variables of the Level class
* @author: Callan Moore
* @author: JC Fowles
* @parameter: _iWidth: Width of the window for the level to cover
* @parameter: _iHeight: Height of the window for the level to cover
* @parameter: _hWnd: Handle to the Window
* @return: bool: Always returns true
********************/
bool CLevel::Initialise(int _iWidth, int _iHeight, HWND _hWnd)
{
	m_hWnd = _hWnd;

	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	//Player Ship creation and positioning
	m_pPlayerShip = new CPlayerShip();
	VALIDATE(m_pPlayerShip->Initialise());
	//position based: x middle of image
	//				  y top of image
	m_pPlayerShip->SetX(_iWidth/2.0f);  // from the left
	m_pPlayerShip->SetY(_iHeight - ( 2 * m_pPlayerShip->GetHeight()));  // from the bottom of the screen


	// Alien Wave Setup constants
	const int kiNumAlienColumns = 11;
	const int kiStartX = 50;
<<<<<<< HEAD
	const int kiStartY = 350;
	const int kiGap = 13;
=======
	const int kiStartY = 200;
	const int kiGap = 15;
>>>>>>> origin/Moore

	// Values to Set up each Alien Column with
	m_fAlienSpeed = 01.0f;

	float fCurrentX = kiStartX;
	float fCurrentY = kiStartY;
	CAlienColumn* pTempAlienColumn = 0;
	float fColumnWidth = 35;

	// Create and push back AlienColumns into the vector of Columns
	for( int i = 0; i < kiNumAlienColumns; i++)
	{
		pTempAlienColumn = new CAlienColumn;
		VALIDATE(pTempAlienColumn->Initialise(fCurrentX, fCurrentY));
		m_pAlienColumns->push_back(pTempAlienColumn);

		fCurrentX += (fColumnWidth + kiGap);
	}

	// Mystery Ship Variable initialisations
	m_pMysteryShip = 0;
	m_fMysteryShipSpeed = 0.1f;

	return true;
}

/***********************
* Draw: Draws all the entities that make up the level
* @author: Callan Moore
* @author: JC Fowles
* @return: void
********************/
void CLevel::Draw()
{
	m_pPlayerShip->Draw();
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		((*m_pAlienColumns)[i])->Draw();
	}
<<<<<<< HEAD
=======

	DrawScore();

	if( m_pMysteryShip != 0)
	{
		m_pMysteryShip->Draw();
	}
>>>>>>> origin/Moore
	//draw all things 
}

/***********************
* Process: Process the changes to the Level for the current delta tick
* @author: Callan Moore
* @author: JC Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CLevel::Process(float _fDeltaTick)
{
<<<<<<< HEAD
	m_pPlayerShip->Process(_fDeltaTick);

	AlienControl(_fDeltaTick);
=======
	m_fTimeElapsed += _fDeltaTick;

	if(m_pPlayerShip->Fired()) 
	{
		for(int i = 0; i < m_pProjectile->GetSpeed() ; i++)
		{
			m_pProjectile->Process(_fDeltaTick);
		}
	}
	
	m_pPlayerShip->Process(_fDeltaTick);

	if(ProjectileCollisionCheck())
	{
		m_pProjectile->SetY(m_pPlayerShip->GetY()+1);
		m_pProjectile->SetX(m_pPlayerShip->GetX());
		m_pProjectile->Process(_fDeltaTick);
	}
   
  	AlienControl();
>>>>>>> origin/Moore
	// Process all the Alien Columns
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		((*m_pAlienColumns)[i])->Process(_fDeltaTick);
	}
<<<<<<< HEAD
=======
	
	MysteryShipControl(_fDeltaTick);

>>>>>>> origin/Moore
}

/***********************
* GetPlayerShip: Retrieves the Levels Playership pointer
* @author: Jc Fowles
* @return: CPlayerShip*: Pointer the the levels playership
********************/
CPlayerShip* CLevel::GetPlayerShip() const
{
	return (m_pPlayerShip);
}

/***********************
* AlienControl: Controls the aliens movement and firing
* @author: Callan Moore
* @return: void
********************/
void CLevel::AlienControl()
{
	bool bMoveDown = false;

	// Moves the Alien Columns once the fAlienSpeed ( in seconds) has passed since they were last moved
	if( (m_fTimeElapsed - m_fAlienLastMove) > m_fAlienSpeed)
	{
		if( m_bAlienDirection == RIGHT)
		{
			for( unsigned int i = (m_pAlienColumns->size() - 1); i >= 0; i--)
			{
				if( (*m_pAlienColumns)[i]->IsAlive())
				{
					vector<CAlien*>* pRightMostColumn = ((*m_pAlienColumns)[i]->GetAliens());
					for( unsigned int j = 0; j < pRightMostColumn->size(); j++)
					{
						if( (*pRightMostColumn)[j]->IsAlive())
						{
							float fRightMostAlienX = (*pRightMostColumn)[j]->GetX();   
							float fRightMostAlienWidth = (*pRightMostColumn)[j]->GetWidth();

							if( (fRightMostAlienX + (fRightMostAlienWidth / 2) + 25) > 672)
							{
								m_bAlienDirection = LEFT;
								bMoveDown = true;
							}
							break;
						}
					}
					break;
				}
			}
		}
		else
		{
			for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
			{
				if( (*m_pAlienColumns)[i]->IsAlive())
				{
					vector<CAlien*>* pLeftMostColumn = ((*m_pAlienColumns)[i]->GetAliens());
					for( unsigned int j = 0; j < pLeftMostColumn->size(); j++)
					{
						if( (*pLeftMostColumn)[j]->IsAlive())
						{
							float fLeftMostAlienX = (*pLeftMostColumn)[j]->GetX();   
							float fLeftMostAlienWidth = (*pLeftMostColumn)[j]->GetWidth();

							if( (fLeftMostAlienX - (fLeftMostAlienWidth / 2) - 10) <= 0)
							{
								m_bAlienDirection = RIGHT;
								bMoveDown = true;
							}
							break;
						}
					}
					break;
				}
			}
		}

		// Moves the Aliens Down or in their current direction
		for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
		{
			((*m_pAlienColumns)[i])->ToggleAnimation();		
			if( bMoveDown)
			{
				((*m_pAlienColumns)[i])->MoveDown();
			}
			else
			{
				((*m_pAlienColumns)[i])->Move(m_bAlienDirection);
			}
			
			// Check each column for having an Alien below Lose threshold
			if( ((*m_pAlienColumns)[i])->BelowLoseThreshold())
			{
				MessageBox( m_hWnd, L"YOU LOSE", L"LOSER", MB_OK);
				break;
			}

			// Fire
			// Place FIRE STUFF HERE
		}
		m_fAlienLastMove = m_fTimeElapsed;
	}
}

/***********************
* MysteryShipControl: Controls the MysteryShip Movement
* @author: Callan Moore
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: bool: Always return true
********************/
bool CLevel::MysteryShipControl(float _fDeltaTick)
{
	if( m_pMysteryShip == 0)
	{
		int iRandomNumber = rand() % 10000;
		if( iRandomNumber < 10)
		{
			m_pMysteryShip = new CMysteryShip;
			VALIDATE(m_pMysteryShip->Initialise());
		}
	}
	else
	{
		if( (m_fTimeElapsed - m_fMysteryShipLastMove) > m_fMysteryShipSpeed)
		{
			m_pMysteryShip->Move();
			m_fMysteryShipLastMove = m_fTimeElapsed;
		}

		m_pMysteryShip->Process(_fDeltaTick);
	}

	return (true);
}