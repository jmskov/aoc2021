#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<long> AocDay1::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<long> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        long l;
        string to_convert = *iter;
        l = strtol(to_convert.c_str(), NULL, 10);
        data.push_back(l);
    }
    return data;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);

    long sum = 0;
    for (int i=1; i<=data.size(); i++) 
    {
        if (data[i] > data[i-1]) 
        {
            sum += 1;
        }
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    vector<long> data = read_input(filename);

    long sum = 0;
    for (int i=0; i<=data.size()-3; i++) 
    {
        long s1 = data[i]+data[i+1]+data[i+2];
        long s2 = data[i+1]+data[i+2]+data[i+3];
        if (s2 > s1)
        {
            sum += 1;
        }
    }
    ostringstream out;
    out << sum;
    return out.str();
}
