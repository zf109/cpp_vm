#pragma once
#include<stdio.h>
#include <fstream>
#include<iostream>
#include <string>
#include <sstream>

#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

class VirtualMachine
{
public:

	VirtualMachine();				//constructor
	virtual ~VirtualMachine();		//destructor

	int LoadingVMimage(const char *fileName);	//the method that read a file
	int InstructionExcution();	//excute the instructions

	bool inputFromString;					//toggle read the input from string
	int SetInputString(std::string str);			//if inputFromString is true, then use this function to set the inputString
	int SetOutputFile(std::string fileName);	//set the output file's name

private:

	int operationCode[8];		//array to hold operation code (8-bit)
	int optionalData[24];		//array to hold optional data (24-bit)
	int optionalDataInt;			//the integer form of the optional data
	int DecodeOperation(int instruction); //decode operation
	int PerformOperation();

	int dataSize;	//size of the data (32-bit)
	int imageSize;	//size of the image (32-bit)
	int *data;		//array to hold the data (8-bit*imageSize)

	int ip;			//the 'ip' register
	int sp;			//the 'sp' register

	int f(int val);				//the f function
	int g();					//the g function
	bool stopexe;               //stop the execution

	std::string outputFileName;		//name of the output file
	std::ofstream outputFile;			//the textfile record output information
	std::stringstream inputString;			//if inputFromString is true, then this string contains the stringstream of input
};

#endif // !VIRTUALMACHINE_H




