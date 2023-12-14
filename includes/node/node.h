#ifndef GAVIN_NODE_H
#define GAVIN_NODE_H


#include <iostream>
#include <assert.h>
using namespace std;

template <typename T>
struct node{
    T _item;
    node* _next;
    node(const T& item = T(), node* next = nullptr): _item(item),_next(next){
        //blank
    }
    friend ostream& operator << (ostream& outs, const node<T> &p){
        outs<<"["<<p._item<<"]";
        return outs;
    }
};

#endif //GAVIN_NODE_H