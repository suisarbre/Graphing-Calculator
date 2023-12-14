#ifndef GAVIN_TOKEN_H
#define GAVIN_TOKEN_H
#include <iostream>
#include "constants.h"

class Token{
public:
Token(){
    _type = -99;
}
    virtual void print(std::ostream& outs) const{

    }

    friend std::ostream& operator <<(std::ostream& outs,const Token& tk){
        tk.print(outs);
        return outs;
    }
    friend std::ostream& operator <<(std::ostream& outs,Token* tk){
        tk->print(outs);
        return outs;
    }
    virtual int tokenType(){
        return TOKEN;
    }
    virtual int precedence() const{
            //
    }
private:
int _type;

};

#endif //GAVIN_TOKEN_H