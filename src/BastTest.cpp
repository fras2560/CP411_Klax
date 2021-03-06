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
    This file contains implementation for the Test class,
    which is defined in Test.hpp
    -------------------------------------------------------
 */
#include "BaseTest.hpp"

BaseTest :: BaseTest(){
	passed = 0;
	failed = 0;
}

BaseTest :: ~BaseTest(){

}

void BaseTest :: setUp(){

}

void BaseTest :: tearDown(){

}

/*
   -------------------------------------------------------
    This function checks if the two conditions are equal
    If they are not equal prints out the error message
    -------------------------------------------------------
    Preconditions:
    	cond1: the first condition (boolean)
    	cond2: the second condition (boolean)
    	message: the error message (char array)
    Postconditions:
    	prints message if conditions are not met
    	increments failed if assert failed
    	increments passed if assert passed
    -------------------------------------------------------
 */
void BaseTest :: assert(bool cond1, bool cond2, char * message){

	if (cond1 != cond2){
		cout << message << "\n";
		this->failed += 1;
	}else{
		this->passed += 1;
	}
}

/*
 *  -------------------------------------------------------
 *  This functions prints the stats out for the tests ran
 *  -------------------------------------------------------
 *  Preconditions:
 *  	None
 *  Postconditions:
 *   	prints out the number of failed tests
 *   	prints out the number of tests ran
 *  -------------------------------------------------------
 */
void BaseTest :: stats(){
	GLint total = this->passed + this->failed;
	cout << "Total Tests Ran: " << total << "\n";
	if (this->failed > 0){
		cout << "Failed: " << this->failed << "\n";
	}
	cout << "\n";
}
