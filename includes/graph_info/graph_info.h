#ifndef GAVIN_GRAPH_INFO_H
#define GAVIN_GRAPH_INFO_H

#include <iostream>
#include <string>
#include "../stack/MyStack.h"
struct Graph_info{

Graph_info(){

}
Graph_info(std::string equation, double screenwidth, double screenheight, double left,double right){
    _equation = equation;
    _screenheight = screenheight;
    _screenwidth = screenwidth;
    _left = left;
    _right = right;
    _updown = 0;
}
void panRight(){
    double pan = (_right - _left)/100;
    _left += pan;
    _right+= pan;
}

void panLeft(){
    double pan = (_right - _left)/100;
    _left -= pan;
    _right -= pan;
}

void zoomOut(){
    double scale = 0.95;
    _left *= scale;
    _right *= scale;
}

void zoomIn(){
    double scale = 1.05;
    _left *= scale;
    _right *= scale;
}

void panUp(){
    _updown += 0.5;
}

void panDown(){
    _updown -= 0.5;
}
bool setEq(std::string a){
    try{
    for (int i = 0; i<a.length();i++){
        a[i] = toupper(a[i]);
    }
    //this changes string to uppercase
    is_valid(a);
    _equation = a;
    return 1;//if no error, return 1
    }
    catch(const std::string& a){
        return 0;
    }
}


std::string _equation;
double _screenheight;
double _screenwidth;
double _right;
double _left;
double _updown;

private:
    void is_valid(const std::string& eq){
        if(eq.empty()){
            std::cout<<"empty"<<std::endl;
            throw eq;
        }
        bool lastWasOp = true;//equation should not start with operator
        bool lastWasDot = false;
        Stack<char> parentheses;
        std::string num;
        std::string func;
        for (int i = 0;i<eq.length();i++){
            char check = eq[i];

            if(check == ' '){
                continue;
            }
            else if(isdigit(check)||check == '.'){
                if (check == '.' && (lastWasDot || num.empty())){
                    throw eq;
                }
                lastWasDot = (check == '.');// this changes lastWasDot
                lastWasOp = false;
                num += check;
            }
            else if (isalpha(check)){
                if(!num.empty()){
                    throw eq;//number followed by a letter without operator
                }
                func += check;
                lastWasOp = false;
            }
            else{
                if(!num.empty()){
                    num.clear();
                    lastWasDot = false;
                }
                if (!func.empty()){
                    if(!isValidFunction(func)){
                        throw eq;
                    }
                    
                    func.clear();
                }
                if(check == '('){
                    parentheses.push(check);
                    lastWasOp = true;//putting left paren is like starting a new equation
                    //thus shouldn't start with operator
                }
                else if (check == ')'){
                    if (parentheses.empty()){
                        throw eq;
                    }
                    parentheses.pop();
                }
                else if(isOperator(check)){
                    //for unary minus
                    if (lastWasOp){
                        if (check != '-' || (i != 0 && eq[i-1] != '(')){
                            throw eq;
                        }

                    }
                    lastWasOp = true;
                }
                else{
                    throw eq;
                }
            }
        }
        if (!parentheses.empty()){
            throw eq; // not closed left paren
        }
        if (lastWasOp){
            throw eq;//equation ended with operator
        }
        if (func =="X"){
            func.clear();
        }
        if(!func.empty()){
            throw eq;
        }
    }
    
    bool isOperator(char c){
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^'){
            return true;
        }
        else return false;
    }
    bool isValidFunction(std::string s){
        if (s == "SIN" || s == "COS" || s == "TAN" ||
            s == "LOG" || s == "SQRT" || s == "X") return true;
        return false;
    }
};

#endif