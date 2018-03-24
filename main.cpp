#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv){

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

