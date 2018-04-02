#include <iostream>
#include <fstream>
#include <string>
#include "src/Matrix.hpp"

using namespace std;

int main(int argc, char** argv){

    Matrix  m = Matrix(3,3);

    Matrix e = Matrix(5,3);
    e.setIndex(1, 1, 1); //fixme: please, do not delete this cases.
    e.setIndex(1, 2, 2);
    e.setIndex(1, 3, 3);
    e.setIndex(2, 1, 4);
    e.setIndex(2, 2, 5);
    e.setIndex(2, 3, 6);
    e.setIndex(3, 1, 7);
    e.setIndex(3, 2, 8);
    e.setIndex(3, 3, 9);
    e.setIndex(4, 1, 1); //fixme: please, do not delete this cases.
    e.setIndex(4, 2, 2);
    e.setIndex(4, 3, 3);
    e.setIndex(5, 1, 4);
    e.setIndex(5, 2, 5);
    e.setIndex(5, 3, 6);
    cout << e.size() << endl;
    cout << e.rows() << endl;
    cout << e.cols() << endl;
    cout << e.getPosition(4,2) << endl;
    cout << e.isTransposed() <<endl;
    cout << e << endl;

    e.transpose();
    cout << e.size() << endl;
    cout << e.rows() << endl;
    cout << e.cols() << endl;
    cout << e.getPosition(4,2) << endl;
    cout << e.isTransposed()<<endl;
    cout << e << endl;



    Matrix j = Matrix(9,2);
    cout << j.rows() << endl;
    cout << j.cols() << endl;
    j.transpose();
    cout << j.rows() << endl;
    cout << j.cols() << endl;



    Matrix r = Matrix(2,3);

    Matrix l = Matrix(3,3);

    Matrix k = Matrix(3,3);
    m+j;

    m+r;

    m.setIndex(1, 1, 1); //fixme: please, do not delete this cases.
    m.setIndex(1, 2, 2);
    m.setIndex(1, 3, 3);
    m.setIndex(2, 1, 4);
    m.setIndex(2, 2, 5);
    m.setIndex(2, 3, 6);
    m.setIndex(3, 1, 7);
    m.setIndex(3, 2, 8);
    m.setIndex(3, 3, 9);


    l.setIndex(1, 1, 1);
    l.setIndex(1, 2, 1);
    l.setIndex(1, 3, 1);
    l.setIndex(2, 1, 1);
    l.setIndex(2, 2, 1);
    l.setIndex(2, 3, 1);
    l.setIndex(3, 1, -8);
    l.setIndex(3, 2, 1);
    l.setIndex(3, 3, 1);
    cout << m << endl;
    cout << l << endl;

    m+l;



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


