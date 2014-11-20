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
	m_fAlienProjectileSpeed = 50.0f;
	m_fAlienSpeed = 0.5f;
	m_fAlienFireFreq = 10;
	fMaxAlienProjectile = 7;

	m_iWidth = 0;
	m_iHeight = 0;
	m_pPlayerShip = 0;
	m_pAlienColumns = new vector<CAlienColumn*>;

	m_fTimeElapsed = 0;
	m_fAlienLastMove = 0;
	m_fMysteryShipLastMove = 0;
	m_bAlienDirection = RIGHT;
	m_iScore = 0;

	m_iPLayerLives = 3;

	// Alien Wave Setup constants
	m_iNumAlienColumns = 11;
	m_fStartX = 50;
	m_fStartY = 200;
	m_iXGap = 18;
	m_fColumnWidth = 35;

	// Barrier Setup
	m_pBarriers = new vector<CBarrier*>;
	m_iNumBarriers = 4;
	//m_iBarrierPairGap = 0;
	m_iBarrierBetweenPairGap = 80;
	m_fBarrierStartX = 95;
	m_fBarrierStartY = 600;
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

	// Values to Set up each Alien Column with
	//m_fAlienSpeed = 0.25f;

	float fCurrentX = m_fStartX;
	float fCurrentY = m_fStartY;
	CAlienColumn* pTempAlienColumn = 0;

	// Create and push back AlienColumns into the vector of Columns
	for( int i = 0; i < m_iNumAlienColumns; i++)
	{
		pTempAlienColumn = new CAlienColumn;
		VALIDATE(pTempAlienColumn->Initialise(fCurrentX, fCurrentY));
		m_pAlienColumns->push_back(pTempAlienColumn);

		fCurrentX += (m_fColumnWidth + m_iXGap);
		m_fAlienLastFired.push_back(0);
	}



	// Mystery Ship Variable initialisations
	m_pMysteryShip = 0;
	m_fMysteryShipSpeed = 0.1f;
	m_fMysteryShipSpawnTimer = -10;

	m_pAlienProjectiles = new vector<CAlienProjectile*>;

	// Barrier Setup
	fCurrentX = m_fBarrierStartX;
	fCurrentY = m_fBarrierStartY;
	CBarrier* m_pTempBarrier = 0;

	for( int i = 0; i < m_iNumBarriers; i++)
	{
		m_pTempBarrier = new CBarrier;
		VALIDATE(m_pTempBarrier->Initialise(fCurrentX, fCurrentY));
		m_pBarriers->push_back(m_pTempBarrier);

		/*if(i % 2 == 0)
		{
			fCurrentX += (m_iBarrierPairGap + m_pTempBarrier->GetWidth());
		}
		else
		{*/
			fCurrentX += (m_iBarrierBetweenPairGap + m_pTempBarrier->GetWidth());
		//}
	}

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

	// Draw all the Alien Columns
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		((*m_pAlienColumns)[i])->Draw();
	}

	// Draw all the Barriers
	for( unsigned int i = 0; i < m_pBarriers->size(); i++)
	{
		((*m_pBarriers)[i])->Draw();
	}

	//DrawScore();

	if( m_pMysteryShip != 0)
	{
		m_pMysteryShip->Draw();
	}

	for(unsigned int i = 0; i <  m_pAlienProjectiles->size() ; i++)
	{
		CAlienProjectile* AlienProj = (*m_pAlienProjectiles)[i];
		AlienProj->Draw();
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

	// Process all the Barriers
	for( unsigned int i = 0; i < m_pBarriers->size(); i++)
	{
		((*m_pBarriers)[i])->Process(_fDeltaTick);
	}
		
	if(m_pPlayerShip->Fired()) 
	{
		m_pProjectile->Process(_fDeltaTick);
	}
	
	m_pPlayerShip->Process(_fDeltaTick);

	if(ShipProjectileCollision())
	{
		m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
		m_pProjectile->Process(_fDeltaTick);
	}

	// Check if anyu column of aliens are still alive
	m_bWaveReset = true;
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		if ( ((*m_pAlienColumns)[i])->IsAlive())
		{
			// if at least one column is still alive do not reset
			m_bWaveReset = false;
			break;
		}
	}

	if( m_bWaveReset == true)
	{
		WaveReset();
	}

	AlienFire();

	vector<CAlienProjectile*>::iterator iterCurrent = m_pAlienProjectiles->begin();
	vector<CAlienProjectile*>::iterator iterEnd = m_pAlienProjectiles->end();

	vector<CAlienProjectile*>::iterator iterDestroy = m_pAlienProjectiles->end();

	while(iterCurrent != iterEnd)
	{
		if(((*iterCurrent)->GetY() > m_iHeight) || ((*iterCurrent)->GetDestroyed() == true))
		{
			iterDestroy = iterCurrent;
		}
		else
		{
			(*iterCurrent)->Process(_fDeltaTick);
		}
		//iterCurrent++;
		
		iterCurrent++;
	
		
	}
	if(iterDestroy != iterEnd)
	{
		delete (*iterDestroy);
		(*iterDestroy) = 0;
		m_pAlienProjectiles->erase(iterDestroy);
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
bool CLevel::ShipProjectileCollision()
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
	else if(BarrierCollision())
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		return true;
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
				

				float fProjectileXL = m_pProjectile->GetX() - m_pProjectile->GetWidth()/2;			
				float fProjectileXR = m_pProjectile->GetX() + m_pProjectile->GetWidth()/2;
				float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetWidth()/2;				
				float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

				float fAlienXL = (*Aliens)[k]->GetX() - (*Aliens)[k]->GetWidth()/2;			
				float fAlienXR = (*Aliens)[k]->GetX() + (*Aliens)[k]->GetWidth()/2;
				float fAlienYT = (*Aliens)[k]->GetY() - (*Aliens)[k]->GetWidth()/2;				
				float fAlienYB = (*Aliens)[k]->GetY() + (*Aliens)[k]->GetHeight()/2;	
				
				TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

				TRectangle rctAlien = {fAlienXL,fAlienYT, fAlienXR,fAlienYB};

				//Check if overlapping
				if (IsIntersection(rctProjectile,rctAlien))

				{
  					(*Aliens)[k]->SetAlive(false);
					m_iScore += (*Aliens)[k]->GetPoints();

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
	
	float fProjectileXL = m_pProjectile->GetX() - m_pProjectile->GetWidth()/2;			
	float fProjectileXR = m_pProjectile->GetX() + m_pProjectile->GetWidth()/2;
	float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetWidth()/2;				
	float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

	float fMysShipXL = m_pMysteryShip->GetX() - m_pMysteryShip->GetWidth()/2;			
	float fMysShipXR = m_pMysteryShip->GetX() + m_pMysteryShip->GetWidth()/2;
	float fMysShipYT = m_pMysteryShip->GetY() - m_pMysteryShip->GetWidth()/2;				
	float fMysShipYB = m_pMysteryShip->GetY() + m_pMysteryShip->GetHeight()/2;	
				
	TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

	TRectangle rctMysShip = {fMysShipXL,fMysShipYT, fMysShipXR,fMysShipYB};
				
	//Check if overlapping
	if (IsIntersection(rctProjectile,rctMysShip))		
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
* AlienCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::BarrierCollision()
{
	for( unsigned int i = 0; i < m_pBarriers->size(); i++)
	{
		CBarrier* currentBarrier = (*m_pBarriers)[i];
		//vector<CAlien*>* Aliens = currentColumn->GetAliens();

		if(currentBarrier->IsAlive())
		{
			
			float fProjectileXL = m_pProjectile->GetX() - m_pProjectile->GetWidth()/2;			
			float fProjectileXR = m_pProjectile->GetX() + m_pProjectile->GetWidth()/2;
			float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetWidth()/2;				
			float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

			float fBarrierXL = currentBarrier->GetX() - currentBarrier->GetWidth()/2;			
			float fBarrierXR = currentBarrier->GetX() + currentBarrier->GetWidth()/2;
			float fBarrierYT = currentBarrier->GetY() - currentBarrier->GetWidth()/2;				
			float fBarrierYB = currentBarrier->GetY() + currentBarrier->GetHeight()/2;	
			
			TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

			TRectangle rctBarrier = {fBarrierXL,fBarrierYT, fBarrierXR,fBarrierYB};
			
			for(unsigned int i = 0; i < m_pAlienProjectiles->size(); i++)
			{
				CAlienProjectile* CurrentAlienProjectile = (*m_pAlienProjectiles)[i];

				float fAlienProjectileXL = CurrentAlienProjectile->GetX() - CurrentAlienProjectile->GetWidth()/2;			
				float fAlienProjectileXR = CurrentAlienProjectile->GetX() + CurrentAlienProjectile->GetWidth()/2;
				float fAlienProjectileYT = CurrentAlienProjectile->GetY() - CurrentAlienProjectile->GetWidth()/2;				
				float fAlienProjectileYB = CurrentAlienProjectile->GetY() + CurrentAlienProjectile->GetHeight()/2;	
				
				TRectangle rctAlienProjectile = {fAlienProjectileXL,fAlienProjectileYT, fAlienProjectileXR,fAlienProjectileYB};

				if (IsIntersection(rctAlienProjectile,rctBarrier))		
				{
  					currentBarrier->DecreaseHealth();
					CurrentAlienProjectile->SetDestroyed(true);
					return true;
				}

			}

			//Check if overlapping
			if (IsIntersection(rctProjectile,rctBarrier))		
			{
  				currentBarrier->DecreaseHealth();
				return true;
			}
		}
	}
	return false; // if no collision detected return false
	
	return false; // if no collision detected return false
}

/***********************
* ShipCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::ShipCollision()
{
	
		for(unsigned int i = 0; i < m_pAlienProjectiles->size(); i++)  
		{
			CAlienProjectile* AlienProjectile = (*m_pAlienProjectiles)[i];
				

				float fPlayerShipXL = m_pPlayerShip->GetX() - m_pPlayerShip->GetWidth()/2;			
				float fPlayerShipXR = m_pPlayerShip->GetX() + m_pPlayerShip->GetWidth()/2;
				float fPlayerShipYT = m_pPlayerShip->GetY() - m_pPlayerShip->GetWidth()/2;				
				float fPlayerShipYB = m_pPlayerShip->GetY() + m_pPlayerShip->GetHeight()/2;	

				float fProjectileXL = AlienProjectile->GetX() - AlienProjectile->GetWidth()/2;			
				float fProjectileXR = AlienProjectile->GetX() + AlienProjectile->GetWidth()/2;
				float fProjectileYT = AlienProjectile->GetY() - AlienProjectile->GetWidth()/2;				
				float fProjectileYB = AlienProjectile->GetY() + AlienProjectile->GetHeight()/2;	
				
				TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

				TRectangle rctPlayerShip = {fPlayerShipXL,fPlayerShipYT, fPlayerShipXR,fPlayerShipYB};

				//Check if overlapping
				if (IsIntersection(rctProjectile,rctPlayerShip))
				{
  					m_iPLayerLives -= 1;
					delete m_pPlayerShip;
					m_pPlayerShip = 0;
 
					return true;
				}
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
    m_strScore = "<";
	m_strScore += ToString(GetPlayerScore());
	m_strScore += ">";

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

	SetBkColor(hdc, RGB(0,0,0));
	const int kiX = 333 - (10*(static_cast<int>(m_strScore.size()))/2);
    const int kiY = static_cast<int>(10);// m_iHeight- 10;
   
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
				CGame::GetInstance().SetLayout(0);
				WaveReset();
				delete m_pMysteryShip;
				m_pMysteryShip =0;
				m_fMysteryShipSpawnTimer = -10;
				m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
				m_pProjectile->SetX(m_pPlayerShip->GetX());
				m_pPlayerShip->setFired(false);
				m_pProjectile->setFired(false);
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

/***********************
* WaveReset: Resets the aliens to the beginning of the level alive
* @author: Callan Moore
* @return: void
********************/
void CLevel::WaveReset()
{
	float fCurrentX = m_fStartX;
	float fCurrentY;
	int iYGap = 16;
	vector<CAlien*>* pTempAlienColumn = 0;
	CAlien* pCurrentAlien = 0;

	// Run through all columns
	for( unsigned int i = 0; i < m_pAlienColumns->size(); i++)
	{
		pTempAlienColumn = ((*m_pAlienColumns)[i])->GetAliens();
		fCurrentY = m_fStartY;

		// Set each alien back to their starting position and set them alive
		for( unsigned int j = 0; j < pTempAlienColumn->size(); j++)
		{
			pCurrentAlien = (*pTempAlienColumn)[j];
			pCurrentAlien->SetAlive(true);

			pCurrentAlien->SetX(fCurrentX);
			pCurrentAlien->SetY(fCurrentY);

			fCurrentY += (pCurrentAlien->GetHeight() + iYGap);
		}
		fCurrentX += (m_fColumnWidth + m_iXGap);
	}
	m_bAlienDirection = RIGHT;
}

/***********************
* AlienFire: Resets the aliens to the beginning of the level alive
* @author: Jc Fowles
* @return: void
********************/
bool CLevel::AlienFire()
{
	if( (m_fTimeElapsed - m_fAlienLastFired[0]) > 1)
	{
		int iRandomCol = rand() % 11;
		CAlienColumn* currentColumn = (*m_pAlienColumns)[iRandomCol];
			
		if( currentColumn->IsAlive())
		{
			int iRandomNumber = rand() % m_fAlienFireFreq;
			if( iRandomNumber < 5)
			{
				if(m_pAlienProjectiles->size() < fMaxAlienProjectile)
				{
					CAlienProjectile* Projectile = new CAlienProjectile;
					
					CAlien* Alien = currentColumn->ReturnLowest();
					float fX = Alien->GetX();
					float fY = Alien->GetY();
					VALIDATE(Projectile->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  m_fAlienProjectileSpeed));
					Projectile->SetX(fX);
					Projectile->SetY(fY);
					m_pAlienProjectiles->push_back(Projectile);
				}
			}
		}
		m_fAlienLastFired[0] = m_fTimeElapsed;
	}
	
	return (true);
}

/***********************
* IsIntersection: calculates if there is an intersection between 2 rectangles 
* @author: Jc Fowles
* @parameter: _krRect1: a refrence to the first geometric shape, which is a rectangle
* @parameter: _krRect2: a refrence to the first geometric shape, which is a rectangle
* @return: bool: true if the shapes do intersect, false if the shapes do not intersect
********************/
bool CLevel::IsIntersection(const TRectangle& _krRect1, const TRectangle& _krRect2)
{
	
	if( _krRect1.m_fTB < _krRect2.m_fYT || _krRect1.m_fYT > _krRect2.m_fTB			
		|| _krRect1.m_fXR < _krRect2.m_fXL || _krRect1.m_fXL > _krRect2.m_fXR )
	//checks  to see if the 2 rectangles do NOT intesect
	{
		return false;
	}
	else
	//if the above conditions are not met therefor the rectanges are intesecting
	{
		return true;
	}

}

