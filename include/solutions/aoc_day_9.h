#ifndef __AOC_DAY_9__
#define __AOC_DAY_9__

#include "aoc_day.h"

class AocDay9 : public AocDay
{
    private:
        vector<int> read_file_input(string filename);
    public:
        AocDay9();
        ~AocDay9();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
