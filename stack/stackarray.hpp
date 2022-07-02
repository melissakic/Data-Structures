#pragma once

template<typename T>
class stack{
    public:
    stack():ptr_{new T[2]},capacity_{2},size_{0},indeks_{0}{}
    ~stack(){delete ptr_;}
    void push(const T& element){
        if (++size_==capacity_)
        {
           capacity_*=1.5;
           auto temp=new T[capacity_];
           for (auto i = 0; i < size_-1; i++)
           {
               temp[i]=ptr_[i];
           }
           delete ptr_;
           ptr_=temp;
           temp=nullptr;
        }
        ptr_[indeks_]=element;
        indeks_++;
    }
    void pop(){
        indeks_--;
        size_--;
    }
    T& front(){
        return ptr_[indeks_-1];
    }
     private:
    T* ptr_;
    size_t capacity_;
    size_t size_;
    size_t indeks_;
};