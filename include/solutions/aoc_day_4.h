#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

#include "aoc_day.h"

class AocDay4 : public AocDay
{
    private:
        vector<int> read_call_order(string filename);
        vector<vector<int>> read_game_boards(string filename);
    public:
        AocDay4();
        ~AocDay4();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
