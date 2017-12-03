#include "VirtualMachine.h"
#include<stdio.h>
#include <fstream>
#include<iostream>
#include <string>
#include <sstream>

using namespace std;
VirtualMachine::VirtualMachine()
{
	ip = 0;
	sp = 0;
	dataSize = 0;
	imageSize = 0;
	inputFromString = false;
	inputString << "";
	outputFileName = "output.txt";
}


VirtualMachine::~VirtualMachine()
{
}

int HexStringToInt(char *str)
{
	/*function that convert a hex string into a signed 32-bit integer*/
	stringstream ss;		//string stream for buffer
	unsigned int number;		//unsigned dummy int

	ss << hex << str;
	ss >> number;
	return static_cast<int>(number);
}

int BinArryToInt(int *binArray, int binSize)
{
	int res = 0;
	for (int i = 0; i < binSize; i++)
	{
		int b = pow(2, i);
		res = res + binArray[i] * b;
	}
	return res;
}
int *IntToBinArray(int value)
{
	/*function that convert a 32-bit signed int to an array of binary values*/
	static int tempArray[32];
	for (int i = 0; i < 32; ++i)
		tempArray[i] = value & (1 << i) ? 1 : 0;
	return tempArray;
}

int VirtualMachine::f(int val)
{
	/*the f(v) function in the instruction*/
	sp = sp - 1;
	data[sp] = val;
	return 0;
}

int VirtualMachine::g()
{
	/*the g() function in the instruction*/
	int val = data[sp];
	sp = sp + 1; 
	return val;
}


int VirtualMachine::DecodeOperation(int instruction)
{
	int *instructionBin;
	instructionBin = IntToBinArray(instruction);

	//fetch operation code
	for (int i = 0; i < 8; i++)
		operationCode[i] = instructionBin[24 + i];

	//fetch optional data
	for (int i = 0; i < 24; i++)
		optionalData[i] = instructionBin[i];

	optionalDataInt = BinArryToInt(optionalData,24);
	return 0;
}


int VirtualMachine::PerformOperation()
{
	bool binop = (bool)operationCode[7];
	int operation = BinArryToInt(operationCode,6);
	int addr;
	int stData;
	int cond;
	int temp;

	if (!binop)	//if not a binary operation
	{
		switch (operation)
		{
		case 0:		//pop
			sp = sp + 1;
			break;
		case 1:		//push<const>
			f(optionalDataInt);
			break;
		case 2:		//push ip
			f(ip);
			break;
		case 3:		//push sp
			f(sp);
			break;
		case 4:		//load
			addr = g();
			f(data[addr]);
			break;
		case 5:		//store
			stData = g();
			addr = g();
			data[addr] = stData;
			break;
		case 6:		//jmp
			cond = g();
			addr = g();
			if (cond != 0)
				ip = addr;
			break;
		case 7:		//not
			if (g() == 0)
				f(1);
			else
				f(0);
			break;
		case 8:		//putc
			temp = g() & 0xff;
			cout << (char)temp;
			outputFile << (char)temp;
			break;
		case 9:		//getc
			char x;
			inputFromString ? inputString >> x : cin >> x;
			f((int)x & 0xff);
			break;
		case 10:	//halt (stop execution)
			stopexe=1;
			break;
		default:
			cout << "operation not recogonised" << endl;
			break;
		}
	}
	else	//if is a binary operation
	{
		int b = g();	//fetch a and b;
		int a = g();
		switch (operation)
		{
		case 0:		// a + b : add
			f(a + b);
			break;
		case 1:		// a - b : sub
			f(a - b);
			break;
		case 2:		// a * b : mul
			f(a * b);
			break;
		case 3:		// a / b : div
			f(a / b);
			break;
		case 4:		// a & b : and
			f(a & b);
			break;
		case 5:		// a | b : or
			f(a | b);
			break;
		case 6:		// a ^ b : xor
			f(a ^ b);
			break;
		case 7:		// a = b : eq
			f(a == b);
			break;
		case 8:		// a < b : lt
			f(a < b);
			break;
		default:
			cout << "operation not recogonised" << endl;
			break;
		}
	}
	return 0;
}

int VirtualMachine::LoadingVMimage(const char *fileName)
{	
	string line;		//buffer for holding each line
	int intRep;			//32-bit integer representation of each line

	ifstream binFile(fileName);	//open the file to read

	 if (binFile.is_open())
	 {
		 //Read the first 32 - bit signed value of data size
		 char str[9];
		 binFile.getline(str, 9);
		 //Allocate an array called 'data' of signed 32-bit integers capable of holding data-size elements
		 dataSize = HexStringToInt(str);//get data size
		 sp = dataSize;
		 data = new int[dataSize];				//allocate the data array

		 //Read the second 32 - bit signed value of image-size
		 binFile.getline(str, 9);
		 imageSize = HexStringToInt(str);//get data size

		 //fill the data array with image-size data
		 for (int i = 0; i < imageSize; i++)
		 {
			 binFile.getline(str, 9);
			 data[i] = HexStringToInt(str);
		 }
	 }
	 else
	 {
		 cout << "file not found" << endl;
	 }
	 binFile.close();	//close the file
	 return 0;
}

int VirtualMachine::InstructionExcution()
{
	int currentInstruction;
	outputFile.open(outputFileName);
	if (dataSize != 0)
	{
		while (!stopexe)
		{
			currentInstruction = data[ip];
			ip++;
			//decode instruction;
			DecodeOperation(currentInstruction);
			//perform action based on operation
			PerformOperation();
		}
		outputFile.close();
	}
	return 0;
}

int VirtualMachine::SetInputString(string str)
{
	inputString << str;
	return 0;
}

int VirtualMachine::SetOutputFile(std::string fileName)
{
	outputFileName = fileName;
	return 0;
}