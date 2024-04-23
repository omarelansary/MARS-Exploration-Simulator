#include "station.h"


// Project [Mars Exploration] //

/*
 Cairo University
 Faculty of Engineering
 Computer Engineering Department
 Spring 2021
 CMPN 102

Names :
 Yahia Ahmed Hatem Mostafa Mahmoud
 Mohamed Ahmed Abdullah Mahmoud	
*/


// Main File which the program run in it
int main(){

	//Create an object of station
	station marsStation;

	//Read Input File
	marsStation.Load();


	//Control station
	marsStation.Control();	

	//Save Output File
	marsStation.Save();

	return 0;

}