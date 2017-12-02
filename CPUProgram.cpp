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
/*		The CPUProgram.cpp contains the functions which are used the read file*/
/*	stores instructions and find size of file.                                */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*							       Includes                                   */
/*----------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>

#include "CPUProgram.h"

using namespace std;

CPUProgram::CPUProgram(){ }

int CPUProgram::ReadFile(string file)
{
	ifstream inFile;
	if(!(inFile))
    {
    	cerr << "ERRORS: FILE COULDN'T BE OPENED!!!\n";
    	return false;
    }// dosya acilamazsa hata verir.
	string line;
	int i;
	inFile.open(file); // dosya acilir.
	
	i=0;
	while(getline(inFile, line))
	{
		instructions[i]=line;
		i++;
	}// tum instructionlari yeni bir string array icine atar.
	total=i;// size, total icinde tutulur.
	if(total>LINE_LIMIT)
	{
    	cerr<<"ERROR: THE .TXT FILE CAN BE MOST 200 LINES!!!\n";
    	return 0;
    }// 200 den fazla line var ise hata verir.	
}
/*----------------------------------------------------------------------------*/
/*							End of CPUProgram.cpp                             */
/*----------------------------------------------------------------------------*/
