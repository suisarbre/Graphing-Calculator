#ifndef GAVIN_FUNCTION_H
#define GAVIN_FUNCTION_H

#include <string>
#include "./token.h"
#include "constants.h"


class Function : public Token{
    public:
Function(std::string input = "X"){
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    _val = input;
    _args = determineArgs(input);
}

void print(std::ostream& outs) const override{
    outs<<"["<<_val<<"]";
}

int tokenType() override{
        return FUNCTION;
    
}

std::string get_val(){
    return _val;
}
int args() const{
    return _args;
}

int precedence() const override{
    return 999;//Highest precedence
}
    private:
    std::string _val;
    int _args;

    int determineArgs(const std::string& functionName) {
        if (functionName == "SIN" || functionName == "COS" || functionName == "TAN" ||
            functionName == "LOG" || functionName == "SQRT") {
            return 1;
        }


        // Default to 0
        return 0;
    }
};

#endif//GAVIN_FUNCTION_H