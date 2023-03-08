/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Choice
*/

#ifndef CHOICE_HPP_
#define CHOICE_HPP_
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <functional>
#include "Street.hpp"
#include "Address.hpp"
typedef std::function<bool(std::pair<char, int>, std::pair<char, int>)> Comparator;

enum ProposalState { 
    FirstChoice,
    CityChoice,
    CityNumberChoice,
    StreetChoice,
    StreetNumberChoice,
    AddressChoice
};

class Choice {
    public:
        Choice(std::vector<std::pair<char, std::vector<Address>>> addresses);
        ~Choice();
        bool Selection(char character);
        void print();
        static std::vector<Address> search(Choice *proposals) {
            std::vector<Address> matching;
            if (proposals->getState() == CityChoice)
            {
                std::vector<std::string> cities;
                for (auto &address : proposals->getAddresses()) 
                {
                    std::string buffer;
                    std::stringstream stream(address.getCity());
                    while (stream >> buffer)
                    {
                        transform(buffer.begin(), buffer.end(), buffer.begin(),(int (*)(int))tolower);
                        if (stringncasecmp(buffer, proposals->getQuery(), proposals->getQuery().length())) {      
                            matching.push_back(address);
                            if(std::find(cities.begin(), cities.end(), toLower(address.getCity())) == cities.end())
                            {
                                cities.push_back(toLower(address.getCity()));
                            }
                            break;
                        }
                    }
                }
                if (cities.size() == 1)
                {
                    proposals->chooseCity(cities.at(0));
                    return proposals->search(proposals);
                }
            }
            else if (proposals->getState() == StreetChoice)
            {
                std::vector<std::string> streets;
                for (auto &address : proposals->getStreetName()) 
                {
                    std::string buffer;
                    std::stringstream stream(address.first);
                    while (stream >> buffer)
                    {
                        if (stringncasecmp(buffer, proposals->getQuery(), (proposals->getQuery()).length()) || proposals->getQuery() == "")
                        {
                            for (auto &elem : address.second.getAddresses())
                                matching.push_back(elem);
                            if(std::find(streets.begin(), streets.end(), address.first) == streets.end())
                            {
                                streets.push_back(address.first);
                            }
                            break;
                        }
                    }   
                }
                if (streets.size() == 1)
                {
                    proposals->chooseStreet(streets.at(0));
                    return proposals->search(proposals);
                }
            }
            else if (proposals->getState() == AddressChoice)
            {
                std::vector<std::string> streets;
                std::string buffer;
                int index = 1;
                for (auto &address : proposals->getStreetName()) 
                {   
                    if (equals_ignore_case(address.first, proposals->getSelectedStreet())) {
                        std::vector<Address> tmp = address.second.getAddresses();
                        std::sort(tmp.begin(), tmp.end(), addressSort);
                        for (auto &street : tmp) {
                            matching.push_back(street);
                            proposals->addAddress_to_choose(index, street);
                            index++;
                        }
                    }
                }
            }
            return (matching);
        };
        std::vector<char> Possibility();
        std::string getSelectedCity() { return this->selectedCity; }
        std::string getSelectedStreet() { return this->selectedStreet; }
        std::vector<std::pair<std::string, Street>> getStreetName() { return this->StreetName;}
        ProposalState getState() { return this->state; }
        std::vector<Address> getAddresses() { return this->data; }
        void chooseCity(std::string city);
        void chooseStreet(std::string street);
        static bool is_match(Address &a) {
            if (SelecteCity.compare(toLower(a.getCity())) != 0) {
                return (true);
            }
            return (false);
        }
        static bool is_match2(std::pair<std::string, Street> a) {
            if (!stringncmp(a.first, myquery, myquery.length())) {
                return (true);
            }
            return (false);
        }
        std::string getQuery() { return this->query; }
        std::string getLastQuery() { return this->lastQuery; }
        std::string getstatestr();
        void addAddress_to_choose(int i, Address &ad) { this->Address_to_choose.push_back(std::make_pair(i, ad)); }
        static std::string SelecteCity;
        static std::string myquery;
        std::vector<std::pair<char , int>> sort(std::vector<char>);
    protected:
    private:
        std::vector<std::pair<char, std::vector<Address>>> addresses;
        std::vector<std::pair<std::string, Street>> StreetName;
        std::vector< std::pair<int, Address>> Address_to_choose;
        std::vector<Address> lastResult;
        std::vector<Address> data;
        std::vector<char> pos;
        std::string query;
        std::string lastQuery;
        std::vector<std::pair<char , int>> choices;
        ProposalState state;
        std::string selectedCity;
        std::string selectedStreet;
        int nb_lettre;
};

struct {
    bool operator()(std::pair<char, std::vector<Address>> left, std::pair<char, std::vector<Address>> right) const
    {   
        return (left.second.size() > right.second.size());
    }   
} addressesSort;

struct {
    bool operator()(std::pair<char, int> left,  std::pair<char, int> right) const
    {   
        if (left.second == right.second)
            return (left.first > right.first);
        return (left.second > right.second);
    }   
} charSort;

#endif /* !CHOICE_HPP_ */
