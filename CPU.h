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
/*		The CPU.h contains the functions which are used the execute of        */
/*		instructions.                                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef _CPU_H__
#define _CPU_H__
/*----------------------------------------------------------------------------*/
/*								Includes                                      */
/*----------------------------------------------------------------------------*/
#include <iostream>

#include "Memory.h"

using namespace std;

class CPU{

	public:
	
		CPU();
		CPU(int setOpt){ option=setOpt; }		
		void setRegisters(int value); 
		const int halted();
		const int execute(const string line, Memory& myMemory);
		const int myAtoi(const string constant);
		int isWhichInstruction(string line, int reg1, int reg2, int cons, 
					int memo, Memory& objMemory);
		const int isMov(const string line, const int reg1, const int reg2, 
					const int cons, const int memo, Memory& objMemory);
		const int isAdd(const string line, const int reg1, const int reg2, 
					const int cons, const int memo, Memory& objMemory);
		const int isSub(const string line, const int reg1, const int reg2, 
					const int cons, const int memo, Memory& objMemory);
		const int isJmp(const string line, const int reg1, const int reg2, 
					const int cons, Memory& objMemory);
		const int isJpn(const string line, const int reg1, const int reg2, 
					const int cons, Memory& objMemory);
		const int isPrn(const string line, const int reg1, const int reg2, 
					const int cons, const int memo, Memory& objMemory);
		void printLine(string line);
		void print();
		int getPC(){ return PC; } //inline
		void setPC(int pCounter){ PC=pCounter; } //inline
		void setOption(int setOpt){ option=setOpt; } //inline
		int getOption(){ return option; } //inline
	
	private:
		
		string lowToUpper(string line)const;
		const int findFirst(const string line)const; 
		int allControls(string line, Memory& objMemory);
		const int isValid(const string line, int first)const;
		const int spaceForReg(const string line, int first)const;
		const int findFirstInst(const string line,int first)const;
		const int controlValid(const string line,int regOrConst)const;
		int controlComments(string line)const;
		string removeComments(string line)const;    
		const int controlSpace(const string line,int regOrConst)const;
		string removeSpaces(string line)const;
		const int register1(const string line)const;
		const int register2(const string line)const;
		const int constant(const string line);
		const int memoryCons(const string line);
		const int convertInt(string constant);
		string line;
		int PC;
		int option;
		int reg[5];
		int flag=-1;
		int mod;
		int consSize;
		
};
#endif
/*----------------------------------------------------------------------------*/
/*								End of CPU.h                                  */
/*----------------------------------------------------------------------------*/
