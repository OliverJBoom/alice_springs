#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> 
#include "Linear_Regression.h"
#include "Utils.h"
#include "Tests.h"

using namespace std;


int main()
{
	string Temp_File = "Data\\IDCJAC0002_015590\\IDCJAC0002_015590_Data1.csv";
	struct data Temp_In;
	Temp_In.loadData(Temp_File, 4);						// Load the input data in a data structure.
	
	test_regression();									// Tests linear regression model for known data

	vector<double> sma_temp;							// Calculating the simple moving average for temperature
	sma_temp = sma_calc(sma_temp, Temp_In.y_in);		// Calculates the simple moving average 
	//vector_print(sma_temp);							// for temp over the known time frame

	system("pause");
}
