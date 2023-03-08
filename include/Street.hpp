/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Street
*/
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <functional>
#include "Address.hpp"
#include "Choice.hpp"
#ifndef STREET_HPP_
#define STREET_HPP_

class Street {
    public:
        Street(std::string &, Address &);
        ~Street();
        void print();
        void addAddress(Address &);
        std::vector<Address> getAddresses() { return address; }
        std::string streetType(std::string &);
    protected:
        std::vector<Address> address;
        std::string streetName;
        std::string selectedStreet;
    private:
};

#endif /* !STREET_HPP_ */
