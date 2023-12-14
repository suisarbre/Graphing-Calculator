#ifndef GAVIN_OPERATOR_H
#define GAVIN_OPERATOR_H

#include <string>
#include "./token.h"
#include "constants.h"

class Operator : public Token{
    public:
Operator(char val = '+'){
    _val = val;
}
Operator(std::string s){
    _val = s[0];
}

char getval()const{
    return _val;
}

void print(std::ostream& outs) const override{
    outs<<"["<<_val<<"]";
}

int tokenType() override{
        return OPERATOR;
    
}
int precedence() const override{
    if (_val == '+' || _val == '-') return 3;
    if (_val == '*' || _val == '/') return 4;
    if (_val == '^') return 5;
    return 88; //undefined operator
}
    private:
    char _val;

};


#endif //GAVIN_OPERATOR_H