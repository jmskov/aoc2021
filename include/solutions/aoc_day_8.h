#ifndef __AOC_DAY_8__
#define __AOC_DAY_8__

#include "aoc_day.h"

class AocDay8 : public AocDay
{
    private:
        vector<map<char, vector<string>>> read_file_input(string filename);
    public:
        AocDay8();
        ~AocDay8();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
