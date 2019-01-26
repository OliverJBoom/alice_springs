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