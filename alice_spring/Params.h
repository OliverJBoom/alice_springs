#ifndef PARAMS
#define PARAMS
#include <string>


using namespace std;


// Define a structure that will contain the input parameters.
struct Input_Params
{
	string file_name;							// Name of the input file.
	double time_wnd;							// Size (in months) of the time window used
												// in the SMA calculation.

	double smt_fac;								// The exponential term associated with smoothing

	void read_params();							// The method that reads the input parameters file.
};



// Structure that will contain input parameters defined by the user via terminal.
struct Inp_Par_Ter
{
	int year;									// Year of the forecasted temperature.
	int month;									// Month of the forecasted temperature.

	void get_inp_ter();							// Method to get input from the terminal.
	double convert_date(int year, int month);	// Method to convert the date to a number.
};

#endif