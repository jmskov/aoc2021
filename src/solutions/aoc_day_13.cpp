#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_13.h"
#include "file_utils.h"

using namespace std;

AocDay13::AocDay13():AocDay(13)
{
}

AocDay13::~AocDay13()
{
}

vector<string> AocDay13::read_file_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<string> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        data.push_back(raw);
    }

    return data;
}

string AocDay13::part1(string filename, vector<string> extra_args)
{
    ostringstream out;
    out << "foo";
    return out.str();
}

string AocDay13::part2(string filename, vector<string> extra_args)
{
    ostringstream out;
    out << "foo";
    return out.str();
}

