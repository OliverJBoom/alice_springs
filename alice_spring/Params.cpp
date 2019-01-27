#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Params.h"


using namespace std;


// Reading in the key parameters from the params.txt file
void Input_Params::read_params()
{
	fstream in_file;
	in_file.open("Params.txt", fstream::in);

	if (in_file.fail())								// Checking to see if params file exists
	{
		cout << "Error, Params.txt file not found." << endl;
	}

	string line;
	while (getline(in_file, line))
	{
		stringstream stream(line);
		vector<string> prsd_line;

		while (stream.good())
		{
			string substr;
			getline(stream, substr, ' ');

			prsd_line.push_back(substr);
		}

		if (prsd_line[0] == "input_file")			// Loading in the input file name
		{
			file_name = prsd_line[2];
		}

		if (prsd_line[0] == "time_window") 			// Loading in the time window for smoothing
		{
			time_wnd = atof(prsd_line[2].c_str());
		}

		if (prsd_line[0] == "smoothing_factor")		// Loading in the exponential term
		{											// associated with smoothing
			smt_fac = atof(prsd_line[2].c_str());
		}
	}
}



// Promt the user to input the year and the month for the temperature forecast.
void Inp_Par_Ter::get_inp_ter()
{
	bool b_fail;

	cout << endl << "Type the year of the forecasted temperature:" << endl;

	do {
		cin >> year;									// Get the year
		b_fail = cin.fail();

		if (b_fail == true)								// Make sure that a numeric value has been typed
		{						
			cout << endl << "Error, an integer number is requested." << endl;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (b_fail == true);

	cout << endl << "Type the month (in numbers, e.g., type 1";
	cout <<	" for January) of the forecasted temperature:" << endl;

	do {
		cin >> month;									// Get the month
		b_fail = cin.fail();

		if (b_fail == true)								// Make sure that a numeric value has been typed.
		{
			cout << endl << "Error, an integer number is requested." << endl;
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (b_fail == true);
}



// Reading in the key parameters from the params.txt file
double Inp_Par_Ter::convert_date(int year, int month)
{
	return (double)year + ((double)month - 0.5) / 12.;	// Normalize the month in fraction of the year.
}														// Assume temperature is relative to the the mid of the month.