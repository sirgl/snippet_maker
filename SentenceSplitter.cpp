//
// Created by roman on 16.05.17.
//

#include "SentenceSplitter.h"

SentenceSplitter::SentenceSplitter(std::istream &istream) : istream(istream) {}

SentenceSplitter::iterator SentenceSplitter::begin() {
    return iterator(Splitter::iterator(istream, false, {'.', '!', '?'}));
}

SentenceSplitter::iterator SentenceSplitter::end() {
    return iterator(Splitter::iterator(istream, true, {}));
}

SentenceSplitter::iterator::iterator(const Splitter::iterator &splitterIterator) : splitterIterator(splitterIterator) {}
