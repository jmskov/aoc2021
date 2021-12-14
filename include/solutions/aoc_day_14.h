#ifndef __AOC_DAY_14__
#define __AOC_DAY_14__

#include "aoc_day.h"

class AocDay14 : public AocDay
{
    private:
        vector<string> read_file_input(string filename);
    public:
        AocDay14();
        ~AocDay14();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
