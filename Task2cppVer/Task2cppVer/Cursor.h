#pragma once
#include<string>
#include"vector2.h"

#ifndef CURSOR_H
#define CURSOR_H
using namespace std;
class Cursor
{
public:
	Cursor();
	//overload constructor
	Cursor(vector2 initPos, vector2 initSLen);
	~Cursor();


	// go from position 1 to position 2 without draw anyting
	int SVGgoto(int x2, int y2);

	//draw a black line from position 1 to position 2;
	int SVGdraw(int x2, int y2);
	
	//display info
	int DisplayCurrentStat();

	int SetPosition(vector2 pos);		//set position
	int SetStepLength(vector2 slen);	//set step length
	//getters
	vector2 GetPosition();		//access position
	vector2 GetStepLength();	//access step length
	string GetTrace();			//access trace

private:

	vector2 position;		//the current position of the cursor
	vector2 stepLength;		//the current step length of the cursor
	string trace;			//the trace left by the cursor

	string ResetStepLengthX();
	string ResetStepLengthY();
};

#endif
