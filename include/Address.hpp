/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Address
*/

#ifndef ADDRESS_HPP_
#define ADDRESS_HPP_
#include <iomanip>
#include "my.hpp"

enum StreetType { 
    Allee,
    Avenue,
    Boulevard,
    Chemin,
    Impasse,
    Place,
    Quai,
    Rue,
    Square 
};

class Address {
    public:
        Address(int streetNumber, std::string city, std::string streetName, std::string streetType, std::string _address);
        ~Address();
        std::string getCity() { return this->city; }
        int getStreetNumber() { return this->streetNumber; }
        std::string getStreetName() { return this->streetName; }
        StreetType getStreetType() { return this->streetType; }
        std::string getStreetTypeStr() { return this->streetTypeStr; }
        std::string getBaseCity() { return this->baseCity; }
        std::string getBaseStreetName() { return this->baseStreetName; }
        std::string getaddress() { return this->address; }
        void setCity(std::string city) { this->city = city;}
        void setStreetName(std::string _streetName) { this->streetName = _streetName ;}
        void setStreetType(std::string streetType) { this->streetTypeStr = streetType; }
    protected:
    private:
        std::string city;
        int streetNumber;
        std::string streetName;
        StreetType streetType;
        std::string baseCity;
        std::string baseStreetName;
        std::string streetTypeStr;
        std::string address;
};

std::ostream &operator<<(std::ostream &os, Address &m);


struct {
    bool operator()(Address left, Address right) const
    {   
        if (toLower(left.getCity()) == toLower(right.getCity())) {
            if (toLower(left.getStreetTypeStr()) == toLower(right.getStreetTypeStr())) {
                if (toLower(left.getStreetName()) == toLower(right.getStreetName())) 
                    return (left.getaddress() < right.getaddress());
                else
                    return (toLower(left.getStreetName()) > toLower(right.getStreetName()));
            } else
                return  (toLower(left.getStreetTypeStr()) > toLower(right.getStreetTypeStr()));
        } else
            return (toLower(left.getCity()) > toLower(right.getCity()));
    }   
} addressSort;

#endif /* !ADDRESS_HPP_ */
