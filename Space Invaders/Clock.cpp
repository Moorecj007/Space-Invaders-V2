/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
* 
* (c) 2005 - 2014 Media Design School 
* 
* File Name : Clock.cpp 
* Description : Implementaion file for the Clock Class
* Author :	Asma Shakil
*			Callan Moore
* 			JC Fowles
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*/

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"
    
/***********************
* CClock: Contructor, also initialises member variables to 0.0f
* @author: Asma Shakil
* @return: void
********************/
CClock::CClock()	: m_fTimeElapsed(0.0f)
					, m_fDeltaTime(0.0f)
					, m_fLastTime(0.0f)
					, m_fCurrentTime(0.0f)
{
}

/***********************
* ~CClock: Destructor, deletes instance of the clock
* @author: Asma Shakil
* @return: void
********************/
CClock::~CClock()
{
}

/***********************
* Initialise: Initialises the clock instance???
* @author: Asma Shakil
* @return: bool: true 
********************/
bool CClock::Initialise()
{
	return (true);
}

/***********************
* Process: Updates the member variables, using the current time lapsed from programe start
* @author: Asma Shakil
* @return: void
********************/
void CClock::Process()
{
	m_fLastTime = m_fCurrentTime;
	m_fCurrentTime = static_cast<float>(timeGetTime());
	if (m_fLastTime == 0.0f)
	{
		m_fLastTime = m_fCurrentTime;
	}
	m_fDeltaTime = m_fCurrentTime - m_fLastTime;
	m_fTimeElapsed += m_fDeltaTime;
}

/***********************
* GetDeltaTick: Returns the delta tick. DetlaTick is how long has it taken to complete a process(the clock update)
* @author: Asma Shakil
* @return: float: The deltaTick in seconds
********************/
float CClock::GetDeltaTick()
{
	return (m_fDeltaTime / 1000.0f);
}