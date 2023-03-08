/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** Dictionnaire
*/

#ifndef DICTIONNAIRE_HPP_
#define DICTIONNAIRE_HPP_
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include "Address.hpp"

class Dictionnaire {
    public:
        Dictionnaire(char *filename);
        ~Dictionnaire();
        std::vector<std::pair<char, std::vector<Address>>> getdico() { return _dico;};

    protected:
        std::vector<Address> dico;
        std::vector<std::pair<char, std::vector<Address>>> _dico;
    private:
};

#endif /* !DICTIONNAIRE_HPP_ */
