#include "requiredIncs.h"



int main(int argc, char** argv){

	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//Testing class Memory 
	Memory myMemory(option);

	//index, value
	myMemory.setMem(0, 100);
	cout << myMemory.getMem(0) << endl;

	//should print in a way that similar to this:
	//Memory Values:
	//[0] -> 100
	//[1] -> 0
	//[2] -> 0
	//.
	//.
	//[49] -> 0	
	myMemory.printAll();
	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	//Testing class CPU 
	CPU myCPU(option);
	myCPU.execute("MOV #0, R1", myMemory);
	myCPU.execute("MOV R1, #1", myMemory);

	//should print in a way that similar to this:
	//CPU Register Values:
	//[0] -> 100
	//[1] -> 0
	//[2] -> 0
	//[3] -> 0
	//[4] -> 0	
	myCPU.print();

	//should print in a way that similar to this:
	//Memory Values:
	//[0] -> 100
	//[1] -> 100
	//[2] -> 0
	//.
	//.
	//[49] -> 0	
	myMemory.printAll();
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgram 
	CPUProgram myCPUProgram(option);

	myCPUProgram.ReadFile(filename);

	cout << myCPUProgram.getLine(0) << endl;
	cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//Testing class Computer 
	CPU myNewCPU(option);

	Computer myComputer1(myNewCPU, myCPUProgram, myMemory, option);
	Computer myComputer2(option);

	myComputer2.setCPU( myComputer1.getCPU() );
	myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
	myComputer2.setMemory(myComputer1.getMemory() );

	myComputer2.execute();

	//////////////////////////////////////////////////////////////////////////

	return 0;
}
