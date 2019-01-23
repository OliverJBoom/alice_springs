#include <iostream>
#include <string>
#include "Linear_Regression.h"			// Including the appropriate header file 
										//containing the linear regression class

using namespace std;


void linear_regression()
{
	Linear_Regression Example;
	Example.alpha = 9;
	Example.beta = 10;
	Example.std = -100.45;
	Example.regression_coefficients();
}



void hello_world()
{
	cout << "hello world!" << endl;
}

