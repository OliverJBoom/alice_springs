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
		cout << i << " ";
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


int main()
{
	string nameFile = "Data\\IDCJAC0002_015590\\IDCJAC0002_015590_Data1.csv";
    
	loadData(nameFile);				// Load the input data in a data structure.
	vector<double> x_vec;
	vector<double> y_vec;
	x_vec = inData.x_vec;
	y_vec = inData.y_vec;

	vector_print(y_vec);
	cout << endl;
	system("pause");
}


