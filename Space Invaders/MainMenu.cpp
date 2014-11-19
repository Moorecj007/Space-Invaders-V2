/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Leave.cpp
* Description : Implementation file for the Level class
* Author :	Jc Fowles
* Mail :	Jc.Fowles@mediadesign.school.nz	
*/

// This Include
#include "MainMenu.h"


CMainMenu::CMainMenu(void)
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_pPlayerShip = 0;
}


CMainMenu::~CMainMenu(void)
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
bool CMainMenu::Initialise(int _iWidth, int _iHeight, HWND _hWnd)
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

	
}

/***********************
* Draw: Draws all the entities that make up the level
* @author: Callan Moore
* @author: JC Fowles
* @return: void
********************/
void CMainMenu::Draw()
{
	m_pProjectile->Draw();
	m_pPlayerShip->Draw();
}

/***********************
* Process: Process the changes to the Level for the current delta tick
* @author: Callan Moore
* @author: JC Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CMainMenu::Process(float _fDeltaTick)
{
	PlayerInput();

	if(m_pPlayerShip->Fired()) 
	{
		m_pProjectile->Process(_fDeltaTick);
	}
	
	m_pPlayerShip->Process(_fDeltaTick);

	/*ShipProjectileCollision();

	if(m_pPlayerShip->Fired()) 
	{
		m_pProjectile->Process(_fDeltaTick);
	}*/

	if(ShipProjectileCollision())
	{
		CGame::GetInstance().SetLayout(1);
	}


}


/***********************
* PlayerInput: Recieves Keyboard input to contol the player ship
* @author: Jc Fowles
* @return: void
********************/
void CMainMenu::PlayerInput()
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
			m_pPlayerShip->SetVelocity(125.0);
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
			m_pPlayerShip->SetVelocity(-125.0f);
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
		
		m_pProjectile->SetVelocity(-500);
		m_pPlayerShip->setFired(true);
		m_pProjectile->setFired(true);
	}
	else
	{
		// Do nothing.
	}
}


/***********************
* ProjectileCollisionCheck: collistion checks for projectile
* @author: Jc Fowles
* @return: bool: true if collision detected
********************/
bool CMainMenu::ShipProjectileCollision()
{
	int iPositionY = static_cast<int>(m_pProjectile->GetY());
		
	if(iPositionY < 0 )
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		return true;
	}
	
	return false;
}
