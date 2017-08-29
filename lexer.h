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
        std::string value;

    };

    Lexer(std::istream& is) : is_(is), lookahead_('\0'), eoi_(false) {
        getNextCharWithEOI();
    }

    void next( Token& token ) {

        while ( !eoi_ && isspace( lookahead_ ) ) { // eliminate white spaces.
            getNextCharWithEOI();
        }
        token.value.clear();
        if ( eoi_ ) {
            token.type = Tokentype::EndOfInput;
            token.value = '\0';
        }
        else if (isdigit(lookahead_)) {
            token.type = Tokentype::Digit;
            token.value.push_back(lookahead_);
            getNextCharWithEOI();
            while (!eoi_ && isdigit(lookahead_)){
                token.value.push_back(lookahead_);
                getNextCharWithEOI();
            }
        }
        else if (lookahead_ == '+') {
            token.type = Tokentype::Plus;
            token.value.push_back(lookahead_);
        }
        else if (lookahead_ == '-') {
            token.type = Tokentype::Minus;
            token.value.push_back(lookahead_);
        }
        else if (lookahead_ == '*') {
            token.type = Tokentype::Multiply;
            token.value.push_back(lookahead_);
        }
        else if (lookahead_ == '/') {
            token.type = Tokentype::Divide;
            token.value.push_back(lookahead_);
        }
        else if (lookahead_ == '(') {
            token.type = Tokentype::ParOpen;
            token.value.push_back(lookahead_);
        }
        else if (lookahead_ == ')') {
            token.type = Tokentype::ParClose;
            token.value.push_back(lookahead_);
        }
        else {
            token.type = Tokentype::Unknown;
            token.value.push_back(lookahead_);
        }

        if (token.type != Tokentype::Digit){
        getNextCharWithEOI();
        }
    }
    void getNextCharWithEOI(){
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
