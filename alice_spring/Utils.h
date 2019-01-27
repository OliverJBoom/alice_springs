#ifndef UTILS
#define UTILS
#include <iostream>
#include <vector>


using namespace std;


vector <double> exp_smt(vector<double> vec, double w);
double rounding(double input, int dp);


void vector_print(vector <double> vec);
void writeOutput(vector<double> x_vec, vector<double> y_vec, string nameFile);
void plotXY(vector<double> x_vec, vector<double> y_vec);
void plotXY_reg(vector<double> x_vec, vector<double> y_vec,
	vector<double> x_vec_regr, vector<double> y_vec_regr);


// Define a structure that will contain the input data.
struct Data
{
	// Struct Attributes
	vector<double> x_in;									// x_in : time values
	vector<double> y_in;									// y_in : temperature values	
	vector<double> x_sma;									// corresponding time value to sma
	vector<double> y_sma;									// simple moving average values

	// Struct Methods
	void load_data(string nameFile, int col_num);			// The method that loads in the data
	void load_climate_data(string nameFile);				// The method that loads in the data
	void sma_calc(											// The method that calculates the 
		vector<double> x_vec,								// simple moving average
		vector<double> y_vec,
		int period);
};


#endif
