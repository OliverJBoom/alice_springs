#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> 

using namespace std;


// Define a structure that will contain the input data.
struct data 
{
	vector<double> x_vec;			// x_vec : time values
	vector<double> y_vec;			// y_vec : temperature values
} inData;


// Generic vector print function
void vector_print(vector <double> vec)
{
	for (auto &i : vec)			
		cout << i << endl;
}


// Load the data in a struct.
void loadData(string nameFile)
{
	fstream inFile;									// Get a stream variable
	inFile.open(nameFile, fstream::in);				// Open the input file
	if (inFile.fail())								// Check input file is succesfully opened
	{
		cout<<"Error opening the file"<<endl;
	}

	string header;									// Read the file header.
	getline(inFile, header);
	stringstream stream(header);					// Parse it.
	vector<string> prsd_line;

	while( stream.good() )
	{
		string substr;
		getline( stream, substr, ',' );
		prsd_line.push_back(substr);
	}

	int n_col = prsd_line.size();					// Get the number of columns in the input file.
	prsd_line.clear();

    vector<double> x_vec;							// Time in months,
    vector<double> y_vec;							// Temperature values
	string line;
	double cnt = 0.;								// Counter
	double temp;

	while (getline(inFile, line))
	{
		cnt++;
		stringstream stream(line);
		while( stream.good() )
		{
			string substr;
			getline( stream, substr, ',' );
			prsd_line.push_back(substr);
		}
		
		x_vec.push_back(cnt);
		temp = atof(prsd_line[n_col-2].c_str());	// Temperature is always in the 2nd last column.
		y_vec.push_back(temp);
		prsd_line.clear();
	}
	inData.x_vec = x_vec;
	inData.y_vec = y_vec;
}



// Simple moving average calculator
vector <double> sma_calc(
	vector <double> sma,
	vector <double> x_vec,
	vector <double> y_vec)
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
			sum += y_vec[i+j];					// Summing up for that year
			i++;
		}
		avr = sum / period;						// Average over a year
		sma.push_back(avr);						// Adding to SMA vector
		j++;
	}
	return sma;
}


int main()
{
	string nameFile = "Data\\IDCJAC0002_015590\\IDCJAC0002_015590_Data1.csv";
    
	loadData(nameFile);				// Load the input data in a data structure.
	vector<double> x_vec;
	vector<double> y_vec;
	vector<double> sma;

	x_vec = inData.x_vec;
	y_vec = inData.y_vec;

	// Want to load in the xvec and yvec and be returned a vector with SMA
	sma = sma_calc(sma, x_vec, y_vec);
	vector_print(sma);
	//cout << endl;

	system("pause");
}


