#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

const int MINIMUM_CAPACITY = 3;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);

template<class T>
T* reallocate(T* a, int size, int capacity);

template<class T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout);

template <class T>
void print(T* a, int how_many, ostream& outs = cout);

template<class T>
T* search_entry(T* a, int size, const T& find_me);

template <class T>
int search(T* a, int size, const T& find_me);

template <class T>
void shift_left(T* a, int& size, int shift_here);

template <class T>
void shift_left(T* a, int& size, T* shift_here);

template <class T>
void shift_right(T *a, int &size, int shift_here);

template <class T>
void shift_right(T *a, int &size, T* shift_here);

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy);

template <class T>
T* copy_array(const T *src, int size);




template<class T>
T* allocate(int capacity){
    assert(capacity>=0);//Allowing capacity to be 0
    T* a = new T[capacity];//initializing
    return a;
}

template<class T>
T* reallocate(T* a, int size, int capacity){
    assert(size<=capacity&&"[size] has to be less than or equal to [capacity]");
    //making sure new capacity is greater than original size
    T* new_a = allocate<T>(capacity);//allocating new array
    copy_array(new_a,a,size);//copy original to new one
    delete[] a;//release the previous array
    a = nullptr;
    return new_a;//usage : a = reallocate(a,[size],[capacity])
}

template<class T>
void print_array(T* a, int size, int capacity, ostream& outs){
    print(a,size);
    outs<<"("<<size<<"/"<<capacity<<")"<<endl;//([size]/[capacity])
}



template <class T>
void print(T* a, int how_many, ostream& outs){
    assert(how_many>=0);
    if(how_many > 0){
        outs<<*a;
    }//preventing trailing comma
    for (int i =1; i<how_many;i++){
        T *walker = a + i;
        outs<<","<<*walker;
    }
}

template<class T>
T* search_entry(T* a, int size, const T& find_me){
    for (int i = 0;i<size;i++){
        T *walker = a + i;
        if (find_me == *walker) return walker;//when value has been found, return the address
    }
    return nullptr;//When the value DNE
}

template <class T>
int search(T* a, int size, const T& find_me){
        for (int i = 0;i<size;i++){
            T *walker = a + i;
            if (find_me == *walker)return i;
        }
    return -1;
}

template <class T>
void shift_left(T* a, int& size, int shift_idx){
    assert(shift_idx >= 0);
    assert(shift_idx < size);
    T* new_shift = a + shift_idx;
    shift_left(a,size,(T*) new_shift);
}

template <class T>
void shift_left(T* a, int& size, T* shift_here){
    assert((shift_here<(a + size)));
    assert(shift_here>=a);
    T *walker = shift_here;
    T *walker2 = shift_here +1;
    while (walker2 < a + size){
        *walker = *walker2;
        walker ++;
        walker2 ++;
    }
    size--;
}

template <class T>
void shift_right(T *a, int &size, int shift_idx){
    T* new_shift = a + shift_idx;
    shift_right(a,size,new_shift);
    
}

template <class T>
void shift_right(T *a, int &size, T* shift_here){
    assert(shift_here<(a+ size));
    assert(shift_here>=a);
    T *walker = a + size;
    T *walker2 = a + size-1;
    while(walker > shift_here){
        *walker = *walker2;
        walker--;
        walker2--;
    }
    size++;
}

template<class T>
void copy_array(T *dest, const T* src, 
                                int many_to_copy){
    T* destptr = dest;
    const T* srcptr = src;
    for (int i = 0; i < many_to_copy;i++){
        *destptr = *srcptr;
        destptr++;
        srcptr++;
    }
}

template <class T>
T* copy_array(const T *src, int size){
    T* new_a = allocate<T>(size);
    copy_array(new_a,src,size);
    return new_a;
}
template <class T>
T* resize (T* src,int old_index, int new_index){
    int new_size = new_index + 1;
    int old_size = old_index + 1;
    src = reallocate(src,old_size,new_size);
    fill((src + old_size),(src + new_size),T());
    return src;
}




#endif