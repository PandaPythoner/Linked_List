#include <iostream>
#include <string>
#include "LinkedForwardList.h"


using namespace std;


int main() {
    LinkedForwardList<int> lst;
    while(true){
        try{
            string command;
            cin >> command;
            if(command == "empty"){
                cout << lst.empty() << "\n";
            }
            else if(command == "push_back"){
                int x;
                cin >> x;
                lst.push_back(x);
            }
            else if(command == "push_front"){
                int x;
                cin >> x;
                lst.push_front(x);
            }
            else if(command == "insert"){
                int i, x;
                cin >> i >> x;
                lst.insert(i, x);
            }
            else if(command == "pop_front"){
                lst.pop_front();
            }
            else if(command == "pop_back"){
                lst.pop_back();
            }
            else if(command == "pop_mid"){
                int i;
                cin >> i;
                lst.pop_mid(i);
            }
            else if(command == "erase"){
                int x;
                cin >> x;
                lst.erase(x);
            }
            else if(command == "find"){
                int x;
                cin >> x;
                cout << lst.find(x) << "\n";
            }
            else if(command == "index"){
                int i;
                cin >> i;
                cout << lst[i] << "\n";
            }
            else if(command == "sort"){
                lst.sort();
            }
        }
        catch(const char* x){
            cout << x << "\n";
            return 0;
        }
        cout << lst << "\n";
    }
    return 0;
}


/*
push_back 6
push_back 4
push_back 9
push_back 1
push_back 7
push_front 0
push_back 2
push_back 3
sort
 */