//
// Created by Korst on 24.08.2017.
//

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

#include <iostream>
#include <exception>
#include "lexer.h"

//
// expr -> term rest
//
// rest -> + term rest
//       | - term rest
//       | eps
//
// frest -> * factor frest
//       |  / factor frest
//       | eps
//
// term -> factor frest
//
// factor -> number
//        | ( expr )
// number -> 0|1|2|...|9 //this is not reflected in the code
//        | 0 number | 1 number | 2 number | ... | 9 number

class Parser {
public:

    class parsing_exception: public std::exception {
        virtual const char* what() const noexcept {
            return "Parsing expression: invalid syntax.";
        }
    };

    Parser( std::istream& is ) : lexer_(is) {
        lexer_.next( token_ );
    }

    void parse() {
        expr();
        match( Lexer::Tokentype::EndOfInput );
    }

private:

    void expr() {
        term();
        rest();
    }

    void rest() {

        if ( token_.type == Lexer::Tokentype::Plus ) {
            match( Lexer::Tokentype::Plus );
            term();
            std::cout << '+' << " "; std::cout.flush();
            rest();

        }
        else if ( token_.type == Lexer::Tokentype::Minus ) {
            match( Lexer::Tokentype::Minus );
            term();
            std::cout << '-' << " "; std::cout.flush();
            rest();
        }
    }

    void frest() {

        if ( token_.type == Lexer::Tokentype::Multiply ) {
            match( Lexer::Tokentype::Multiply );
            factor();
            std::cout << '*' << " "; std::cout.flush();
            frest();

        }
        else if ( token_.type == Lexer::Tokentype::Divide ) {
            match( Lexer::Tokentype::Divide );
            factor();
            std::cout << '/' << " "; std::cout.flush();
            frest();
        }
    }

    void factor() {
        if ( token_.type == Lexer::Tokentype::ParOpen ) {
            match(Lexer::Tokentype::ParOpen);
            std::cout << '(' << " ";std::cout.flush();
            expr();


        }
        if( token_.type == Lexer::Tokentype::ParClose){
            match(Lexer::Tokentype::ParClose);
            std::cout << ')' << " "; std::cout.flush();


        }
        else {
            if ( token_.type == Lexer::Tokentype::Digit ) {
                std::cout << token_.value << " "; std::cout.flush();
            }
            match( Lexer::Tokentype::Digit );
        }
    }
    void term() {
        factor();
        frest();
    }

    void match( Lexer::Tokentype type ) {
        if ( token_.type == type ) {
            lexer_.next( token_ );

        }
        else {
            throw parsing_exception();
        }
    }

    Lexer lexer_;
    Lexer::Token token_;
};

#endif //LEXER_PARSER_H
