//
// Created by roman on 16.05.17.
//

#ifndef UNTITLED_SNIPPETMAKER_H
#define UNTITLED_SNIPPETMAKER_H


#include "Index.h"
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::string;

class SnippetMaker {

public:
    SnippetMaker(std::istream &istream);

    vector<string> getSnippetFragments(string query, unsigned fragmentCount);

private:
    std::istream &istream;
    Index index;

    vector<Sentence *> collectSentences(vector<string> &words);

    vector<double> calculateWordIdf(const vector<string> &words, long totalDocumentCount) const;

    double computeSentenceScore(const vector<string> &words, const vector<double> &wordIdf, Sentence *sentence) const;

    vector<double> computeSentenceScores(const vector<string> &words,
                                         const vector<Sentence *> &allSentences,
                                         const vector<double> &wordIdf) const;

    vector<Sentence *> getTopResults(const vector<Sentence *> &allSentences,
                                     const vector<double> &sentenceScores, unsigned count) const;

    vector<string> extractTopSentences(const vector<Sentence *> &top) const;

};


#endif //UNTITLED_SNIPPETMAKER_H
