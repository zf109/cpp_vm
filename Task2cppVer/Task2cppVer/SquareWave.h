#pragma once
#include "vector2.h"
#include "Cursor.h"

#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H
class SquareWave
{
public:
	SquareWave();
	//overload constructor
	SquareWave(int x, int y, int ort, int s);

	~SquareWave();

	Cursor swCursor;		//the cursor for drawing
	int DrawSquareWave();	//draw the square wave
	vector2 GetEndLocation();	//get the end location
	vector2 GetEndSlength();	//get the end step length
	string GetTrace();		//get the trace

private:
	int size;			//size of the square wave
	int orientation;	//orientation of the square wave
						//0: normal
						//1: flip left-right
						//2: flip up-down
						//4: normal rotate 90 degree
						//5: flip up-down rotate 90 degree

	vector2 startLocation;		//start location of the cursor
	vector2 endLocation;		//end location of the cursor
	vector2 startSlength;		//start step length of the cursor
	vector2 endSlength;			//end step slength of the curosr

	string trace;		//the trace of the square wave
};

#endif