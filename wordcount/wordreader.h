#ifndef WORD_READER_H
#define WORD_READER_H

#include <fstream>
#include "string8.h"

#if READ_WHOLE_FILE

#include <stdlib.h>
#include <sys/stat.h>

class WordReader {
	char *m_wholeFile;
	char *m_rdPos;
	char *m_endPos;

public:
	WordReader(const char *fn);
	String8 getWord();
};

#else

class WordReader {
	std::ifstream m_inFile;
public:
	WordReader(const char *filename) : m_inFile(filename) {}
	String8 getWord();
};

#endif
#endif
