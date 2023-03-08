/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Choice
*/

#include "../include/Choice.hpp"
#include <iterator>


bool is_in_list(std::string str2, std::vector<std::pair<std::string, Street>> StreetNames)
{
    std::string str(toLower(str2));
    std::string tmp;

    for (auto const & s : StreetNames) {
        tmp = toLower(s.first);
        if (tmp.compare(str) == 0)
            return (true);
    }
    return (false);
}

std::vector<std::pair<std::string, Street>> init_streat_choice(std::vector<Address> adresses, std::string city)
{
    std::vector<std::pair<std::string, Street>> StreetNames;
    std::string line;

    for (auto& item : adresses) {
        std::istringstream name(item.getStreetName());

        while (getline(name, line, ' ')) {
            if (is_in_list(line, StreetNames) && toLower(item.getCity()).compare(toLower(city)) == 0) {
                for (auto &elem: StreetNames) {
                    if (elem.first.compare(line) == 0)
                        elem.second.addAddress(item);   
                }
            } else if (toLower(item.getCity()).compare(toLower(city)) == 0) {
                std::string str = toLower(line);
                StreetNames.push_back(std::make_pair(line, Street(str, item)));
            }
        }
    }

    return (StreetNames);
}

Choice::Choice(std::vector<std::pair<char, std::vector<Address>>> addresses)
{
    copy(addresses.begin(), addresses.end(), back_inserter(this->addresses));
    this->state = FirstChoice;
    this->nb_lettre = 0;
    this->selectedCity = "";
}

Choice::~Choice()
{
}

bool Choice::Selection(char character)
{
    lastQuery = query;


    if (this->state == FirstChoice) {
        for(auto& address : this->addresses) {
            if (character == address.first) {
                this->data = address.second;
                break;
            }
        }
        this->state = CityChoice;
        query += character;
        myquery = query;
        if (!data.empty()) {
            if (data.size() == 1){
                std::cout << "=> " << data.at(0) << std::endl;
                exit(0);
            }
        }
        lastResult = this->search(this);
        if (lastResult.size() == 1) {
            std::cout << "=> " << lastResult.at(0) << std::endl;
            exit(0);
        } else if (!lastResult.empty()) {
            nb_lettre++;
            return (true);
        }
    } else if (this->state == AddressChoice) {
        if (std::isdigit(character)) {
            for (auto &item: this->Address_to_choose) {
                if (item.first == character - 48) {
                    std::cout << "=> " << item.second << std::endl;
                    exit(0);
                }
            }
            return (false);
        } else {
            query += character;
            myquery = query;
            lastResult = this->search(this);
            if (lastResult.size() == 1) {
                std::cout << "=> " << lastResult.at(0) << std::endl;
                exit(0);
            } else if (!lastResult.empty()) {
                nb_lettre++;
                return (true);
            }
        }
    } else {
        query += character;
        myquery = query;
        lastResult = this->search(this);
        if (lastResult.size() == 1) {
            std::cout << "=> " << lastResult.at(0) << std::endl;
            exit(0);
        } else if (!lastResult.empty()) {
            nb_lettre++;
            return (true);
        }
    }
    return (false);
}

std::string Choice::getstatestr()
{
    switch(this->state)
    {
        case FirstChoice: return ("First Choice");
        case CityChoice: return ("City Choice");
        case CityNumberChoice: return ("City Number Choice");
        case AddressChoice: return ("Address Choice");
        case StreetChoice: return ("StreetChoice");
        case StreetNumberChoice: return ("Street Number Choice");
        default: return ("Unknown state");
    }
}


std::vector<std::pair<char , int>> Choice::sort(std::vector<char> ch)
{
    std::string s;
    int p[ch.size()];
    std::vector<std::pair<char, int>> results;

    for (int i = 0; i < ch.size(); i++){
        p[i] = 0;
    }
    for (auto &elem: ch) {
        s.push_back(elem);
    }
    for (int i = 0; i < ch.size(); i++) {
        for (auto &elem: StreetName) {
            if (s[i] == elem.first[nb_lettre])
                p[i]++;
        }
    }
    for (int i = 0; i < ch.size(); i++) {
        results.push_back(std::make_pair(s[i], p[i]));
    }
    std::sort(results.begin(), results.end(), charSort);
    return (results);
}

void Choice::print()
{
    int index = 0;

    if (this->state == FirstChoice) {
        std::sort(addresses.begin(), addresses.end(), addressesSort);
        for (auto &element : this->addresses) {
            if (index != 0 && index != 5)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << element.first << "}";
            index++;
        }
        std::cout << std::endl;
    } else if (this->state == CityChoice)  {
        std::vector<char> possibility = Possibility();
        for (auto &element : possibility) {
            if (index != 0 && index != 5)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << toUpper(query) << (char) std::tolower(element) << "}";
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == CityNumberChoice) 
    {
        std::sort(lastResult.begin(), lastResult.end(), addressSort);
        for (auto &address : lastResult) 
        {
            if (index != 0)
                std::cout << " ";
            std::cout << "{" << (index + 1) << " : " << toUpperQuery(address.getCity(), lastQuery) << "}";
            pos.push_back((char) (index + 49));
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == StreetChoice) 
    {
        if (query.compare("") != 0) {
            std::remove_if(this->StreetName.begin(), this->StreetName.end(), is_match2);
        }
        std::vector<char> possibility = Possibility();
        choices = this->sort(possibility);
        if (choices.size() == 1) {
            this->Selection((*possibility.begin()));
            this->print();
            return;
        }
        for (auto &element : choices) {
             if (index != 0 && index != 5)
                std::cout << " ";
            if (index == 5)
                break;
            std::cout << "{" << toUpper(selectedCity) << ", " << toUpper(query) << (char) std::tolower(element.first) << "}";
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == StreetNumberChoice) 
    {
        std::sort(lastResult.begin(), lastResult.end(), addressSort);
        for (auto &address : lastResult) 
        {
            if (index != 0)
                std::cout << " ";
            std::cout << "{" << (index + 1) << " : " << toUpper(address.getCity()) << ", " << address.getStreetNumber() << " " << toUpper(address.getStreetTypeStr()) << " " << toUpperQuery(address.getStreetName(), lastQuery) << "}";
            pos.push_back((char) (index + 49));
            index++;
        }
        std::cout << std::endl;
    }
    else if (this->state == AddressChoice) 
    {
        for (auto &elem: this->StreetName) {
            if (elem.first.compare(this->getSelectedStreet()) == 0) {
                elem.second.print();
            }
        }
    }
}

bool in_list(char c, std::vector<char> result)
{
    for (auto &element : result) {
        if (element == c)
            return (true);
    }
    return (false);
}

std::vector<char> Choice::Possibility()
{
    std::vector<char> result;

    if (this->state == CityChoice) {
        for (auto& item : lastResult) {
            if (!in_list(item.getCity()[nb_lettre], result))
                result.push_back(item.getCity()[nb_lettre]);
        }
        return (result);
    } else if (this->state == StreetChoice) {
        
        for (auto& item : StreetName) {
            if (!in_list(item.first[nb_lettre], result) || (query !=  "" && item.first[nb_lettre - 1] == query[nb_lettre - 1])) {
                result.push_back(item.first[nb_lettre]);
            }
        }
        return (result);
    }
    return (result);
}

std::string Choice::SelecteCity = "";
std::string Choice::myquery = "";

void Choice::chooseCity(std::string city)
{
    this->query = "";
    myquery = "";
    this->state = StreetChoice; 
    this->selectedCity = city;
    this->SelecteCity = city;
    this->nb_lettre = -1;

    std::remove_if(data.begin(), data.end(), is_match);
    for (auto &elem : data) {
        elem.setCity(toUpper(elem.getCity()));
    }
    StreetName = init_streat_choice(data, city);
}

void Choice::chooseStreet(std::string street)
{
    this->query = "";
    myquery = "";
    this->state = AddressChoice; 
    this->selectedStreet = street;
    this->nb_lettre = -1;
}