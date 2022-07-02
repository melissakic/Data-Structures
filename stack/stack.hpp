#pragma once
#include <iostream>

template<typename T>
class Stack{
    public:
    Stack():size_{0},head_{nullptr}{};
    void pop();
    template<typename U>
    void push(U&&);
    T& back();
    size_t size()const;
    ~Stack();

    private:
    struct Node{
        Node* ptrN_;
        T element_;
        Node()=default;
        Node(const T& element):element_{element},ptrN_{nullptr}{}
    };
    Node* head_;
    size_t size_;
};

template<typename T>
template<typename U>
void Stack<T>::push(U&& element){
    if (size_==0)
    {
        head_=new Node(std::forward<U>(element));
        head_->ptrN_=nullptr;
        ++size_;
    }else{
        auto temp=head_;
        head_=new Node(std::forward<U>(element));;
        head_->ptrN_=temp;
        ++size_;
    }
}

template<typename T>
void Stack<T>::pop(){
    if (size_==1)
    {
        delete head_;
        head_=nullptr;
        --size_;
    }else if(size_>1){
        auto temp=head_->ptrN_;
        delete head_;
        head_=temp;
        --size_;
    }else{
        throw std::out_of_range("Nije moguce izbaciti iz praznog steka");
    }
}

template<typename T>
Stack<T>::~Stack(){
    auto temp=head_;
    while (head_)
    {
        temp=temp->ptrN_;
       delete head_;
       head_=temp;
    }
    size_=0;
    head_=nullptr;
}

template<typename T>
T& Stack<T>::back(){
    return head_->element_;
}

template<typename T>
size_t Stack<T>::size()const{
    return size_;
}

