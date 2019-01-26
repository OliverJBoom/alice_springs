#ifndef PARAMS
#define PARAMS
#include <string>


using namespace std;


// Define a structure that will contain the input parameters.
struct Input_Params
{
	string file_name;					// Name of the input file.
	double time_wnd;					// Size (in months) of the time window used
										// in the SMA calculation.

	double smt_fac;						// The exponential term associated with smoothing

	void read_params();					// The method that reads the input parameters file.
};


#endif
