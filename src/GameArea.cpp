/*
 -------------------------------------------------------
 Author: Tom LaMantia
 Id: 110283790
 Email: lama3790@mylaurier.ca
 Version: December 1, 2014
 -------------------------------------------------------
 */

/*
   -------------------------------------------------------
    This file contains implementation for the GameArea class,
    which is defined in GameArea.hpp
    -------------------------------------------------------
 */

#include"GameArea.hpp"

GameArea :: GameArea()
{
	//game area constructed
}

void GameArea :: reset()
{
	GLint row, col;
	for(row = 0; row < 3; row++)
	{
		for(col = 0; col < 3; col++)
		{
			this->gameAreaMatrix[row][col].resetShape();
			this->gameAreaMatrix[row][col].colorCode = -1;
		}
	}
}

bool GameArea :: checkGameAreaFull(){

	bool result = true;
	GLint row, col;

	for(row = 0; row < 3; row++){

		for(col = 0; col < 3; col++){

			if(this->gameAreaMatrix[row][col].colorCode == -1){
				result = false;
			}
		}
	}

	return result;
}

void GameArea :: draw()
{
	//Draw the game area itself
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
		glVertex3f(-1,-3.5,-.8);
		glVertex3f(1,-3.5,-.8);
		glVertex3f(1,-3.5,-1.5);
		glVertex3f(-1,-3.5,-1.5);
	glEnd();

	GLint row, col;
	GLfloat translateFactorX;
	GLfloat translateFactorY = -2.5;

	for(row = 0; row < 3; row++)
	{
		translateFactorX = -0.6;

		for(col = 0; col < 3; col++)
		{
			this->gameAreaMatrix[2 - row][col].translate(translateFactorX,0,0);
			this->gameAreaMatrix[2 - row][col].translate(0,translateFactorY,0);
			this->gameAreaMatrix[2 - row][col].draw();
			this->gameAreaMatrix[2 - row][col].resetShape();
			translateFactorX += 0.6;
		}

		translateFactorY += 0.4;
	}
}

/*
 * Testing method - not part of calling program
 */
void GameArea :: printGameAreaTest()
{
	int row, col;

	for(row = 0; row < 3; row++)
	{
		for(col = 0; col < 3; col++)
		{
			cout << this->gameAreaMatrix[row][col].colorCode << " ";
 		}

		cout << endl;
	}

	cout << endl;
}

GLint GameArea :: checkRightDiagonalKlax(){

	GLint result = -1;


	if (this->gameAreaMatrix[0][2].colorCode == this->gameAreaMatrix[1][1].colorCode &&
			this->gameAreaMatrix[1][1].colorCode == this->gameAreaMatrix[2][0].colorCode
			&& this->gameAreaMatrix[0][2].colorCode != -1) {
		result = 0;
	}

	return result;
}

GLint GameArea :: checkLeftDiagonalKlax()
{
	GLint result = -1;

	if (this->gameAreaMatrix[0][0].colorCode == this->gameAreaMatrix[1][1].colorCode &&
			this->gameAreaMatrix[1][1].colorCode == this->gameAreaMatrix[2][2].colorCode
			&& this->gameAreaMatrix[0][0].colorCode != -1) {
		result = 0;
	}

	return result;
}

GLint GameArea :: checkHorizontalKlax()
{
	GLint row = 0;
	GLint result = -1;
	bool foundKlax = false;

	while(row < 3 && foundKlax == false){
		if (this->gameAreaMatrix[row][0].colorCode == this->gameAreaMatrix[row][1].colorCode &&
				this->gameAreaMatrix[row][1].colorCode == this->gameAreaMatrix[row][2].colorCode
				&& this->gameAreaMatrix[row][0].colorCode != -1)
		{
			foundKlax = true;
			result = row;
		}

		row++;
	}

	return result;
}

GLint GameArea :: checkVerticalKlax()
{
	GLint col = 0;
	GLint result = -1;
	bool foundKlax = false;

	while(col < 3 && foundKlax == false){
		if (this->gameAreaMatrix[0][col].colorCode == this->gameAreaMatrix[1][col].colorCode &&
				this->gameAreaMatrix[1][col].colorCode == this->gameAreaMatrix[2][col].colorCode
				&& this->gameAreaMatrix[0][col].colorCode != -1)
		{
			foundKlax = true;
			result = col;
		}

		col++;
	}

	return result;
}

bool GameArea :: insertNewBlock(GLint colNumber, GLint newColor)
{
	bool blockInserted = false;
	GLint i = 2;

	if(this->gameAreaMatrix[0][colNumber].colorCode == -1)
	{
		while(i >= 0 && blockInserted == false)
		{
			if(this->gameAreaMatrix[i][colNumber].colorCode == -1)
			{
				this->gameAreaMatrix[i][colNumber].colorCode = newColor; //ie put the shape in!
				blockInserted = true;
			}
			i--;
		}
	}

	return blockInserted;
}

void GameArea :: breakDownRightDiagonalKlax(){

	this->gameAreaMatrix[0][2].colorCode = -1;

	this->gameAreaMatrix[1][1] = this->gameAreaMatrix[0][1];
	this->gameAreaMatrix[0][1].colorCode = -1;

	this->gameAreaMatrix[2][0] = this->gameAreaMatrix[1][0];
	this->gameAreaMatrix[1][0] = this->gameAreaMatrix[0][0];
	this->gameAreaMatrix[0][0].colorCode = -1;
}

void GameArea :: breakDownLeftDiagonalKlax()
{
	this->gameAreaMatrix[0][0].colorCode = -1;

	this->gameAreaMatrix[1][1] = this->gameAreaMatrix[0][1];
	this->gameAreaMatrix[0][1].colorCode = -1;

	this->gameAreaMatrix[2][2] = this->gameAreaMatrix[1][2];
	this->gameAreaMatrix[1][2] = this->gameAreaMatrix[0][2];
	this->gameAreaMatrix[0][2].colorCode = -1;
}

void GameArea :: breakDownHorizontalKlax(GLint klaxRow)
{
	GLint rowIndex, colIndex;

	for(colIndex = 0; colIndex < 3; colIndex++)
	{
		rowIndex = klaxRow;
		while(rowIndex > 0)
		{
			this->gameAreaMatrix[rowIndex][colIndex] = this->gameAreaMatrix[rowIndex - 1][colIndex];
			rowIndex--;
		}

		this->gameAreaMatrix[0][colIndex].colorCode = -1;
	}
}

void GameArea :: breakDownVerticalKlax(GLint klaxCol)
{
	this->gameAreaMatrix[0][klaxCol].colorCode = -1;
	this->gameAreaMatrix[1][klaxCol].colorCode = -1;
	this->gameAreaMatrix[2][klaxCol].colorCode = -1;
}


