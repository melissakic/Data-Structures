#pragma once
#include <list>

template<typename T>
class queue{
    public:
    T& front();
    void pop();
    template<typename U>
    void push(U&&);
    size_t size()const{
        return element_.size();
    }
    private:
    std::list<T> element_;
};

template<typename T>
T& queue<T>::front(){
    return element_.front();
}

template<typename T>
template<typename U>
void queue<T>::push(U&& element){
    element_.push_back(std::forward<U>(element));
}

template<typename T>
void queue<T>::pop(){
    element_.pop_front();
}

