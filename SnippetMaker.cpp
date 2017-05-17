//
// Created by roman on 16.05.17.
//

#include "SnippetMaker.h"
#include "Splitter.h"
#include "SentenceSplitter.h"
#include <cmath>


SnippetMaker::SnippetMaker(std::istream &istream) : istream(istream) {
    SentenceSplitter splitter(istream);
    for (auto &&sentence : splitter) {
        if(sentence.text == "") {
            continue;
        }
        index.addSentence(sentence);
    }
}

vector<string> SnippetMaker::getSnippetFragments(string query, unsigned fragmentCount) {
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);
    auto words = split(query, {' ', ',', '.', '/', '\\', '!', '?'});
    auto totalSentenceCount = index.getTotalSentenceCount();
    vector<Sentence *> allSentences = collectSentences(words);
    vector<double> wordIdf = calculateWordIdf(words, totalSentenceCount);
    vector<double> sentenceScores = computeSentenceScores(words, allSentences, wordIdf);
    vector<Sentence *> top = getTopResults(allSentences, sentenceScores, fragmentCount);
    vector<string> topSentences = extractTopSentences(top);
    return topSentences;
}

vector<string> SnippetMaker::extractTopSentences(const vector<Sentence *> &top) const {
    vector<string> topSentences;
    for (auto &&topSentence : top) {
        topSentences.push_back(topSentence->text);
    }
    return topSentences;
}

vector<Sentence *> SnippetMaker::getTopResults(const vector<Sentence *> &allSentences, const vector<double>& sentenceScores, unsigned count) const {
    std::priority_queue<std::pair<double, unsigned>> sortQueue;
    for (int i = 0; i < sentenceScores.size(); ++i) {
        sortQueue.push(std::pair<double, unsigned>(sentenceScores[i], i));
    }
    vector<Sentence *> top;
    for (int i = 0; i < count; ++i) {
        if (!sortQueue.empty()) {
            auto position = sortQueue.top().second;
            top.push_back(allSentences[position]);
            sortQueue.pop();
        } else {
            break;
        }
    }
    return top;
}

vector<double> SnippetMaker::computeSentenceScores(const vector<string> &words, const vector<Sentence *> &allSentences,
                                                   const vector<double> &wordIdf) const {
    vector<double> sentenceScores(allSentences.size());

    for (int i = 0; i < allSentences.size(); ++i) {
        auto sentence = allSentences[i];
        sentenceScores[i] = computeSentenceScore(words, wordIdf, sentence);
    }
    return sentenceScores;
}

double SnippetMaker::computeSentenceScore(const vector<string> &queryWords, const vector<double> &wordIdf,
                                          Sentence *sentence) const {
    double sentenceScore = 0;
    for (int j = 0; j < queryWords.size(); ++j) {
        auto queryWord = queryWords[j];
        auto sentenceTermFrequency = sentence->wordToFrequency[queryWord];
        double tf;
        if(sentenceTermFrequency == 0) {
            tf = 0;
        } else {
            tf = log((double) sentenceTermFrequency) + 1;
        }
        auto idf = wordIdf[j];
        auto tfIdf = tf * idf;
        sentenceScore += tfIdf;
    }
    return sentenceScore;
}

vector<double> SnippetMaker::calculateWordIdf(const vector<string> &words, long totalDocumentCount) const {
    vector<double> wordIdf;

    for (int i = 0; i < words.size(); ++i) {
        auto word = words[i];
        auto documentFrequency = index.getDocumentFrequency(word);
        if(documentFrequency == 0) {
            wordIdf.push_back(0);
            continue;
        }
        auto idf = log((double) totalDocumentCount / documentFrequency);
        wordIdf.push_back(idf);
    }
    return wordIdf;
}

struct comparator {
    bool operator()(Sentence* s1, Sentence* s2) {
        return s1->text < s2->text;
    }
};


std::vector<Sentence *> SnippetMaker::collectSentences(vector<string> &words) {
    set<Sentence *, comparator> allSentences;
    for (auto &&word : words) {
        auto sentences = index.getSentences(word);
        allSentences.insert(sentences.begin(), sentences.end());
    }
    vector<Sentence *> sentenceVector;
    std::copy(allSentences.begin(), allSentences.end(), std::back_inserter(sentenceVector));
    return sentenceVector;
}
