#pragma once
#include <iostream>
#include <queue>


struct stanje{
        int iznos_{0};
        std::string vrijeme_;
        stanje()=default;
        stanje(int novac,std::string vrijeme):iznos_{novac},vrijeme_{vrijeme}{}
        stanje& operator+(const stanje& other){
            iznos_=iznos_+other.iznos_;
            vrijeme_=other.vrijeme_;
            return *this;
        }
    };


class Banka
{
private:
    stanje racun;
    std::queue<stanje> transakcije;
public:
    void nova_transakcija();
    void potvrdi_transakciju();
    void trenutna_transakcija();
    void odbaci();
    void stanjeracuna();
};