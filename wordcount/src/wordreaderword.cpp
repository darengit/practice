#include <fstream>
#include "string8.h"

class WordReader {
    std::ifstream m_inFile;
public:
    WordReader(const char *filename) : m_inFile(filename) {}
    String8 getWord();
};

String8 WordReader::getWord() {
    String8 result;
    if(m_inFile.tellg() != std::ios::end) {
        char *chars = result.getChars();
        m_inFile.get(chars, 9);
    }
    return result;
}

