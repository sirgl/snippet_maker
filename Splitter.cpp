//
// Created by roman on 16.05.17.
//

#include "Splitter.h"


Splitter::Splitter(std::istream &istream, vector<char> delimiters) : istream(istream), delimiters(delimiters) {

}

Splitter::iterator Splitter::begin() {
    iterator iterator1 = iterator(istream, false, delimiters);
    ++iterator1;
    return iterator1;
}

Splitter::iterator Splitter::end() {
    return Splitter::iterator(istream, true, delimiters);
}

vector<string> split(string str, vector<char> delimiters) {
    std::stringstream ss(str);
    Splitter splitter(ss, delimiters);
    vector<string> parts;
    for (auto &&part : splitter) {
        parts.push_back(part);
    }
    return parts;
}
