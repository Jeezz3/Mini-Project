#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;
int main(int argc, char *argv[] ){
    ifstream in;
    ofstream out;
    string line;
    int line_count = 0;

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    }

    in.open(argv[1]);
    if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

    out.open(argv[2]);
    if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
    BigInteger A;
    BigInteger B;

    while(getline(in,line)){
        if(line_count == 0){
            A = BigInteger(line);
        }else if(line_count == 2){
            B = BigInteger(line);
        }
        line_count++;
    }
    
    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A-B << endl << endl;
    out << A-A << endl << endl;
    out << (BigInteger("3")*A)-(BigInteger("2")*B) << endl << endl;
    out << A*B << endl << endl;
    out << A*A << endl << endl;
    out << B*B << endl << endl;
    out << (BigInteger("9")*A*A*A*A)+(BigInteger("16")*B*B*B*B*B) << endl << endl;

    in.close();
    out.close();

    return 0;
}