#include <iostream>
using namespace std;

class Node{

    public:
        int value;
        Node* previous = nullptr;
        Node* next = nullptr;

        Node(int n){
            value = n;
        }
};

class Queue{

    public:
        Node* head = nullptr;
        Node* tail = nullptr;

        ~Queue(){
            if(!isEmpty()){
                while (head!=tail){
                    head = head -> next;
                    delete head -> previous;
                }
                delete head;
            }
        }


        bool isEmpty(){
            return head == nullptr;
        }


        void push(int n){
            Node* temp = new Node(n);
            if(isEmpty()){
                cout << "stack is empty \n\n"; 
                head = tail = temp;
            }else{
                tail -> next = temp;
                temp -> previous = tail;
                tail = temp;
            }
        }

        int pop(){
            if(isEmpty()){
                
                throw 100;
            }

            int res = head -> value;
            if(head != tail){  
                
                head = head -> next;  
                delete head -> previous;
                head -> previous = nullptr;
                return res;
            }

            delete head;
            head = nullptr;
            return res;
        }

       
        //----------------print-------------------
        void print(){
            cout << "\nPrint result!!!! \n\n";
            
            if(isEmpty()){
                cout << "nothing to print \n";
                return;
            }
            
            for(Node* h = head; h != nullptr; h = h -> next){
                cout << "value = " << h -> value << "\t";
                
            } 

            cout << endl << endl;   
        }

};

int main(){

    Queue q;
    for(int i = 0; i < 5; i++){
        q.push(i);
    }

    // q.print();
    try{
        for(int i = 0; i < 6; i++){
            int res = q.pop();
            cout << "pop = " << res << endl;
        }
    }catch(int ex){
        if(ex == 100){
            cout << "stack is empty \n"; 
        }
    }
    

    return 0;
}