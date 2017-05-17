//
// Created by roman on 16.05.17.
//

#ifndef UNTITLED_INDEX_H
#define UNTITLED_INDEX_H


#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "Sentence.h"

using std::string;
using std::vector;
using std::set;
using std::unordered_map;

class Index {
private:
    unordered_map<string, long> wordDocumentFrequency;
    unordered_map<string, set<Sentence*>> wordToSentence;
    long sentenceCount = 0;
public:
    void addSentence(Sentence sentence);
    long getDocumentFrequency(const string& word) const;
    set<Sentence*> getSentences(const string& word);
    long getTotalSentenceCount();

    virtual ~Index();
};


#endif //UNTITLED_INDEX_H
