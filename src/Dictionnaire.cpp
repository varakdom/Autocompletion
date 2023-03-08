/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Dictionnaire
*/

#include "../include/Dictionnaire.hpp"



Dictionnaire::Dictionnaire(char *filename)
{
    std::ifstream input(filename);
    int a = 0;
    std::regex address_regex("^([\\w\\s]*), ([\\d]+) (impasse|quai|rue|square|allée|place|boulevard|rue|chemin|avenue) ([\\w\\s-zàâçéèêëîïôûùüÿñæœ']+)$");
    std::smatch matches;
    std::string alpha = "abcdefghijklmnopqrstuvwxyz";
    std::vector<std::string> str;
    std::string s;
    std::string temp = "";
    int alpha2[27];
    char c;

    if (!input) {
        fprintf(stderr, "Invalid argument\n");
        exit(84);
    }
    for (int i = 0; i < 27; i++)
        alpha2[i] = 0;
    for ( std::string line; getline(input, line);) {
        if (regex_search(line, matches, address_regex)) {
            Address *address = new Address(atoi(matches[2].str().c_str()), matches[1].str(), matches[4].str(), matches[3].str(), line);
            dico.push_back(*address);
            s = matches[1].str();
            for(int i = 0; i < s.length(); ++i){
                if(s[i]==' '){
                    str.push_back(temp);
                    temp = "";
                }
                else{
                    temp.push_back(s[i]);
                }
                
            }
            str.push_back(temp);
            for (auto &item : str) {
                if (alpha.find(::tolower(item[0])) != std::string::npos)
                    alpha2[alpha.find(::tolower(item[0]))] = alpha2[alpha.find(::tolower(item[0]))] + 1;
            }
            str.clear();
            temp = "";
        } else {
            fprintf(stderr, "%s\n",line.c_str());
            a++;
        }
    }
    if (dico.empty()) {
        fprintf(stderr, "Invalid argument\n");
        exit(84);
    }
    for (int i = 0; i < 27; i++) {
        std::vector<Address> address;
        if (alpha2[i] > 0) {
            for (auto &elem : dico) {
                s = elem.getCity();
                for(int i = 0; i < s.length(); ++i){
                    if(s[i]==' '){
                        str.push_back(temp);
                        temp = "";
                    }
                    else{
                        temp.push_back(s[i]);
                    }
                    
                }
                str.push_back(temp);
                for (auto &item: str) 
                    if (::tolower(item[0]) == alpha[i]) 
                        address.push_back(elem);
                str.clear();
                temp = "";
            }
            _dico.push_back(std::make_pair(alpha[i], address));
        }
    }
}

Dictionnaire::~Dictionnaire()
{
}

