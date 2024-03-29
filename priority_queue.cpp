#include <iostream>
#include "rectangle.cpp"
using namespace std;

template <class V>
class Node{

    public:
        V value;
        Node<V>* previous = nullptr;
        Node<V>* next = nullptr;

        Node<V>(V n){
            value = n;
        }
};

template <class V>
class Priority_queue{

    public:
       
        Comparator<V>* comparator;

        Priority_queue(Comparator<V>* c){
            this->comparator = c;
        }

        Priority_queue(const Priority_queue& copy_list){

            // cout << "copy constructor \n";
            
            if(!isEmpty()){
                while (head!=tail){
                    head = head -> next;
                    delete head -> previous;
                }
                delete head;
            }

            Node<V>* h = copy_list.head;
            while (h!=nullptr){
                push_back(h -> value);
                h = h -> next;
            }
        }

               
        ~Priority_queue(){
            // cout << "destructor \n";

            if(!isEmpty()){
                while (head!=tail){
                    head = head -> next;
                    delete head -> previous;
                }
                delete head;
            }
        }

        //------------------operator-------------------------
        
        bool operator==(Priority_queue& second){
            if(len  != second.getLen()){
                return false;
            }

            if(&second == this){
                return true;
            }

            Node<V>* temp1 = head;
            Node<V>* temp2 = second.head;
            for(int i = 0; i < len; i++){

                if(comparator->compare(temp1->value, temp2->value) != 0){
                    //temp1 -> value != temp2->value){  
                    return false;
                }
                temp1 = temp1 -> next;
                temp2 = temp2 -> next;

            }
            return true;
        }

        Priority_queue& operator=(const Priority_queue& copy_list){

            
            if(!isEmpty()){
                while (head!=tail){
                    head = head -> next;
                    delete head -> previous;
                }
                delete head;
                head = tail = nullptr;
            }
            
            Node<V>* h = copy_list.head;
            while (h!=nullptr){
                push_back(h -> value);
                h = h -> next;
            }
            return *this;
        }

        int operator[](int n){
            if(n > len - 1){
                // cout << " WARNING!!!   segmentation fault :( \n"; 
                return -1;
            }

            Node<V>* node = getNode(n);

            return node -> value;

        }

        friend ostream& operator<<(ostream& print, const Priority_queue& pq){
            cout << "\n operator<< Print in priority queue \n\n";
                        
            for(auto h = pq.head; h != nullptr; h = h -> next){
                // cout << "value = " << h -> value << "\t";
                cout << h -> value << endl;
                
            } 

            cout << endl << endl;  
            return print; 
        }

    private:

        Node<V>* head = nullptr;
        Node<V>* tail = nullptr;
        int len = 0;

        bool isEmpty(){
            return head == nullptr;
        }

        //-----------back---------------
        void push_back(V n){
            Node<V>* temp = new Node<V>(n);
            if(isEmpty()){
                // cout << "push back is empty \n\n"; 
                head = tail = temp;
            }else{
                tail -> next = temp;
                temp -> previous = tail;
                tail = temp;
            }
            len++;
        }

        Node<V> pop_back(){
            if(isEmpty()){
                // cout << "pop back is empty \n"; 
                return -1;
            }
    
            // int res = tail -> value;
            Node<V> res = *tail;
            len--;
            if(tail != head){  
                
                tail = tail -> previous; 
                delete tail -> next;  
                tail -> next = nullptr; 
                
                return res;
            }

            delete tail;
            tail = head = nullptr;
            
            return res; 
        }

        //-----------------front------------------------
        void push_front(V n){
            Node<V>* temp = new Node<V>(n);
            if(isEmpty()){
                // cout << "push front is empty \n"; 
                head = tail = temp;
            }else{
                head -> previous = temp;
                temp -> next = head;
                head = temp;
            }

            len++;
        }

        Node<V> pop_front(){
            if(isEmpty()){
                // cout << "pop front is empty \n"; 
                return -1;
            }

            // int res = head -> value;
            Node<V> res = *head;
            len--;

            if(head != tail){  
                
                head = head -> next;  
                delete head -> previous;
                head -> previous = nullptr;
                return res;
            }

            delete head;
            tail = head = nullptr;
            
            return res;
        }

        //--------------- insert --------------------
        void insert(V n, int index){

            Node<V>* node = getNode(index);
            Node<V>* addedNode = new Node<V>(n);
            if(index == 0){
                push_front(n);
            }else if(index == len + 1){
                push_back(n);
            }else{
                addedNode -> previous = node -> previous;
                addedNode -> next = node; 
                node -> previous -> next = addedNode; 
                node -> previous = addedNode;
                len++; 
            }
        }

        bool find(V x){
            Node<V>* node = head;

            while (node != nullptr){
            if(comparator->compare(x, node -> value) == 0){
                    return true;
                }
                node = node -> next;
            }
            
            return false;
        }

    public:

        void add(V n, bool reverse = false){

            if(isEmpty()){
                push_back(n);
                return;
            }

            if(!reverse){
                if(comparator->compare(n, head->value) != 1){
                    // n <= head->value){

                    push_front(n);

                }else if(comparator->compare(n, tail->value) != -1){
                    //n >= tail->value){

                    push_back(n);

                }else{

                    Node<V>* node = head;
                    Node<V>* addedNode = new Node<V>(n);

                    while (comparator->compare(n, node->value) == 1){
                        //n > node->value){
                        node = node->next;
                    }
                    
                    addedNode -> next = node; 
                    addedNode -> previous = node->previous;
                    node -> previous -> next = addedNode; 
                    node -> previous = addedNode; 

                    len++;
                    return;
                }
                
            }else{
                if(comparator->compare(n, head->value) !=-1){
                    //n >= head->value){

                    push_front(n);

                }else if(comparator->compare(n, tail->value) != 1){
                    //n <= tail->value){

                    push_back(n);

                }else{

                    Node<V>* node = head;
                    Node<V>* addedNode = new Node<V>(n);

                    while (comparator->compare(n, node->value) == -1){
                        //n < node->value){
                        node = node->next;
                    }
                    
                    addedNode -> next = node; 
                    addedNode -> previous = node->previous;
                    node -> previous -> next = addedNode; 
                    node -> previous = addedNode; 

                    len++;
                    return;
                }
            }
        }

        //----------------print-------------------

        void print_reverse(){
            cout << "\nPrint reverse!!!! \n\n";
            
            for(auto t = tail; t != nullptr; t = t -> previous){
                cout << "value = " << t -> value << "\t";
            }   

            cout << endl << endl;    
        }

        //-----------get-------------------------
        

        int getLen(){
            return len;
        }

        Node<V>* getNode(V n){

            if(isEmpty()){
                cout << "nothing to return \n";
                return nullptr;
            }

            Node<V>* node = head;
            for(int i = 0; i < n; i++){
                node = node -> next;
            }

            return node;
        }       
};



int main(){


    SortByWidth width;
    SortByLength length;
    SortByArea area;
    SortByPerimeter perimeter;

    Priority_queue<Rectangle> pq(&width);

    pq.add(Rectangle(10, 100));
    pq.add(Rectangle(30, 500));
    pq.add(Rectangle(20, 200));
    pq.add(Rectangle(50, 550));
    pq.add(Rectangle(35, 350));
    pq.add(Rectangle(10, 80));
    pq.add(Rectangle(6, 50));
    pq.add(Rectangle(150, 230));
    pq.add(Rectangle(75, 400));
    pq.add(Rectangle(205, 45));

    // pq.add(10);
    // pq.add(0);
    // pq.add(50);
    // pq.add(5);
    // pq.add(5);
    // pq.add(25);

    // cout << "pq \n"; 
    cout << pq;

    // Priority_queue<char> pq1;

    // pq1.add('c');
    // pq1.add('d');
    // pq1.add('u');
    // pq1.add('a');
    // pq1.add('k');
    // pq1.add('x');
    // cout << "pq1 \n"; 
    // pq1.print();

    return 0;

}