//
// Created by roman on 16.05.17.
//

#ifndef UNTITLED_SPLITTER_H
#define UNTITLED_SPLITTER_H


#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

class Splitter {

public:
    Splitter(std::istream &istream, vector<char> delimiters);

    class iterator : public std::iterator<
            std::input_iterator_tag,
            string,
            vector<string>,
            const string *,
            const string &
    > {
    private:
        std::istream &istream;
        bool finished = false;
        string current;
        vector<char> delimiters;
    public:

        iterator(std::istream &istream, bool finished, vector<char> delimiters) : istream(istream),
                                                                                  finished(finished),
                                                                                  delimiters(delimiters) {}

        reference operator*() const {
            return current;
        }

        iterator &operator++() {
            string tmp;
            while (true) {
                char tmpCh = 0;
                if(!istream.get(tmpCh)) {
                    finished = true;
                    break;
                }
                bool foundDelimiter = false;
                for (auto &&delim : delimiters) {
                    if (delim == tmpCh) {
                        foundDelimiter = true;
                        break;
                    }
                }
                if (foundDelimiter) {
                    break;
                } else {
                    tmp.push_back(tmpCh);
                }
            }
            current = tmp;
            return *this;
        }

        iterator operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }


        bool operator==(iterator other) const {
            if (finished && other.finished && current == "" && other.current == "") {
                return true;
            } else {
                return other.current == current && finished == other.finished;
            }
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

    };

    iterator begin();

    iterator end();

private:
    std::istream &istream;
    vector<char> delimiters;
};


vector<string> split(string str, vector<char> delimiters);

#endif //UNTITLED_SPLITTER_H
