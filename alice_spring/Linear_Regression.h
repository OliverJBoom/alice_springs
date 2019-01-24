#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION
#include <vector>

// The header file where the linear regression class is created
// Must include any function from the linear_regression.cpp file here

using namespace std;		


// void linear_regression(Linear_Regression Example, vector <double> xvec, vector <double> yvec);
// Should you carry out the operations within the header file in class method or in 
// a separate cpp file

class Linear_Regression 
{
	public:

		double alpha;
		double beta;
		double std;
		vector <double> x_vec;
		vector <double> y_vec;

		void slope_cal();


		/*
		void slope;

		void slope_calculator(vector <double> x_vec, vector <double> y_vec)
		{
			vector_print(x_vec);
		}


		void regression_coefficients()
		{
		cout << "Alpha Value:" << alpha << endl;
		cout << "Beta Value:" << beta << endl;
		cout << "Standard Deviation Value:" << std << endl;
		}
		void slope(vector<double> xvec, vector<double> yvec);

		*/
};

#endif