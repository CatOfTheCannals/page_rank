#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.hpp"

using namespace std;

int main(int argc, char** argv){
	
	Matrix  m = Matrix(3,3);
	
	cout << m.size() << endl;	

	cout << m.getPosition(1,1) << endl;

	cout << m << endl;

	// m.printarray();

	string line;

	ifstream f_test("test.txt");
	if ( f_test.is_open() ){
		while( getline(f_test, line) ){
			cout << line << endl;
		}
		f_test.close();
	} else {
		cout << "Unable to open file." << endl;
	}

	return 0;
}

