#ifndef GAVIN_MYQUEUE_H
#define GAVIN_MYQUEUE_H

#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
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

    Queue(){
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }

    Queue(const Queue<T>& copyMe){
        _size = copyMe._size;
        _rear = _copy_list(_front,copyMe._front);
    }
    ~Queue(){
        _front = _clear_all(_front);
    }
    Queue& operator=(const Queue<T>& RHS){
        if (&RHS == this) return *this;
        _front = _clear_all(_front);
        _size = RHS._size;
        _rear = _copy_list(_front,RHS._front);
        return *this;
    }

    bool empty(){
        return !(_front);
    }

    T front(){
        assert(_front&&"front() called on empty list");
        return _front->_item;
    }
    T back(){
        assert(_rear&&"back() called on empty list");
        return _rear->_item;
    }

    void push(T item){
        _size++;
        _rear = _insert_after(_front,_rear,item);
        //if _rear == nullptr(_front == nullptr)
        /*From _insert_after()
        ...
        if (after_this == nullptr){
        head = _insert_head(head,insert_this);
        return head;
        }
        ...
        sets head (_front in this case) as the return value of _insert_head(which is head)
        after the fucntion call, _rear is set as return value, which is head

        For general cases, where _front is not empty,
        _rear will be the inserted node, which is the last node every time.
        */
    }
    T pop(){
        assert(_front&&"pop() called on empty list");
        _size--;
        T temp = _front->_item;
        _front = _remove_head(_front);
        if (_front == nullptr) _rear = nullptr;//this prevents hanging pointer.
        return temp;
    }

    Iterator begin() const{
        return Iterator(_front);
    }            //Iterator to the head node
    Iterator end() const{
        return Iterator();
    }              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        outs<<printMe._front;
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

#endif //GAVIN_MYQUEUE_H