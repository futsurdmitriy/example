// AI_Maze_Runner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>


using namespace std;
int iterations;
const int Wall ='#';
const int Free =' ';
const char AI = '*';

int startPosX;
int startPosY;
int EndPosX;
int EndPosY;
//SizeMaze1[31][32]; SizeMaze2 [20][40]; SizeMaze3 [22][69]
const int mazeHight = 22;
const int mazeWidth = 69;
fstream Mazefile("maze3.txt");
FILE *mazeSize = fopen ("maze3size.txt","rt");
char mazeArray[mazeHight][mazeWidth];


void readFrom() {

	//fscanf(mazeSize,"%d %d %d %d %d %d", &mazeHight, &mazeWidth, &startPosX, &startPosY, &EndPosX, &EndPosY);
	fscanf(mazeSize, "%d %d %d %d", &startPosX, &startPosY, &EndPosX, &EndPosY);
	for (int i = 0; i < mazeHight; i++)
	{
		for (int j = 0; j < mazeWidth; j++)
		{
			Mazefile.get(mazeArray[i][j]);
		}
	}
	
}

class COORD
{
public:
	int X, Y;
	COORD(int x = 0, int y = 0) {
		X = x; Y = y;
	}
	COORD(const COORD &coord) {
		X = coord.X; Y = coord.Y;
	}
};



void printMaze() {
	cout << endl;
	for (int i = 0; i<mazeHight; i++)
	{
		for (int j = 0; j<mazeWidth; j++)
		{			
			cout << mazeArray[i][j];
		}
	}
	iterations++;
	cout << endl;
}

bool AIMovement(int X,int Y) {

	COORD StartingPoint(startPosX, startPosY);
	COORD EndingPoint(EndPosX, EndPosY);

	double time;
	mazeArray[Y][X] = AI;	
	printMaze();
	//If you want to see step by step solution 
	//please uncomment that.

	//_getch();	

	if (X == EndingPoint.X && Y == EndingPoint.Y)	{
		time = clock() / 1000.0;
		cout << endl;
		cout << "***************Congrats!!!*****************" << endl;;
		cout << "AI done " << iterations << " steps for "<<time<<" seconds." << endl;
		return true;
	}

	if (X > 0 && mazeArray[Y][X - 1] == Free && AIMovement(X - 1, Y))	{
		return true;
	}

	if (X < mazeWidth && mazeArray[Y][X + 1] == Free && AIMovement(X + 1, Y)) {
		return true;
	}

	if (Y > 0 && mazeArray[Y - 1][X] == Free && AIMovement(X, Y - 1)) {
		return true;
	}

	if (Y < mazeHight && mazeArray[Y + 1][X] == Free && AIMovement(X, Y + 1)) {
		return true;
	}

	mazeArray[Y][X] = Free;

	//If you want to see step by step solution 
	//please uncomment that.
	
	//printMaze();
	//_getch();
	
	return false;
}

int main()	{

	readFrom();

	COORD StartingPoint(startPosX, startPosY);
	COORD EndingPoint(EndPosX, EndPosY);

	if (AIMovement(StartingPoint.X, StartingPoint.Y))	{
		

		_getch();
	}
	else	{
		printf("Something went wrong :( \n");
	}

	return 0;
}

