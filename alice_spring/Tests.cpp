#include <iostream>
#include <string>
#include "Linear_Regression.h"			// Including the appropriate header file 
#include "Utils.h"
#include "Tests.h"	
#include "assert.h"


// Known case to test the Linear Regression calculator
void test_regression()
{
string FILE_TEST = "Data\\Numerical_Example.csv";

struct Data DATA_TEST_x;							// Loading in the numerical examples into the  
struct Data DATA_TEST_y;							// x and y vectors  
DATA_TEST_x.load_data(FILE_TEST, 0);
DATA_TEST_y.load_data(FILE_TEST, 1);

Linear_Regression Test;
Test.x_vec = DATA_TEST_x.y_in;
Test.y_vec = DATA_TEST_y.y_in;
Test.slope_cal();									// Calculating the linear regression slope
assert(rounding(Test.alpha, 3) == -39.062);			// Asserting that it matches the known values
assert(rounding(Test.beta, 3) == 61.272);
cout << endl << "Linear regression testing complete" << endl;
}
