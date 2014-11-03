/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : AlienColumn.h
* Description : Header file for the AlienColumn class
* Author :	Callan Moore
* Mail :	Callan.moore@mediadesign.school.nz	
*/

#pragma once

// Library Includes
#include <vector>

// Local Includes
#include "Alien.h"
#include "Utilities.h"

using namespace std;

class CAlienColumn
{
	// Member Functions
public:
	CAlienColumn(void);
	~CAlienColumn(void);
	virtual bool Initialise( float _fX, float _fY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);
	void Move(bool& _rbDirection);
	void MoveDown();
	bool IsAlive() const;
	vector<CAlien*>* GetAliens();
	void ToggleAnimation();
	bool BelowLoseThreshold();


	// Member Variables
private:
	vector<CAlien*>* m_vecpAliens;
};

