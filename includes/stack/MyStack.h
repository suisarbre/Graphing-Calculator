#ifndef GAVIN_MYSTACK_H
#define GAVIN_MYSTACK_H

#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = nullptr;}                    //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }
                                                    //Point Iterator to where p
                                                    //  is pointing to
        T &operator*(){
            assert(_ptr&&"Iterator::dereference on nullptr");
            return _ptr->_item;
        }                             //dereference operator

        T *operator->(){
            assert(_ptr&&"Iterator::Member accessed on nullptr");
            return &(_ptr->_item);
        }                            //member access operator
        bool is_null(){
            return !(_ptr);
        }                             //true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right){
            return !(left == right);
        } //true if left != right

        friend bool operator==(const Iterator &left, const Iterator &right){
            if (left._ptr == right._ptr) return true;
            return false;
        } //true if left == right

        Iterator &operator++(){
            assert(_ptr &&"Iterator ++(): called on nullptr");
            _ptr = _ptr->_next;
            return *this;
        }                         //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it, int unused){
            node<T>* temp = it._ptr;
            it._ptr=it._ptr->_next;
            assert(temp &&"Iterator ++(): called on nullptr");
            return Iterator(temp);
        }          //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack(){
        _top = nullptr;
        _size = 0;
    }
    Stack(const Stack<T>& copyMe){
        _top = _copy_list(copyMe._top);
        _size = copyMe._size;
    }
    ~Stack(){
        _top = _clear_all(_top);
    }
    Stack<T>& operator=(const Stack<T>& RHS){
        if (&RHS == this) return *this;
        _top = _clear_all(_top);
        _top = _copy_list(RHS._top);
        _size = RHS._size;
        return *this;
    }

    T top(){
        assert(_top&&"top() called on empty stack");
        return _top->_item;
    }
    bool empty(){
        return !(_top);
    }
    void push(T item){
        _size++;
        _top = _insert_head(_top,item);
    }

    T pop(){
        assert(_top&&"pop() called on empty stack");
        T temp = _top->_item;
        _top = _remove_head(_top);
        return temp;
    }
    // template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        outs<<printMe._top;
        return outs;
    }

    Iterator begin() const{
        return Iterator(_top);
    }              //Iterator to the head node
    Iterator end() const{
        return Iterator();
    }                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

#endif //GAVIN_MYSTACK_H