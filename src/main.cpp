/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** main
*/

#include "../include/Dictionnaire.hpp"
#include "../include/Choice.hpp"
#include <exception>

bool equals_ignore_case(const std::string& a, const std::string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

bool stringncmp(const std::string& a, const std::string& b, size_t len)
{
    return strncmp(a.c_str(), b.c_str(), len) == 0;
}

bool stringncasecmp(const std::string& a, const std::string& b, size_t len)
{
    return strncasecmp(a.c_str(), b.c_str(), len) == 0;
}


std::string toUpper(std::string str)
{
    std::string newstr(str);
    std::transform(newstr.begin(), newstr.end(),newstr.begin(), ::toupper);
    return newstr;
}

std::string toUpperQuery(std::string str, std::string query)
{
    std::string newstr(str);
    int firstIndex = 0;
    int lastIndex = 0;
    firstIndex = newstr.find(query);
    lastIndex = newstr.find(" ", firstIndex);
    if (lastIndex == 0)
        lastIndex = newstr.size();
    newstr.replace(firstIndex, query.size() + firstIndex, toUpper(str.substr(firstIndex, lastIndex)));
    return newstr;
}


int main(int argc, char** argv)
{
    if (argc != 2)
        return (84);
    else {
        try {
                Dictionnaire *dico = new Dictionnaire(argv[1]);
                Choice *proposals = new Choice(dico->getdico());
                std::string line;
                proposals->print();    
                while (std::getline(std::cin, line))
                {
                    if (line.compare("ABORT") == 0)
                        return (84);
                    if (!proposals->Selection(std::tolower(line[0]))) {
                        fprintf(stderr, "Unknown address.\n");
                        return (84);
                    }
                    proposals->print();
                }
            } catch (std::exception &e) {
                exit(84);
            }
    }
    return (0);
}