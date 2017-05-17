cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Splitter.cpp
        Splitter.h
        SentenceSplitter.cpp
        SentenceSplitter.h
        Sentence.h
        Index.cpp
        Index.h
        SnippetMaker.cpp
        SnippetMaker.h
        TrimUtils.h
        )
add_executable(untitled ${SOURCE_FILES})
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
