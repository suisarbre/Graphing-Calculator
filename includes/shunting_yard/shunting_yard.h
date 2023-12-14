#ifndef GAVIN_SHUNTING_YARD_H
#define GAVIN_SHUNTING_YARD_H

#include "../token/token.h"

#include "../token/integer.h"
#include "../token/operator.h"


#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"

#include "../token/constants.h"

class ShuntingYard{
public:
ShuntingYard(){
}
ShuntingYard(Queue<Token*> input){
    _infix = input;
    infix(input);
}

Queue<Token*> infix( Queue<Token*> input){
        while(_postfix.empty() == false){
            _postfix.pop();
        }
        _infix = input;

        while (_infix.empty() == false){
        Token* temp = _infix.pop();
        int type = temp->tokenType();
        switch (type)
        {
        case INTEGER:
            _postfix.push(temp);
            break;
        
        case LEFTPAREN:
            _stack.push(temp);
            break;
        
        case RIGHTPAREN:
            while (_stack.top()->tokenType() != LEFTPAREN){
                _postfix.push(_stack.pop());
            }
            _stack.pop();//removes Leftparen
            break;

        case OPERATOR:
            while (_stack.empty() == false && temp->precedence() <= _stack.top()->precedence()){
                _postfix.push(_stack.pop());
            }
            _stack.push(temp);
            break;

        case FUNCTION:
            while (_stack.empty() == false && temp->precedence() <= _stack.top()->precedence()){
                _postfix.push(_stack.pop());
            }
            _stack.push(temp);
            break;
        }



    }
    while (_stack.empty() == false){
        _postfix.push(_stack.pop());
    }
    return _postfix;
}


Queue<Token*> postfix() const{
    return _postfix;
}

Queue<Token*> postfix(Queue<Token*> input){
    _infix = input;
    return infix(input);
}
private:
Queue<Token*> _postfix;

Stack<Token*> _stack;//shouldn't be returned
Queue<Token*> _infix;
};

#endif //GAVIN_SHUNTING_YARD_H
