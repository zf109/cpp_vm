#include "VirtualMachine.h"
#include "ImageGen.h"

#include<iostream>
#include<stdio.h>
#include <fstream>
#include<string>
using namespace std;

void main()
{
	VirtualMachine newVM;
	ImageGen newIG;

	newVM.inputFromString = true;               //if ture, console read the input from input string(the generated commands)
	                                         //if false, console read the string stream 

	newVM.LoadingVMimage("task2.bin");       //read binary file
	newIG.CommandGen();                      //generate the commands
	newIG.OutputCommand();                   //output the commands to text file
	newVM.SetInputString(newIG.myCommand);   //save the commands to the input string
	newVM.SetOutputFile("outputImage.svg");  //set the output svg file
	newVM.InstructionExcution();             //excute the binary file
	system("pause");   
}