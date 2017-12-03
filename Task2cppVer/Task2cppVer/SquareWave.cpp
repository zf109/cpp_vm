#include "SquareWave.h"
#include<string>

SquareWave::SquareWave()
{
	startLocation.x = 10;
	startLocation.y = 10;
	size = 10;
	orientation = 0;
}

SquareWave::SquareWave(int x, int y, int ort, int s)
{
	startLocation.x = x;
	startLocation.y = y;
	size = s;
	orientation = ort;
}

SquareWave::~SquareWave()
{
}


int SquareWave::DrawSquareWave()
{

	vector2 midLocation;
	swCursor.SVGgoto(startLocation.x, startLocation.y);					//go to the location

	switch (orientation)
	{
	case(0) :	//normal
		swCursor.SVGdraw(startLocation.x, startLocation.y - size);			//go up
		swCursor.SVGdraw(startLocation.x + size, startLocation.y - size);	//go right
		swCursor.SVGdraw(startLocation.x + size, startLocation.y);			//go down
		swCursor.SVGdraw(startLocation.x + 2 * size, startLocation.y);		//go right

		midLocation.x = startLocation.x + 2 * size;
		midLocation.y = startLocation.y;

		swCursor.SVGdraw(midLocation.x, midLocation.y - size);			//go up
		swCursor.SVGdraw(midLocation.x + size, midLocation.y - size);	//go right
		swCursor.SVGdraw(midLocation.x + size, midLocation.y);			//go down
		swCursor.SVGdraw(midLocation.x + 2 * size, midLocation.y);		//go right

		break;

	case(1) : //flip left-right
		swCursor.SVGdraw(startLocation.x + size, startLocation.y - size);	//go right
		swCursor.SVGdraw(startLocation.x, startLocation.y - size);			//go up
		swCursor.SVGdraw(startLocation.x + 2 * size, startLocation.y);		//go right
		swCursor.SVGdraw(startLocation.x + size, startLocation.y);			//go down

		midLocation.x = startLocation.x + 2 * size;
		midLocation.y = startLocation.y;

		swCursor.SVGdraw(midLocation.x + size, midLocation.y - size);	//go right
		swCursor.SVGdraw(midLocation.x, midLocation.y - size);			//go up
		swCursor.SVGdraw(midLocation.x + 2 * size, midLocation.y);		//go right
		swCursor.SVGdraw(midLocation.x + size, midLocation.y);			//go down

		break;

	case(2) :
		break;
	default:
		break;

	}

	endLocation = swCursor.GetPosition();
	endSlength = swCursor.GetStepLength();
	trace = swCursor.GetTrace();
	return 0;
}

vector2 SquareWave::GetEndLocation()
{
	return endLocation;
}
vector2 SquareWave::GetEndSlength()
{
	return endSlength;
}

string SquareWave::GetTrace()
{
	return trace;
}