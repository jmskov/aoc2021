#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

#include "aoc_day.h"

class AocDay5 : public AocDay
{
    private:
        vector<vector<int>> read_file_input(string filename);
    public:
        AocDay5();
        ~AocDay5();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
