#ifndef __AOC_DAY_12__
#define __AOC_DAY_12__

#include "aoc_day.h"

class AocDay12 : public AocDay
{
    private:
        vector<string> read_file_input(string filename);
    public:
        AocDay12();
        ~AocDay12();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
