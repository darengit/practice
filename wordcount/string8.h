#ifndef STRING8_H
#define STRING8_H

#include <stdint.h>
#include <string.h>

#include <string>


class String8 {
    // this union makes it such that we dont have to type cast, this is cool
    union {
        uint64_t m_value;
        char m_chars[8];
    };

public:
    inline String8() : m_value(0) {}

    String8(const char *from) {
        memcpy(m_chars, from, 8);
    }

    char *getChars() {
        return m_chars;
    }

    uint64_t getValue() const {
        return m_value;
    }

    std::string toString() const {
        char buf[9];
        memcpy(buf, m_chars, 8);
        buf[8] = '\0';
        return buf;
    }

    operator bool() const {
        return m_value != 0;
    }

};

inline bool operator<(const String8 &a, const String8 &b) {
    return a.getValue() < b.getValue();
}

inline bool operator==(const String8 &a, const String8 &b) {
    return a.getValue() == b.getValue();
}

namespace std {
    template<> struct hash<String8> {
        size_t operator()(const String8 &s) const {
            return hash<uint64_t>()(s.getValue());
        }
    };
}

#endif
