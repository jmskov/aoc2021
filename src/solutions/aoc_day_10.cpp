#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>
#include <algorithm>

#include "aoc_day_10.h"
#include "file_utils.h"

using namespace std;

AocDay10::AocDay10():AocDay(10)
{
}

AocDay10::~AocDay10()
{
}

vector<int> AocDay10::read_file_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<int> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    
    data.push_back(raw_lines.size());

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        for (int i=0;i<raw.length();i++)
        {
            data.push_back(stoi(raw.substr(i,1)));
        }
    }

    return data;
}

bool is_opening(char c)
{
    return (c == '(' || c == '{' || c == '<' || c == '[');
}

bool is_closing(char c)
{
    return (c == ')' || c == '}' || c == '>' || c == ']');
}

bool is_valid_closing(char c1, char c2)
{
    return ((c1 == '(' && c2 == ')') || (c1 == '{' && c2 == '}') || (c1 == '<' && c2 == '>') || (c1 == '[' && c2 == ']'));
}

string AocDay10::part1(string filename, vector<string> extra_args)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return "err";
    }
    
    map<char, int> vals = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    int score = 0;
    vector<string> valid_lines;

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        bool corrupt = false; 
        vector<char> openings;
        vector<char> closings;
        for (int i=0; i<raw.length(); i++)
        {
            if (is_opening(raw[i]))
            {
               openings.push_back(raw[i]); 
            }
            else if (is_closing(raw[i]))
            {
                closings.push_back(raw[i]);
                if (is_valid_closing(openings[openings.size()-1], closings[closings.size()-1]))
                {
                    openings.pop_back();
                    closings.pop_back();
                } 
                else
                {
                    score += vals[raw[i]];
                    break;
                }
            }
        }
    }

    ostringstream out;
    out << score;
    return out.str();
}

string AocDay10::part2(string filename, vector<string> extra_args)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return "err";
    }
    
    map<char, int> vals = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
    map<char, char> closers = {{'(',')'}, {'[',']'}, {'{','}'},{'<','>'}};
    vector<string> valid_lines;
    vector<long> scores;

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        bool corrupt = false; 
        vector<char> openings;
        vector<char> closings;
        for (int i=0; i<raw.length(); i++)
        {
            if (is_opening(raw[i]))
            {
               openings.push_back(raw[i]); 
            }
            else if (is_closing(raw[i]))
            {
                closings.push_back(raw[i]);
                if (is_valid_closing(openings[openings.size()-1], closings[closings.size()-1]))
                {
                    openings.pop_back();
                    closings.pop_back();
                } 
                else
                {
                    corrupt = true;
                    break;
                }
            }
        }

        if (!corrupt)
        {
            long score = 0;
            for (int i=openings.size()-1; i>=0; i--)
            {
                score = 5*score + (long)vals[closers[openings[i]]];
            }
            scores.push_back(score);
        }
    }

    sort(scores.begin(), scores.end()); 
    ostringstream out;
    out << scores[(scores.size()-1)/2];
    return out.str();
}

