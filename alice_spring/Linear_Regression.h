#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION
#include <vector>


using namespace std;		


class Linear_Regression 
{
	public:

		// Class attributes
		double alpha;
		double beta;
		double std;
		vector <double> x_vec;
		vector <double> y_vec;
		double extrapolation(double x);


		// Class methods
		void slope_cal();
		void slope_print();
		
};

#endif