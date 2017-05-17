#include "Splitter.h"
#include "SentenceSplitter.h"
#include "Index.h"
#include "SnippetMaker.h"

#include <fstream>
#include <chrono>


static const char *const USAGE = "Usage: snippet_maker <path to file>";
static const char *const QUIT_KEYWORD = "quit";

using std::cout;;
using std::cin;;
using std::endl;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << USAGE << endl;
        return EXIT_FAILURE;
    }

    auto path = argv[1];

    std::fstream fileStream(path, std::fstream::in);
    SnippetMaker snippetMaker(fileStream);
    cout << "Index is built" << endl;
    while (true) {
        string query;
        std::getline(std::cin, query);
        if(query == QUIT_KEYWORD) {
            break;
        }

        auto begin = std::chrono::steady_clock::now();
        auto fragments = snippetMaker.getSnippetFragments(query, 10);
        auto end= std::chrono::steady_clock::now();

        auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        unsigned i = 0;
        cout << "Snippet formed in " << time << " microseconds" << endl;
        for (auto &&fragment : fragments) {
            std::cout << i << " " << fragment << std::endl;
            i++;
        }
    }
}