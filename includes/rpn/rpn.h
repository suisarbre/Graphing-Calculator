#ifndef RPN_H
#define RPN_H

#include "../token/token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"

#include <string>
#include <math.h>

class RPN {
    public:
    RPN(){
        
    }

    RPN(Queue<Token*> p){
        _postfix = p;
    }

    double evaluate(double ev = 0){
        // while (!_postfix.empty())
        
        for(Queue<Token*>::Iterator iter = _postfix.begin();iter != _postfix.end();iter++){
            Token* temp = *iter;
            int type = temp->tokenType();
            switch (type)
            {
            case INTEGER:{
                _stck.push(temp);
                break;
            }
            
            case OPERATOR:{
                Operator* new_temp = static_cast<Operator*>(temp);
                //stack has to have 2 integer
                if (new_temp->getval() == 42){// char(42) = '*'
                Integer* push_this = new Integer(static_cast<Integer*>(_stck.pop())->getval() * static_cast<Integer*>(_stck.pop())->getval());
                _stck.push(push_this);
                }
                if (new_temp->getval() == 43){// char(43) = '+'
                Integer* push_this = new Integer(static_cast<Integer*>(_stck.pop())->getval() + static_cast<Integer*>(_stck.pop())->getval());
                _stck.push(push_this);
                }
                if (new_temp->getval() == 45){// char(45) = '-'
                double rhs = static_cast<Integer*>(_stck.pop())->getval();
                Integer* push_this = new Integer(static_cast<Integer*>(_stck.pop())->getval() - rhs);
                _stck.push(push_this);
                }
                if (new_temp->getval() == 47){// char(47) = '/'
                double rhs = static_cast<Integer*>(_stck.pop())->getval();
                Integer* push_this = new Integer(static_cast<Integer*>(_stck.pop())->getval() / rhs);
                _stck.push(push_this);
                }
                if (new_temp->getval() == '^'){
                    double rhs = static_cast<Integer*>(_stck.pop())->getval();
                    _stck.push(new Integer(pow(static_cast<Integer*>(_stck.pop())->getval(),rhs)));
                }
                break;
            }

            case FUNCTION: {
                Function* func = static_cast<Function*>(temp);
                if (func->get_val() == "X") _stck.push(new Integer(ev));//when function is x just put num
                else{
                    int argc = func->args();
                    if (func->get_val() == "SIN"){
                        _stck.push(new Integer(std::sin(static_cast<Integer*>(_stck.pop())->getval())));
                    }
                    else if (func->get_val() == "COS"){
                        _stck.push(new Integer(std::cos(static_cast<Integer*>(_stck.pop())->getval())));
                    }
                    else if (func->get_val() == "TAN"){
                        _stck.push(new Integer(std::tan(static_cast<Integer*>(_stck.pop())->getval())));
                    }
                    else if (func -> get_val() == "LOG"){
                        _stck.push(new Integer(std::log10(static_cast<Integer*>(_stck.pop())->getval())));
                    }
                    else if (func->get_val() == "SQRT"){
                        _stck.push(new Integer(std::sqrt(static_cast<Integer*>(_stck.pop())->getval())));
                    }
                }
                break;
            }
            }
            
        }
        Integer* res = static_cast<Integer*>(_stck.pop());//this is the answer
        return res->getval();
    }


    void set_input(Queue<Token*> input){
        _postfix = input;
    }
    double operator ()(double ev = 0){
        return evaluate(ev);
    }
private:
Queue<Token*> _postfix;
Stack<Token*> _stck;
};
#endif //RPN_H