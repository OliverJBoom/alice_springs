#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include <stdlib.h> 

#include "Utils.h"
#include "Linear_Regression.h"
#include "Params.h"
#include "Tests.h"


using namespace std;


int main()
{
	cout << endl << "Temperature Forecast for Alice Springs" << endl << endl;
	
	struct Input_Params params;							// Reading the input parameters for the model
	params.read_params();
	
	cout << endl << "Input data read from the file:" << endl;
	cout << params.file_name << endl;

	test_regression();									// Tests linear regression model for known data

	struct Data temp_in;
	temp_in.load_climate_data(params.file_name);		// Load the input data in a data structure.
	temp_in.sma_calc(temp_in.x_in,						// Simple moving average calculation
					temp_in.y_in,
					params.time_wnd);

	vector<double> exp_smooth;							// Calculating exponential smoothing
	exp_smooth = exp_smt(temp_in.y_sma, params.smt_fac);

	Linear_Regression regress;							// Performs linear regression on the  		
	regress.x_vec = temp_in.x_sma;						// exponentially smoothed simple moving 		
	regress.y_vec = exp_smooth;							// average data		
	regress.slope_cal();
	//regress.slope_print();

	struct Inp_Par_Ter params_ter;						// Get from the user the month and year
	params_ter.get_inp_ter();							// of the extrapolated temperature.
	double time;
	time = params_ter.convert_date(params_ter.year, params_ter.month);

	int ini_time = (int)temp_in.x_in[0];				// Get the initial time.
	int end_time = (int)(time + 1);						// Get the final time for the extrapolation.
	for (int i = ini_time; i < end_time; i++)			// Extrapolate using regression coefficients
	{
		regress.x_pred.push_back(i);
		regress.y_pred.push_back(regress.extrapolation(i));
	}

	
	double tem_forecast = regress.extrapolation(time);	//Output on screen the value of the 
	cout << endl << "The forecasted temperature is:";	//forecasted temperature.
	cout <<	"\t" << setprecision(4) << tem_forecast;	//temperature calculated to 2 d.p
	cout << " " << "\370" << "C" << endl;


	plotXY_reg(regress.x_vec, regress.y_vec,			// Plot exponentially smoothed data
		regress.x_pred, regress.y_pred);				// and extrapolated predictions
														
	system("pause");
}
