#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_2.h"
#include "file_utils.h"

using namespace std;

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

vector<long> AocDay2::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;

    // How to change this - vector of pairs? or just read and parse as we go!    
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

string AocDay2::part1(string filename, vector<string> extra_args)
{
    FileUtils fileutils;
    vector<string> raw_lines;

    long horizontal = 0;
    long depth = 0;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        int space_pos = 0;
        string str = *iter;
        for (int i=0; i<str.length();i++)
        {
            if (str[i] == ' ')
            {
                space_pos = i;
                break;
            }
        } 

        string d = str.substr(space_pos+1, str.length()-1);

        long l;
        l = strtol(d.c_str(), NULL, 10);

        switch(space_pos) {
            printf("%d", space_pos);
            case 2 :
                depth -= l;
                break;
            case 4 :
                depth += l;
                break;
            case 7 :
                horizontal += l;
                break;
        }
    }

    ostringstream out;
    out << horizontal*depth;
    return out.str();
}

string AocDay2::part2(string filename, vector<string> extra_args)
{
    FileUtils fileutils;
    vector<string> raw_lines;

    long horizontal = 0;
    long depth = 0;
    long aim = 0;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        int space_pos = 0;
        string str = *iter;
        for (int i=0; i<str.length();i++)
        {
            if (str[i] == ' ')
            {
                space_pos = i;
                break;
            }
        } 

        string d = str.substr(space_pos+1, str.length()-1);

        long l;
        l = strtol(d.c_str(), NULL, 10);

        switch(space_pos) {
            printf("%d", space_pos);
            case 2 :
                aim -= l;
                break;
            case 4 :
                aim += l;
                break;
            case 7 :
                horizontal += l;
                depth += aim*l;
                break;
        }
    }

    ostringstream out;
    out << horizontal*depth;
    return out.str();
}
