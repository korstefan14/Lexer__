//
// Created by Korst on 24.08.2017.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H


#include <iostream>
#include <string.h>

class Lexer {
public:

    enum class Tokentype { Digit, Plus, Minus, Multiply, Divide, ParOpen, ParClose,  EndOfInput, Unknown };

    struct Token {
        Tokentype type;
        char value;

    };

    Lexer(std::istream& is) : is_(is), lookahead_('\0'), eoi_(false) {
        if ( !is_.get( lookahead_ ) ) {
            eoi_ = true;
        }
    }

    void next( Token& token ) {

        while ( !eoi_ && isspace( lookahead_ ) ) { // eliminate white spaces.
            if ( !is_.get( lookahead_ ) ) {
                eoi_ = true;
            }
        }

        if ( eoi_ ) {
            token.type = Tokentype::EndOfInput;
            token.value = '\0';
        }
        else if (isdigit(lookahead_)) {
            token.type = Tokentype::Digit;
            token.value = lookahead_;
        }
        else if (lookahead_ == '+') {
            token.type = Tokentype::Plus;
            token.value = lookahead_;
        }
        else if (lookahead_ == '-') {
            token.type = Tokentype::Minus;
            token.value = lookahead_;
        }
        else if (lookahead_ == '*') {
            token.type = Tokentype::Multiply;
            token.value = lookahead_;
        }
        else if (lookahead_ == '/') {
            token.type = Tokentype::Divide;
            token.value = lookahead_;
        }
        else if (lookahead_ == '(') {
            token.type = Tokentype::ParOpen;
            token.value = lookahead_;
        }
        else if (lookahead_ == ')') {
            token.type = Tokentype::ParClose;
            token.value = lookahead_;
        }
        else {
            token.type = Tokentype::Unknown;
            token.value = lookahead_;
        }

        if ( !eoi_ && !is_.get( lookahead_ ) ) {
            eoi_ = true;
        }
    }

private:

    std::istream& is_;
    char lookahead_;
    bool eoi_;

};

#endif //LEXER_LEXER_H
