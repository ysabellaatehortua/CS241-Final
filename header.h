#include <iostream>
#include <map>
#include <string>
#include <array>

#ifndef HEADER_H_
#define HEADER_H_

using namespace std;
map<const string, int> createDict (std::string text);

void addWord(map<const string, int>& mapInput, string word);


#endif


