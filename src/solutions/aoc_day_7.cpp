#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>

#include "aoc_day_7.h"
#include "file_utils.h"

using namespace std;

AocDay7::AocDay7():AocDay(7)
{
}

AocDay7::~AocDay7()
{
}

vector<int> AocDay7::read_file_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<int> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        int strl = raw.length(); 
        int str_x = 0;
        for (int i=0;i<strl;i++)
        {
            if (raw[i] == ',')
            { 
                data.push_back(stoi(raw.substr(str_x,i-str_x)));
                str_x = i+1;
            }
            else if (i == strl-1)
            {
                data.push_back(stoi(raw.substr(str_x)));
            }
        } 
    }

    return data;
}

string AocDay7::part1(string filename, vector<string> extra_args)
{
    vector<int> crab_pos = read_file_input(filename);
    int max_pos = 0;
    for (int i=0; i< crab_pos.size(); i++)
    {
          max_pos = max(max_pos, crab_pos[i]);
    }

    int best_pos = 0;
    long min_fuel = 999999999;
    for (int i=0; i<=max_pos; i++)
    {
        long fuel_cost_l = 0;
        for (int j=0; j<crab_pos.size();j++)
        {
            fuel_cost_l += abs(crab_pos[j] - i);
        }

        if (fuel_cost_l < min_fuel) 
        {
            min_fuel = fuel_cost_l;
            best_pos = i;
        }
        
    }
    ostringstream out;
    out << (int) min_fuel;
    return out.str();
}

int rec_fact(int in)
{
    int sum = 0;
    for (int i=in; i>0; i--)
    {
        sum += i;
    }
    return sum;
}

string AocDay7::part2(string filename, vector<string> extra_args)
{
    vector<int> crab_pos = read_file_input(filename);
    int max_pos = 0;
    for (int i=0; i< crab_pos.size(); i++)
    {
          max_pos = max(max_pos, crab_pos[i]);
    }

    int best_pos = 0;
    long min_fuel = 999999999;
    for (int i=0; i<=max_pos; i++)
    {
        long fuel_cost_l = 0;
        for (int j=0; j<crab_pos.size();j++)
        {
            
            int dis = abs(crab_pos[j] - i);
            fuel_cost_l += rec_fact(dis);
        }

        if (fuel_cost_l < min_fuel) 
        {
            min_fuel = fuel_cost_l;
            best_pos = i;
        }
        
    }
    ostringstream out;
    out << (int) min_fuel;
    return out.str();
}
