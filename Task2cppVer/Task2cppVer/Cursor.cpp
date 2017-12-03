#include "Cursor.h"
#include<math.h>
#include<iostream>

Cursor::Cursor()
{
	//initial position
	position.x = 0;
	position.y = 0;

	//initial step length
	stepLength.x = 10;
	stepLength.y = 10;

	//initial trace
	trace = "";
}

Cursor::Cursor(vector2 initPos, vector2 initSLen)
{
	position.x = initPos.x;
	position.y = initPos.y;

	//initial step length
	stepLength.x = initSLen.x;
	stepLength.y = initSLen.y;

	//initial trace
	trace = "";
}

Cursor::~Cursor()
{
}


/*the following three functions are needed to calculate the minimum		*/
/* number of operations to achieve the cursor translation				*/
/*Assume distance is s, current step length is d, we need to increment	*/
/*the step length by x, then perform y step increment then further		*/
/*increase/decrease the step length by z, and perform one more step.	*/
/*That is to say we need to satisfy the following equation:				*/	
/*																		*/
/*						s = y(d+x)+z+(d+x)								*/	
/*																		*/
/*Our objective is to minimize the total number of operations:			*/
/*																		*/
/*abs(x): the number of operations to increase/decrease the step length */
/*	   y: the number of steps taken										*/
/*abs(z): the number of operations to increas/decrease the last step	*/
/*																		*/
/*we also need to add 1 for the last step, the optimization problem		*/
/* becomes																*/
/*																		*/
/*					min abs(x) + y + abs(z)+1							*/
/*					s.t. s = y(d+x)+z+(d+x)								*/
/*																		*/
/*We can find that y, and z are functions of x, therefore we endup with */
/*a univariate (nonsmooth) optimization problem and can be solved by	*/
/*exauhstive search resonably with about 100 points						*/					

int CostFunction(int x, int s, int d)
{
	/*this function returns the cost function of our optimization problem*/
	if ((d + x) <= 0)	//if the new step length is not valid
		return 100000;	//return a random large number as panelty

	int z;				//initialize z: the last step size adjustment
	int y;				//initialize y: number of steps take
	if ((s % (d + x)) < (d + x) / 2)
		z = -s % (d + x);
	else
		z = (d + x) - s % (d + x);
	y = (s + z) / (d + x);

	return abs(x) + y + abs(z);
};
int IndexofSmallestElement(int *xarray, int size)
{
	/*the function perform exauhstive search*/
	int index = 0;
	int min = xarray[0];
	for (int i = 1; i < size; ++i)
	{
		if (xarray[i] < min)
		{
			min = xarray[i];
			index = i;
		}
	}
	return index;
};
int * OptimalNumbers(int s, int d)
{
	/*the function takes the distance and current step length*/
	/* and returns the optimal x, y, z*/
	int xmin = -50;
	int xarray[100];
	int yarray[100];
	static int narray[3];
	for (int i = 0; i < 100; i++)
	{
		xarray[i] = xmin + i;
		yarray[i] = CostFunction(xarray[i], s, d);
	}
	int iOpt = IndexofSmallestElement(yarray, 100);

	int xOpt = xarray[iOpt];
	int zOpt;
	int yOpt;
	if ((s % (d + xOpt)) < (d + xOpt) / 2)
		zOpt = -s % (d + xOpt);
	else
		zOpt = (d + xOpt) - s % (d + xOpt);
	yOpt = (s + zOpt) / (d + xOpt);

	narray[0] = xOpt;
	narray[1] = yOpt;
	narray[2] = zOpt;
	return narray;
};

vector2* GetNumOperations(int dx, int dy, vector2 sLen)
{
	static vector2 numOperations[3];
	int numIncreaseInNorm;	//number of increase of step size

	//get the norm of the step length
	double normStepLength = sqrt((double)(pow(sLen.x, 2) + pow(sLen.y, 2)));

	//get the norm of the distance
	double normD = sqrt((double)(pow(dx, 2) + pow(dy, 2)));

	int *nums = OptimalNumbers(normD,normStepLength);
	int numStepAdjustInNorm = nums[0];		//the x
	int numStepTaken = nums[1];				//the y
	int numLastStepAdjustInNorm = nums[2];	//the z


	//get the angle between y and x coordinate
	double angle = atan2((double)dy, (double)dx);	//angle in rad;


	//the optimal (approximately) number of of operations
	numOperations[0].x = (int)(numStepAdjustInNorm * cos(angle));	//the step adjustment in x direction
	numOperations[0].y = (int)(numStepAdjustInNorm * sin(angle));	//the step adjustment in y direction

	//the number of step length increase should be the same for x and y direction
	numOperations[1].x = numStepTaken;	//the number of steps in x direction
	numOperations[1].y = numStepTaken;	//the number of steps in y direction

	numOperations[2].x = (int)(numLastStepAdjustInNorm * cos(angle));	//the last step adjustment in x direction
	numOperations[2].y = (int)(numLastStepAdjustInNorm * sin(angle));	//the last step adjustment in y direction

	return numOperations;
}

//sub-optimal way to get number of operations
//first take y steps, then shrink the stepby z and take the last step if necessary
vector2* GetNumOperationsSubOptimal(int dx, int dy, vector2 sLen)
{
	static vector2 numOperations[3];
	int numStepTaken;
	int numLastStepAdjustX;
	int numLastStepAdjustY;

	if (dx != 0 & dy != 0)	//if not right, left, up or down
	{
		//get the norm of the step length
		double normStepLength = sqrt((double)(pow(sLen.x, 2) + pow(sLen.y, 2)));

		//get the norm of the distance
		double normD = sqrt((double)(pow(dx, 2) + pow(dy, 2)));

		//int numStepTaken = (int)(normD - remainder(normD,normStepLength)) / normStepLength;
		double dummy = (normD - floor(normD / normStepLength)*normStepLength);
		numStepTaken = (normD - dummy) / normStepLength;
		//int numStepTaken = (int)(normD - (normD - floor(normD/normStepLength)*normStepLength)) / normStepLength;
		if (numStepTaken != 0)
		{
			numLastStepAdjustX = abs(dx) - numStepTaken*sLen.x;
			numLastStepAdjustY = abs(dy) - numStepTaken*sLen.y;
		}
		else
		{
			numLastStepAdjustX = abs(dx) - sLen.x;
			numLastStepAdjustY = abs(dy) - sLen.y;
		}
	}
	else if (dx != 0 & dy == 0)	//if left or right
	{
		int dummy = (abs(dx) - floor(abs(dx) / sLen.x)*sLen.x);
			numStepTaken = (abs(dx) - dummy) / sLen.x;

			numLastStepAdjustY = 0;
			if (numStepTaken != 0)
				numLastStepAdjustX = numStepTaken*sLen.x - abs(dx);
			else
				numLastStepAdjustX = sLen.x - abs(dx);
	}
	else if (dx == 0 & dy != 0)	//if up or down
	{
		int dummy = (abs(dy) - floor(abs(dy) / sLen.y)*sLen.y);
		numStepTaken = (abs(dy) - dummy) / sLen.y;

		numLastStepAdjustX = 0;
		if (numStepTaken != 0)
			numLastStepAdjustY = numStepTaken*sLen.y - abs(dy);
		else
			numLastStepAdjustX = sLen.y - abs(dy);
	}
	else	//if not move
	{
		numStepTaken = 0;
		numLastStepAdjustX = 0;
		numLastStepAdjustY = 0;
	}

	//the optimal (approximately) number of of operations
	numOperations[0].x = 0;	//the step adjustment in x direction
	numOperations[0].y = 0;	//the step adjustment in y direction

	//the number of step length increase should be the same for x and y direction
	numOperations[1].x = numStepTaken;	//the number of steps in x direction
	numOperations[1].y = numStepTaken;	//the number of steps in y direction

	numOperations[2].x = numLastStepAdjustX;	//the last step adjustment in x direction
	numOperations[2].y = numLastStepAdjustY;	//the last step adjustment in y direction

	return numOperations;
}

string GetDirection(int dx, int dy)
{
	string direction;

	//right left up and down
	if (dx > 0 & dy == 0)
		direction = "R";
	if (dx < 0 & dy == 0)
		direction = "L";
	if (dx == 0 & dy > 0)
		direction = "U";
	if (dx == 0 & dy < 0)
		direction = "D";

	//right-up right-down left-up and left-down
	if (dx > 0 & dy > 0)
		direction = "A";
	if (dx < 0 & dy < 0)
		direction = "E";
	if (dx < 0 & dy > 0)
		direction = "B";
	if (dx < 0 & dy < 0)
		direction = "C";

	//if not move
	if (dx == 0 & dy == 0)
		direction = "";

	return direction;
}

string *GetAdjustment(vector2 *numOperations)
{
	static string adjustment[4];

	//step adjustment in x direction
	if (numOperations[0].x > 0)
		adjustment[0] = "K";
	if (numOperations[0].x < 0)
		adjustment[0] = "J";
	if (numOperations[0].x == 0)
		adjustment[0] = "";
	//step adjustment in y direction
	if (numOperations[0].y > 0)
		adjustment[1] = "N";
	if (numOperations[0].y < 0)
		adjustment[1] = "M";
	if (numOperations[0].y == 0)
		adjustment[1] = "";
	//last step adjustment in x direction
	if (numOperations[2].x > 0)
		adjustment[2] = "K";
	if (numOperations[2].x < 0)
		adjustment[2] = "J";
	if (numOperations[2].x == 0)
		adjustment[2] = "";
	//step adjustment in y direction
	if (numOperations[2].y > 0)
		adjustment[3] = "N";
	if (numOperations[2].y < 0)
		adjustment[3] = "M";
	if (numOperations[2].y == 0)
		adjustment[3] = "";

	return adjustment;
}

string TranslateToSVGcommand(int dx, int dy, vector2 *numOperations)
{
	string record = "";
	string direction = GetDirection(dx, dy);
	string *adjustment = GetAdjustment(numOperations);

	int numStepTaken = numOperations[1].x;

	string stepLengthAdjustmentX = adjustment[0];
	string stepLengthAdjustmentY = adjustment[1];

	int numStepLengthAdjustmentX = abs(numOperations[0].x);
	int numStepLengthAdjustmentY = abs(numOperations[0].y);

	string lastStepLengthAdjustmentX = adjustment[2];
	string lastStepLengthAdjustmentY = adjustment[3];

	int numLastStepLengthAdjustmentX = abs(numOperations[2].x);
	int numLastStepLengthAdjustmentY = abs(numOperations[2].y);

	//adjust step length in x direction
	for (int i = 0; i < numStepLengthAdjustmentX; i++)
		record = record + stepLengthAdjustmentX;
	//adjust step length in y direction
	for (int i = 0; i < numStepLengthAdjustmentY; i++)
		record = record + stepLengthAdjustmentY;

	//take 'numStepTaken' number of steps
	for (int i = 0; i < numStepTaken; i++)
		record = record + direction;

	if (numLastStepLengthAdjustmentX != 0 | numLastStepLengthAdjustmentY != 0)
	{
		//adjust last step length in x direction
		for (int i = 0; i < numLastStepLengthAdjustmentX; i++)
			record = record + lastStepLengthAdjustmentX;
		//adjust last step length in y direction
		for (int i = 0; i < numLastStepLengthAdjustmentY; i++)
			record = record + lastStepLengthAdjustmentY;
		//take the last step
		record = record + direction;
	}
	return record;
}

string Cursor::ResetStepLengthX()
{
	string record;
	int numReset = 10 - stepLength.x;

	if (numReset > 0)
		for (int i = 0; i < numReset; i++)
			record = record + "K";
	else
		for (int i = 0; i < abs(numReset); i++)
			record = record + "J";

	stepLength.x = 10;
	return record;
}

string Cursor::ResetStepLengthY()
{
	string record;
	int numReset = 10 - stepLength.y;

	if (numReset > 0)
		for (int i = 0; i < numReset; i++)
			record = record + "N";
	else
		for (int i = 0; i < abs(numReset); i++)
			record = record + "M";

	stepLength.y = 10;
	return record;
}

int Cursor::SVGdraw( int x2, int y2)
{
	int dx = x2 - position.x;
	int dy = y2 - position.y;

	//vector2 *numOperations = GetNumOperations(dx, dy, stepLength);
	vector2 *numOperations = GetNumOperationsSubOptimal(dx, dy, stepLength);
	trace = trace + TranslateToSVGcommand(dx, dy, numOperations);

	//update step length
	stepLength.x = stepLength.x + numOperations[0].x + numOperations[2].x;
	stepLength.y = stepLength.y + numOperations[0].y + numOperations[2].y;

	//if step length gets too small, reset the step length
	if (stepLength.x < 5)
		trace = trace + ResetStepLengthX();
	if (stepLength.y < 5)
		trace = trace + ResetStepLengthY();

	// update position
	position.x = x2;
	position.y = y2;
	return 0;
}

int Cursor::SVGgoto(int x2, int y2)
{
	int dx = x2 - position.x;
	int dy = y2 - position.y;

	trace = "P";
	vector2 *numOperations = GetNumOperationsSubOptimal(dx, dy, stepLength);
	trace = trace + TranslateToSVGcommand(dx, dy,numOperations);
	trace = trace + "P";

	//update step length
	stepLength.x = stepLength.x + numOperations[0].x + numOperations[2].x;
	stepLength.y = stepLength.y + numOperations[0].y + numOperations[2].y;
	//update position
	position.x = x2;
	position.y = y2;
	return 0;
}

int Cursor::SetPosition(vector2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	return 0;
}
int Cursor::SetStepLength(vector2 slen)
{
	stepLength.x = slen.x;
	stepLength.y = slen.y;
	return 0;
}

string Cursor::GetTrace()
{
	return trace;
}

vector2 Cursor::GetPosition()
{
	return position;
}

vector2 Cursor::GetStepLength()
{
	return stepLength;
}

int Cursor::DisplayCurrentStat()
{
	cout << "current position: (" << position.x << "," \
		<< position.y << ")" << endl;
	cout << "current step length: (" << stepLength.x << ","\
		<< stepLength.y << ")" << endl;
	return 0;
}
