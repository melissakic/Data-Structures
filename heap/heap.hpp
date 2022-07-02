#pragma once
#include <iostream>
#include <math.h>

template<typename T>
class heap{
    T* array_;
    size_t size_;
    size_t capacity_;
    int min_;

    int find_parent(int position){
        return (position-1)/2;
    } 
    
    int find_left_cild(int position){
        return (position*2)+1;
    }
    int find_right_cild(int position){
        return find_left_cild(position)+1;
    }
    void create_heap(int child,int parent){
        if(array_[child]<=array_[parent]) return;
        if(array_[child]>array_[parent]) std::swap(array_[child],array_[parent]);
        create_heap(parent,find_parent(parent));
    }
    public:
    size_t size(){return size_;}
    heap():array_{new T[20]},size_{0},capacity_{20}{}
    heap(const heap& other):size_{other.size_},capacity_{other.capacity_*2}{
        array_=new T[capacity_];
        std::copy(other.array_,other.array_+size_,array_);
    }
    heap(heap&& other):size_{other.size_},capacity_{other.capacity_},array_{other.array_}{other.array_==nullptr;};
    heap& operator=(const heap& other){
        delete array_;
        array_=new T[other.capacity_];
        size_=other.size_;
        capacity_=other.capacity_;
        std::copy(other.array_,other.array_+size_,array_);
        return *this;
    }
    heap& operator=(heap&& other){
        delete array_;
        array_=other.array_;
        other.array_=nullptr;
        size_=other.size_;
        capacity_=other.capacity_;
        return *this;
    }
    ~heap(){ delete[] array_;}

    void realloc(){
        auto temp=new T[capacity_*2];
        std::copy(array_,array_+size_,temp);
        capacity_=capacity_*2;
        delete array_;
        array_=temp;
        temp=nullptr;
    }

    void insert(const T& element){
        if(size_==capacity_) realloc();
        if(size_==0){
            array_[size_++]=element;
            min_=0;
            return;}
        array_[size_++]=element;
        create_heap(size_-1,find_parent(size_-1));
    }

    const T& max(){
        return array_[0];
    }

    const T& min(){
        int last_row_position=std::pow(2,(int)log2(size_))-2;
        auto min=array_[last_row_position];
        min_=last_row_position;
        for (auto i = last_row_position; i < size_; i++)
        {
            if(array_[i]<min){
                min=array_[i];
                min_=i;
            }
        }
        return array_[min_];
    }

    void removeMin(){
        if (size_==0) return;
        std::swap(array_[min_],array_[size_-1]);
        size_--;
        create_heap(min_,find_parent(min_));
        min();
    }

    void removeMax(){
        if(size_==0) return;
        std::swap(array_[0],array_[size_-1]);
        size_--;
        for (auto i = 0; i < size_;)
        {
            if(find_left_cild(i)<size_ && array_[i]<array_[find_left_cild(i)]){
            auto temp=find_left_cild(i);
            if(find_right_cild(i)<size_ && array_[temp]<array_[find_right_cild(i)]) temp=find_right_cild(i);
            std::swap(array_[i],array_[temp]);
            i=temp;
            }else break;
        }
        
    }
    const T& operator[](int position){
        return array_[position];
    }

   std::ostream& process(std::ostream& out,int position){
        if(find_left_cild(position)<size_) process(out,find_left_cild(position));
        out << array_[position] <<",";
        if(find_right_cild(position)<size_) process(out,find_right_cild(position));
        return out;
    }    
};

template<typename T>
std::ostream& operator<<(std::ostream& out,heap<T> kontejner){
    kontejner.process(out,0);
    return out;
}