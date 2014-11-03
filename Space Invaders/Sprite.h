/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Sprite.h
* Description : Header file for the sprite class
* Author :	Asma Shakil
*			Callan Moore
*			JC Fowles
* Mail :	Asma.shakil@mediadesign.school.nz
*			Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz		
*/

#pragma once

#if !defined(__SPRITE_H__)
#define __SPRITE_H__

// Library Includes
#include "windows.h"

// Prototypes
class CSprite
{
	// Member Functions
public:
	CSprite();
	~CSprite();
	bool Initialise(int _iResourceID, int _iMaskResourceID, int _iNumFrames);
	void Draw();
	void Process(float _fDeltaTick);
	int GetWidth() const;
	int GetHeight() const;
	int GetX() const;
	int GetY() const;
	void SetX(int _i);
	void SetY(int _i);
	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);
	int GetFrame(); 
	void SetFrame(int _iNewFrame);

private:
	// Disallowing copies
	CSprite(const CSprite& _kr);
	CSprite& operator= (const CSprite& _kr);

	// Member Variables
protected:
	int m_iX;
	int m_iY;
	HBITMAP m_hSprite;
	HBITMAP m_hMask;
	BITMAP m_bitmapSprite;
	BITMAP m_bitmapMask;
	static HDC s_hSharedSpriteDC;
	static int s_iRefCount;
	int m_iFrame;
	int m_iNumFrames;
};

#endif // __SPRITE_H__
