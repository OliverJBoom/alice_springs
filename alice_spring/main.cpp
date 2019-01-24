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

// make sure to go through and have camelcase naming convention consistent

int main()
{
	test_regression();									// Tests linear regression model for known data

	string Temp_File = "Data\\IDCJAC0002_015590\\IDCJAC0002_015590_Data1.csv";
	struct data Temp_In;
	Temp_In.load_climate_data(Temp_File);				// Load the input data in a data structure.					

	//cout << "Temp In X:" << endl;
	//vector_print(Temp_In.x_in);
	//cout << "Temp In Y:" << endl;
	//vector_print(Temp_In.y_in);

	//vector<double> sma_temp;							// Calculating the simple moving average for temperature
	//sma_temp = sma_calc(sma_temp, Temp_In.y_in);		// Calculates the simple moving average 
	
	//cout << "Simple Moving Average :" << endl;
	//vector_print(sma_temp);							// for temp over the known time frame
	
	Temp_In.sma_calc(Temp_In.x_in, Temp_In.y_in, 48);

	cout << "Temp In X:" << endl;
	vector_print(Temp_In.x_in);
	cout << "Temp In Y:" << endl;
	vector_print(Temp_In.y_in);


	//Linear_Regression Temp;								// Loading in smoothed temperature readings
	//Temp.x_vec = Temp_In.x_in;
	//Temp.y_vec = Temp_In.y_in;
	//Temp.slope_cal();
	//Temp.slope_print();
	//Temp.extrapolation(2050);

	/*
	Linear_Regression Temp;								// Loading in smoothed temperature readings
	Temp.x_vec = Temp_In.x_in;
	Temp.y_vec = sma_temp;
	Temp.slope_cal();
	Temp.slope_print();
	Temp.extrapolation(2050);
	*/

	system("pause");
}
