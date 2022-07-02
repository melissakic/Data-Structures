#pragma once
#include <stack>
#include <queue>

template <typename T>
class Tree{

    struct Node
    {
        T value_;
        Node(T value):value_{value}{}
        Node* left_;
        Node* right_;
    };
    Node* root_=nullptr;    
    public:
    Tree():root_{nullptr}{};
    Tree(Tree&& other):root_{other.root_}{
        other.root_=nullptr;
    }
    Tree(const Tree& other){
       std::queue<Node*> buffer;
    buffer.push(other.root_);
    while (!buffer.empty()) {
      auto node = buffer.front();
      buffer.pop();
      insert(node->value_);
      if (node->left_) buffer.push(node->left_);
      if (node->right_) buffer.push(node->right_);
    }
    }

    Tree& operator=(const Tree& other){
        clear();
        Tree<T> temp=other;
        *this=std::move(temp);
        return *this; 
    }

    Tree& operator=(Tree&& other){
        clear();
        root_=other.root_;
        other.root_=nullptr;
        return *this;
    }


    static void preorder(Node* current){
        if(current==nullptr) return;
        std::cout << current->value_ <<" ";
        preorder(current->left_);
        preorder(current->right_);
    }

    static void inorder(Node* current){
        if(current==nullptr) return;
        inorder(current->left_);
        std::cout << current->value_ <<' ';
        inorder(current->right_);
    }

    static void postorder(Node* current){
        if(current==nullptr)return;
        postorder(current->left_);
        postorder(current->right_);
        std::cout << current->value_ << std::endl;
    }

  void preorder() {
    preorder(root_);
  }

  void inorder() {
    inorder(root_);
  }


  void postorder() {
    postorder(root_);
  }

    bool empty(){
        return root_==nullptr;
    }

    int depth(Node* current){
        if(current==nullptr) return 0;
        int desno=depth(current->right_);
        int lijevo=depth(current->left_);
        return 1+std::max(desno,lijevo);
    }

    T& operator[](T v){
        auto temp=find(v);
        if(find(v)!=nullptr){
            temp->value_=v;
            return temp->value_;
        }else{
            insert(v);
            return find(v)->value_;
        }
    }

    int depth() { return depthHelp(root_); }

    static int depthHelp(Node* current) {
    if (current == nullptr) return 0;
    int dubina_lijevo = depthHelp(current->left_);
    int dubina_desno = depthHelp(current->right_);
    return 1 + std::max(dubina_lijevo, dubina_desno);
  }
    static void clearHelper(Node*& current){
        if(current==nullptr) return;
        clearHelper(current->left_);
        clearHelper(current->right_);
        delete current;
        current=nullptr;
    }

  void clear(){clearHelper(root_);};


//rekurzivno
  static  void insertHelp(T v,Node* current){
        if(current->value_<v && current->right_==nullptr){
            current->right_=new Node(v);
        }else if(current->value_>v && current->left_==nullptr){
            current->left_=new Node(v);
        }
        else if(current->value_<v) {
            insertHelp(v,current->right_);
        }
          else  if(current->value_>v) insertHelp(v,current->left_);
    }


    void insert(T v){
        if(empty()){
            root_=new Node(v);
        }else{
            insertHelp(v,root_);
        }
        };

        // void insert(T v){
        //     if (empty())
        //     {
        //         root_=new Node(v);
        //     }else{
        //         Node* current=root_;
        //         while (1)
        //         {
        //             if(current->value_<v && current->right_==nullptr){
        //                 current->right_=new Node(v);
        //                 break;
        //             }else if(current->value_>v && current->left_==nullptr){
        //                 current->left_=new Node(v);
        //                 break;
        //             }else if(current->value_<v){
        //                 current=current->right_;
        //             }else {
        //                 current=current->left_;
        //             }
        //         }}}


    static Node* findHelper(T v,Node* current){
        if(current->value_==v) return current;
        else {
            if(current->value_<v && current->right_!=nullptr) return findHelper(v,current->right_);
            if(current->value_>v && current->left_!=nullptr) return findHelper(v,current->left_);
            else return nullptr;
        }
    }

    Node* find(T v){
        if(root_->value_==v) return root_;
        else{
          return findHelper(v,root_);
        }
    }


    // void erase(T v){
    //     Node* previous=nullptr;
    //     Node* current=root_;
    //     while ()
    //     {
    //         if(current->value_=v){
    //             if(previous==nullptr){
    //                 delete root_;
    //                 root_=nullptr;
    //             }else{
                    
    //             }
    //         }else if(current->value_<v){
    //             previous=current;
    //             current=current->right_;
    //         }else{
    //             previous=current;
    //             current=current->left_;
    //         }
    //     }
        
    // }
};