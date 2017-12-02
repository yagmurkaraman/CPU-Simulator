/*----------------------------------------------------------------------------*/
/*                                                                            */
/* HW03_141044016_Yagmur_Karaman                                              */
/*                                                                            */
/* Computer.cpp                                                               */
/* -------------                                                              */
/* Created on 06/11/2016 by Yagmur_Karaman                                    */
/*                                                                            */
/* Description                                                                */
/* ------------                                                               */
/*		The Computer.cpp contains the functions which are used the execute    */
/*		program.                                                              */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*							       Includes                                   */
/*----------------------------------------------------------------------------*/
#include <iostream>

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"

Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, int option)
{
	myCPU.setPC(1);
	setCPU(myCPU);
	setCPUProgram(myCPUProgram);
	setMemory(myMemory);
	mod=option;	
}// call setters and get option
Computer::Computer(int option){ mod=option; }
			
int Computer::execute()
{
	if(mod!=0 && mod!=1 && mod!=2)
	{
    	cerr << "ERROR: INVALID OPTION!!!\n";
    	return 0;	
    }// 0-1-2 disindaki option'lar icin hata verir.
	while(!exeCPU.halted())
	{
		if(exeCPU.halted())
			exeMemory.printAll();
			
		instruction=exeProg.getLine(exeCPU.getPC()-1);
		exeCPU.setOption(mod);	
		// eger instruction uygun degilse program bitirilir.
		if(instruction[0]=='H')
		{
			cout << "HALT!\n";
			exeMemory.printAll();
		}// end of file	
		if(!exeCPU.execute(instruction,exeMemory))  
			return 0;
		
	}// program halt edene kadar calisir.
	return 1;
}
