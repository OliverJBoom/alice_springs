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



// Compute exponential smoothing.
vector<double> exp_smt(vector<double> vec, double w)
{
	int num = vec.size();
	vector<double> vec_smt;  // vector with smoothed values
	vec_smt.push_back(vec[0]);  // initialize the smoothed vector
	for (int i = 1; i < num; i++) {
		double val = w * vec[i] + (1 - w) * vec_smt[i - 1];
		vec_smt.push_back(val);
	}
	return vec_smt;
}



// Exponential smoothing average
void Data::sma_calc(
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

		y_sma.push_back(avr);						// Adding to SMA vector
		x = x_vec[j] + (x_vec[j + period - 1] - x_vec[j]) / 2.;
		x_sma.push_back(x);
		j++;
	}
}



// Load the data in a struct
void Data::load_data(string nameFile, int col_num)
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
void Data::load_climate_data(string nameFile)
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



// Write x and y vectors in a .csv file.
void writeOutput(vector<double> x_vec, vector<double> y_vec, string nameFile)
{
	fstream outFile;
	outFile.open(nameFile, std::ios::out);

	for (int i = 0; i < x_vec.size(); i++) {
		outFile << x_vec[i]
		<< "," << y_vec[i] << endl;
	}
	outFile.close();

	x_vec.clear();
	y_vec.clear();
}



// Plot x and y values.
void plotXY(vector<double> x_vec, vector<double> y_vec)
{
	// Write x and y in an output .csv file.
	string outFile = "out.csv";
	writeOutput(x_vec, y_vec, outFile);

	// Create a pipe to send information to gnuplot.
	FILE *gnuplotPipe = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");

	if (gnuplotPipe) {   // If gnuplot is found
		fprintf(gnuplotPipe, "set xlabel 'X'\n");
		fprintf(gnuplotPipe, "set ylabel 'Y'\n");
		fprintf(gnuplotPipe, "set title 'Title'\n");

		//To plot a multi - column datafile using the 1st column for the abscissa and the 2nd column as the ordinate, use
		fprintf(gnuplotPipe, "set datafile separator \",\"\n");
		fprintf(gnuplotPipe, "plot \"out.csv\" using 1:2\n");
		// fprintf(gnuplotPipe, "plot \"out.csv\" using 1:2 every 24\n");

		//example 4: (try turning this on to save your plot to a file)
		fprintf(gnuplotPipe, "set terminal push\n"); //(save original format setting)
		fprintf(gnuplotPipe, "set terminal gif size 640, 480\n"); //    (change to new format)
		fprintf(gnuplotPipe, "set output \"out.gif\"\n"); //		   (set file name for output)
		fprintf(gnuplotPipe, "replot\n"); //(save gif plot in file)
		fprintf(gnuplotPipe, "set terminal pop\n"); //(restore original format setting)
		fflush(gnuplotPipe); //flush pipe

		//gnuplot has a huge amount of options!
		fprintf(gnuplotPipe, "\nexit \n");   // exit gnuplot
		_pclose(gnuplotPipe);    //close pipe
	}
}


// Plot x and y values and the regression line as seperate markers
void plotXY_reg(vector<double> x_vec, vector<double> y_vec, vector<double> x_vec_regr, vector<double> y_vec_regr)
{
	// Write x_vec and y_vec in an output .csv file.
	string outFile = "out_0.csv";
	writeOutput(x_vec, y_vec, outFile);

	// Write output from linear regression in an output .csv file.
	outFile = "out_1.csv";
	writeOutput(x_vec_regr, y_vec_regr, outFile);

	// Create a pipe to send information to gnuplot.
	FILE *gnuplotPipe = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");

	if (gnuplotPipe) {   // If gnuplot is found
		fprintf(gnuplotPipe, "set xlabel 'Time (years)'\n");
		fprintf(gnuplotPipe, "set ylabel 'Temperature ({\260}C)'\n");
		fprintf(gnuplotPipe, "set title 'Temperature vs. Time'\n");

		// Make a 2D plot.
		fprintf(gnuplotPipe, "set datafile separator \",\"\n");
		fprintf(gnuplotPipe, "set key\n");
		fprintf(gnuplotPipe, "set key right bottom\n");  //define the legend location
		fprintf(gnuplotPipe, "set termoption dash \n");
		fprintf(gnuplotPipe, "set for [i=1:5] linetype i dt i \n");  // reset some linetypes
		fprintf(gnuplotPipe, "set style line 4 lt 2 lc rgb \"green\" lw 2\n");  // define a linetype
		fprintf(gnuplotPipe, "plot \"out_0.csv\" title \"Smoothed values\" with points,\
                                       \"out_1.csv\" ls 4 title \"Linear regression\" with lines \n");  //plot and add legend

			// fprintf(gnuplotPipe, "plot \"out.csv\" using 1:2 every 24\n"); //plot only every x values

			// Save the plot as .gif.
		fprintf(gnuplotPipe, "set terminal push\n");
		fprintf(gnuplotPipe, "set terminal gif size 640, 480\n");
		fprintf(gnuplotPipe, "set output \"output_plot.gif\"\n");
		fprintf(gnuplotPipe, "replot\n");
		fprintf(gnuplotPipe, "set terminal pop\n");

		fflush(gnuplotPipe); //flush pipe
		fprintf(gnuplotPipe, "\nexit \n");   // exit gnuplot
		_pclose(gnuplotPipe);    //close pipe {{1111223ssdww
	}
}