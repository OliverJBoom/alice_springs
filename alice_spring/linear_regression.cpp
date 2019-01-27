#include <iostream>
#include <string>

#include "Linear_Regression.h"			
#include "Utils.h"						


using namespace std;

// Performs linear regression by reducing the error from least squares
void Linear_Regression::slope_cal()
{
		int i = 0;
		int n = y_vec.size();
		double Sx = 0;
		double Sxx = 0;
		double Sxy = 0;
		double Sy = 0;
		
	while (i < n)
		{
			Sx += x_vec[i];
			Sy += y_vec[i];
			Sxy += x_vec[i] * y_vec[i];
			Sxx += x_vec[i] * x_vec[i];
			i++;
		}

	beta = (n * Sxy - (Sx * Sy)) / (n * Sxx - (Sx * Sx));	//aThe slope of the line of regression
	alpha = Sy / n - (beta * Sx / n);						//The y-intercept of the line of regression
}



void Linear_Regression::slope_print()
{
	cout << "Alpha:" << alpha << endl;
	cout << "Beta:" << beta << endl;
}



double Linear_Regression::extrapolation(double x)
{
	//cout << endl << "Temperature Prediction: " << (x * beta) + alpha << endl;
	return (x * beta) + alpha;
}