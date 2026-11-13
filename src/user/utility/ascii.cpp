#include "ascii.h"
#include "stdint.h"

namespace ASCII {
    char* getAllValidUserChars() {
        char* charStart = new char[63];
        char* curChar = charStart;

        // Get all capital letters by their ASCII code
        for(uint8_t code = 65; code <= 90; code++) {
            *curChar = (char)code;
            curChar++;
        }

        // Get all lower case letters by their ASCII code
        for(uint8_t code = 97; code <= 122; code++) {
            *curChar = (char)code;
            curChar++;
        }

        // Get all numbers by their ASCII code
        for(uint8_t code = 48; code <= 57; code++) {
            *curChar = (char)code;
            curChar++;
        }
        *curChar = '\0';
        return charStart;
    };
}