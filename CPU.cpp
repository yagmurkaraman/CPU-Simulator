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
/*		The CPU.cpp contains the functions which are used the read file       */
/*	stores instructions and find size of file.                                */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*							       Includes                                   */
/*----------------------------------------------------------------------------*/
#include <iostream>

#include "Memory.h"
#include "CPU.h"


using namespace std;
/*----------------------------------------------------------------------------*/
/*							Function Implementations                          */
/*----------------------------------------------------------------------------*/
/* Function CPU::CPU                                                          */
/* -----------------                                                          */
/*		Call setter functions for registers and PC(Program Counter)           */

CPU::CPU()
{
	setRegisters(0);
	setPC(1);
}
/*----------------------------------------------------------------------------*/
/* Function CPU::setRegisters                                                 */
/* ---------------                                                            */
/*		Setter for registers.                                                 */

void CPU::setRegisters(int value)
{
	reg[0]=value;
	reg[1]=value;
	reg[2]=value;
	reg[3]=value;
	reg[4]=value;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::execute                                                      */
/* ---------------                                                            */
/*		Call allControl function for the execute of instruction.              */

const int CPU::execute(const string line,Memory& objMemory)
{
	
	if(!allControls(line,objMemory))
		return 0;				
}
/*----------------------------------------------------------------------------*/
/* Function CPU::allControls                                                  */
/* ----------------                                                           */
/*		This function is base function to our CPU program. All controls are   */
/*		made in this function. Return 1 on success, 0 on error and            */
/*		exit program.                                                         */

int CPU::allControls(string line, Memory& objMemory)
{
	int first,regOrConst;
    int reg1,reg2,cons,memo;
    
	line=lowToUpper(line);// buyuk harfe cevirir.
	first=findFirst(line);// ilk harfin indexini bulur.

	if(line[first]=='H')
	{
		flag=1;
		halted(); //eger HLT gelirse programi bitirir. 
		return 0;
	}
	if(line[first]=='\0')
		return 0;
		
	if(!controlComments(line))
	{
		cerr << "ERROR: " << line << "-PLEASE CONTROL YOUR COMMENTS!!!\n";	
		return 0;
	}// instructionda yorum varsa uygun olup olmadigina bakar, uygun degilse
	// hata mesaji verip programi bitirir.
	line=removeComments(line);// yorum varsa ve uygunsa siler.
	
	if(!(isValid(line,first)))				 						 		
	{
		cerr << "ERROR: " << line << "-INVALID COMMAND OR SPACES UNTIL COMMAND!!!\n";
		return 0;	
	}// komut uygunsuzsa hata mesaji verip programi bitirir.	
	if(!(spaceForReg(line,first)))
	{
		cerr << "ERROR: " << line << "-INVALID SPACE AFTER COMMAND!!!\n";
		return 0;
	}// komuttan sonra en az 1 tane bosluk yoksa hata mesaji verip programi bitirir.
	
	// komuttan sonra gelen instructionin indexini bulur.
	regOrConst=findFirstInst(line,first); 
	 
	if(!(controlValid(line,regOrConst)))  
	{
		cerr << "ERROR: " << line << "-IT IS NOT REGISTER OR CONSTANT!!!\n";
		return 0;
	}// instructionin uygun degilse hata mesaji verip programi bitirir.	
	if(!(controlSpace(line,regOrConst))) // 
	{
		cerr << "ERROR: " << line << "-THERE IS INVALID SPACES IN INSTRUCTION!!!\n";	
		return 0;
	}// instructiondaki tüm bosluklari kontrol eder, uygun degilse hata mesaji
	// verip programi bitirir.
	line=removeSpaces(line);// bosluklari siler.
	reg1=register1(line);// ilk registerin degerini bulur.
	reg2=register2(line);// virgulden sonraki registerin degerini bulur.
	cons=constant(line);// constant degerini hesaplar.
	memo=memoryCons(line);// memory location degerini hesaplar.
	
	if(memo==-2)
	{
		cerr << "ERROR: " << line << "-MEMORY CAN NOT CONTAIN NEGATIVE VALUES\n"
			<< "                 OR CAN NOT BE SMALLER 0 OR BIGGER 49!!!\n";
		return 0;
	}		
	else if(reg1==0 || reg2==0)
	{
		cerr << "ERROR: "<< line << "INVALID REGISTER FOR INSTRUCTION\n";
		return 0;
	}	
	// satirdaki komut uygunsa calistirir, degilse hata mesaji verip 
	// programi bitirir.
	if(!(isWhichInstruction(line,reg1,reg2,cons,memo,objMemory)))	
		return 0; 
	
	return 1;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::lowToUpper                                                   */
/* --------------------                                                       */
/*		This function takes line and convert upper all letters, and return    */
/*		line with upper letters.                                              */

string CPU::lowToUpper(string line)const
{
	int size,i;
	
	size=line.length();
	
	for(i=0; i<size; i++)
	{
		if(line[i]>='a' && line[i]<='z')
			line[i]=line[i]+('A'-'a');
	}
	return line;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::findFirst                                                    */
/* ------------------                                                         */
/*		This function takes line and find first nonspace index and return     */
/*		index.                                                                */

const int CPU::findFirst(const string line)const
{
	int i;
	
	for(i=0; line[i]==' '; ++i)
	;
	
	return i;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isValid                                                      */
/* ------------------                                                         */
/*		This function takes line and first nonspace index, and control        */
/*		first nonspace index in line is valid or invalid.                     */
/*      Return 1 on success, 0 on error.                                      */

const int CPU::isValid(const string line,int first)const
{
	if(line[first]=='M' && line[first+1]=='O' && line[first+2]=='V')
		return 1;
	
	else if(line[first]=='A' && line[first+1]=='D' && line[first+2]=='D')
		return 1;
		
	else if(line[first]=='S' && line[first+1]=='U' && line[first+2]=='B')
		return 1;
	
	else if(line[first]=='J' && line[first+1]=='M' && line[first+2]=='P')
		return 1;
		
	else if(line[first]=='J' && line[first+1]=='P' && line[first+2]=='N')
		return 1;
		
	else if(line[first]=='P' && line[first+1]=='R' && line[first+2]=='N')
		return 1;
		
	else if(line[first]=='H' && line[first+1]=='L' && line[first+2]=='T')
		return 1;

	return 0;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::spaceForReg                                                  */
/* ----------------------                                                     */
/*		This function takes line and first nonspace index, and control        */
/*		space after command.                                                  */
/*		Return 1 on success, 0 on error.                                      */

const int CPU::spaceForReg(const string line,int first)const
{
	first=first+3;
	
	if(line[first]==' ')
		return 1;		
	else
		return 0;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::findFirstIns                                                 */
/* ------------------------                                                   */
/*		This function takes line and first nonspace index, and find           */
/*		first nonspace index after the command, and return this index.        */

const int CPU::findFirstInst(const string line,int first)const
{
	int i;
	first=first+3;
	
	for(i=first; line[i]==' '; ++i)
	;	
	
	return i;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::controlValid                                                 */
/* ----------------------                                                     */
/*		This function takes line and first nonspace index after command       */
/*		(regOrConst), and control this index valid or invalid.                */
/*		Return 1 on success, 0 on error.                                      */

const int CPU::controlValid(const string line,int regOrConst)const
{
	if(line[regOrConst]=='R' || (line[regOrConst]>='0' && line[regOrConst]<='9')
		|| line[regOrConst]=='#')
		return 1;
	
	return 0;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::controlComments                                              */
/* ------------------------                                                   */
/*		This function takes line control comments are valid or invalid.       */
/*		After instruction, if line have ; and some comments after ; or        */
/*		line does not have ; and some comments return 1(success);             */
/*      if line have ; but does not have some comments after ; or line        */
/*      have some comments but does not have ; before comments,               */
/*		return 0(error).                                                      */

int CPU::controlComments(string line)const
{
	int i=0;
	int size;
	
	size=line.length();
	i=line.find(";");
	i++;
				
	if(i>0)
	{
		while(i!=size)
		{
			if(line[i]==' ')
				i++;
				
			else
				line.erase(i,size);
				return 1;
			
		}
		return 0;
	}
	else
		return 1;

}
/*----------------------------------------------------------------------------*/
/* Function CPU::removeComments                                               */
/* -------------------------                                                  */
/*		This function takes line and and if line have some comments           */
/*		remove these, and return cleaned line.                                */

string CPU::removeComments(string line)const
{
	int i=0,size;
	
	size=line.length();
	i=line.find(";");
	i++;
	
	if(i>0)
		line.erase(i-1,size);
	
	return line;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::controlSpace                                                 */
/* ----------------------                                                     */
/*		This function takes line and control all spaces are valid             */
/*		or invalid, return 1 on success, 0 on error.                          */

const int CPU::controlSpace(const string line,int regOrConst)const
{
	int i,size,sizetemp;
	string temp;

	temp=removeSpaces(line);
	sizetemp=temp.length();
	size=line.length();
	
	if(line[regOrConst]=='R')
	{
		if(line[regOrConst+1]>='1' && line[regOrConst+1]<='5')
		{
			i=regOrConst+2;
			while(line[i]!=',' && sizetemp!=5)
			{
				if(line[i]==' ')
					i++;	
					
				else 
					return 0;	
			}
			++i;
			while(line[i]==' ')
				++i;
			
			if(line[0]=='P')
				return 1;
				
			else if((line[i]>='0' && line[i]<='9') || line[i]=='#')
			{
				++i;
				while((line[i]>='0' && line[i]<='9') && i!=size)
					++i;
	
				while(i!=size)
				{
					if(line[i]!=' ')
						return 0;
					else
						++i;
				}
			}	
		}
		else
			return 0;	
	}	
	else if(line[regOrConst]>='0' && line[regOrConst]<='9')
	{	
		i=regOrConst;
		while((line[i]>='0' && line[i]<='9') && i!=size)
			++i;
		
		while(i!=size)
		{
			if(line[i]!=' ')
				return 0;
			else
				++i;	
		}
	}
	else if(line[regOrConst]=='#')
	{
		i=regOrConst+1;
		while((line[i]>='0' && line[i]<='9') && line[i]!=',')
			++i;
			
		if(line[i]==',')
		{
			++i;
			while(line[i]==' ')
				++i;
					
			if(line[i]=='R')
			{
				if(line[i+1]>='1' && line[i+1]<='5')
				{
					i=i+2;
					if(i!=size)
					{
						while(i!=size)
						{
							if(line[i]!=' ')
								return 0;
							else
								++i;	
						}
					}
					else
						return 1;
				}
			}
			else if(line[i]>='0' && line[i]<='9')
			{
				while((line[i]>='0' && line[i]<='9') && i!=size)
					++i;
	
				while(i!=size)
				{
					if(line[i]!=' ')
						return 0;
					else
						++i;
				}
			}		
		}
		else if(i==size && temp[0]=='P') 
			return 1;

		else
			return 0;		
	}
	return 1;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::removeSpaces                                                 */
/* ----------------------                                                     */
/*		This function takes line and and if line have some comments           */
/*		remove these, and return cleaned line.                                */

string CPU::removeSpaces(string line)const
{
	int size,i;
		
	size=line.length();
	
	for(i=size-1; i>=0; --i)
	{
 		if(line[i]==' ')
 		{
 			line.erase(i,1);
 		}	
	}
	return line;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::register1                                                    */
/* -------------------                                                        */
/*		This function takes line and if line have register after command,     */
/*		find its value, and control is it between 1-5, return register value  */
/*		on success, -1 on invalid register and 0 on other errors.             */

const int CPU::register1(const string line)const
{
	int indexOfFirstReg=3;
	if(line[indexOfFirstReg]=='R' && (line[indexOfFirstReg+1]>='1' && 
						line[indexOfFirstReg+1]<='5'))
		return (line[indexOfFirstReg+1]-'0');
	
	else if(line[indexOfFirstReg]=='R' && !(line[indexOfFirstReg+1]>='1' && 
				line[indexOfFirstReg+1]<='5'))
		return 0;
	else
		return -1;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::register2                                                    */
/* ------------------                                                         */
/*		This function takes line and if line have register after comma,       */
/*		find its value, and control is it between 1-5, return register value  */
/*		on success, -1 on invalid register and 0 on other errors.             */

const int CPU::register2(const string line)const
{
	
	int indexOfFirstReg;
	int j=0;
	
	j=line.find(',');
	
	if(j>0)
		indexOfFirstReg=j+1;
	
	else
		return -1;
	//cout << indexOfFirstReg <<endl;
	if(line[indexOfFirstReg]=='R'  && (line[indexOfFirstReg+1]>='1' && 
				line[indexOfFirstReg+1]<='5'))
		return (line[indexOfFirstReg+1]-'0');		
	
	else if(line[indexOfFirstReg]=='R' && !(line[indexOfFirstReg+1]>='1' && 
			line[indexOfFirstReg+1]<='5'))
		return 0;
	else
		return -1;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::constant                                                     */
/* ------------------                                                         */
/*		This function takes line and if line have constant find its value,    */
/*		and return constant value on success, -1 on error.                    */

const int CPU::constant(const string line)
{
	string constant;
	int index;
	int i=0,j,size;
	
	size=line.length();
	j=line.find(',');
	
	if((line[3]=='R' || line[3]=='#') && j>0)
		index=j+1;
	
	else
		index=3;
	
	while(index<size)
	{ 	
		if((line[index]>='0' && line[index]<='9')){
							
			constant[i]=line[index];		
			index++;		
			i++;
		}
		else
			return -1;
	}
	consSize=i;
	return convertInt(constant);
}
const int CPU::memoryCons(const string line)
{
	int index,i,k,cons;
	string constant;
	
	if(line[3]=='R')
	{
		if(line[6]!='#')
			return -1;
			
		else
			index=7;
	}
	else if(line[3]!='#')
		return -1;
	
	else
		index=4;
	
	i=line.find(',');
	if(i<=0 && line[0]!='P')
		return -1;
	
	else if(i<index)
	{
		i=0;
		while(line[index]!='\0')
		{	
			if((line[index]>='0' && line[index]<='9')){
							
				constant[i]=line[index];		
				index++;		
				i++;
			}
			else
				return -1;
		}
	}
	else
	{
		i=0;
		while(line[index]!=',')
		{ 	
			if((line[index]>='0' && line[index]<='9')){
							
				constant[i]=line[index];		
				index++;		
				i++;
			}
			else
				return -1;
		}
		if(i>=2 && constant[1]>=5)
			return -2;
				
	}
	consSize=i;
	return convertInt(constant);
}
const int CPU::convertInt(string constant)
{
	int cons=0,k;
	
	for(k=0; k<consSize; k++)
		cons=10*cons+(constant[k]-'0');
	
	return (cons);
}
const int CPU::myAtoi(string constant){

		return constant[0]-'0';
}

/*----------------------------------------------------------------------------*/
/* Function CPU::isWhichInstruction                                           */
/* --------------------                                                       */
/*		This function calls instruction functions.                            */

int CPU::isWhichInstruction(string line, int reg1, int reg2, int cons, int memo, 
			Memory& objMemory)
{
	if(line[0]=='M')
	{
		isMov(line,reg1,reg2,cons,memo,objMemory);
		setPC(PC+1);
	}	
	else if(line[0]=='A')
	{
		isAdd(line,reg1,reg2,cons,memo,objMemory);
		setPC(PC+1);
	}
	else if(line[0]=='S')
	{
		isSub(line,reg1,reg2,cons,memo,objMemory);
		setPC(PC+1);
	}
	else if(line[0]=='J' && line[1]=='M')
	{	
		if(!(isJmp(line,reg1,reg2,cons,objMemory)))
			return 0;			
	}
	else if(line[0]=='J' && line[1]=='P')
	{	
		if(!(isJpn(line,reg1,reg2,cons,objMemory)))
			return 0;			
	}
	else if(line[0]=='P')
	{
		isPrn(line,reg1,reg2,cons,memo,objMemory);
		setPC(PC+1);	
	}
	else if(line[0]=='H')
	{	
		flag=1;
		halted();	
	}
	if(option==2)
		objMemory.printAll();
	
	return 1;	
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isMov                                                        */
/* --------------                                                             */
/*		This function relaizes MOV command.                                   */

const int CPU::isMov(const string line, const int reg1, const int reg2, 
				const int cons, const int memo, Memory& objMemory)
{
	int index=memo;
	int value=reg[reg1-1];
	int value1=reg[reg2-1];
	
	if(cons==-1 && memo==-1)
		reg[reg2-1]=reg[reg1-1]; 
		
	else if(memo==-1 && reg2==-1)
		reg[reg1-1]=cons;
					
	else if(reg2==-1 && cons==-1)
	{
		if(line[3]=='R')
			objMemory.setMem(index,value);
			
		else if(line[3]=='#')
			reg[reg1-1]=objMemory.getMem(index);	
	}
	else if(reg1==-1 && reg2==-1)
		objMemory.setMem(index,cons);
	
	else if(reg1==-1 && cons==-1)
	{
		if(line[3]=='#')
			reg[reg2-1]=objMemory.getMem(index);
		
		else if(line[3]=='R')
			objMemory.setMem(index,value1);
			
	}
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}
	return 1;
		
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isAdd                                                        */
/* ----------------                                                           */
/*		This function relaizes ADD command.                                   */

const int CPU::isAdd(const string line, const int reg1, const int reg2, 
					const int cons, const int memo, Memory& objMemory)
{
	int index=memo;
	
	if(cons==-1 && memo==-1)
		reg[reg1-1]+=reg[reg2-1];

	else if(memo==-1 && reg2==-1)
		reg[reg1-1]+=cons;
		
	else if(reg2==-1 && cons==-1)
		reg[reg1-1]+=objMemory.getMem(index);

		if(option==1 || option==2)
	{
		printLine(line);
		print();
	}
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}
	return 1;
		
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isSub                                                        */
/* ----------------                                                           */
/*		This function relaizes SUB command.                                   */

const int CPU::isSub(const string line, const int reg1, const int reg2, 
						const int cons, const int memo, Memory& objMemory)
{
	int index=memo;
	
	if(cons==-1 && memo==-1)
		reg[reg1-1]-=reg[reg2-1];

	else if(memo==-1 && reg2==-1)
		reg[reg1-1]-=cons;
	
	else if(reg2==-1 && cons==-1)
		reg[reg1-1]-=objMemory.getMem(index);
	
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}	
	return 1;	
		
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isJmp                                                        */
/* ----------------                                                           */
/*		This function relaizes JMP command.                                   */

const int CPU::isJmp(const string line, const int reg1, const int reg2, 
						const int cons, Memory& objMemory)
{
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}		
	if(reg1==-1)
		setPC(cons);
	
	else if(reg[reg1-1]==0)
		setPC(cons);
	
	else
		setPC(PC+1);
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isJpn                                                        */
/* ----------------                                                           */
/*		This function relaizes JPN command.                                   */

const int CPU::isJpn(const string line, const int reg1, const int reg2, 
						const int cons, Memory& objMemory)
{
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}	
	if(reg[reg1-1]<=0)
		setPC(cons);
		
	else
		setPC(PC+1);	
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isPrn                                                        */
/* ----------------                                                           */
/*		This function relaizes PRN command.                                   */

const int CPU::isPrn(const string line, const int reg1, const int reg2, 
						const int cons, const int memo, Memory& objMemory)
{
	int index=memo;
	
	if(cons==-1 && memo==-1)	
		cout << reg[reg1-1] << endl;
	
	else if(reg1==-1 && memo==-1)
		cout << cons << endl;
	
	else if(reg1==-1 && cons==-1)
		cout << objMemory.getMem(index) << endl;	
	
	
	if(option==1 || option==2)
	{
		printLine(line);
		print();
	}
	return 1;
}
/*----------------------------------------------------------------------------*/
/* Function CPU::isHlt                                                        */
/* ----------------                                                           */
/*		This function relaizes HLT command, exits program.                    */

const int CPU::halted()
{
	if(flag==1)
	{
		cout << "HLT\n";
		cout <<"[0] -> "<<reg[0]<<"\n[1] -> "<<reg[1]<<"\n[2] -> "<<reg[2]
				<<"\n[3] -> "<<reg[3] <<"\n[4] -> "<<reg[4]<<endl<<endl;
	
		cout <<"PROGRAM COUNTER:"<<PC<<endl;
		return true;
	}
	else
		return false;
}
void CPU::printLine(string line)
{
	for(int i=0; i<3; ++i)
		cout << line[i];
	
	cout << " ";

	for(int i=3; line[i]!='\0'; ++i)
		cout << line[i];
	
	cout << endl;
	return;
}
/*----------------------------------------------------------------------------*/
/*	Function CPU::print                                                       */
/*  ---------------                                                           */
/*		This function print all registers values, if option is 1.             */

void CPU::print()
{
	 cout << "[0]"<<" -> " <<reg[0]<<endl<< "[1]"<<" -> " <<reg[1]<<endl<< 
	 	"[2]"<<" -> " <<reg[2] <<endl<< "[3]"<<" -> " <<reg[3]<< endl <<
	 	"[4]"<<" -> " <<reg[4]<<endl<<endl;
		
	return;
}
/*----------------------------------------------------------------------------*/
/*								End of CPU.cpp                                */
/*----------------------------------------------------------------------------*/
