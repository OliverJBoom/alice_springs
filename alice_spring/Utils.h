#ifndef UTILS
#define UTILS
#include <iostream>
#include <vector>

// Contains code related to general functions

using namespace std;

void vector_print(vector <double> vec);		
vector <double> sma_calc(vector <double> sma, vector <double> y_vec);
double rounding(double input, int dp);

// Define a structure that will contain the input data.
struct data
{
	vector<double> x_in;									// x_in : time values
	vector<double> y_in;									// y_in : temperature values

	void loadData(string nameFile, int col_num);			// The method that loads in the data
};

#endif
