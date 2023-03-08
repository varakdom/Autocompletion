/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Address
*/

#include "../include/Address.hpp"

std::string toLower(std::string str)
{
    std::string newstr(str);
    std::transform(newstr.begin(), newstr.end(), newstr.begin(), ::tolower);
    return newstr;
}

Address::Address(int streetNumber, std::string city, std::string streetName, std::string streetType, std::string _address)
{
    this->streetNumber = streetNumber;
    this->baseCity = city;
    this->baseStreetName = streetName;
    this->address = _address;

    city.erase(std::remove(city.begin(), city.end(), '\''), city.end());
    this->city = toLower(city);
    streetName.erase(std::remove(streetName.begin(), streetName.end(), '\''), streetName.end());
    this->streetName = toLower(streetName);

    if (streetType == "allée")
        this->streetType = Allee;
    else if (streetType == "avenue")
        this->streetType = Avenue;
    else if (streetType == "boulevard")
        this->streetType = Boulevard;
    else if (streetType == "chemin")
        this->streetType = Chemin;
    else if (streetType == "impasse")
        this->streetType = Impasse;
    else if (streetType == "place")
        this->streetType = Place;
    else if (streetType == "quai")
        this->streetType = Quai;
    else if (streetType == "rue")
        this->streetType = Rue;
    else if (streetType == "quai")
        this->streetType = Square;

    this->streetTypeStr = streetType;
}

Address::~Address()
{
}

std::ostream &operator<<(std::ostream &os, Address &addr)
{
    return os << addr.getaddress();
}