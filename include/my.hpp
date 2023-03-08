/*
** EPITECH PROJECT, 2022
** B-SYN-400-LIL-4-1-autoCompletion-dominique.kambale-baraka [WSL : Ubuntu]
** File description:
** my
*/

#ifndef MY_HPP_
#define MY_HPP_
#include <string.h>
#include <sstream>
#include <iostream>
#include <set>
#include <fstream>
#include <regex>
#include <vector>

bool equals_ignore_case(const std::string& a, const std::string& b);
bool stringncmp(const std::string& a, const std::string& b, size_t len);
bool stringncasecmp(const std::string& a, const std::string& b, size_t len);
std::string toUpper(std::string str);
std::string toLower(std::string str);
std::string toUpperQuery(std::string str, std::string query);
#endif /* !MY_HPP_ */
