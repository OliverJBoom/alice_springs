#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <stdlib.h> 

#include "Utils.h"
#include "Linear_Regression.h"
#include "Params.h"
#include "Tests.h"


using namespace std;
/*

Add requirements + Readme (GNU PLOT, Visual studio etc)
Get rid of legend in plot
Have colour of lines plotted in different colours

*/


int main()
{
	test_regression();									// Tests linear regression model for known data

	struct Input_Params params;
	params.read_params();

	struct Data temp_in;
	temp_in.load_climate_data(params.file_name);		// Load the input data in a data structure.
	temp_in.sma_calc(temp_in.x_in,						// Simple moving average calculations
					temp_in.y_in,
					params.time_wnd);

	vector<double> exp_smooth;							// Calculating exponential smoothing
	exp_smooth = exp_smt(temp_in.y_sma, params.smt_fac);

	Linear_Regression regress;							// Performs linear regression on the  		
	regress.x_vec = temp_in.x_sma;						// exponentially smoothed simple moving 		
	regress.y_vec = exp_smooth;							// average data		
	regress.slope_cal();
	//regress.slope_print();

	for (int i = 2018; i < 2050; i++)					// Extrapolate using regression coefficients
	{
		regress.x_vec.push_back(i);
		regress.y_vec.push_back(regress.extrapolation(i));
	}

	plotXY(regress.x_vec, regress.y_vec);				// Plot exponentially smoothed data
														// and extrapolated predictions

	system("pause");
}
