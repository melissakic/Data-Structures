#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
public:
  MojVector():capacity_{2000},size_{0},arr_{new T[2000]}{
    for (auto i = 0; i < 2000; i++)
    {
      arr_[i]=T{};
    }
  };
  MojVector(const std::initializer_list<T> &);
  MojVector(const MojVector &);
  MojVector &operator=(const MojVector &);
  MojVector(MojVector &&);
  MojVector &operator=(MojVector &&);
  ~MojVector(){
    delete[] arr_;
  }

  MojVector &push_back(T);
  T &at(size_t) const;
  T &operator[](size_t) const;
  void clear();

  size_t size() const;
  bool empty() const;
  const T &back() const;
  const T &front() const;
  T &back();
  T &front();

  void resize(size_t);
  void realoc();

  MojVector &pop_back();
  size_t capacity() const;
  bool operator==(const MojVector &) const;
  bool operator!=(const MojVector &) const;

  class Iterator;

  Iterator begin() const{
    return arr_;
  }
  Iterator end() const{
    return arr_+size_;
  }
  Iterator find(const T &element) const{
    int a=0;
    auto c=begin();
    for (auto i = 0; i < size_; i++,++a)
    { 
      if (arr_[i]==element)
      {
        return c+a;
      }
    }
    return end();
  }

  MojVector& insert(Iterator it, T element){
    auto c=it-begin();
    if (size_==capacity_)
    {

  auto ptr=new T[size_*2+2];
  for (auto i = 0; i < size_; i++) {
    ptr[i]=arr_[i];
  }
  delete[] arr_;
  arr_=ptr;
  capacity_=size_*2+2;

    }
    it=begin()+c;
    if (it==end())
    {
      push_back(element);
      return *this;
    }
    ++size_;
    for (auto i = end()-1,j=end()-2; i !=it ; --i,--j)
    {
      *i=*j;
    }
    *it=element;
    return *this;
  }

  Iterator erase(Iterator pos){
    int c=pos-begin();
    if (pos==end() || pos<begin() || end()<pos)
    {
     throw std::out_of_range("Izvan granica");
    }
    for (auto i = pos+1; i <end() ; ++i,++pos)
    {
      *pos=*i;
     }
   --size_;
    return begin()+c;
  }


  Iterator erase(Iterator beginIt, Iterator endIt){
    auto c=beginIt-begin();
     auto temp=endIt;
      if (endIt==this->end())
      {
        temp=endIt;
      }
      auto temp2=beginIt;
      size_t a=temp-temp2;
      auto kraj=this->end()-1;
      while (temp<this->end())
      {
        *temp2=*temp;
        temp2++;
        temp++;
      }
      size_-=a;
      return begin()+c;
  }

private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};


//Konstrukutori
template<typename T>
MojVector<T>::MojVector(const std::initializer_list<T>& lista):capacity_{2000},size_{lista.size()},arr_{new T[2000]}{
  for (auto i = 0,j=lista.begin(); j < lista.end() ; ++i,++j)
  {
    arr_[i]=*j;
  }
}

template<typename T>
MojVector<T>::MojVector(const MojVector &prvi):capacity_{prvi.capacity_},size_{prvi.size_},arr_{new T[2000]}{
     for (auto i = 0; i < size_; ++i)
  {
    arr_[i]=prvi.arr_[i];
  }
}

template<typename T>
MojVector<T>::MojVector(MojVector && prvi):capacity_{prvi.capacity_},size_{prvi.size_},arr_{prvi.arr_}{
  prvi.arr_=nullptr;
  prvi.capacity_=0;
  prvi.size_=0;
}




//operatori
template<typename T>
MojVector<T>& MojVector<T>::operator=(const MojVector &prvi){
  capacity_=prvi.capacity_;
  size_=prvi.size_;
  delete[] arr_;
  arr_=new T[size_];
   for (auto i = 0; i < size_; ++i)
  {
    arr_[i]=prvi.arr_[i];
  }
  return *this;
}

template<typename T>
bool MojVector<T>::operator==(const MojVector &prvi) const{
  if (size_==prvi.size_ && capacity_==prvi.capacity_)
  {
    for (auto i = 0; i < size_; i++)
    {
      if (arr_[i]!=prvi[i])
      {
        return false;
      }
    }
    return true;
  }
  return false;
}

template<typename T>
bool MojVector<T>::operator!=(const MojVector &prvi) const{
  if (size_==prvi.size_ && capacity_==prvi.capacity_)
  {
    for (auto i = 0; i < size_; i++)
    {
      if (arr_[i]==prvi[i])
      {
        return false;
      }
    }
    return true;
  }
  return true;
}

template<typename T>
MojVector<T>& MojVector<T>::operator=(MojVector &&prvi){
  if (this==&prvi) return *this;
  delete[] arr_;
  capacity_=prvi.capacity_;
  size_=prvi.size_;
  arr_=prvi.arr_;
  prvi.arr_=nullptr;
  prvi.size_=0;
  prvi.capacity_=0;
  return *this;  
}

template<typename T>
T& MojVector<T>::operator[](size_t a) const{
  return arr_[a];
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &prvi){
  for (auto i = 0; i < prvi.size(); i++)
  {
    out<<prvi[i]<<' ';
  }
  return out;
}

//metode
template<typename T>
MojVector<T>& MojVector<T>::push_back(T value){
  if (size_ == capacity_) realoc();
  arr_[size_++] = value;
  return *this;
}

template<typename T>
void MojVector<T>::realoc() {
  T* tmp = new T[capacity_];
  std::copy(arr_, arr_ + size_, tmp);
  delete[] arr_;
  capacity_ *= 2;
  arr_ = new T[capacity_];
  std::copy(tmp, tmp + size_, arr_);
  delete[] tmp;
}

template<typename T>
size_t MojVector<T>::capacity() const{
  return capacity_;
}

template<typename T>
void MojVector<T>::resize(size_t value){
  if (size_>=value)
  {
    size_=value;
  }else{
  auto tmp = new T[capacity_];
  for (auto i = 0; i < value; i++)
  {
    tmp[i]=arr_[i];
    if (i>size_-1)
    {
      tmp[i]=T{};
    }
  }
  delete[] arr_;
  arr_ = tmp;
  size_ = value;
  }
}

template<typename T>
T& MojVector<T>::at(size_t value) const{
  if (value>=size_)
  {
    throw std::out_of_range("Nepostojeci index");
  }
  return arr_[value];
}

template<typename T>
bool MojVector<T>::empty() const{
  return size_==0;
}

template<typename T>
void MojVector<T>::clear(){
  size_=0;
}
template<typename T>
MojVector<T>& MojVector<T>::pop_back(){
  if (empty())
  {
    throw std::out_of_range("Prazan vektor");
  }
  --size_;
  return *this;
}

template<typename T>
size_t MojVector<T>::size() const{
  return size_;
}

template<typename T>
const T& MojVector<T>::back() const{
  return arr_[size_-1];
};

template<typename T>
const T& MojVector<T>::front() const{
  return arr_[0];
};

template<typename T>
T& MojVector<T>::back(){
  return arr_[size_-1];
};

template<typename T>
T& MojVector<T>::front(){
  return arr_[0];
};

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr);
  T &operator*() const;
  T *operator->() const;
  Iterator &operator++(){
    ++ptr_;
    return *this;
  }
  Iterator operator++(int){
    return ptr_++;
  }
  Iterator &operator--(){
    --ptr_;
    return *this;
  }
  Iterator operator--(int){
    return ptr_--;
  }
  Iterator operator+(size_t index){
    return ptr_+index;
  }
  Iterator operator-(size_t index){
    return ptr_-index;
  };
  size_t operator-(Iterator other){
    return  ptr_-other.ptr_;
  };

  bool operator==(const Iterator &it) const{
    return ptr_==it.ptr_;
  }
  bool operator!=(const Iterator &it) const{
    return ptr_!=it.ptr_;
  }
  bool operator<(const Iterator &it) const{
    return ptr_<it.ptr_;
  }

  ~Iterator()=default;

private:
  T *ptr_;
};

//iteratori

template<typename T>
MojVector<T>::Iterator::Iterator(T* ptr):ptr_{ptr}{};


template<typename T>
T& MojVector<T>::Iterator::operator*() const{
  return *ptr_;
};


template<typename T>
T* MojVector<T>::Iterator::operator->() const{
  return ptr_;
};

