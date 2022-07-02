#include "MojVektor.hpp"
#include <iostream>
#include <math.h>
#include <initializer_list>

class Clan{
  int koeficijent_{0};
  int stepen_{0};
  public:
  Clan()=default;
  Clan(int koeficijent,int stepen):koeficijent_{koeficijent},stepen_{stepen}{}
  friend std::ostream& operator<<(std::ostream&,const Clan&);
  friend std::istream& operator>>(std::istream&,const Clan&);
  bool operator==(const Clan& clan){
    return koeficijent_==clan.koeficijent_ && stepen_==clan.stepen_;
  }
  bool operator<(int a){
    return koeficijent_<a;
  }
  void SetKoeficijent(int a){
    koeficijent_=a;
  }
  int GetKoeficijent()const{
    return koeficijent_; 
    }
};

std::ostream& operator<<(std::ostream& out,const Clan& clan){
  if (clan.stepen_==0)
  {
    return out<<clan.koeficijent_;
  }else if(clan.stepen_==1){
    return out<<clan.koeficijent_<<"*X";
  }
  return out<<clan.koeficijent_<<"*X^"<<clan.stepen_;
}

class Polinom{
  MojVector<Clan> polinom;
  public:
  Polinom(int stepen){
   for (auto i = 0; i < stepen; i++)
   {
     polinom.push_back(Clan(i,i));
   }
  }
  Polinom(std::initializer_list<int> lista){
    int stepen=0;
    for (auto i = lista.begin(); i < lista.end(); i++)
    {
      polinom.push_back(Clan(*i,stepen));
      ++stepen;
    }
  }
  Polinom& operator=(const Polinom& prvi){
    polinom=prvi.polinom;
    return *this;
  }
  friend std::ostream& operator<<(std::ostream&,const Polinom&);
  friend std::istream& operator>>(std::istream&,const Polinom&);
  Polinom operator+(const Polinom& prvi)const{
    int a=0;
    if (polinom.size()>prvi.polinom.size())
    {
      a=polinom.size();
    }else{
      a=prvi.polinom.size();
    }
    Polinom temp(a);
    for (auto i = 0; i < a; ++i)
    {
      temp.polinom[i].SetKoeficijent(polinom[i].GetKoeficijent()+prvi.polinom[i].GetKoeficijent());
    }
    return temp;
  }
  Polinom operator*(const Polinom& prvi)const{
    int a=0,b=0;
    if (polinom.size()>prvi.polinom.size())
    {
      a=polinom.size();
    }else{
      a=prvi.polinom.size();
    }
    Polinom temp(a);
    for (auto i = 0; i < a; ++i)
    {
      if (polinom[i].GetKoeficijent()==0 || prvi.polinom[i].GetKoeficijent()==0)
      {
        b=i;
        break;
      }
      temp.polinom[i].SetKoeficijent(polinom[i].GetKoeficijent()*prvi.polinom[i].GetKoeficijent());
    }
    for (auto i = b; i < a; i++)
    {
     if (polinom.size()>prvi.polinom.size())
     {
       temp.polinom[i].SetKoeficijent(polinom[i].GetKoeficijent());
     }else{
        temp.polinom[i].SetKoeficijent(prvi.polinom[i].GetKoeficijent());
     }
    }
    return temp;
  }
  Polinom operator-(const Polinom& prvi)const{
    int a=0,b=0;
    if (polinom.size()>prvi.polinom.size())
    {
      a=polinom.size();
    }else{
      a=prvi.polinom.size();
    }
    Polinom temp(a);
    for (auto i = 0; i < a; ++i)
    {
      if (polinom[i].GetKoeficijent()==0 || prvi.polinom[i].GetKoeficijent()==0)
      {
        b=i;
        break;
      }
      temp.polinom[i].SetKoeficijent(polinom[i].GetKoeficijent()-prvi.polinom[i].GetKoeficijent());
    }
    for (auto i = b; i < a; i++)
    {
     if (polinom.size()>prvi.polinom.size())
     {
       temp.polinom[i].SetKoeficijent(polinom[i].GetKoeficijent());
     }else{
        temp.polinom[i].SetKoeficijent(prvi.polinom[i].GetKoeficijent());
     }
    }
    return temp;
  }
  double operator()(int)const;
  Polinom izvod()const;
  Polinom& operator+=(const Polinom&);
};

Polinom& Polinom::operator+=(const Polinom& prvi){
  int a=0;
    if (polinom.size()>prvi.polinom.size())
    {
      a=polinom.size();
    }else{
      a=prvi.polinom.size();
    }
    for (auto i = 0; i < a; ++i)
    {
    polinom[i].SetKoeficijent(polinom[i].GetKoeficijent()+prvi.polinom[i].GetKoeficijent());
    }
    return *this;
}

Polinom Polinom::izvod()const{
  Polinom temp(this->polinom.size()-1);
  for (auto i = 0; i < polinom.size(); i++)
  {
    temp.polinom[i].SetKoeficijent(polinom[i+1].GetKoeficijent()*(i+1));
  }
  return temp;
}

double Polinom::operator()(int broj)const{
  double rez=polinom[0].GetKoeficijent();
  for (auto i = 1; i < polinom.size(); i++)
  {
    rez+=polinom[i].GetKoeficijent()*std::pow(broj,i);
  }
  return rez;
}

std::ostream& operator<<(std::ostream& out,const Polinom& polinom){
  for (auto i:polinom.polinom)
  {
    if ( i== *(polinom.polinom.end()-1)){
      if (i<0)
      {
        out<<"( "<<i<<" )";
        return out;
      }
      out<<i;
      return out;
    }else if(i.GetKoeficijent()==0){
    }
    else if (i < 0)
    { 
      out<<"( "<<i<<" )"<<" + ";
    }else
    out<<i<<" + ";
  }
  return out;
}

std::istream& operator>>(std::istream& in,const Polinom& polinom){
    int c=0;
  for (auto& i:polinom.polinom)
  {
    in>>c;
    i.SetKoeficijent(c);
  }
  return in;
}

int main() {
Polinom p1({-1,2,4});   
Polinom p2(5);       
std::cin >> p2;     

std::cout << "P1(x): " << p1 << std::endl;
std::cout << "P2(x): " << p2 << std::endl;

 auto p3 = p1 * p2;
 auto p4 = p1 - p2;
 auto p5 = p1 + p2;

std::cout << "P3(x*): " << p3 << std::endl;
std::cout << "P4(x-): " << p4 << std::endl;
std::cout << "P5(x+): " << p5 << std::endl;

 double rezultat = p1(5);
 std::cout << "P1(5): " << rezultat << std::endl;

 p3 = p2.izvod();
 std::cout << "P2'(x): " << p3 << std::endl;

std::cout << "P2'(5): " << p3(5) << std::endl;

p2 += p1;
}
