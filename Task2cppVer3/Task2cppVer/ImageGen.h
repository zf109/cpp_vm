#pragma once
#include<iostream>
#include<stdio.h>
#include <fstream>


#ifndef IMAGEGEN_H
#define IMAGEGEN_H
class ImageGen
{
public:
	ImageGen();
	~ImageGen();
	int OutputCommand();
	int CommandGen();
	std::string myCommand;

private:
	int DrawVerticalLine(int unitSize, bool up, bool down);
	int DrawHorizontalLine(int unitSize, bool left, bool right);
	int BasicUnit(std::string uname);			//basic unit, in our case it is the square wave with size 10, with different orientation
	int VariableUnit(int size);					//the basic unit with variable size
	int GoToPosition(int x1, int y1, int x2, int y2);
	std::ofstream outputFile;			//the output file record the command for generating the svg picture
};

#endif