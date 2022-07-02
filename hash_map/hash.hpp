#pragma once
#include <list>
#include <vector>

#define max_capacity 300

template <typename T>
int hash_function(T key)
{
    std::string temp{key};
    size_t sum = 0;
    for (auto i : temp)
    {
        sum += (i * 7413 << 2) | 0xf12cd1a;
    }
    return sum % max_capacity;
}

template <typename Key, typename U>
class UnorderedMap
{
    std::list<std::pair<Key, U>> *map;
    size_t size_;
    size_t capacity_;
    bool exists(int hash, Key key)
    {
        auto &lista = map[hash];
        for (auto i : lista)
        {
            if (i.first == key)
                return true;
        }
        return false;
    }
    U &find_in_bucket(int hash, Key key)
    {
        auto &lista = map[hash];
        for (auto &i : lista)
        {
            if (i.first == key)
                return i.second;
        }
        return lista.front().second;
    }
    U &add_in_bucket(int hash, Key key, U value = U{})
    {
        auto &lista = map[hash];
        lista.push_back({key, value});
        ++size_;
        return lista.back().second;
    }

    void pop_from_bucket(int hash, Key key)
    {
        auto &lista = map[hash];
        for (auto i = lista.begin(); i != lista.end(); i++)
        {
            if (i->first == key)
            {
                lista.erase(i);
                --size_;
                return;
            }
        }
    }

public:
    UnorderedMap() : size_{0}, capacity_{max_capacity}, map{new std::list<std::pair<Key, U>>[300]} {}
    ~UnorderedMap() { delete[] map; };
    size_t GetCapacity()
    {
        return capacity_;
    }

    // if element exist in map update its value otherwise make new element with given key
    U &operator[](Key key)
    {
        if (exists(hash_function(key), key))
            return find_in_bucket(hash_function(key), key);
        else
            return add_in_bucket(hash_function(key), key);
    }

    // return true if element is erased otherwise return false
    bool erase(Key key)
    {
        if (!exists(hash_function(key), key))
            return false;
        else
        {
            pop_from_bucket(hash_function(key), key);

            return true;
        }
    }

    // if element exists throw exepction otherwise add key,value pair in hash map
    void emplace(Key key, U value)
    {
        if (exists(hash_function(key), key))
            throw std::invalid_argument("Par vec postoji u mapi");
        else
        {
            add_in_bucket(hash_function(key), key, value);
        }
    }

    std::pair<Key, U> *getelement(U key)
    {
        auto &list = map[hash_function(key)];
        return &list.front();
    }


    class Iterator : public std::iterator<std::bidirectional_iterator_tag, U>
    {
        std::pair<Key, U> *ptr_;
        std::list<std::pair<Key, U>> *map_;

    public:
        Iterator(std::pair<Key, U> *ptr, std::list<std::pair<Key, U>> *map) : ptr_{ptr}, map_{map} {}
        ~Iterator() = default;

        std::pair<Key, U> &operator*()
        {
            if (&(map_[0].front()) == ptr_) ++(*this);
            return *ptr_;
        }
        std::pair<Key, U> *operator->()
        {
            if (&(map_[0].front()) == ptr_) ++(*this);
            return ptr_;
        }

        Iterator &operator++()
        {
            if (&(map_[0].front()) == ptr_)
            {
                for (auto i = 0; i < max_capacity; i++)
                {
                    if (map_[i].size() != 0)
                    {
                        ptr_ = &(map_[i].front());
                        return *this;
                    }
                }
                return *this;
            }

            auto hash = hash_function(ptr_->first);
            if (map_[hash].size() > 1)
            {
                for (auto i = map_[hash].begin(); i != map_[hash].end(); ++i)
                {
                    if (i->first == ptr_->first)
                    {
                        if (++i != map_[hash].end())
                        {
                            ptr_ = &(*i);
                            return *this;
                        }
                        else
                            --i;
                    }
                }
            }
            for (auto i = hash + 1; i < max_capacity; i++)
            {
                if (map_[i].size() != 0)
                {
                    ptr_ = &(map_[i].front());
                    return *this;
                }
                if(i==max_capacity-1){
                ptr_=&(map_[max_capacity-1].front());
                return *this;
                }
            }
            return *this;
        }

        Iterator operator++(int)
        {
            auto temp=*this;
            ++(*this);
            return temp;
        }
        Iterator& operator--(){
            if(&(map_[0].front())==ptr_) return (*this);
            if(&(map_[max_capacity-1].front())==ptr_){
                for (int i = max_capacity-1; i >=0; --i)
               {
                if (map_[i].size()!=0)
                {
                    ptr_=&map_[i].back();
                    return *this;
                }
               }
            }
            auto hash=hash_function(ptr_->first);
            if (map_[hash].size()==1 )
            {
               for (int i = hash-1; i >=0; --i)
               {
                if (map_[i].size()!=0)
                {
                    ptr_=&map_[i].back();
                    return *this;
                }
               }
            }
    
        for (auto i = map_[hash].begin(),update=i; i !=map_[hash].end(); i++)
        {
            if((++update)->first==ptr_->first){
                ptr_=&(*i);
                return *this;
                }
        }
        return *this;
        }
        Iterator operator--(int){
            auto temp=*this;
            --(*this);
            return temp;
        }

        bool operator!=(const Iterator& other){
            return ptr_!=other.ptr_;
        }
    };

    Iterator begin()
    {
        auto &list = map[0];
        return Iterator(&list.front(), map);
    }

     Iterator end(){
        auto& list=map[capacity_-1];
        return Iterator(&list.back(),map);
     }

     Iterator find(Key key){
        auto hash=hash_function(key);
        if(map[hash].size()==0) return end();
        if(map[hash].size()==1) return Iterator{&map[hash].front(),map};
        if(map[hash].size()>1){
            for (auto i = map[hash].begin(); i!=map[hash].end(); i++)
            {
                if(i->first==key) return Iterator{&(*i),map};
            }
            return end();
        }
        return end();
     }
};
