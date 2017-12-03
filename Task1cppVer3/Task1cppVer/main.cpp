#include<iostream>
#include<stdio.h>
#include "VirtualMachine.h"
#include <fstream>
#include<string>
using namespace std;

void main()
{
	VirtualMachine newVM;
	/*
	cout << "Enter the bin file name.."<< endl;
	string fname;
	cin >> fname;
	char *fileName = new char[fname.size() + 1];
		fileName[fname.size()] = 0;
	memcpy(fileName, fname.c_str(), fname.size());
    newVM.LoadingVMimage(fileName);
	*/

	newVM.LoadingVMimage("task1.bin");
	newVM.InstructionExcution();
	system("pause");
}