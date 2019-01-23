#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION


// The header file where the linear regression class is created
// Must include any function from the linear_regression.cpp file here

using namespace std;


void linear_regression();			


class Linear_Regression 
{
	public:

		double alpha;
		double beta;
		double std;

		void regression_coefficients()
		{
		cout << "Alpha Value:" << alpha << endl;
		cout << "Beta Value:" << beta << endl;
		cout << "Standard Deviation Value:" << std << endl;
		}
};

#endif