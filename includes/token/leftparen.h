#ifndef GAVIN_LEFTPAREN_H
#define GAVIN_LEFTPAREN_H

#include <string>
#include "./token.h"
#include "constants.h"

class LeftParen : public Token{
    public:
LeftParen(){
    _val = '(';
}
void print(std::ostream& outs) const override{
    outs<<"["<<_val<<"]";
}
int tokenType() override{
        return LEFTPAREN;
    
}
int precedence() const override{
    return -1;
}

    private:
    char _val;

};


#endif //GAVIN_LEFTPAREN_H