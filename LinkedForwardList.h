#ifndef LINKED_LIST_LINKEDFORWARDLIST_H
#define LINKED_LIST_LINKEDFORWARDLIST_H


#include <iostream>
#include <vector>


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

    int s = 0;
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
        return s == 0;
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
        s += 1;
    }


    void push_front(const T &x){
        pnode v = new node(x);
        v->r = head;
        head = v;
        if(tail == nullptr){
            tail = v;
        }
        s += 1;
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
        s += 1;
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
        s -= 1;
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
        s -= 1;
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
        s -= 1;
    }


    void erase(const T& x){
        int i = find(x);
        if(i != -1){
            pop_mid(i);
            s -= 1;
        }
    }


    T& operator[](int i){
        pnode v = get(i);
        if(v == nullptr){
            throw "ForwardListIndex out of range";
        }
        return v->x;
    }


    void push_back_node(pnode &v){
        if(tail != nullptr) {
            tail->r = v;
        }
        tail = v;
        if(head == nullptr){
            head = v;
        }
        s += 1;
    }


    void clear_without_delete(){
        head = tail = nullptr;
        s = 0;
    }


    LinkedForwardList merge(LinkedForwardList &a, LinkedForwardList &b){
        auto v1 = a.head;
        auto v2 = b.head;
        LinkedForwardList res;
        while(v1 != nullptr && v2 != nullptr){
            if(v1->x <= v2->x){
                res.push_back_node(v1);
                v1 = v1->r;
            }
            else{
                res.push_back_node(v2);
                v2 = v2->r;
            }
        }
        while(v1 != nullptr){
            res.push_back_node(v1);
            v1 = v1->r;
        }
        while(v2 != nullptr){
            res.push_back_node(v2);
            v2 = v2->r;
        }
        a.clear_without_delete();
        b.clear_without_delete();
        return res;
    }


    void sort(){
        if(empty()){
            return;
        }
        std::vector<LinkedForwardList> s;
        auto v = head;
        while(v != nullptr){
            s.push_back(LinkedForwardList());
            auto to = v->r;
            v->r = nullptr;
            s.back().push_back_node(v);
            while(s.size() > 1 && s.back().s >= s[s.size() - 2].s){
                auto f = merge(s.back(), s[s.size() - 2]);
                s.pop_back();
                s.pop_back();
                s.push_back(f);
            }
            v = to;
        }
        while(s.size() > 1){
            auto f = merge(s.back(), s[s.size() - 2]);
            s.pop_back();
            s.pop_back();
            s.push_back(f);
        }
        head = s[0].head;
        tail = s[0].tail;
        this->s = s[0].s;
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
