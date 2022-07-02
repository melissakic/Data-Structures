#include <iostream>

template<typename T>
class forwards_lista{
    public:
    forwards_lista():size_{0},head_{nullptr},tail_{nullptr}{}
    forwards_lista(const forwards_lista&);
    forwards_lista(forwards_lista&& other);
    forwards_lista& operator=(const forwards_lista& other);
    forwards_lista& operator=(forwards_lista&& other);
    ~forwards_lista();

    size_t size()const{
      return size_;
    }

    class iterator;
    template<typename U>
    iterator find(U);
    iterator remove(iterator);
    void add(const T&);
    T at(int);
    iterator begin(){
    return head_;
    }
    iterator end(){
    return tail_->ptrN_;
    }

    private:
    struct Node{
      T element_;
      Node* ptrN_;
      Node()=default;
      Node(const T& element):element_{element},ptrN_{nullptr}{}
  };
  Node* head_;
  Node* tail_;
  size_t size_{0};
};

template<typename T>
forwards_lista<T>::~forwards_lista(){
 Node* temp;
    while (head_)
    {
    temp = head_->ptrN_;
    delete head_;
    head_ = temp;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out,forwards_lista<T>& lista){
  for (auto i = 0; i <  lista.size(); i++)
  {
    out<<lista.at(i)<<',';
  }
  return out;
}


template<typename T>
T forwards_lista<T>::at(int pozicija){
  if (pozicija==0)
  {
    return head_->element_;
  }
  auto temp=head_;
    for (auto i = 0; i < pozicija; i++)
    {
      temp=temp->ptrN_;
    }
    return temp->element_;
}

template<typename T>
void forwards_lista<T>::add(const T& element){
  if (size_==0)
  {
    head_=new Node(element);
    tail_=head_;
    head_->ptrN_=nullptr;
    ++size_;
  }else if(size_==1){
    head_->ptrN_=new Node(element);
    head_->ptrN_->ptrN_=nullptr;
    tail_=head_->ptrN_;
    if (head_->element_>element)
    {
      std::swap(head_->element_,tail_->element_);
    }
    ++size_;
  }else if(element<head_->element_){
        auto temp=head_->ptrN_;
        head_->ptrN_=new Node(element);
        head_->ptrN_->ptrN_=temp;
        std::swap(head_->element_,head_->ptrN_->element_);
        ++size_;
  }else{
    auto ptr=head_;
    while (ptr)
    {
      if (element>tail_->element_)
      {
        tail_->ptrN_=new Node(element);
        tail_->ptrN_->ptrN_=nullptr;
        tail_=tail_->ptrN_;
        ++size_;
        break;
      }
      if (element>ptr->element_ && element>=ptr->ptrN_->element_) 
      {
        ptr=ptr->ptrN_;
        continue;
      }
      auto temp=ptr->ptrN_;
      ptr->ptrN_=new Node(element);
      ptr->ptrN_->ptrN_=temp;
      ++size_;
      break;
    }
  }
  
}

template<typename T>
forwards_lista<T>::forwards_lista(forwards_lista&& other):size_{other.size_},head_{other.head_},tail_{other.tail_}{  
  other.head_=other.tail_=nullptr;
  other.size_=0;
}

template<typename T>
forwards_lista<T>::forwards_lista(const forwards_lista& other):size_{other.size_}{
    head_=new Node(other.head_->element_);
      tail_=head_;
      head_->ptrN_=nullptr;
      auto ptr=other.head_->ptrN_;
      for (auto i = 1; i < other.size_; i++)
      {
        tail_->ptrN_=new Node(ptr->element_);
        tail_->ptrN_->ptrN_=nullptr;
        tail_=tail_->ptrN_;
        ptr=ptr->ptrN_;
      }  
}

template<typename T>
forwards_lista<T>& forwards_lista<T>::operator=(const forwards_lista& other){
  if (other.size_==0)
  {
   Node* temp;
    while (head_)
    {
    temp = head_->ptrN_;
    delete head_;
    head_ = temp;
    }
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
  head_->ptrN_=nullptr;
  auto ptr=other.head_->ptrN_;
    for (auto i = 1; i < other.size_; i++)
      {
        tail_->ptrN_=new Node(ptr->element_);
        tail_->ptrN_->ptrN_=nullptr;
        tail_=tail_->ptrN_;
        ptr=ptr->ptrN_;
      }   
  size_=other.size_;
  return *this;
}

template <typename T>
forwards_lista<T>& forwards_lista<T>::operator=(forwards_lista&& other) {
  if (other.size_==0)
  {
    Node* temp;
    while (head_)
    {
    temp = head_->ptrN_;
    delete head_;
    head_ = temp;
    }
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
  other.head_=nullptr;
  other.tail_=nullptr;
  size_=other.size_;
  other.size_=0;
  return *this;
}

template<typename T>
class forwards_lista<T>::iterator : public std::iterator<std::forward_iterator_tag,T>{
  public:
  friend class forwards_lista<T>;

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
  bool operator==(const iterator& other) {
    return p_==other.p_; 
  }

  bool operator!=(const iterator& other) { 
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

template<typename T>
typename forwards_lista<T>::iterator forwards_lista<T>::remove(forwards_lista<T>::iterator position){
  if (position==begin())
  {
   auto temp=position.p_->ptrN_;
   delete position.p_;
   head_=temp;
   --size_;
   return begin();
  }else if(position==end()){
    auto temp=head_;
    while (temp->ptrN_!=tail_)
    {
      temp=temp->ptrN_;
    }
    temp->ptrN_=nullptr;
    delete tail_;
    tail_=temp;
    --size_;
    return end();
  }else{
    auto temp=head_;
    while (temp->ptrN_!=position.p_)
    {
      temp=temp->ptrN_;
    }
    auto iza=position.p_->ptrN_;
    temp->ptrN_=iza;
    delete position.p_;
    --size_;
    return temp->ptrN_;
  }
}


template<typename T>
template<typename U>
typename forwards_lista<T>::iterator forwards_lista<T>::find(U predicate){
  auto povratnik=begin();
  while (povratnik!=end())
  {
    if(predicate(povratnik.p_->element_)){
      return povratnik;
    }
    ++povratnik;
  }
  return end();
}