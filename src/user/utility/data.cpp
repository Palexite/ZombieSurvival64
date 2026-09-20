#include <cstdio>
#include <string>
#include <vector>
#include "data.h"

namespace data {
    std::string readtxt(std::string filePath) {
        FILE* mapsFile = fopen(filePath.c_str(), "rb");
        if (mapsFile == nullptr) {
            return {};
        }

        if (fseek(mapsFile, 0, SEEK_END) != 0) {
            fclose(mapsFile);
            return {};
        }

        const long fileSize = ftell(mapsFile);
        if (fileSize < 0 || fseek(mapsFile, 0, SEEK_SET) != 0) {
            fclose(mapsFile);
            return {};
        }

        std::string contents(static_cast<size_t>(fileSize), '\0');
        const size_t bytesRead = fread(contents.data(), 1, contents.size(), mapsFile);
        fclose(mapsFile);

        if (bytesRead != contents.size()) {
            return {};
        }

        return contents;
    }


    std::vector<std::string> getLinesFromString(std::string content) {

        std::vector<std::string> lines{};

        size_t pos = 0;
        while (pos < content.size()) {
            size_t nextPos = content.find('\n', pos);
            if (nextPos == std::string::npos) {
                nextPos = content.size();
            }

            std::string line = content.substr(pos, nextPos - pos);
            pos = nextPos + 1;
            lines.push_back(line);

        }
        
        return lines;

    }
}