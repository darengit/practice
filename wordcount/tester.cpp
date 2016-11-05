#include <vector>
#include "tester.h"

void testLinearSearch(WordReader &reader) {
    std::vector<Item> wordList;

    while(String8 word = reader.getWord()) {
	size_t i;
	for(i=0; i<wordList.size(); ++i) {
	    if(wordList[i].word == word) {
		++wordList[i].count;
		break;
	    }
        }

	if(i>=wordList.size())
	    wordList.emplace_back(Item(word,1));
    }

    for (const Item &item : wordList)
        printf("%s: %d\n", item.word.toString().c_str(), item.count);
}

template <typename T>
void testMap(WordReader &reader) {
    T wordCount;

    while(String8 word = reader.getWord())
	wordCount[word] += 1;

    for(const std::pair<String8, int> &p : wordCount)
        printf("%s: %d\n", p.first.toString().c_str(), p.second);
}
