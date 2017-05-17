//
// Created by roman on 16.05.17.
//

#ifndef UNTITLED_SENTENCE_H
#define UNTITLED_SENTENCE_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

struct Sentence {
    string text;
    unordered_map<string, int> wordToFrequency;

    Sentence(const string &text, const unordered_map<string, int> &wordToFrequency) : text(text), wordToFrequency(
            wordToFrequency) {}

    friend bool operator <(const Sentence& s1, const Sentence& s2) {
        return s1.text < s2.text;
    }

    int getWordFrequency(const string& word) const {
        auto iterator = wordToFrequency.find(word);
        return iterator == wordToFrequency.end() ? 0 : (*iterator).second;
    }
    
    int totalCount() {
        int sum = 0;
        for (auto &&wordToFreq : wordToFrequency) {
            sum += wordToFreq.second;
        }
        return sum;
    }
};


#endif //UNTITLED_SENTENCE_H
