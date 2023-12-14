#ifndef GAVIN_INTEGER_H
#define GAVIN_INTEGER_H

#include <string>
#include "./token.h"

class Integer : public Token{
public:

Integer(double val):_val(val){}

Integer(std::string s){
    _val = std::stod(s);
}

void print(std::ostream& outs) const override{
    outs<<"["<<_val<<"]";
}
int precedence() const override{
    return -1;
}
// friend std::ostream& operator<<(std::ostream& outs, Integer* print_me)
// {
//     outs << print_me->_val;
//     return outs;
// }

// friend std::ostream& operator<<(std::ostream& outs, const Integer& print_me)
// {
//     outs << print_me._val;
//     return outs;
// }
double getval()const{
    return _val;
}
int tokenType() override{
        return INTEGER;
    }
private:
double _val;
};

#endif //GAVIN_INTEGER_H