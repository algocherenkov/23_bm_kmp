#include "substringSearch.h"
#include <vector>
#include <cassert>
#include <climits>
#include <algorithm>
#include <cstring>

namespace  {    
    int suffix_match(const char *needle, size_t nlen, size_t offset, size_t suffixlen)
    {
        if (offset > suffixlen)
            return needle[offset - suffixlen - 1] != needle[nlen - suffixlen - 1] &&
                memcmp(needle + nlen - suffixlen, needle + offset - suffixlen, suffixlen) == 0;
        else
            return memcmp(needle + nlen - offset, needle, offset) == 0;
    }

    void createSuffixTable(const std::string& pattern, int* suffixTable)
    {
        auto pattLength = pattern.size();
        for(size_t a = 0; a < pattLength; ++a)
        {
           size_t offs = pattLength;
           while(offs && !suffix_match(pattern.c_str(), pattLength, offs, a))
               --offs;
           suffixTable[pattLength - a - 1] = pattLength - offs;
        }
    }

    std::vector<int> prefixFunction (std::string& s)
    {
        int n = static_cast<int>(s.length());
        std::vector<int> pi(n);

        for (int i = 1; i < n; ++i)
        {
            int j = pi[i - 1];

            while (j > 0 && s[i] != s[j])
                j = pi[j-1];

            if (s[i] == s[j])
                ++j;

            pi[i] = j;
        }

        return pi;
    }
}

int sssearch::bmSearch(const std::string &text, const std::string &pattern)
{    
    int prefix[UCHAR_MAX + 1];
    int suffix[pattern.size()];

    //prefix table creation    
    for(size_t i = 0; i < UCHAR_MAX + 1; i++)
        prefix[i] = -1;

    for(size_t i = 0; i < pattern.size() - 1; i++)
        prefix[pattern[i]] = i;

    //suffix table creation    
    createSuffixTable(pattern, suffix);

    for(size_t textPos = 0; textPos <= text.size() - pattern.size(); )
    {
        size_t patternPos = pattern.size() - 1;
        while(pattern[patternPos] == text[patternPos + textPos])
        {
            if(patternPos == 0)
                return textPos;

            --patternPos;
        }

        textPos += std::max(suffix[patternPos], static_cast<int>(patternPos - prefix[text[patternPos + textPos]]));
    }

    return -1;
}

int sssearch::kmpSearch(const std::string &text, const std::string &pattern)
{
    std::string line = pattern + '#' + text;
    auto pi = prefixFunction(line);
    int pattSize = pattern.size();

    for(size_t i = 2*pattSize; i < line.size(); i++)
    {
        if(pi[i] == pattSize)
            return i - 2*pattSize;
    }
    return -1;
}
