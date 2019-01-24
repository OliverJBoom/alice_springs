#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
#include "Utils.h"	
#include <math.h>

using namespace std;



// Generic vector print function
void vector_print(vector <double> vec)
{
	for (auto &i : vec)
		cout << i << endl;
}



// Function to round to a certain number of decimal places
double rounding(double input, int dp) 
{
	return roundf(input * pow(10, dp)) / pow(10, dp);
}



// Simple moving average calculator
vector <double> sma_calc_old(vector <double> sma,vector <double> y_vec)
{
	int period = 12;							// Setting a year to avoid seasonality
	int j = 0;									// Counter

	while (j < (y_vec.size() - 12))				// Steps up 1 month at a time
	{
		double sum = 0;							// Resetting the sum and average
		double avr = 0;
		int i = 0;								// Counter
		while (i < period)						// Gives a full years sum
		{
			sum += y_vec[i + j];				// Summing up for that year
			i++;
		}
		avr = sum / period;						// Average over a year
		sma.push_back(avr);						// Adding to SMA vector
		j++;
	}
	return sma;
}



// Simple moving average calculator, modified function.
void data::sma_calc(
	vector<double> x_vec,
	vector<double> y_vec,
	int period)
{
	int j = 0;									// Counter
	int i = 0;
	double x = 0;
	double sum = 0;
	double avr = 0;
	vector<double> sma_x;
	vector<double> sma;

	while (j < (y_vec.size() - (period - 1)))
	{
		sum = 0;							// Resetting the sum and average
		avr = 0;
		i = 0;								// Counter
		while (i < period)						// Gives a full years sum
		{
			sum += y_vec[i + j];					// Summing up for that year
			i++;
		}
		avr = sum / period;						// Average over a year
		y_in.push_back(avr);						// Adding to SMA vector
		x = x_vec[j] + (x_vec[j + period - 1] - x_vec[j]) / 2.;
		x_in.push_back(x);
		j++;
	}
}




// Load the generic data in a struct
void data::load_data(string nameFile, int col_num)
{
	fstream inFile;									// Get a stream variable
	inFile.open(nameFile, fstream::in);				// Open the input file
	if (inFile.fail())								// Check input file is succesfully opened
	{
		cout << "Error opening the file" << endl;
	}

	string header;									// Read the file header.
	getline(inFile, header);
	stringstream stream(header);					// Parse it.
	vector<string> prsd_line;

	while (stream.good())
	{
		string substr;
		getline(stream, substr, ',');
		prsd_line.push_back(substr);
	}

	prsd_line.clear();

	string line;
	double cnt = 0.;								// Counter
	double temp;

	while (getline(inFile, line))
	{
		cnt++;
		stringstream stream(line);
		while (stream.good())
		{
			string substr;
			getline(stream, substr, ',');
			prsd_line.push_back(substr);
		}

		x_in.push_back(cnt);						// Loading the data into the struct
		temp = atof(prsd_line[col_num].c_str());
		y_in.push_back(temp);						
		prsd_line.clear();
	}
}



// Load the date specific weather data in a struct.
void data::load_climate_data(string nameFile)
{
	fstream inFile;									// Get a stream variable
	inFile.open(nameFile, fstream::in);				// Open the input file
	if (inFile.fail())								// Check input file is succesfully opened
	{
		cout << "Error opening the file" << endl;
	}

	string header;									// Read the file header.
	getline(inFile, header);
	stringstream stream(header);					// Parse it.
	vector<string> prsd_line;

	while (stream.good())
	{
		string substr;
		getline(stream, substr, ',');
		prsd_line.push_back(substr);
	}

	prsd_line.clear();

	string line;
	double year;
	double month;
	vector<double> x_vec;							// Time in months,
	vector<double> y_vec;							// Temperature values
	double cnt = 0.;								// Counter
	double time;
	double temp;

	while (getline(inFile, line))
	{
		cnt++;
		stringstream stream(line);
		while (stream.good())
		{
			string substr;
			getline(stream, substr, ',');
			prsd_line.push_back(substr);
		}

		year = atof(prsd_line[2].c_str());
		month = atof(prsd_line[3].c_str());
		time = year + (month - 0.5) / 12.;
		x_in.push_back(time);
		temp = atof(prsd_line[4].c_str());	
		y_in.push_back(temp);
		prsd_line.clear();
	}
}

