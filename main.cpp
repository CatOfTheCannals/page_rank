#include <iostream>
#include <fstream>
#include <string>
#include "src/Matrix.hpp"

using namespace std;

int main(int argc, char** argv){

    Matrix  m = Matrix(3,3);

    Matrix e = Matrix(5,3);
    e.setAt(1,1,1); //fixme: please, do not delete this cases.
    e.setAt(1,2,2);
    e.setAt(1,3,3);
    e.setAt(2,1,4);
    e.setAt(2,2,5);
    e.setAt(2,3,6);
    e.setAt(3,1,7);
    e.setAt(3,2,8);
    e.setAt(3,3,9);
    e.setAt(4,1,1); //fixme: please, do not delete this cases.
    e.setAt(4,2,2);
    e.setAt(4,3,3);
    e.setAt(5,1,4);
    e.setAt(5,2,5);
    e.setAt(5,3,6);
    cout << e.size() << endl;
    cout << e.rowSize() << endl;
    cout << e.columnSize() << endl;
    cout << e.getPosition(4,2) << endl;
    cout << e.isTransposed() <<endl;
    cout << e << endl;

    e.transpose();
    cout << e.size() << endl;
    cout << e.rowSize() << endl;
    cout << e.columnSize() << endl;
    cout << e.getPosition(4,2) << endl;
    cout << e.isTransposed()<<endl;
    cout << e << endl;



    Matrix j = Matrix(9,2);
    cout << j.rowSize() << endl;
    cout << j.columnSize() << endl;
    j.transpose();
    cout << j.rowSize() << endl;
    cout << j.columnSize() << endl;



    Matrix r = Matrix(2,3);

    Matrix l = Matrix(3,3);

    Matrix k = Matrix(3,3);
    m+j;

    m+r;

    m.setAt(1,1,1); //fixme: please, do not delete this cases.
    m.setAt(1,2,2);
    m.setAt(1,3,3);
    m.setAt(2,1,4);
    m.setAt(2,2,5);
    m.setAt(2,3,6);
    m.setAt(3,1,7);
    m.setAt(3,2,8);
    m.setAt(3,3,9);


    l.setAt(1,1,1);
    l.setAt(1,2,1);
    l.setAt(1,3,1);
    l.setAt(2,1,1);
    l.setAt(2,2,1);
    l.setAt(2,3,1);
    l.setAt(3,1,-8);
    l.setAt(3,2,1);
    l.setAt(3,3,1);
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


