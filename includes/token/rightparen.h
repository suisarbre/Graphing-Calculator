#ifndef GAVIN_RIGHTPAREN_H
#define GAVIN_RIGHTPAREN_H

#include <string>
#include "./token.h"
#include "constants.h"

class RightParen : public Token{
    public:
RightParen(){
    _val = ')';
}

void print(std::ostream& outs) const override{
    outs<<"["<<_val<<"]";
}

int tokenType() override{
        return RIGHTPAREN;
    
}
int precedence() const override{
    return -1;
}
    private:
    char _val;

};


#endif //GAVIN_RIGHTPAREN_H