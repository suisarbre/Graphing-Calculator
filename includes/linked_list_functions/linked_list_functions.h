#ifndef GAVIN_LINKED_LIST_FUNCTIONS_H
#define GAVIN_LINKED_LIST_FUNCTIONS_H

#include "../node/node.h"

template<typename T>
ostream& operator<< (ostream& outs,node<T>* head){
    node<T>* walker = head;
    while (walker){
        outs<<*walker<<"->";
        walker = walker ->_next;
    }
    outs<<"|||";
    return outs;
}

template<typename T>
void _print_list(node<T>* head){
    cout<<head<<endl;
}

template <typename T>
node<T>* _where_this_goes(node<T>* head,const T& key, bool order){
    node<T>* walker = head;
    node<T>* prev = nullptr;
    if (walker == nullptr) return nullptr;

    if (order){//ascending
        while (walker && walker->_item < key) {
            prev = walker;
            walker = walker->_next;
        }

    } else { //descending
        while (walker && walker->_item > key) {
            prev = walker;
            walker = walker->_next;
        }
    }
    return prev;
}

template <typename T>
void _print_list_backwards(node<T>* head){
    //check for bottom condition(such as next is nullptr or something like that)
    //if it's met, do nothing(stop the recursion)
    //call _print_list_backwards with head->next
    //print out current node
    
    if(!head) return;//edge case for nullptr
    if(head->_next == nullptr){
        cout<<*head;
        return;
    }
    _print_list_backwards(head->_next);
    cout<<*head;
}

template<typename T>
node<T>* _search_list(node<T>* head, const T& key){
    node<T>* walker = head;
    while (walker){
        if (walker->_item == key) return walker;
        walker= walker->_next;
    }
    return nullptr;
}

template<typename T>
node<T>* _insert_after(node<T>*& head, node<T>* after_this, T insert_this){
    if (after_this == nullptr){
        head = _insert_head(head,insert_this);
        return head;
    }
    node<T>* temp = new node<T>(insert_this);//create new node that points
    //to the same place as after_this->next
    temp->_next =after_this->_next;
    after_this->_next = temp;//change after_this -> next to the new node
    return temp;//return the inserted node
}

template<typename T>
node<T>* _insert_head(node<T>*& head, T insert_this){
    node<T>* new_head = new node<T>(insert_this,head);
    return new_head;
}

template<typename T>
node<T>* _remove_head(node<T>*& head){
    assert(head && "_remove_head: cannot remove from empty list.");
    if (head->_next == nullptr){
        delete head;
        return nullptr;
        }//if next is nullptr(meaning single node), free that node and return nullptr
    node<T>* temp = head;//for delete
    head = head->_next;//walks forward
    delete temp;//free up the node
    return head;
}

template<typename T>
node<T>* _previous_node(node<T>* head,node<T>* before_this){
    /*
        if _headptr == before_this:
            return nullptr;
        else
            return pointer to the node prvious to before_this
    
    */
   if (!head ||!before_this) return nullptr;
   if (head == before_this) return nullptr;
    node<T>* p = head;
    while(p->_next != before_this){
        p = p->_next;
        assert(p->_next && "_previous_node(): before_this is not in the list");
    }
    return p;
}

template<typename T>
node<T>* _insert_before(node<T>*& head,node<T>* before_this,T insert_this){
    node<T>* after_this = _previous_node(head,before_this);
    if (after_this == nullptr) {
        head = _insert_head(head,insert_this);
        return head;
        }

    /*
        if after_this is nullptr:
            insert _head
        else
            insert after.
    
    */
    return _insert_after(head,after_this,insert_this);
}

template<typename T>
T _delete_node(node<T>* _head, node<T>* delete_this){
    assert(_head && delete_this && "_delete_node(): Empty list or null node.");
    T res = delete_this->_item;
    node<T>* before = _previous_node(_head,delete_this);
    if (before) before->_next = delete_this->_next;
    else _head = _remove_head(_head);
    delete delete_this;
    delete_this = nullptr;
    return res;
}

template <typename T>
node<T>* _copy_list(node<T>*& dest, node<T>* src){
    //Assuming dest is empty? (dest = nullprt)
    if(!src) return nullptr;
    dest = new node<T>(src->_item);
    node<T>* destwalker = dest;
    //holder
    node<T>* srcwalker = src->_next;
    while(srcwalker){
        destwalker->_next = new node<T>(srcwalker->_item);
        destwalker= destwalker->_next;
        srcwalker = srcwalker->_next;
    }
    return destwalker;
    //returning the last node
}

template<typename T>
node<T>* _copy_list(node<T>*src){
    node<T>* res = nullptr;
    _copy_list(res,src);
    return res;
}

template<typename T>
T& _at(node<T>* _head, int index){
    node<T>* walker = _head;
    while(index){
        assert(walker && "_at(): index larger than list size.");
        walker = walker->_next;
        index--;
    }
    return walker->_item;
}

template<typename T>
node<T>* _clear_all(node<T>* _head){
    while(_head) _head = _remove_head(_head);//while p exists (or p is not nullptr) call _remove__head(p)
    return nullptr;//p should be clean so return nullptr;
}
#endif //GAVIN_LINKED_LIST_FUNCTIONS_H