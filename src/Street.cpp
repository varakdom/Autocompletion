/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Street
*/

#include "../include/Street.hpp"

Street::Street(std::string &name, Address &elem) : streetName(name)
{
    this->address.push_back(elem);

}

std::string Street::streetType(std::string &type)
{
    int i = 0;

    for (auto &elem: this->address) {
        if (elem.getStreetTypeStr().compare(type) == 0)
            i++;
    }
    if (i == this->address.size()) {
        return (toUpper(type));
    }
    return (type);
}

void Street::print()
{
    int index = 0;
    std::string str;
    std::sort(address.begin(), address.end(), addressSort);
    for (auto &item : address) {
        if (index != 0)
            std::cout << " ";
        str = item.getStreetTypeStr();
        std::cout << "{" << (index + 1) << " : " << item.getCity() << ", " << item.getStreetNumber() << " " << this->streetType(str) << " " << toUpperQuery(item.getStreetName(), streetName) << "}";
        index++;
    }
    std::cout << std::endl;
}

void Street::addAddress(Address &addresses)
{
    this->address.push_back(addresses);
}

Street::~Street()
{
}
