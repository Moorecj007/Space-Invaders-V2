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
	m_fPlayerShipSpeed = 250.0f;
	m_fProjectileSpeed = 750.0f;
	m_fAlienProjectileSpeed = 250.0f;
	m_fAlienSpeed = 0.5f;
	m_fAlienSpeedOrig = 0.5f;
	m_fAlienFireFreq = 10;
	m_fAlienFireFreqOrig = 10;
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
	m_iExtraLife = 0;
	m_iHiScore = 5000;
	m_iPLayerLives = 3;
	respawn = 0;
	respawnTime = 1000;

	// Alien Wave Setup constants
	m_iNumAlienColumns = 11;
	m_fStartX = 50;
	m_fStartY = 200;
	m_iXGap = 30;
	m_fColumnWidth = 44;

	// Barrier Setup
	m_pBarriers = new vector<CBarrier*>;
	m_iNumBarriers = 4;
	m_iBarrierBetweenPairGap = 102;
	m_fBarrierStartX = 151;
	m_fBarrierStartY = 800;
}

/***********************
* ~CLevel: Destructor for the Level class
* @author: Callan Moore
********************/
CLevel::~CLevel()
{
	delete m_pPlayerShip;
	m_pPlayerShip = 0;

	//delete m_pProjectile;
	//m_pProjectile = 0;

	m_pProjectile->DestroyInstance();
	m_pProjectile = 0;

	// Delete all Alien Columns
	while( m_pAlienColumns->empty() == false)
	{
		delete (*m_pAlienColumns).back();
		(*m_pAlienColumns).back() = 0;
		(*m_pAlienColumns).pop_back();
	}
	delete m_pAlienColumns;
	m_pAlienColumns = 0;

	// Delete all Barriers
	while( m_pBarriers->empty() == false)
	{
		delete (*m_pBarriers).back();
		(*m_pBarriers).back() = 0;
		(*m_pBarriers).pop_back();
	}
	delete m_pBarriers;
	m_pBarriers = 0;

	// Delete Mystery Ship if it exists
	if( m_pMysteryShip != 0)
	{
		delete m_pMysteryShip;
		m_pMysteryShip = 0;
	}

	// Delete all Alien Projectiles
	while( m_pAlienProjectiles->empty() == false)
	{
		delete (*m_pAlienProjectiles).back();
		(*m_pAlienProjectiles).back() = 0;
		(*m_pAlienProjectiles).pop_back();
	}
	delete m_pAlienProjectiles;
	m_pAlienProjectiles = 0;
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
	m_pPlayerShip->SetY(_iHeight - ( 1.5f * m_pPlayerShip->GetHeight()));  // from the bottom of the screen

	//Projectile creation and positioning
	const float fBallVelY = 75.0f;
	m_pProjectile = &(CPlayerProjectile::GetInstance());
	VALIDATE(m_pProjectile->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  fBallVelY));
	//position based: x middle of image
	//				  y top of image
	m_pProjectile->SetX(_iWidth/2.0f);  // from the left
	m_pProjectile->SetY(_iHeight - ( 1.5f * m_pPlayerShip->GetHeight()));  // from the bottom of the screen

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
		m_fAlienLastFired = 0;
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

		fCurrentX += (m_iBarrierBetweenPairGap + m_pTempBarrier->GetWidth());

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
	//m_pProjectile->Draw();
	//m_pPlayerShip->Draw();

	if(!(m_pPlayerShip->GetDestroyed()))
	{
		m_pPlayerShip->Draw();
		m_pProjectile->Draw();
	}

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

	if(m_iPLayerLives <= 0)
	{
		GameOver(true);
	}

	if(!(m_pPlayerShip->GetDestroyed()))
	{
		ShipCollision();
	
		PlayerInput();
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
	}
	else 
	{
		respawn++;
	}
	
	if(respawn > respawnTime)
	{
 		respawn = 0;
		m_pPlayerShip->SetX(m_pPlayerShip->GetWidth()/2);
		m_pPlayerShip->SetDestroyed(false);
	}
	
	AlienControl();
	MysteryShipControl(_fDeltaTick);
	BarrierAlienCollision();
	
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
		
		iterCurrent++;
	
		
	}
	if(iterDestroy != iterEnd)
	{
		delete (*iterDestroy);
		(*iterDestroy) = 0;
		m_pAlienProjectiles->erase(iterDestroy);
	}
	
	if(ShipCollision())
	{
		//respawn++;
	}

	if(m_iExtraLife >= 10000)
	{
		m_iPLayerLives += 1;
		m_iExtraLife = 0;
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
	bool bIsHit = false;

	if(iPositionY < 0 )
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		bIsHit =  true;
	}

	if(AlienCollision())
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		bIsHit = true;
	}
	
	if(m_pMysteryShip != 0)
	{
		if(MysteryShipCollision())
		{
			m_pPlayerShip->setFired(false);
			m_pProjectile->setFired(false);
			bIsHit = true;
		}
	}
	
	if(BarrierCollision())
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		bIsHit =  true;
	}
	return bIsHit;
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
				float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetHeight()/2;				
				float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

				float fAlienXL = (*Aliens)[k]->GetX() - (*Aliens)[k]->GetWidth()/2;			
				float fAlienXR = (*Aliens)[k]->GetX() + (*Aliens)[k]->GetWidth()/2;
				float fAlienYT = (*Aliens)[k]->GetY() - (*Aliens)[k]->GetHeight()/2;				
				float fAlienYB = (*Aliens)[k]->GetY() + (*Aliens)[k]->GetHeight()/2;	
				
				TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

				TRectangle rctAlien = {fAlienXL,fAlienYT, fAlienXR,fAlienYB};

				//Check if overlapping
				if (IsIntersection(rctProjectile,rctAlien))

				{
  					(*Aliens)[k]->SetAlive(false);
					m_iScore += (*Aliens)[k]->GetPoints();
					m_iExtraLife += (*Aliens)[k]->GetPoints();
					m_fAlienSpeed = m_fAlienSpeed - (m_fAlienSpeed/60);
					m_fAlienFireFreq += 15; 

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
	float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetHeight()/2;				
	float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

	float fMysShipXL = m_pMysteryShip->GetX() - m_pMysteryShip->GetWidth()/2;			
	float fMysShipXR = m_pMysteryShip->GetX() + m_pMysteryShip->GetWidth()/2;
	float fMysShipYT = m_pMysteryShip->GetY() - m_pMysteryShip->GetHeight()/2;				
	float fMysShipYB = m_pMysteryShip->GetY() + m_pMysteryShip->GetHeight()/2;	
				
	TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

	TRectangle rctMysShip = {fMysShipXL,fMysShipYT, fMysShipXR,fMysShipYB};
				
	//Check if overlapping
	if (IsIntersection(rctProjectile,rctMysShip))		
	{
		int iAddedScore  = m_pMysteryShip->GetPoints();
		m_iScore += iAddedScore;
		m_iExtraLife += iAddedScore;
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
			float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetHeight()/2;				
			float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

			float fBarrierXL = currentBarrier->GetX() - currentBarrier->GetWidth()/2;			
			float fBarrierXR = currentBarrier->GetX() + currentBarrier->GetWidth()/2;
			float fBarrierYT = currentBarrier->GetY() - currentBarrier->GetHeight()/2;				
			float fBarrierYB = currentBarrier->GetY() + currentBarrier->GetHeight()/2;	
			
			TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

			TRectangle rctBarrier = {fBarrierXL,fBarrierYT, fBarrierXR,fBarrierYB};
			
			
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
* AlienCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::BarrierAlienCollision()
{
	for( unsigned int i = 0; i < m_pBarriers->size(); i++)
	{
		CBarrier* currentBarrier = (*m_pBarriers)[i];
		//vector<CAlien*>* Aliens = currentColumn->GetAliens();

		if(currentBarrier->IsAlive())
		{
			float fBarrierXL = currentBarrier->GetX() - currentBarrier->GetWidth()/2;			
			float fBarrierXR = currentBarrier->GetX() + currentBarrier->GetWidth()/2;
			float fBarrierYT = currentBarrier->GetY() - currentBarrier->GetHeight()/2;				
			float fBarrierYB = currentBarrier->GetY() + currentBarrier->GetHeight()/2;	
			
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
		}
	}
	return false; // if no collision detected return false
	
	
}

/***********************
* ShipCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CLevel::ShipCollision()
{	
	if(!(m_pPlayerShip->GetDestroyed()))
	{

	
		for(unsigned int i = 0; i < m_pAlienProjectiles->size(); i++)  
		{
			CAlienProjectile* AlienProjectile = (*m_pAlienProjectiles)[i];
				

				float fPlayerShipXL = m_pPlayerShip->GetX() - m_pPlayerShip->GetWidth()/2;			
				float fPlayerShipXR = m_pPlayerShip->GetX() + m_pPlayerShip->GetWidth()/2;
				float fPlayerShipYT = m_pPlayerShip->GetY() - m_pPlayerShip->GetHeight()/2;				
				float fPlayerShipYB = m_pPlayerShip->GetY() + m_pPlayerShip->GetHeight()/2;	

				float fProjectileXL = AlienProjectile->GetX() - AlienProjectile->GetWidth()/2;			
				float fProjectileXR = AlienProjectile->GetX() + AlienProjectile->GetWidth()/2;
				float fProjectileYT = AlienProjectile->GetY() - AlienProjectile->GetHeight()/2;				
				float fProjectileYB = AlienProjectile->GetY() + AlienProjectile->GetHeight()/2;	
				
				TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};

				TRectangle rctPlayerShip = {fPlayerShipXL,fPlayerShipYT, fPlayerShipXR,fPlayerShipYB};

				//Check if overlapping
				if (IsIntersection(rctProjectile,rctPlayerShip))
				{
  					//m_iPLayerLives -= 1;
					m_pPlayerShip->SetDestroyed(true);
					AlienProjectile->SetDestroyed(true);
					m_iPLayerLives = m_iPLayerLives - 1;
					return true;
				}
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
* UpdateScoreText: Updates the text that contains the players score
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
* UpdateHiScoreText: Updates the text that contains the high score
* @author: Jc Fowles
* @return: void
********************/
void CLevel::UpdateHiScoreText()
{
    m_strHiScore = "High Score<";
	m_strHiScore += ToString(GetIntHighScore());
	m_strHiScore += ">";
}

/***********************
* GetHighScore: Retrieves the Hi Score
* @author: Jc Fowles
* @return: string: The current hi score
********************/
string CLevel::GetHighScore()
{
	UpdateHiScoreText();
	return m_strHiScore;
}

/***********************
* UpdateLivesText: update the Life count text
* @author: Jc Fowles
* @return: void
********************/
void CLevel::UpdateLivesText()
{
    m_strLives = "Lives: ";
	m_strLives += ToString(GetPlayerLives());
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
* GetPlayerLives: Retrieves the Players life count
* @author: Jc Fowles
* @return: float: The players life count
********************/
int CLevel::GetPlayerLives()
{
	return m_iPLayerLives;
}

/***********************
* GetIntHighScore: Retrieve the Hi Score
* @author: Jc Fowles
* @return: int: The hi score
********************/
int CLevel::GetIntHighScore()
{
	return m_iHiScore;
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
	int kiX = m_iWidth/2 - (10*(static_cast<int>(m_strScore.size()))/2);
    int kiY = static_cast<int>(10);// m_iHeight- 10;
   
	UpdateScoreText();
		
	TextOut(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
	
	UpdateLivesText();

	kiX = 50;
    kiY = static_cast<int>(10);// m_iHeight- 10;

	TextOut(hdc, kiX, kiY, m_strLives.c_str(), static_cast<int>(m_strLives.size()));

	UpdateHiScoreText();

	kiX = m_iWidth - (10*(static_cast<int>(m_strHiScore.size())) + 10);
    kiY = static_cast<int>(10);// m_iHeight- 10;

	TextOut(hdc, kiX, kiY, m_strHiScore.c_str(), static_cast<int>(m_strHiScore.size()));

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
				// Find the right most column of aliens alive
				if( (*m_pAlienColumns)[i]->IsAlive())
				{
					vector<CAlien*>* pRightMostColumn = ((*m_pAlienColumns)[i]->GetAliens());
					for( unsigned int j = 0; j < pRightMostColumn->size(); j++)
					{
						if( (*pRightMostColumn)[j]->IsAlive()) 
						{			
							float fRightMostAlienX = (*pRightMostColumn)[j]->GetX();   
							float fRightMostAlienWidth = (*pRightMostColumn)[j]->GetWidth();

							// Check if the right most column has reached the screen border
							if( (fRightMostAlienX + (fRightMostAlienWidth / 2) + 25) > 900)
							{
								m_bAlienDirection = LEFT;
								bMoveDown = true;
								m_fAlienSpeed = m_fAlienSpeed - (m_fAlienSpeed/60);
								m_fAlienFireFreq += 5; 
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
								m_fAlienSpeed = m_fAlienSpeed - (m_fAlienSpeed/60);
								m_fAlienFireFreq += 5; 
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
				GameOver(true);
				break;
			}

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
		if( m_pMysteryShip->GetX() > 900)
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
		if(m_pPlayerShip->GetX() + (m_pPlayerShip->GetWidth()/2 + 25) > 900)//- (theShip->GetWidth())))
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
	m_fAlienSpeedOrig = m_fAlienSpeedOrig - (m_fAlienSpeedOrig/20);
	m_fAlienSpeed = m_fAlienSpeedOrig;
	m_fAlienFireFreqOrig += m_fAlienFireFreqOrig + 5;
	m_fAlienFireFreq = m_fAlienFireFreqOrig;
	fMaxAlienProjectile += 2;
	m_iPLayerLives++;
}

/***********************
* AlienFire: Resets the aliens to the beginning of the level alive
* @author: Jc Fowles
* @return: void
********************/
bool CLevel::AlienFire()
{
	if( (m_fTimeElapsed - m_fAlienLastFired) > 1)
	{
		int iRandomCol = rand() % 11;
		CAlienColumn* currentColumn = (*m_pAlienColumns)[iRandomCol];
			
		if( currentColumn->IsAlive())
		{
			int iRandomNumber = rand() % 100;
			if( iRandomNumber <= m_fAlienFireFreq)
			{
				if(static_cast<float>(m_pAlienProjectiles->size()) < fMaxAlienProjectile)
				{
					CAlienProjectile* Projectile = new CAlienProjectile;
					
					CAlien* Alien = currentColumn->ReturnLowest();
					float fX = Alien->GetX();
					float fY = Alien->GetY();

					// Random gen to see which Projectile type to spawn
					int iRandomProjectile = rand() % 3;
					if(iRandomProjectile == 1)
					{
						VALIDATE(Projectile->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  m_fAlienProjectileSpeed, 1));
					}
					else
					{
						VALIDATE(Projectile->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  m_fAlienProjectileSpeed / 2, 0));
					}

					Projectile->SetX(fX);
					Projectile->SetY(fY);
					m_pAlienProjectiles->push_back(Projectile);
				}
			}
		}
		m_fAlienLastFired = m_fTimeElapsed;
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

/***********************
* GameOver: Checks If player has any lives left if not Pop up Game over message
* @author: Jc Fowles
* @return: bool: true if the shapes do intersect, false if the shapes do not intersect
********************/
bool CLevel::GameOver(bool _bGameOver)
{
	
	if(_bGameOver)
	{
		if(m_iScore > m_iHiScore)
		{
			MessageBox( m_hWnd, "You Broke the High Score", "Winner", MB_OK);
			m_iHiScore = m_iScore;
		}
		else
		{
			MessageBox( m_hWnd, "YOU LOSE", "LOSER", MB_OK);
		}
		
		CGame::GetInstance().SetLayout(0);
		WaveReset();
		m_fAlienSpeedOrig = 0.5f;
		m_fAlienSpeed = m_fAlienSpeedOrig ;
		delete m_pMysteryShip;
		m_pMysteryShip =0;
		m_fMysteryShipSpawnTimer = -10;
		m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
		m_pProjectile->SetX(m_pPlayerShip->GetX());
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		m_iPLayerLives = 3;
		m_iScore = 0;
		respawn = respawnTime +1;
		for(unsigned int i = 0; i < m_pBarriers->size(); i++)
		{
			(*m_pBarriers)[i]->ResetHealth();
		}

		while(!(m_pAlienProjectiles->empty()))
		{
			delete m_pAlienProjectiles->back();
			m_pAlienProjectiles->back() = 0;
			m_pAlienProjectiles->pop_back();
		}


		return true;
	}
	return false;
}

/***********************
* SetPlayerProjSpeed: Sets the Players Ships Projectile speed
* @author: Callan Moore
* @parameter: _iSpeed: The new Speed
* @return: void
********************/
void CLevel::SetPlayerProjSpeed(float _fSpeed)
{
	m_fProjectileSpeed = _fSpeed;
}

/***********************
* SetAlienProjSpeed: Sets the Aliens Projectile speed
* @author: Callan Moore
* @parameter: _iSpeed: The new Speed
* @return: void
********************/
void CLevel::SetAlienProjSpeed(float _fSpeed)
{
	m_fAlienProjectileSpeed = _fSpeed;
}

/***********************
* SetPlayerMoveSpeed: Sets the Player Movement speed
* @author: Callan Moore
* @parameter: _iSpeed: The new Speed
* @return: void
********************/
void CLevel::SetPlayerMoveSpeed(float _fSpeed)
{
	m_fPlayerShipSpeed = _fSpeed;
}

/***********************
* SetAlienMoveSpeed: Sets the Alien base Movement speed
* @author: Callan Moore
* @parameter: _iSpeed: The new Speed
* @return: void
********************/
void CLevel::SetAlienMoveSpeed(float _fSpeed)
{
	m_fAlienSpeed = _fSpeed;
}

/***********************
* GetPlayerProjSpeed: Retrieves the base player projectile speed
* @author: Callan Moore
* @return: unsigned int: Value for the Speed
********************/
float CLevel::GetPlayerProjSpeed()
{
	return m_fProjectileSpeed;
}

/***********************
* GetAlienProjSpeed: Retrieves the base Alien projectile speed
* @author: Callan Moore
* @return: unsigned int: Value for the Speed
********************/
float CLevel::GetAlienProjSpeed()
{
	return m_fAlienProjectileSpeed;
}

/***********************
* GetPlayerMoveSpeed: Retrieves the Player movement speed
* @author: Callan Moore
* @return: unsigned int: Value for the Speed
********************/
float CLevel::GetPlayerMoveSpeed()
{
	return m_fPlayerShipSpeed;
}

/***********************
* GetAlienMoveSpeed: Retrieves the base Alien movement speed
* @author: Callan Moore
* @return: unsigned int: Value for the Speed
********************/
float CLevel::GetAlienMoveSpeed()
{
	return m_fAlienSpeed;
}


