/*----------------------------------------------------------------------------*/
/*                                                                            */
/* HW03_141044016_Yagmur_Karaman                                              */
/*                                                                            */
/* Memory.cpp                                                                 */
/* -------------                                                              */
/* Created on 06/11/2016 by Yagmur_Karaman                                    */
/*                                                                            */
/* Description                                                                */
/* ------------                                                               */
/*		The Memory.cpp contains the functions which are used the memory       */
/*	array.                                                                    */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*							       Includes                                   */
/*----------------------------------------------------------------------------*/
#include <iostream>

#include "Memory.h"

using namespace std;

Memory::Memory()
{
	setterMemory(0);
}
void Memory::setterMemory(int value)
{
	for(int i=0; i<SIZE_MEMORY; ++i)	
		memory[i]=value;	
}// set memory

void Memory::setMem(int index, int value){ memory[index]=value; }

unsigned int Memory::getMem(int index){	return memory[index];	}

void Memory::printAll()
{	
	cout << endl<<"                        ***CONTENTS OF THE MEMORY***                   \n";
	for(int i=0; i<50; ++i)
	{
		cout << "#"<<i<<"->"<< memory[i] << "	";

		if(!((i+1)%10))
			cout << endl;
	}
	cout << "------------------------------------------------------------------------------\n";		
}
/*----------------------------------------------------------------------------*/
/*							End of Memory.cpp                                 */
/*----------------------------------------------------------------------------*/
