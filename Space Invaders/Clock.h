/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
  
* (c) 2005 - 2014 Media Design School 
  
* File Name : Clock.h 
* Description : Header file for the Clock class
* Author :	Asma Shakil
*			Callan Moore
* 			JC Fowles
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*/

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
// Local Includes
// Types
// Constants
    
// Prototypes
class CClock
{
	// Member Functions
public:
	CClock();
	~CClock();
	bool Initialise();
	void Process();
	float GetDeltaTick();

private:
	//Disallowing copies
	CClock(const CClock& _kr);
	CClock& operator= (const CClock& _kr);

	// Member Variables
protected:
	float m_fTimeElapsed;
	float m_fDeltaTime;
	float m_fLastTime;
	float m_fCurrentTime;
};

#endif // __CLOCK_H__