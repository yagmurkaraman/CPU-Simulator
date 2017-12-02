/*----------------------------------------------------------------------------*/
/*                                                                            */
/* HW04_141044016_Yagmur_Karaman                                              */
/*                                                                            */
/* CPUProgram.h                                                               */
/* -------------                                                              */
/* Created on 06/11/2016 by Yagmur_Karaman                                    */
/*                                                                            */
/* Description                                                                */
/* ------------                                                               */
/*		The CPUProgram.h contains the functions which are used the read file, */
/*	stores instructions and find size of file.                                */
/*----------------------------------------------------------------------------*/
#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__

/*----------------------------------------------------------------------------*/
/*						     Includes                                         */
/*----------------------------------------------------------------------------*/
#include <iostream>

using namespace std;

const int LINE_LIMIT=200;

class CPUProgram{

	public:
		
		CPUProgram();
		CPUProgram(string inFile){ ReadFile(inFile); } //inline
		CPUProgram(int option){	mod=option;	}
		void setOption(int setOpt){ option=setOpt; } //inline
		char getOption(){ return option; } //inline
		int ReadFile(string file);
		int size(){ return total; } //inline
		
		string getLine(int line){ return instructions[line]; }//inline
		
	private:

		string file; 
		string instructions[LINE_LIMIT];
		int total;
		int mod;
		int option;		
};
#endif
/*----------------------------------------------------------------------------*/
/*							End of CPUProgram.h                               */
/*----------------------------------------------------------------------------*/
