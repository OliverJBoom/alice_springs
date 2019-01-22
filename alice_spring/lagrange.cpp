#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h> 

using namespace std;

// Interpolator using the Lagrange method.
vector<double> interpLagrange(vector<double> x_vec, vector<double> y_vec, vector<double> x_int)
{
	int n_x_vec = x_vec.size();
	int n_x_int = x_int.size();
	cout << n_x_int;
	// Calculate basis polynomials.
	// Initialise the array with ones.

	double l_basis[n_x_vec][n_x_int];
	for (int i=0; i<n_x_vec; i++){
		for (int j=0; j<n_x_int; j++){
			l_basis[i][j] = 1.0;
		}
	}
	// Compute the basis.
	for (int k=0; k<n_x_int; k++){
		for (int i=0; i<n_x_vec; i++){
			for (int j=0; j<n_x_vec; j++){
				if (j!=i) {
					l_basis[i][k] = l_basis[i][k] * (x_int[k]-x_vec[j])/(x_vec[i]-x_vec[j]);
				}
			}
		}
	}

	// Calculate the lagrange interpolation polynomial.
	vector<double> y_int(n_x_int, 0.0);
	for (int k=0; k<n_x_int; k++){
		for (int i=0; i<n_x_vec; i++){
			y_int[k] = y_int[k] + l_basis[i][k]*y_vec[i];
		}
	}

	return y_int;

}


// Test the Lagrange interpolator.
// Compare its result with a SciPy results.
void testLagrange()
{
	// Define a 2D array
	double array[6][2] = { {0.5,0.5}, {2.0,0.4}, {4.0,0.3}, {5.0,0.1}, {7.0,0.9}, {9.0,0.8} };

	// Get time and temperature vectors.
	vector<double> x_vec(6);
	vector<double> y_vec(6);
	for (int i = 0; i < 6; i++) {
		x_vec[i] = array[i][0];
		y_vec[i] = array[i][1];
	}

	// Define x_int, time values when the interpolation is done.
	vector<double> x_int(5);
	vector<double> y_int(5);
	x_int[0] = 1.;
	x_int[1] = 2.5;
	x_int[2] = 3.5;
	x_int[3] = 4.5;
	x_int[4] = 8.;
	//y_int = interpLagrange(x_vec, y_vec, x_int);

	// Print the first result.
	// cout << y_int[0] << endl;
}


int main()
{
	// // Call a simple function to test the Lagrange interpolator.
	// testLagrange();


	// Test the lagrange interpolator.
	vector<double> x_int;
	vector<double> y_int;
	x_int = x_vec;
	// x_int[0] = 1;
	/*y_int = interpLagrange(x_vec, y_vec, x_int);

	for (int i=0; i<x_vec.size(); i++){
		cout << i << "  " << y_vec[i] << "  " << y_int[i] << endl;

	}*/
	return 0;
}