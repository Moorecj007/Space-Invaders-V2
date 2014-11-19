/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
  
* File Name : Utilities.h 
* Description : Header file for the Utilities used.
* Author :	Asma Shakil
*			Callan Moore
* 			JC Fowles
* Mail :	Asma.Shakil@mediadesign.school.nz 
* 			Callan.Moore@mediadesign.school.nz 
*			Jc.Fowles@mediadesign.school.nz 
*/

#pragma once

#if !defined(__UTILITIES_H__)
#define __UTILITIES_H__

// Library Includes
#include <strstream>
#include <tchar.h>
#include <string>

// Macros
	// Check to see if "a" exists 
#define VALIDATE(a) if (!a) return (false)
#define RIGHT true
#define LEFT false


/***********************
* ToString: Returns the printable string of the passed in object  
* @author: Asma Shakil
* @parameter: _value: constant variable of any type
* @return: string: the sring version of the passed in object
********************/
template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

#endif // __UTILITIES_H__