/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Sprite.cpp
* Description : Implementation file for the Sprite class
* Author :	Asma Shakil
*			Callan Moore
*			JC Fowles
* Mail :	Asma.shakil@mediadesign.school.nz
*			Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz		
*/

// Local Includes
#include "resource.h"
#include "Game.h"
#include "BackBuffer.h"
#include "Utilities.h"

// This include
#include "Sprite.h"

// Static Variables
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

/***********************
* CSprite: Contructor for the Sprite class
* @author: Asma Shakil
********************/
CSprite::CSprite()	: m_iX(0)
					, m_iY(0)
{
	++s_iRefCount;
	m_iFrame = 0;
}

/***********************
* ~CSprite: Destructor for the Sprite class
* @author: Asma Shakil
********************/
CSprite::~CSprite()
{
	DeleteObject(m_hSprite);
	DeleteObject(m_hMask);
	--s_iRefCount;
	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;
	}
}

/***********************
* Initialise: Initialises all the Sprite member variables
* @author: Asma Shakil
* @author: Callan Moore
* @parameter: _iSpriteResourceID: ID as an integer value used to locate the Sprite Image
* @parameter: _iMaskResourceID:	ID as an integer value used to locate the Sprite Mask
* @parameter: _iMaxFrames: The The maximum number of frames for the sprite to have
* @return: bool: always returns true
********************/
bool CSprite::Initialise(int _iSpriteResourceID, int _iMaskResourceID, int _iNumFrames)
{
	m_iNumFrames = _iNumFrames;
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();
	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}
	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_iSpriteResourceID));
	VALIDATE(m_hSprite);
	m_hMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_iMaskResourceID));
	VALIDATE(m_hMask);
	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);
	GetObject(m_hMask, sizeof(BITMAP), &m_bitmapMask);
	return (true);
}

/***********************
* Draw: Draws the sprite onto the backbuffer
* @author: Asma Shakil
* @author: Callan Moore
* @return: void
********************/
void CSprite::Draw()
{
	int iW = GetWidth();
	int iH = GetHeight();
	int iX = m_iX - (iW / 2);
	int iY = m_iY - (iH / 2);
	CBackBuffer* pBackBuffer = CGame::GetInstance().GetBackBuffer();
	HGDIOBJ hOldObj = SelectObject(s_hSharedSpriteDC, m_hMask);
	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, (m_iFrame * iW), 0, SRCAND);
	SelectObject(s_hSharedSpriteDC, m_hSprite);
	BitBlt(pBackBuffer->GetBFDC(), iX, iY, iW, iH, s_hSharedSpriteDC, (m_iFrame * iW), 0, SRCPAINT);
	SelectObject(s_hSharedSpriteDC, hOldObj);
}

/***********************
* Process: All Sprite actions are processed here
* @author: Asma Shakil
* @parameter: _fDeltaTick: How long it takes to do the process
* @return: void
********************/
void CSprite::Process(float _fDeltaTick)
{
}

/***********************
* GetWidth: Retrieves the width of the sprites bitmap image
* @author: Asma Shakil
* @author: Callan Moore
* @return: int: Width of the sprites bitmap image
********************/
int CSprite::GetWidth() const
{
	return ((m_bitmapSprite.bmWidth) / m_iNumFrames);
}

/***********************
* GetHeight: Retrieves the height of the sprites bitmap image
* @author: Asma Shakil
* @return: int: Height of the sprites bitmap image
********************/
int CSprite::GetHeight() const
{
	return (m_bitmapSprite.bmHeight);
}

/***********************
* GetX: Retrieves the X position of the sprite
* @author: Asma Shakil
* @return: int: X position of the sprite
********************/
int CSprite::GetX() const
{
	return (m_iX);
}

/***********************
* GetY: Retrieves the Y position of the sprite
* @author: Asma Shakil
* @return: int: Y position of the sprite
********************/
int CSprite::GetY() const
{
	return (m_iY);
}

/***********************
* SetX: Sets the X position of the sprite to the given value
* @author: Asma Shakil
* @parameter: _i: The new X position for the sprite
* @return: void
********************/
void CSprite::SetX(int _i)
{
	m_iX = _i;
}

/***********************
* SetY: Sets the Y position of the sprite to the given value
* @author: Asma Shakil
* @parameter: _i: The new Y position for the sprite
* @return: void
********************/
void CSprite::SetY(int _i)
{
	m_iY = _i;
}

/***********************
* TranslateRelative: Translates the sprite by the given X and Y values
* @author: Asma Shakil
* @parameter: _iX: The ammount to move the sprite by on the X axis
* @parameter: _iY: The ammount to move the sprite by on the Y axis
* @return: void
********************/
void CSprite::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

/***********************
* TranslateAbsolute: Moves the sprite to the given coordinates
* @author: Asma Shakil
* @parameter: _iX: The X coordinate to move the sprite to
* @parameter: _iY: The X coordinate to move the sprite to
* @return: void
********************/
void CSprite::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}

/***********************
* SetFrame: Set the sprites Frame to the input frame number
* @author: Callan Moore
* @parameter: _iNewFrame: The new frame number
* @return: void
********************/
void CSprite::SetFrame(int _iNewFrame)
{
	m_iFrame = _iNewFrame;
}

/***********************
* GetFrame: Retrieves the sprites current frame number
* @author: Callan Moore
* @return: int: The current frame number
********************/
int CSprite::GetFrame()
{
	return m_iFrame;
}