#ifndef LINKED_LIST_LINKEDFORWARDLIST_H
#define LINKED_LIST_LINKEDFORWARDLIST_H


#include <iostream>


template<class T>
class LinkedForwardList{
public:
    class node{
    public:
        typedef node* pnode;

        T x;
        pnode r = nullptr;

        node(const T &x) : x(x) {}
        node() : x(0) {}
    };

    typedef node* pnode;

    pnode head = nullptr;
    pnode tail = nullptr;

    pnode& get(int i){
        if(i == 0){
            return head;
        }
        pnode v = head;
        for(int j = 0; j < i - 1; ++j){
            if(v == nullptr || v->r == nullptr){
                throw "LinkedForwardList index out of range";
            }
            v = v->r;
        }
        return v->r;
    }


    int find(const T& x){
        pnode v = head;
        int c = 0;
        while(v != nullptr){
            if(v->x == x){
                return c;
            }
            ++c;
            v = v->r;
        }
        return -1;
    }


    bool empty(){
        return head == nullptr;
    }

    void push_back(const T &x){
        pnode v = new node(x);
        if(tail != nullptr) {
            tail->r = v;
        }
        tail = v;
        if(head == nullptr){
            head = v;
        }
    }


    void push_front(const T &x){
        pnode v = new node(x);
        v->r = head;
        head = v;
        if(tail == nullptr){
            tail = v;
        }
    }


    T& front(){
        if(empty()){
            throw "Can't get front element of an empty list";
        }
        return head->x;
    }


    T& back(){
        if(empty()){
            throw "Can't get back element of an empty list";
        }
        return tail->x;
    }


    void insert(int i, const T &x){
        pnode &plc = get(i);
        pnode r = plc;
        plc = new node(x);
        plc->r = r;
        if(tail == nullptr){
            tail = plc;
        }
        if(tail->r != nullptr){
            tail = tail->r;
        }
    }

    void pop_front(){
        if(empty()){
            throw "Can't delete element from an empty list";
        }
        auto v = head;
        head = head->r;
        if(head == nullptr){
            tail = nullptr;
        }
        delete v;
    }

    void pop_back(){
        if(empty()){
            throw "Can't delete element from an empty list";
        }
        if(head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        auto v = head;
        while(v->r != tail){
            v = v->r;
        }
        tail = v;
        delete v->r;
        v->r = nullptr;
    }


    void pop_mid(int i){
        if(i == 0){
            pop_front();
            return;
        }
        pnode v = get(i - 1);
        if(v == nullptr || v->r == nullptr){
            throw "LinkedForwardList index out of range";
        }
        if(v->r == tail){
            tail = v;
        }
        v->r = v->r->r;
    }


    void erase(const T& x){
        int i = find(x);
        if(i != -1){
            pop_mid(i);
        }
    }


    T& operator[](int i){
        pnode v = get(i);
        if(v == nullptr){
            throw "ForwardListIndex out of range";
        }
        return v->x;
    }

    template<class Type>
    friend std::ostream& operator<<(std::ostream &, LinkedForwardList<Type>&);
};


template<class T>
std::ostream& operator<<(std::ostream &out, LinkedForwardList<T>& lst){
    auto v = lst.head;
    while(v != nullptr) {
        out << v->x << " ";
        v = v->r;
    }
    return out;
}


#endif //LINKED_LIST_LINKEDFORWARDLIST_H
