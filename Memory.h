/*----------------------------------------------------------------------------*/
/*                                                                            */
/* HW04_141044016_Yagmur_Karaman                                              */
/*                                                                            */
/* Memory.h                                                                   */
/* -------------                                                              */
/* Created on 06/11/2016 by Yagmur_Karaman                                    */
/*                                                                            */
/* Description                                                                */
/* ------------                                                               */
/*		The Memory.h contains the functions which are used memory array.      */
/*----------------------------------------------------------------------------*/
#ifndef _MEMORY_H__
#define _MEMORY_H__

#include <iostream>

using namespace std;

const int SIZE_MEMORY=50;

class Memory{

	public:
	
		Memory();
		Memory(int option){	mod=option;	}	
		void setterMemory(int value);
		void setMem(int index,int value);
		unsigned int getMem(int index);
		void printAll();
	
	private:
		
		unsigned int memory[SIZE_MEMORY];
		int mod;
		int value;

};
#endif
/*----------------------------------------------------------------------------*/
/*							End of Memory.h                                   */
/*----------------------------------------------------------------------------*/
