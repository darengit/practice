#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>
#include "string8.h"

class WordReader {
	char *m_wholeFile;
	char *m_rdPos;
	char *m_endPos;

public:
	WordReader(const char *fn);
	String8 getWord();
};

WordReader::WordReader(const char *filename) : m_rdPos(NULL), m_endPos(NULL) {
	std::ifstream inFile(filename);
	if(!inFile.fail()) {
		struct stat s;
		stat(filename, &s);
		size_t fileSize = s.st_size;
		m_wholeFile = (char *)malloc(fileSize*sizeof(char));
		inFile.read(m_wholeFile, fileSize);
		m_rdPos = m_wholeFile;
		m_endPos = m_rdPos + fileSize;
	}
}

String8 WordReader::getWord() {
	String8 result;
	if(m_rdPos<m_endPos) {
		char *chars = result.getChars();
		memcpy(chars, m_rdPos, 8);
		m_rdPos += 8;
	}
	return result;
}

