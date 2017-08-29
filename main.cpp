//
// Compilers, Fall 2017
// Coding in Lecture, August 24th.
//
//
// This program translates simple infix expression to postfix format.
// For example:
//      9 + 5 - 2  -->   95+2-
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"

using namespace std;

void test_lexer( istream& is )
{
    Lexer lexer(is);
    Lexer::Token token;
    lexer.next(token);
    while ( token.type != Lexer::Tokentype::EndOfInput ) {
        cout << token.value << endl;
        lexer.next(token);
    }
}


int main(int argc, char* argv[] )
{
    // Decide whether to read input from a file (name provided as commmand line argument) or standard input.
    ifstream fin;
    if ( argc == 2 ) {
        fin.open( argv[1] );
        if ( !fin.good() ) {
            cerr << "Could not open input file '" << argv[1] << "'." << endl;
            return -1;
        }
    }
    else {
        cout << "Reading from standard input (enter 'quit' to stop)." << endl;
    }
    istream& is = fin.is_open() ? fin : cin;

    // Parse the expressions (each expression expected to be on a separate line).
    string line;
    while ( getline(is, line) && line != "quit" ) {
        stringstream ss(line);
        // test_lexer( ss );
        Parser parser(ss);
        cout << "Parsing infix expression '" + line + "'" << endl;
        try {
            parser.parse();
        }
        catch ( exception& e ) {
            cout << e.what() << endl;
        }
        cout << endl;
    }

    return 0;
}