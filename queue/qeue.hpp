#pragma once
#include <iostream>

template<typename T>
class queue{
    public:
    queue():size_{0},begin_{nullptr}{};
    template<typename U>
    void push(U&&);
    void pop();
    T& front();
    ~queue();
    private:
    struct Node{
        Node* next_;
        T element_;
        Node(T element):element_{element},next_{nullptr}{}
    };
    size_t size_;
    Node* begin_;
    Node* end_;
};
template<typename T>
template<typename U>
void queue<T>::push(U&& element){
    if(size_==0){
    end_=begin_=new Node(std::forward<U>(element));
    ++size_;}else
    end_=end_->next_=new Node(std::forward<U>(element));++size_;
}

template<typename T>
T& queue<T>::front(){
    return begin_->element_;
}

template<typename T>
void queue<T>::pop(){
    if(size_==1){
        delete begin_;
        end_=begin_=nullptr;
        size_=0;
    }else{
    auto temp=begin_;
    begin_=begin_->next_;
    delete temp;
    --size_;}
}

template<typename T>
queue<T>::~queue(){
    auto temp=begin_;
    while (begin_)
    {
        temp=temp->next_;
        delete begin_;
        begin_=temp;
    }
    size_=0;
}
