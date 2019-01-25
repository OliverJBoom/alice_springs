#ifndef UTILS
#define UTILS
#include <iostream>
#include <vector>

// Contains code related to general functions

using namespace std;

vector <double> sma_calc(vector <double> sma, vector <double> y_vec);
vector <double> expSmt(vector<double> vec, double w);

double rounding(double input, int dp);

void vector_print(vector <double> vec);
void writeOutput(vector<double> x_vec, vector<double> y_vec, string nameFile);
void plotXY(vector<double> x_vec, vector<double> y_vec);


// Define a structure that will contain the input data.
struct data
{
	vector<double> x_in;									// x_in : time values
	vector<double> y_in;									// y_in : temperature values
	
	vector<double> x_sma;
	vector<double> y_sma;

	vector<double> expSmt(vector<double> vec, double w);

	void loadData(string nameFile, int col_num);			// The method that loads in the data
	void load_climate_data(string nameFile);			// The method that loads in the data
	void sma_mat(vector<double> x_vec, vector<double> y_vec, int period);
};


#endif
