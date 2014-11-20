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
	virtual ~CAlienColumn(void);
	virtual bool Initialise( float _fX, float _fY);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void Move(bool& _rbDirection);
	void MoveDown();
	void ToggleAnimation();

	bool IsAlive() const;
	bool BelowLoseThreshold();

	CAlien* ReturnLowest();

	// Getters
	vector<CAlien*>* GetAliens();

	// Member Variables
private:
	vector<CAlien*>* m_vecpAliens;
};

