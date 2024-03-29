#include <iostream>
using namespace std;


template <class T>
class Node{

    public:

    int number = 0;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;

    Node<T>(T n){
        number = n;
    }
};

template <class T>
class Bst{

    private:
        Node<T>* root = nullptr;

    public:

        Node<T>* parent = nullptr;

        Bst<T>(){};

        Bst<T>(const Bst& copy){

            if(!isEmpty()){
                destructor(root);
            }

            copy_constructor(copy.root);
           
        }

        void copy_constructor(Node<T>* temp){

            if(temp!=nullptr){

                add(temp->number);
                copy_constructor(temp->left);
                copy_constructor(temp->right);
            }
        }

        Bst(Bst&& second){

            this->root = second.root;
            second.root = nullptr;
            
        }

        
        ~Bst(){

            if(!isEmpty()){
                destructor(root);
            }
                  
        }

        void destructor(Node<T>* temp){
            if(temp!=nullptr){
               
                
                destructor(temp->left);
                destructor(temp->right);

                delete temp;
            }  
            
            root = nullptr;
        }

        bool isEmpty(){
            return root == nullptr;
        }

        void add(T x){
            add(x, root);
        }

        void add(T x, Node<T>* r){
            if(isEmpty()){
                root = new Node<T>(x);
            }else if(x > r->number){
                if(r->right == nullptr){
                    r->right = new Node<T>(x);
                    return;
                }
                add(x, r->right);
            }else if(x < r->number){
                if(r->left == nullptr){
                    r->left = new Node<T>(x);
                    return;
                }
                add(x, r->left);

            }
        }

        bool find(T n, bool b){
            if(find(n)!=nullptr){
                return true;
            }else{
                return false;
            }
        }

        Node<T>* find(T n){

            return find(n, root);
        }

        Node<T>* find(T n, Node<T>* temp){
            
            if(temp!=nullptr){
                if(temp -> number == n){
                    return temp;
                }

                if(n > temp->number){ 
                    parent = temp;       
                    return find(n, temp->right);

                }else{
                    parent = temp; 
                    return find(n, temp->left);
                }    
            }else{
                return nullptr;
            }
        }

        void del_leaf(Node<T>* deleted, Node<T>* find=nullptr){

            int num = deleted->number;

            if(deleted->number < parent->number){
                    parent->left = nullptr;
            }else{
                parent->right = nullptr;
            }

            if(find){
                find->number = num;  // then the deleted is leaf give argument only deleted 
            }
            
            delete deleted;
        }   

        void del(T x){

            Node<T>* finded = find(x);

            if(finded==nullptr){
                return;
            }

            if(finded->left!=nullptr){
                Node<T>* temp = finded->left;
                parent = finded;
                while(temp->right!=nullptr){
                    
                    temp = temp->right;
                }

                del_leaf(temp, finded); 

            }else if(finded->right!=nullptr){
                Node<T>* temp = finded->right;
                parent = finded;
                while(temp->left!=nullptr){
                    temp = temp->left;
                }

                del_leaf(temp, finded);
                
            }else if(finded->left==nullptr and finded->right==nullptr){
                if(finded != root){
                    del_leaf(finded);
                }else{
                    delete root;
                }   
            }
        }

        // ____________  print  ________________

        void print(){        
            print(root);
        }

        void print(Node<T>* temp){

            if(isEmpty()){
                cout << "Is empty! Nothing to print\n";
                return;
            }

            if(temp != nullptr){

                cout << temp -> number << "\t";  // print the sequence of function calls
                print(temp->left);
                print(temp->right);
            }
        }

        void print_AZ(Node<T>* temp = nullptr){

            if(isEmpty()){
                cout << "Is empty! Nothing to print\n";
                return;
            }

            if(temp == nullptr){            // first initialize for root
                temp = root;
            }

            if(temp->left == nullptr and temp->right == nullptr){   // stop the recursion function
                cout << temp -> number << "\t";  
            }else{
                print_AZ(temp -> left);
                cout << temp -> number << "\t";
                print_AZ(temp -> right);
            }
        }

        void print_ZA(Node<T>* temp = nullptr){

            if(isEmpty()){
                cout << "Is empty! Nothing to print\n";
                return;
            }

            if(temp == nullptr){            // first initialize for root
                temp = root;
            }

            if(temp->left == nullptr and temp->right == nullptr){   // stop the recursion function
                cout << temp -> number << "\t";  
            }else{
                print_ZA(temp->right);
                cout << temp -> number << "\t";  
                print_ZA(temp->left); 

            }           
        }


        //___________________ operators ________________

        Bst& operator=(const Bst& copy){

            if(!isEmpty()){
                destructor(root);
            }

            copy_constructor(copy.root);
            return *this;   
        }

        bool operator==(Bst& second){
            if(&second == this){
                return true;
            }

            return equals(root, second.root);
        }

        bool operator!=(Bst& second){
            if(this == &second){
                return false;
            } 

            return !equals(root, second.root);

            // return !(*this == second);  // call operator==
        }

        bool equals(Node<T>* self, Node<T>* second){


            if (self!=nullptr and second!=nullptr)      // when we have a Node for checking
            {
                if(self->number == second->number){     // when the numbers are equal, continue to check

                    bool left = equals(self->left, second->left);
    
                    bool right = equals(self->right, second->right);

                    return left and right; 

                }else{
                    return false;    // if the numbers not equal return false
                } 

            }else if (self==nullptr and second==nullptr){   // when we don't have Node for checking and not breaking the function with false
                return true;                                                                
            }else{
                return false;     // when the self = nullptr or second = nullptr
            }
           
        }
          
};

// int main(){

//     Bst<int> bst;

//     bst.add(50);
//     bst.add(100);
//     bst.add(30);
//     bst.add(40);
//     bst.add(10);
//     bst.add(90);
//     bst.add(200);
//     bst.add(9);
//     bst.add(15);
//     bst.add(35);
//     bst.add(45);
//     bst.add(70);
//     bst.add(95);
//     bst.add(150);
//     bst.add(250);
//     bst.add(145);
//     bst.add(160);
//     bst.add(11);
//     bst.add(16);
   

//     bst.print();

//     Bst<int> bst2 = std::move(bst);

//     // cout << "\n";
//     // bst.del(15);
//     cout <<"bst2 \n";
//     bst2.print();

//     cout <<"bst \n";
//     bst.print();


//     return 0;
// }

 /*
                       50
                
            30                    100

     10          40           90           200

 9     15      35   45    70    95    150     250
    11     16                      145     160

*/                    