#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"	

using namespace std;

void hello_world() 
{
	cout << "Hello World" << endl;
}


// Generic vector print function
void vector_print(vector <double> vec)
{
	for (auto &i : vec)
		cout << i << endl;
}
