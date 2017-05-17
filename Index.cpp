//
// Created by roman on 16.05.17.
//

#include "Index.h"

void Index::addSentence(Sentence sentence) {
    for (auto &&wordToFreq : sentence.wordToFrequency) {
        auto word = wordToFreq.first;
        wordDocumentFrequency[word]++;
        auto& sentences = wordToSentence[word];
        sentences.insert(new Sentence(sentence.text, sentence.wordToFrequency));
    }
    sentenceCount++;
}

long Index::getDocumentFrequency(const string &word) const {
    auto iterator = wordDocumentFrequency.find(word);
    if (iterator != wordDocumentFrequency.end()) {
        return (*iterator).second;
    }
    return 0;
}

set<Sentence *> Index::getSentences(const string &word) {
    auto iterator = wordToSentence.find(word);
    if (iterator != wordToSentence.end()) {
        return (*iterator).second;
    }
    return set<Sentence *>();
}

long Index::getTotalSentenceCount() {
    return sentenceCount;
}

Index::~Index() {
    for (auto &&wordToSent : wordToSentence) {
        auto sentences = wordToSent.second;
        for (auto &&sentence : sentences) {
            delete sentence;
        }
    }
}
