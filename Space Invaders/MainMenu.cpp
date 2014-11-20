/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Leave.cpp
* Description : Implementation file for the Level class
* Author :	Jc Fowles
*         	Callan Moore
* Mail   :	Jc.Fowles@mediadesign.school.nz	
*		 :  Callan.moore@mediadesign.school.nz	
*/

// This Include
#include "MainMenu.h"

/***********************
* CMainMenu: Constructor for the MainMenu Class
* @author: Jc Fowles
********************/
CMainMenu::CMainMenu(void)
{
	// Initial Values
	m_iWidth = 0;
	m_iHeight = 0;
	m_pPlayerShip = 0;

	m_fPlayerShipSpeed = 250.0f;
	m_fProjectileSpeed = 500.0f;
	m_fLastTime = 0.0f;
	m_fTimeElapsed = 0.0f;

	m_iToggle = 0;

	// Player Instructions
	m_strMove = "Move: <- and -> ";
	m_strShoot = "Shoot: SpaceBar";
	m_strShootToStart = "Shoot To Start";
}

/***********************
* ~CMainMenu: Destructor for the MainMenu Class
* @author: Callan Moore
********************/
CMainMenu::~CMainMenu(void)
{
	delete m_pPlayerShip;
	m_pPlayerShip = 0;

	delete m_pAlienStart;
	m_pAlienStart = 0;

	delete m_pAlienExit;
	m_pAlienExit = 0;

	delete m_pAlienTitle;
	m_pAlienTitle = 0;
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

	// Create Player Ship
	m_pPlayerShip = new CPlayerShip();
	VALIDATE(m_pPlayerShip->Initialise());

	// Set initial Positioning
	m_pPlayerShip->SetX(_iWidth/2.0f); 
	m_pPlayerShip->SetY(_iHeight - ( 2 * m_pPlayerShip->GetHeight())); 

	//Projectile creation
	const float fBallVelY = 75.0f;
	m_pProjectile = &(CPlayerProjectile::GetInstance());

	// Set initial Positioning
	m_pProjectile->SetX(_iWidth/2.0f);  
	m_pProjectile->SetY(_iHeight - ( 2 * m_pPlayerShip->GetHeight()));  

	// Create Start sprite
	m_pAlienStart = new CAlien;
	VALIDATE(m_pAlienStart->Initialise(4));

	// Set initial Positioning
	m_pAlienStart->SetX(250);
	m_pAlienStart->SetY(400);

	// Create Exit Sprite
	m_pAlienExit = new CAlien;
	VALIDATE(m_pAlienExit->Initialise(5));

	// Set initial Positioning
	m_pAlienExit->SetX(649);
	m_pAlienExit->SetY(400);

	// Create Title
	m_pAlienTitle = new CAlien;
	VALIDATE(m_pAlienTitle->Initialise(6));

	// Set initial Positioning
	m_pAlienTitle->SetX(448);
	m_pAlienTitle->SetY(150);
	 
	return true;
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
	m_pAlienStart->Draw();
	m_pAlienExit->Draw();
	m_pAlienTitle->Draw();
	DrawText();
}

/***********************
* Process: Process the changes to the MainMenu for the current delta tick
* @author: Callan Moore
* @author: JC Fowles
* @parameter: _fDeltaTick: The time elapsed during the last frame
* @return: void
********************/
void CMainMenu::Process(float _fDeltaTick)
{
	// Blink " Shoot to Start"
	BlinkText(_fDeltaTick);

	// Take user input
	PlayerInput();

	m_pAlienStart->Process(_fDeltaTick);
	m_pAlienExit->Process(_fDeltaTick);
	m_pAlienTitle->Process(_fDeltaTick);

	// Process Collisions on the Menu Sprites
	AlienCollision(m_pAlienStart, 4);
	AlienCollision(m_pAlienExit, 5);
	AlienCollision(m_pAlienTitle, 6);

	if(m_pPlayerShip->Fired() == false) 
	{
		// Set the Position of the Projectile under the ship 
		m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
	}

	if(m_pPlayerShip->Fired()) 
	{
		// Process the Projectil eonly if it has been fired
		m_pProjectile->Process(_fDeltaTick);
	}
	
	m_pPlayerShip->Process(_fDeltaTick);
	
	// Reset the projectile under the ship if it goes outside the screen
	if(ShipProjectileCollision())
	{
		m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
		CGame::GetInstance().SetLayout(1);
	}
}


/***********************
* PlayerInput: Recieves Keyboard input to control the player ship
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
* ProjectileCollisionCheck: collistion checks for projectile
* @author: Jc Fowles
* @return: bool: true if collision detected
********************/
bool CMainMenu::ShipProjectileCollision()
{
	int iPositionY = static_cast<int>(m_pProjectile->GetY());
	
	// Destroys Player projectile if it goes off the screen
	if(iPositionY < 0 )
	{
		m_pPlayerShip->setFired(false);
		m_pProjectile->setFired(false);
		return true;
	}
	
	return false;
}


/***********************
* DrawScore: Draws the instructions text 
* @author: Jc Fowles
* @return: void
********************/
void CMainMenu::DrawText()
{
	 HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	
	SetTextColor(hdc, RGB(255,0,0));	// Red Text
	SetBkColor(hdc, RGB(0,0,0));		// Black background
	
	// Starting coordinates for moving instructions
	int kiX = 10;
    int kiY = m_iHeight- 50;
   	
	// Print the moving instruction
	TextOut(hdc, kiX, kiY, m_strMove.c_str(), static_cast<int>(m_strMove.size()));

	SetTextColor(hdc, RGB(255,0,0));	// Red Text
	SetBkColor(hdc, RGB(0,0,0));		// Black background
	
	// Starting coordinates for shooting instructions
	kiX = m_iWidth - (9*(static_cast<int>(m_strShoot.size())));
    kiY = m_iHeight - 50;

	// Print the shooting instruction
	TextOut(hdc, kiX, kiY ,m_strShoot.c_str(), static_cast<int>(m_strShoot.size()));

	// Starting coordinates for the high score
	kiX = m_iWidth - (10*(static_cast<int>(m_strHiScore.size())) + 10);
    kiY = static_cast<int>(10);// m_iHeight- 10;

	// Print out the high score
	TextOut(hdc, kiX, kiY, m_strHiScore.c_str(), static_cast<int>(m_strHiScore.size()));

	// Starting coordinates for the How to start instruction
	kiX = m_iWidth/2 - (5*(static_cast<int>(m_strShootToStart.size())) );
	kiY = static_cast<int>(10);// m_iHeight- 10;
	
	// Print the how to start instruction
	TextOut(hdc, kiX, kiY, m_strShootToStart.c_str(), static_cast<int>(m_strShootToStart.size()));
}

/***********************
* BlinkText: Makes the 'How to start' instruction blink on and off
* @author: Jc Fowles
* @return: void
********************/
void CMainMenu::BlinkText(float _fDeltaTick)
{
	m_fTimeElapsed += _fDeltaTick;

	// Change the animation every 0.5 seconds
	if((m_fTimeElapsed - m_fLastTime) > 0.5)
	{
		// Print nothing
		if(m_iToggle == 0)
		{
			m_strShootToStart =  "";
			m_iToggle = 1;
		}
		// Print instruction
		else if(m_iToggle == 1)
		{
			m_strShootToStart = "Shoot To Start";
			m_iToggle = 0;
		}

		m_fLastTime = m_fTimeElapsed;
	}
}

/***********************
* GetShip: Return the Ship belonging to main menu
* @author: Jc Fowles
* @return: CPlayerShip*: Pointer to the Players ship
********************/
CPlayerShip* CMainMenu::GetShip()
{
	return m_pPlayerShip;
}

/***********************
* GetShip: Return the Player Projectile belonging to main menu
* @author: Jc Fowles
* @return: CPlayerProjectile*: Pointer to the player projectile
********************/
CPlayerProjectile* CMainMenu::GetShipProj()
{
	return m_pProjectile;
}


/***********************
* AlienCollision: collistion checks for projectile and aliens
* @author: Jc Fowles
* @return: bool: true if collision detected with alien
********************/
bool CMainMenu::AlienCollision(CAlien* _Alien, int _iType)
{
	// Get Rectangle points for the Players projectile
	float fProjectileXL = m_pProjectile->GetX() - m_pProjectile->GetWidth()/2;			
	float fProjectileXR = m_pProjectile->GetX() + m_pProjectile->GetWidth()/2;
	float fProjectileYT = m_pProjectile->GetY() - m_pProjectile->GetHeight()/2;				
	float fProjectileYB = m_pProjectile->GetY() + m_pProjectile->GetHeight()/2;	

	// Get Rectangle points for the Alien 
	float fAlienXL = _Alien->GetX() - _Alien->GetWidth()/2;			
	float fAlienXR = _Alien->GetX() + _Alien->GetWidth()/2;
	float fAlienYT = _Alien->GetY() - _Alien->GetHeight()/2;				
	float fAlienYB = _Alien->GetY() + _Alien->GetHeight()/2;	
		
	// Create the rectangles from the points
	TRectangle rctProjectile = {fProjectileXL,fProjectileYT,fProjectileXR, fProjectileYB};
	TRectangle rctAlien = {fAlienXL,fAlienYT, fAlienXR,fAlienYB};

	//Check if overlapping
	if (IsIntersection(rctProjectile,rctAlien))

	{
  		switch(_iType)
		{
		case (4):	// Start Game sprite
			{
				m_pProjectile->SetY(m_pPlayerShip->GetY() - 1);
				m_pProjectile->SetX(m_pPlayerShip->GetX());
				m_pPlayerShip->setFired(false);
				m_pProjectile->setFired(false);
				CGame::GetInstance().SetLayout(1);
				return true;
			}
		break;
		case (5):	// Exit Game sprite
			{
				SendMessage(m_hWnd, WM_DESTROY, 0,0);
				return true;
			}
			break;
		case (6):	// Title sprite
			{
				m_pPlayerShip->setFired(false);
				m_pProjectile->setFired(false);
				return true;
			}
			break;
		default:break;
		}

		return true;
	}
			
	return false; // if no collision detected return false
}

/***********************
* IsIntersection: calculates if there is an intersection between 2 rectangles 
* @author: Jc Fowles
* @parameter: _krRect1: a refrence to the first geometric shape, which is a rectangle
* @parameter: _krRect2: a refrence to the first geometric shape, which is a rectangle
* @return: bool: true if the shapes do intersect, false if the shapes do not intersect
********************/
bool CMainMenu::IsIntersection(const TRectangle& _krRect1, const TRectangle& _krRect2)
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
* SetHiScore: Sets the hi Score
* @author: Jc Fowles
* @parameter: _strHiScore: The new hi score
* @return: void
********************/
void CMainMenu::SetHiScore(string _strHiScore)
{
	m_strHiScore = _strHiScore;
}

