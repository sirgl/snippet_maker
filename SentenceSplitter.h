//
// Created by roman on 16.05.17.
//

#ifndef UNTITLED_SENTENCESPLITTER_H
#define UNTITLED_SENTENCESPLITTER_H


#include <iterator>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "Sentence.h"
#include "Splitter.h"
#include "TrimUtils.h"

using std::string;
using std::vector;
using std::unordered_map;

class SentenceSplitter {
private:
    std::istream& istream;

    class iterator : public std::iterator<
            std::input_iterator_tag,
            Sentence,
            vector<Sentence>,
            const Sentence *,
            const Sentence &
    > {
    public:
        iterator(const Splitter::iterator &splitterIterator);

        iterator &operator++() {
            splitterIterator++;
            return *this;
        }

        iterator operator++(int) {
            iterator retval = *this;
            ++(*this);
            return retval;
        }

        bool operator==(iterator other) const {
            return this->splitterIterator == other.splitterIterator;
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

        Sentence operator*() const {
            string sentenceText = *splitterIterator;
            trim(sentenceText);
            auto ss = std::stringstream(sentenceText);
            Splitter splitter(ss, {' '});
            unordered_map<string, int> frequencies;
            for (auto word : splitter) {
                if(word == "") {
                    continue;
                }
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                frequencies[word]++;
            }
            return Sentence(sentenceText, frequencies);
        }

    private:
        Splitter::iterator splitterIterator;
    };

public:
    SentenceSplitter(std::istream &istream);

    iterator begin();
    iterator end();
};


#endif //UNTITLED_SENTENCESPLITTER_H
