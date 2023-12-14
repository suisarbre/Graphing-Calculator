#include "plot.h"

#include <iostream>

Plot::Plot(Graph_info* gi):_gi(gi){
    Tokenizer();
    }

void Plot:: set_info(Graph_info* gi){
    _gi = gi;
}

void Plot::Tokenizer(){
    std::string str = _gi->_equation;
    std::string integer;
    std::string function;
    bool negation = false;
    for (int i = 0; i< str.length();i++){
        char check = toupper(str[i]);
        if (check == ' '){
            //does nothing
        }
        else if(isdigit(check)||check == '.'){
            integer+=check;
            if(function!= ""){
                _postfix.push(new Function());
                function = "";
            }
        }


        else if(check == '('){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new LeftParen());
        }
        else if(check == ')'){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new RightParen());
        }
        else if(check == '+'){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new Operator('+'));
        }
        else if(check == '-'){
            if(i == 0 || str[i-1] == '(' || !isdigit(str[i-1])){
                // Handle unary minus: treat it as '0 - <value>'
                _postfix.push(new Integer("0"));
            }
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new Operator('-'));
        }
        else if(check == '*'){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new Operator('*'));
        }
        else if(check == '/'){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new Operator('/'));
        }
        else if(check == '^'){
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            if(function!= ""){
                _postfix.push(new Function(function));
                function = "";
            }
            _postfix.push(new Operator('^'));
        }
        else{
            if(integer != ""){
                _postfix.push(new Integer(integer));
                integer = "";
            }
            function+= check;
        }

    }
    if (integer != ""){
        _postfix.push(new Integer(integer));
    }
    if (function != ""){
        _postfix.push(new Function(function));
    }
}

vector<sf::Vector2f> Plot :: operator()(){//graph points
    ShuntingYard sy;
    _postfix = sy.postfix(_postfix);
    RPN rpn(_postfix);
    vector<sf::Vector2f> points;
    double left = _gi->_left;
    double right = _gi->_right;
    double diff = (right-left)/(NUMOFPOINTS);
    double res ;
    for (int i = 0; i < NUMOFPOINTS; i++){
        res = rpn(left);
        points.push_back(sf::Vector2f(left, res));
        left += diff;
    }

    return points;
}

void Plot :: transform(vector<sf::Vector2f>& screenpoints){
    double scale = ((_gi->_screenwidth-SIDEBARWIDTH)/(_gi->_right - _gi->_left));
    for (int i = 0; i < screenpoints.size(); i++){
        screenpoints[i].x = (screenpoints[i].x - _gi->_left) * scale;
        screenpoints[i].y = _gi->_screenheight / 2 - (screenpoints[i].y  + _gi->_updown) * scale;
    }
}