#pragma once
#include <iostream>
#include <vector>

template <typename T>
class queue
{
public:
    queue(size_t kapacitet) : ptr_{new T[kapacitet]}, capacity_{kapacitet}, size_{0}, indeksout_{0}, indeksin_{0} {}
    ~queue() { delete ptr_; }
    queue(const queue &);
    queue(queue &&);
    size_t size() { return size_; }
    size_t capacity() { return capacity_; }
    bool empty() { return size_ == 0; }
    void realokacija();
    template <typename U>
    void push(U &&);
    T pop();
    T &front() { return ptr_[indeksout_]; }
    T &back() { return ptr_[indeksin_]; }
    const T &front() const { return ptr_[indeksout_]; }
    const T &back() const { return ptr_[indeksin_]; }
    T &operator[](int element)
    {
        return ptr_[element];
    }

private:
    T *ptr_;
    size_t capacity_;
    size_t size_;
    size_t indeksout_;
    size_t indeksin_;
};

template <typename T>
queue<T>::queue(const queue &other) : size_{other.size_}, capacity_{other.capacity_}, indeksin_{other.indeksin_}, indeksout_{other.indeksout_}
{
    ptr_=new T[other.capacity_];
    for (auto i = 0; i < other.capacity_; i++)
    {
        ptr_[i]=other.ptr_[i];
    }
}

template <typename T>
queue<T>::queue(queue&& other): size_{other.size_}, capacity_{other.capacity_}, indeksin_{other.indeksin_}, indeksout_{other.indeksout_}
{
    ptr_=other.ptr_;
    other.ptr_=nullptr;
}

template <typename T>
template <typename U>
void queue<T>::push(U &&element)
{
    if (size_ == 0 || indeksin_ == 0)
    {
        ptr_[0] = std::forward<U>(element);
        size_++;
        indeksin_++;
        return;
    }
    if (indeksin_ == capacity_)
        indeksin_ = 0;
    if (indeksin_ == indeksout_)
        realokacija();
    ptr_[indeksin_] = std::forward<U>(element);
    indeksin_++;
    size_++;
}

template <typename T>
T queue<T>::pop()
{
    auto temp = ptr_[indeksout_];
    if (indeksout_ == capacity_)
        indeksout_ = 0;
    if (indeksout_ == indeksin_)
    {
        indeksin_ = indeksout_ = 0;
        size_=0;
        return temp;
    }
    ptr_[indeksout_] = T{};
    ++indeksout_;
    --size_;
    return temp;
}

template <typename T>
void queue<T>::realokacija()
{
    auto c = capacity_;
    capacity_ *= 2;
    auto temp = new T[capacity_];
    for (auto i = 0; i <= indeksin_; i++)
    {
        temp[i] = ptr_[i];
    }
    indeksout_ = capacity_ - (c - indeksout_);
    for (auto i = indeksout_, j = indeksin_; i < capacity_; i++, j++)
    {
        temp[i] = ptr_[j];
    }
    delete ptr_;
    ptr_ = temp;
    temp = nullptr;
}