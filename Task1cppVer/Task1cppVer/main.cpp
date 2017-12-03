#include<iostream>
#include<stdio.h>
#include "VirtualMachine.h"
#include <fstream>
#include<string>
using namespace std;

void main()
{
	VirtualMachine newVM;

	newVM.LoadingVMimage("task2.bin");
	newVM.inputFromString = true;
	newVM.SetInputString("RULDX");
	newVM.SetOutputFile("thepic.svg");
	newVM.InstructionExcution();
	system("pause");
}