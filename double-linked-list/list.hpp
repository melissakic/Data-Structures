#include <iostream>

#include <initializer_list>
#pragma once

template <typename T>
class mojaLista {
  public:
  mojaLista():size_{0},head_{nullptr},tail_{nullptr}{}
  mojaLista(const mojaLista& other);
  mojaLista(std::initializer_list<T>);
  mojaLista(mojaLista&& other);
  mojaLista& operator=(const mojaLista& other);
  mojaLista& operator=(mojaLista&& other);
  bool operator==(const mojaLista&)const;
  bool operator!=(const mojaLista&)const;
  ~mojaLista();
  void clear();
  template<typename U>
  void push_back(U&& element);
  template<typename U>
  void push_front(U&& element);
  T& front();
  T& back();
  size_t size() const;
  bool empty() const;
  void pop_front();
  void pop_back();

  const T& at(size_t index) const;

  class iterator;
  
  iterator find(const T& element){
      auto p=head_;
      auto f=begin();
      while (p)
      {
        if (p->element_==element)
        {
          return (iterator)f;
        }
        p=p->ptrN_;
        ++f;
      }
      return (iterator)end();
  }

  iterator begin(){
    return (iterator)head_;
  }
  iterator end(){
    if (tail_->ptrN_==nullptr)
    {
     tail_->ptrN_=new Node(T{});
     tail_->ptrN_->ptrN_=nullptr;
     tail_->ptrN_->ptrP_=tail_;
    }
    return tail_->ptrN_;
  }

  void insert(iterator, const T&);
  void erase(iterator);
  void erase(iterator,iterator);
 
  private:
  struct Node{
      T element_;
      Node* ptrP_;
      Node* ptrN_;
      Node()=default;
      Node(const T& element):element_{element},ptrP_{nullptr},ptrN_{nullptr}{}
  };
  Node* head_;
  Node* tail_;
  size_t size_{0};
};

template<typename T>
mojaLista<T>::mojaLista(std::initializer_list<T> lista){
  for (auto& i:lista)
  {
    push_back(i);
  }
}

template<typename T>
 bool mojaLista<T>::operator==(const mojaLista<T>& other)const{
   if (size_==other.size_)
   {
     auto ptr=head_;
     auto ptr2=other.head_;
     while (ptr)
     {
       if (ptr->element_!=ptr2->element_)
       {
         return false;
       }
       ptr=ptr->ptrN_;
       ptr2=ptr2->ptrN_;
     }
     return true;
   }
   return false;
 }


template<typename T>
 bool mojaLista<T>::operator!=(const mojaLista<T>& other)const{
   if (size_==other.size_)
   {
     auto ptr=head_;
     auto ptr2=other.head_;
     while (ptr)
     {
       if (ptr->element_!=ptr2->element_)
       {
         return true;
       }
       ptr=ptr->ptrN_;
       ptr2=ptr2->ptrN_;
     }
     return false;
   }
   return true;
 }

template <typename T>
template<typename U>
void mojaLista<T>::push_back(U&& element) {
  if (size_!=0)
  {
    tail_->ptrN_=new Node(std::forward<U>(element));
     tail_->ptrN_->ptrP_=tail_;
     tail_->ptrN_->ptrN_=nullptr;
    tail_=tail_->ptrN_;
  }else{
      head_=new Node(std::forward<U>(element));
      tail_=head_;
      head_->ptrP_=head_;
      head_->ptrN_=nullptr;
  }
  ++size_;
}

template <typename T>
template<typename U>
void mojaLista<T>::push_front(U&& element) {
    if (size_!=0)
    {
        head_->ptrP_=new Node(std::forward<U>(element));
        head_->ptrP_->ptrN_=head_;
        head_=head_->ptrP_;
        head_->ptrP_=head_;
    }else{
      head_=new Node(std::forward<U>(element));
      tail_=head_;
      head_->ptrP_=head_;
      head_->ptrN_=nullptr;
    }
    ++size_;
}

template <typename T>
const T& mojaLista<T>::at(size_t index) const {
    if (size_==0)
    {
      throw std::out_of_range("mojaListaa je prazna");
    }
    if (index>=size_)
    {
      throw std::out_of_range("Nemoguce pristupiti zeljenom ideksu");
    }
    auto temp=head_;
    for (auto i = 0; i < index; i++)
    {
      temp=temp->ptrN_;
    }
    return temp->element_;
}

template <typename T>
size_t mojaLista<T>::size() const {
    return size_;
}

template <typename T>
bool mojaLista<T>::empty() const {
  return size_==0;
}

// template <typename T>
// void mojaLista<T>::push_back(T&& element) {
//   std::cout << "push_back T&&" << std::endl;
// }

// template <typename T>
// void mojaLista<T>::push_front(T&& element) {
//   std::cout << "push_front T&&" << std::endl;
// }

template <typename T>
mojaLista<T>::mojaLista(const mojaLista& other):size_{other.size_}{
  head_=new Node(other.head_->element_);
      tail_=head_;
      head_->ptrP_=head_;
      head_->ptrN_=nullptr;
      for (auto i = 1; i < other.size_; i++)
      {
        tail_->ptrN_=new Node(other.at(i));
        tail_->ptrN_->ptrP_=tail_;
        tail_->ptrN_->ptrN_=nullptr;
        tail_=tail_->ptrN_;
      }  
}

template <typename T>
mojaLista<T>::mojaLista(mojaLista&& other):size_{other.size_}{ 
  head_=other.head_;
  tail_=other.tail_;
  other.head_->ptrP_=head_;
  other.head_=nullptr;
  other.tail_=nullptr;
  other.size_=0;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(const mojaLista& other) {
  if (other.size_==0)
  {
   clear();
   return *this;
  }
  auto temp=head_;
  while (head_)
  {
    temp=temp->ptrN_;
    delete head_;
    head_=temp;
  }
  head_=new Node(other.head_->element_);
  tail_=head_;
  head_->ptrP_=head_;
  head_->ptrN_=nullptr;
    for (auto i = 1; i < other.size_; i++)
      {
        tail_->ptrN_=new Node(other.at(i));
        tail_->ptrN_->ptrP_=tail_;
        tail_->ptrN_->ptrN_=nullptr;
        tail_=tail_->ptrN_;
      }   
  size_=other.size_;
  return *this;
}

template <typename T>
mojaLista<T>& mojaLista<T>::operator=(mojaLista&& other) {
  if (other.size_==0)
  {
   clear();
   return *this;
  }
  auto temp=head_;
  while (head_)
  {
    temp=temp->ptrN_;
    delete head_;
    head_=temp;
  }
  head_=other.head_;
  tail_=other.tail_;
  other.head_->ptrP_=head_;
  other.head_=nullptr;
  other.tail_=nullptr;
  size_=other.size_;
  other.size_=0;
  return *this;
}

template <typename T>
mojaLista<T>::~mojaLista() {
    clear();
}

template <typename T>
void mojaLista<T>::clear() {
  auto temp=head_;
  while (head_)
  {
    temp=temp->ptrN_;
    delete head_;
    head_=temp;
  }
  size_=0;
  head_=nullptr;
  tail_=nullptr;
}
template<typename T>
T& mojaLista<T>::front(){
  return head_->element_;
}

template<typename T>
T& mojaLista<T>::back(){
  return tail_->element_;
}

template <typename T>
void mojaLista<T>::pop_front() {
  if (size_==0)
  {
    throw std::out_of_range("Nije moguce izbaciti iz prazne liste");
  }
  auto temp=head_;
  head_=head_->ptrN_;
  head_->ptrP_=head_;
  temp->ptrN_=temp->ptrP_=nullptr;
  delete temp;
  --size_;
  if(size_==0) tail_=nullptr;
}

template <typename T>
void mojaLista<T>::pop_back() {
  if (size_==0)
  {
    throw std::out_of_range("Nije moguce izbaciti iz prazne liste");
  }
  auto temp=tail_;
  tail_=tail_->ptrP_;
  tail_->ptrN_=temp->ptrN_;
  delete temp;
  --size_;
  if(size_==0) tail_=nullptr;
}


template <typename T>
class mojaLista<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  public:
  friend class mojaLista<T>;

  iterator(Node* p) : p_{p} {}

  iterator& operator++() {
    p_=p_->ptrN_;
    return *this;
  }

  iterator operator++(int) {
      auto temp=p_;
      p_=p_->ptrN_;
      return temp;
  }

  iterator& operator--() {
    p_=p_->ptrP_;
    return *this;
  }

  iterator operator--(int a) {
    auto temp=p_;
      p_=p_->ptrP_;
      return temp;
  }

  bool operator==(const iterator& other)const {
    return p_==other.p_; 
  }

  bool operator!=(const iterator& other)const { 
    return p_!=other.p_;
  }

  T& operator*() {
    return p_->element_;
  }

  T* operator->() {
   return &p_->element_; 
  }
  private:
  Node* p_;
};

template <typename T>
void mojaLista<T>::insert(iterator position, const T& element) {
  if (position==begin())
  {
    push_front(element);
  }else if(position==end()){
    push_back(element);
  }else{
  auto temp=position.p_->ptrP_;
  position.p_->ptrP_=new Node(element);
  temp->ptrN_=position.p_->ptrP_;
  position.p_->ptrP_->ptrN_=position.p_;
  position.p_->ptrP_->ptrP_=temp;
  ++size_;}
}

template <typename T>
void mojaLista<T>::erase(iterator position) {
  if (position==begin())
  {
    pop_front();
  }else if(position==end()){
    pop_back();
  }else{
    auto temp=position.p_->ptrP_;
    position.p_->ptrN_->ptrP_=temp;
    temp->ptrN_=position.p_->ptrN_;
    delete position.p_;
    --size_;
  }
  
}

template <typename T>
void mojaLista<T>::erase(iterator positionbegin,iterator positionend){
  if (positionbegin==begin() && positionend==end())
  {
    clear();
  }else{
    positionbegin.p_->ptrP_->ptrN_=positionend.p_->ptrN_;
    auto temp=positionbegin;
    while (temp!=positionend)
    {
      --size_;
      ++temp;
      delete positionbegin.p_;
      positionbegin=temp;
    }
    --size_;
    delete positionend.p_;
  }
  
}