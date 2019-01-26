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
/*


Add requirements + Readme (GNU PLOT, Visual studio etc)
Make sure naming convention is consistent. All names like this_that
Get rid of legend in plot
Add user interface
Have colour of lines plotted in different colours


*/


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
	
	//cout << "X Mid:" << endl;
	//vector_print(Temp_In.x_mid);
	//cout << "Y smoothed:" << endl;
	//vector_print(Temp_In.y_smoothed);
	

	Linear_Regression Temp;								// Simple moving average readings
	Temp_In.sma_mat(Temp_In.x_in, Temp_In.y_in, 48);
	//Temp.x_vec = Temp_In.x_sma;
	//Temp.y_vec = Temp_In.y_sma;
	//cout << "X_SMA Lenght Smooth:" << Temp_In.x_sma.size() << endl;
	//cout << "Y_SMA Lenght Smooth:" << Temp_In.y_sma.size() << endl;

	vector<double> sma_ex_smooth;
	sma_ex_smooth = expSmt(Temp_In.y_sma, 0.05);
	//vector_print(sma_ex_smooth);
	//cout << "X Length Smooth:" << Temp_In.x_sma.size() << endl;
	//cout << "Y Length Smooth:" << sma_ex_smooth.size() << endl;
	Temp.x_vec = Temp_In.x_sma;							// Calculating exponential smoothing
	Temp.y_vec = sma_ex_smooth;

	Temp.slope_cal();
	Temp.slope_print();

	for (int i = 2018; i < 2050; i++) 
	{
		Temp.x_vec.push_back(i);
		Temp.y_vec.push_back(Temp.extrapolation(i));
	}

	//////plotXY(x_extra, y_extra);5

	plotXY(Temp.x_vec, Temp.y_vec);

	system("pause");
}
