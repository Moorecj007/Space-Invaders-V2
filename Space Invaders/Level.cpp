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
* @author: Jc Fowles
********************/
CLevel::CLevel()
{
	m_fPlayerShipSpeed = 125.0f;
	m_fProjectileSpeed = 500.0f;

	m_iWidth = 0;
	m_iHeight = 0;
	m_pPlayerShip = 0;
	m_pAlienColumns = new vector<CAlienColumn*>;

	m_fTimeElapsed = 0;
	m_fAlienLastMove = 0;
	m_fMysteryShipLastMove = 0;
	m_bAlienDirection = RIGHT;
	m_iScore = 0;

	m_bLevelReset;

}

/***********************
* ~CLevel: Destructor for the Level class
* @author: Callan Moore
********************/
CLevel::~CLevel()
{
	//ship
	//aliens columns
	//player projectile
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

	//Projectile creation and positioning
	const float fBallVelY = 75.0f;
	m_pProjectile = &(CPlayerProjectile::GetInstance());
	VALIDATE(m_pProjectile->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  fBallVelY));
	//position based: x middle of image
	//				  y top of image
	m_pProjectile->SetX(_iWidth/2.0f);  // from the left
	m_pProjectile->SetY(_iHeight - ( 2 * m_pPlayerShip->GetHeight()));  // from the bottom of the screen

	// Alien Wave Setup constants
	const int kiNumAlienColumns = 11;
	const int kiStartX = 50;
	const int kiStartY = 200;
	const int kiGap = 15;

	// Values to Set up each Alien Column with
	m_fAlienSpeed = 0.25f;

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
	m_fMysteryShipSpawnTimer = -10;

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
	m_pProjectile->Draw();
	m_pPlayerShip->Draw();

	m_pPlayerShip->Draw();
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		((*m_pAlienColumns)[i])->Draw();
	}

	//DrawScore();

	if( m_pMysteryShip != 0)
	{
		m_pMysteryShip->Draw();
	}

	DrawScore();
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
	m_fTimeElapsed += _fDeltaTick;
	
	PlayerInput();
	AlienControl();
	MysteryShipControl(_fDeltaTick);
	
	// Process all the Alien Columns
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		((*m_pAlienColumns)[i])->Process(_fDeltaTick);
	}
		
	if(m_pPlayerShip->Fired()) 
	{
		m_pProjectile->Process(_fDeltaTick);
	}
	
	m_pPlayerShip->Process(_fDeltaTick);

	if(ProjectileCollisionCheck())
	{
		m_pProjectile->Process(_fDeltaTick);
	}
 
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
* GetPlayerProjectile: Retrieves the Levels PlayerProjectile pointer
* @author: Jc Fowles
* @return: CPlayerProjectile*: Pointer the the levels CPlayerProjectile
********************/
CPlayerProjectile* CLevel::GetPlayerProjectile() const
{
	return (m_pProjectile);
}

/***********************
* ProjectileCollisionCheck: collistion checks for projectile
* @author: Jc Fowles
* @return: bool: true if collision detected
********************/
bool CLevel::ProjectileCollisionCheck()
{
	int iPositionY = static_cast<int>(m_pProjectile->GetY());
		
	if(iPositionY < 0 )
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		return true;
	}
	else if(AlienCollision())
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		return true;
	}
	else if(m_pMysteryShip != 0)
	{
		if(MysteryShipCollision())
		{
			m_pPlayerShip->setFired(false);
			m_pProjectile->setFired(false);
			return true;
		}
	}
	return false;
}

/***********************
* AlienCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::AlienCollision()
{
	
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		CAlienColumn* currentColumn = (*m_pAlienColumns)[i];
		vector<CAlien*>* Aliens = currentColumn->GetAliens();

		for(unsigned int k = 0; k < Aliens->size(); k++)  
		{
			if((*Aliens)[k]->IsAlive())
			{
				float fProjectileR = m_pProjectile->GetWidth()/2;   // projectile radius

				float fProjectileX = m_pProjectile->GetX();			//projectile x co-ord
				float fProjectileY = m_pProjectile->GetY();			//projectile y co-ord

				float fAlienX = (*Aliens)[k]->GetX();				//Current MysteryShip x co-ord
				float fAlienY = (*Aliens)[k]->GetY();				//Current MysteryShip y co-ord

				float fAlienH = (*Aliens)[k]->GetHeight();			//Current MysteryShip Height
				float fAlienW = (*Aliens)[k]->GetWidth();			//Current MysteryShip Width
				
				//Check if overlapping
				if ((fProjectileX  > fAlienX - fAlienW / 2) &&		//+ fProjectileR	
					(fProjectileX  < fAlienX + fAlienW / 2) &&		//- fProjectileR
					(fProjectileY  > fAlienY - fAlienH / 2) &&      //+ fProjectileR    // changes
					(fProjectileY  < fAlienY + fAlienH / 2))		//- fProjectileR	//chagnes
				{
  					(*Aliens)[k]->SetAlive(false);
					return true;
				}
			}
		}
	}
	return false; // if no collision detected return false
}

/***********************
* AlienCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::MysteryShipCollision()
{
	float fProjectileR = m_pProjectile->GetWidth()/2;   // projectile radius

	float fProjectileX = m_pProjectile->GetX();			//projectile x co-ord
	float fProjectileY = m_pProjectile->GetY();			//projectile y co-ord

	float fUFOX = m_pMysteryShip->GetX();				//Current Aliens x co-ord
	float fUFOY = m_pMysteryShip->GetY();				//Current Aliens y co-ord

	float fUFOH = m_pMysteryShip->GetHeight();			//Current Aliens Height
	float fUFOW = m_pMysteryShip->GetWidth();			//Current Aliens Width
				
	//Check if overlapping
	if ((fProjectileX  > fUFOX - fUFOW / 2) &&		//+ fProjectileR	
		(fProjectileX  < fUFOX + fUFOW / 2) &&		//- fProjectileR
		(fProjectileY  > fUFOY - fUFOH / 2) &&      //+ fProjectileR    // changes
		(fProjectileY  < fUFOY + fUFOH / 2))		//- fProjectileR	//chagnes
	{
		m_iScore += m_pMysteryShip->GetPoints();
			 
  		delete m_pMysteryShip;
		m_pMysteryShip =0;
		m_fMysteryShipSpawnTimer = -10;

		return true;
	}
	
	return false; // if no collision detected return false
}

/***********************
* UpdatePlayerScore: Updates the player score with passed in value
* @author: Jc Fowles
* @parameter: _fScore: amount to update score by
* @return: void
********************/
void CLevel::UpdatePlayerScore(int _iScore)
{
	m_iScore += _iScore;
}

/***********************
* UpdateScoreText: Updates the text that contains the playres score
* @author: Jc Fowles
* @parameter: _fScore: amount to update score by
* @return: void
********************/
void CLevel::UpdateScoreText()
{
    m_strScore = "Score: ";

	m_strScore += ToString(GetPlayerScore());
}

/***********************
* GetPlayerScore: Returns the players score
* @author: Jc Fowles
* @return: float: The players score
********************/
int CLevel::GetPlayerScore()
{
	return m_iScore;
}

/***********************
* DrawScore: Draws the score to the buffer
* @author: Jc Fowles
* @return: void
********************/
void CLevel::DrawScore()
{
	 HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	
	SetTextColor(hdc, RGB(255,0,0));
	const int kiX = 0;
    const int kiY = static_cast<int>(m_iHeight - 80);
   
	UpdateScoreText();
		
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
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
			for( int i = static_cast<int>(m_pAlienColumns->size() - 1); i >= 0; i--)
			{
				// Find the left most column of aliens alive
				if( (*m_pAlienColumns)[i]->IsAlive())
				{
					vector<CAlien*>* pRightMostColumn = ((*m_pAlienColumns)[i]->GetAliens());
					for( unsigned int j = 0; j < pRightMostColumn->size(); j++)
					{
						if( (*pRightMostColumn)[j]->IsAlive()) 
						{			
							float fRightMostAlienX = (*pRightMostColumn)[j]->GetX();   
							float fRightMostAlienWidth = (*pRightMostColumn)[j]->GetWidth();

							// Check if the left most column has reached the screen border
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
				// Find the right most column of aliens alive
				if( (*m_pAlienColumns)[i]->IsAlive())
				{
					vector<CAlien*>* pLeftMostColumn = ((*m_pAlienColumns)[i]->GetAliens());
					for( unsigned int j = 0; j < pLeftMostColumn->size(); j++)
					{
						if( (*pLeftMostColumn)[j]->IsAlive())
						{
							float fLeftMostAlienX = (*pLeftMostColumn)[j]->GetX();   
							float fLeftMostAlienWidth = (*pLeftMostColumn)[j]->GetWidth();

							// Check if the right most column has reached the screen border
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
				MessageBox( m_hWnd, "YOU LOSE", "LOSER", MB_OK);
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
	// Random chance to spawn a mystery ship if NONE exist
	if( m_pMysteryShip == 0)
	{
		// Check that the last death happened at least the spawn timer amount ago in seconds
		if( m_fMysteryShipSpawnTimer > 0)
		{
			int iRandomNumber = rand() % 10000;
			if( iRandomNumber < 3)
			{
				m_pMysteryShip = new CMysteryShip;
				VALIDATE(m_pMysteryShip->Initialise());
			}
		}
		else
		{
			m_fMysteryShipSpawnTimer += _fDeltaTick;
		}
	}
	else
	{
		// Move the Mystery ship if one exists
		if( (m_fTimeElapsed - m_fMysteryShipLastMove) > m_fMysteryShipSpeed)
		{
			m_pMysteryShip->Move();
			m_fMysteryShipLastMove = m_fTimeElapsed;
			
		}

		m_pMysteryShip->Process(_fDeltaTick);

		// Check if the mystery ship is off the screen and destroy it
		if( m_pMysteryShip->GetX() > 672)
		{
			delete m_pMysteryShip;
			m_pMysteryShip = 0;
			m_fMysteryShipSpawnTimer = -10;
		}
	}

	return (true);
}

/***********************
* PlayerInput: Recieves Keyboard input to contol the player ship
* @author: Jc Fowles
* @return: void
********************/
void CLevel::PlayerInput()
{
	// IF player presses left or right, 
	if (GetAsyncKeyState( VK_RIGHT ) & 0x8000)
	{
		if(m_pPlayerShip->GetX() > ( 672 - (m_pPlayerShip->GetWidth()/2)-18))//- (theShip->GetWidth())))
		{
			m_pPlayerShip->SetVelocity(0.0f);
			m_pPlayerShip->SetX(static_cast<float>(m_pPlayerShip->GetX()));
			
		}
		else
		{
			m_pPlayerShip->SetVelocity(m_fPlayerShipSpeed);
		}
		
		if(m_pProjectile->GetY() >= m_pPlayerShip->GetY())
		{
			m_pProjectile->SetX(m_pPlayerShip->GetX());
		}
	}
	else if (GetAsyncKeyState( VK_LEFT ) & 0x8000)
	{

		if(m_pPlayerShip->GetX() <= ((m_pPlayerShip->GetWidth()/2) ))
		{
			m_pPlayerShip->SetVelocity(0.0f);
			m_pPlayerShip->SetX(static_cast<float>(m_pPlayerShip->GetX()));
			
		}
		else
		{
			m_pPlayerShip->SetVelocity(-1*m_fPlayerShipSpeed);
		}
		
		if(m_pProjectile->GetY() >= m_pPlayerShip->GetY())
		{
			m_pProjectile->SetX(m_pPlayerShip->GetX());
		}
	}
	else // left or  right key-up
	{
		m_pPlayerShip->SetVelocity( 0.0f );
	}

	if (GetAsyncKeyState( VK_SPACE ) & 0x8000)
	{
		if(!(m_pProjectile->Fired()))
		{
			m_pProjectile->SetX(m_pPlayerShip->GetX());
			m_pProjectile->SetY(m_pPlayerShip->GetY());
		}
		
		m_pProjectile->SetVelocity(-1*m_fProjectileSpeed);
		m_pPlayerShip->setFired(true);
		m_pProjectile->setFired(true);
	}
	else
	{
		// Do nothing.
	}
	
}