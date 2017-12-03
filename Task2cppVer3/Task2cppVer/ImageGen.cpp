#include "ImageGen.h"
#include<math.h>
#include<stdio.h>
#include <fstream>
#include<iostream>
#include <string>
#include <sstream>
using namespace std;

ImageGen::ImageGen()
{
	string myCommand = "";
}

ImageGen::~ImageGen()
{
}


int ImageGen::GoToPosition(int x1, int y1,int x2,int y2)
{
	/*function that move to the position x2y2 from x1y1*/
	int xdif = x2 - x1;          //get the coordinate difference in x axis
	int ydif = y2 - y1;          //get the coordinate difference in y axis
	string gotoCommand;          //string to save the command
	string gotox;                //command for go to x2
	string gotoy;                //command for go to y2
	string goRight = "R";        //default command for direction moves
	string goLeft = "L";
	string goUp = "U";
	string goDown = "D";

	if (xdif > 0)                            //if right direction(use R)
	{
		int tendigitx = (int)xdif / 10;      //get the integer of how many times of move needed
		for (int i = tendigitx; i>0; i--)
		{
			gotox += goRight;                //add one move to command each
		}
	}
	else if (xdif < 0)                       //if left directions(use L)
	{
		int tendigitx = abs((int)xdif / 10); //get the integer of how many times of move needed
		for (int i = tendigitx; i>0; i--)    
		{
			gotox += goLeft;                 //add one move to command each
		}
	}
	else                                     //if no coordinate change no move
	{
		gotox = "";
	}

	if (ydif > 0)                           //if down directions(use U)       
	{
		int tendigity = (int)ydif / 10;
		for (int i = tendigity; i > 0; i--) //get the integer of how many times of move needed
		{
			gotoy += goUp;                  //add one move to command each iteartion
		}
	}
	else if (ydif < 0)                      //if up directions(use D)
	{
		int tendigity = abs((int)ydif / 10);
		for (int i = tendigity; i>0; i--)      //get the integer of how many times of move needed
		{
			gotoy += goDown;                   //add one move to command each
		}
	}
	else                       //if no coordinate change no move
	{
		gotoy = "";            
	}
	gotoCommand += "P";        //use P to disable the lines
	gotoCommand += gotox;      //go to the x2y2 position
	gotoCommand += gotoy;
	gotoCommand += "P";        //use P to disable the lines
	myCommand += gotoCommand;   //add to command
	return 0;
}


int ImageGen::BasicUnit(string unitName)
{
	/*function for draw basic unit (square wave with size 10)*/
	string unitCommand;
	// 6 kind of the sqaure wave units for different directions
	if (unitName == "rulu")          // top left unit(vertical 1)
		unitCommand = "RULURULU";     
	if (unitName == "dldr")          // top right unit(vertical 2)
		unitCommand = "DLDRDLDR";
	if (unitName == "drur")          // circle top left unit(horizontal 1)
		unitCommand = "DRURDRUR";
	if (unitName == "rdru")          // circle top right unit(horizontal 2)
		unitCommand = "RDRURDRU";
	if (unitName == "luld")          // circle buttom left unit(horizontal 3)
		unitCommand = "LULDLULD";
	if (unitName == "uldl")          // circle buttom right unit(horizontal 4)
		unitCommand = "ULDLULDL";

	myCommand += unitCommand;          //add to command 
	return 0;
}
int ImageGen::DrawVerticalLine(int unitSize, bool up, bool down)
{
	string intvar = "";				//string to hold the cmommand
	string verSizePlus = "N";       //vertical step size increase
	string verSizeMinus = "M";		//vertical step size decerase
	string goUp = "U";
	string goDown = "D";
	if (unitSize % 10 == 0)                   //if the size step can divided by 10
	{
		int tendigi = (int)unitSize / 10;     //get the integer of how many times of move needed
		for (int i = tendigi; i > 0; i--)
		{
			if (down)
			{
				intvar += goDown;
			}
			if (up)
			{
				intvar += goUp;
			}
		}
	}
	else                                      //if cannot be divided by 10
	{
		int intSize = (int)unitSize;
		if (intSize > 10)                     //if greater than 10
		{
			int tendigi = (int)unitSize / 10;  //draw the first part of the line and use 10 as step size
			for (int i = tendigi; i > 0; i--)
			{
				if (down)
				{
					intvar += goDown;
				}
				if (up)
				{
					intvar += goUp;
				}
			}//draw the remaining part and change the step size
			for (int i = (10 - (intSize - 10 * tendigi)); i > 0; i--)
			{
				intvar += verSizeMinus;
			}
			if (down)      //set the direction for
			{
				intvar += goDown;
			}
			if (up)
			{
				intvar += goUp;
			}

			for (int i = (10 - (intSize - 10 * tendigi)); i > 0; i--)
			{
				intvar += verSizePlus;         //reset the step size to 10
			}
		}
		else
		{
			for (int i = intSize; i > 0; i--)   //if size is smaller than 10
			{
				intvar += verSizeMinus;         //change the step size
			}
			if (down)                      //set direction
			{
				intvar += goDown;
			}
			if (up)
			{
				intvar += goUp;
			}
			for (int i = intSize; i > 0; i--)
			{
				intvar += verSizePlus;          //reset the step size to 10 
			}
		}
	}
		myCommand += intvar;      //add to command 
		return 0;
	}


int ImageGen::DrawHorizontalLine(int unitSize, bool left, bool right)
{
	string intvar = "";				//string to hold the cmommand
	string horSizePlus = "K";		//horizontal step size increase 
	string horSizeMinus = "J";		//horizontal step size decrease
	string goRight = "R";
	string goLeft = "L";
	if (unitSize % 10 == 0)                   //if the size step can divided by 10
	{
		int tendigi = (int)unitSize / 10;     //get the integer of how many times of move needed
		for (int i = tendigi; i > 0; i--)
		{
			if (left)
			{
				intvar += goLeft;
			}
			if (right)
			{
				intvar += goRight;
			}
		}
	}
	else                                      //if cannot be divided by 10
	{
		int intSize = (int)unitSize;
		if (intSize > 10)                     //if greater than 10
		{
			int tendigi = (int)unitSize / 10;  //draw the first part of the line and use 10 as step size
			for (int i = tendigi; i > 0; i--)
			{
				if (left)
				{
					intvar += goLeft;
				}
				if (right)
				{
					intvar += goRight;
				}
			}//draw the remaining part and change the step size
			for (int i = (10 - (intSize - 10 * tendigi)); i > 0; i--)
			{
				intvar += horSizeMinus;
			}
			if (left)
			{
				intvar += goLeft;
			}
			if (right)
			{
				intvar += goRight;
			}

			for (int i = (10 - (intSize - 10 * tendigi)); i > 0; i--)
			{
				intvar += horSizePlus;         //reset the step size to 10
			}
		}
		else
		{
			for (int i = intSize; i > 0; i--)   //if size is smaller than 10
			{
				intvar += horSizeMinus;         //change the step size
			}
			if (left)
			{
				intvar += goLeft;
			}
			if (right)
			{
				intvar += goRight;
			}
			for (int i = intSize; i > 0; i--)
			{
				intvar += horSizePlus;          //reset the step size to 10 
			}
		}
	}
		myCommand += intvar;      //add to command 
		return 0;
}

int ImageGen::VariableUnit(int unitSize)
{
	/*function for variable size unit*/
	string intvar = "";				//string to hold the cmommand

	//draw the variable size unit line by line	
	for (int m = 0; m<2; m++)
	{
		DrawVerticalLine(unitSize,0,1);       //draw the down direction vertical line
		DrawHorizontalLine(unitSize, 0, 1);   //draw the right direction vertical line
		DrawVerticalLine(unitSize, 1, 0);       //draw the up direction vertical line
		DrawHorizontalLine(unitSize, 0, 1);   //draw the right direction vertical line
	}           
	myCommand += intvar;      //add to command 
	return 0;
}

//function for generate the command by the givin coordinate
int ImageGen::CommandGen()
{
	//draw the first unit on top left
	BasicUnit("rulu");
	//go to next position, draw the second unit on buttom left
    GoToPosition(0,40,0,360);
	BasicUnit("rulu");
	//go to next position, draw the 3rd unit on buttom right
	GoToPosition(0,400, 400,400);
	BasicUnit("dldr");
	//go to next position, draw the 3rd unit on buttom right
	GoToPosition(400, 360, 400, 40);
	BasicUnit("dldr");

	//draw the units in the middle circle
	GoToPosition(400,0,180,40);
	BasicUnit("drur");
	//draw the top left of circle
	GoToPosition(220, 40, 260, 70); 
	BasicUnit("rdru");
	GoToPosition(300, 70, 310, 140); 
	BasicUnit("rdru");
	GoToPosition(350, 140, 330, 200);
	BasicUnit("rdru");
	//draw the buttom left of circle
	GoToPosition(370, 200, 350, 260);
	BasicUnit("uldl");
	GoToPosition(310, 260, 300, 330); 
	BasicUnit("uldl");
	//draw the buttom right of circle
	GoToPosition(260, 330, 220, 360); 
	BasicUnit("luld");
	GoToPosition(180, 360, 140, 330); 
	BasicUnit("luld");
	GoToPosition(100, 330, 90, 260); 
	BasicUnit("luld");
	//draw the top right of circle
	GoToPosition(50, 260, 30, 200);
	BasicUnit("drur");
	GoToPosition(70, 200, 50, 140);
	BasicUnit("drur");
	GoToPosition(90, 140, 100, 70);
	BasicUnit("drur");

	//draw the middle variable units
	GoToPosition(140, 70, 130, 170); 
	VariableUnit(40);
	GoToPosition(290, 170, 150, 220);
	VariableUnit(30);
	GoToPosition(270, 220, 160, 260);
	VariableUnit(20);
	GoToPosition(250, 250, 180, 280);
	VariableUnit(10);
	GoToPosition(240, 280, 210, 300);
	VariableUnit(5);

	myCommand += "X";               //use X to stop the command       
	return 0;
}
//function for execute the command and generate the svg file
int ImageGen::OutputCommand()
{
	outputFile.open("result.txt");
	outputFile << myCommand;                //output the commands to the text file
	outputFile.close();
	return 0;
}
