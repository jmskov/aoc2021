#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <bitset>

#include "aoc_day_6.h"
#include "file_utils.h"

using namespace std;

AocDay6::AocDay6():AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

vector<int> AocDay6::read_file_input(string filename)
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
        // Split string according to ->
        string raw = *iter;
        int strl = raw.length(); 
        for (int i=0;i<strl;i++)
        {
            if (i % 2 == 0)
            {
                data.push_back(stoi(raw.substr(i,1)));
            }
        } 
    }

    return data;
}

string AocDay6::part1(string filename, vector<string> extra_args)
{
    vector<int> init_state = read_file_input(filename);
    vector<int> num_fish(9,0);

    // Parse the initial state
    for (int i=0; i< init_state.size(); i++)
    {
        num_fish[init_state[i]] += 1;
    }

    int num_days = 80;
    vector<int> current_count = num_fish;
    vector<int> next_count(9,0);
    for (int i=0; i<num_days; i++)
    {
        for(int j=8; j>=1; j--)
        {
            next_count[j-1] = current_count[j];
        }        
        next_count[6] += current_count[0]; 
        next_count[8] = current_count[0];
        current_count = next_count;
    }

    int sum = 0;

    for(int i=0; i<current_count.size();i++)
    { 
        sum += current_count[i];
    }

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay6::part2(string filename, vector<string> extra_args)
{
    vector<int> init_state = read_file_input(filename);
    vector<long> num_fish(9,0);

    // Parse the initial state
    for (int i=0; i< init_state.size(); i++)
    {
        num_fish[init_state[i]] += 1;
    }

    

    int num_days = 256;
    vector<long> current_count = num_fish;
    vector<long> next_count(9,0);
    for (int i=0; i<num_days; i++)
    {
        for(int j=8; j>=1; j--)
        {
            next_count[j-1] = current_count[j];
        }        
        next_count[6] += current_count[0]; 
        next_count[8] = current_count[0];
        current_count = next_count;
    }

    long sum = 0;

    for(int i=0; i<current_count.size();i++)
    { 
        sum += current_count[i];
    }

    ostringstream out;
    out << sum;
    return out.str();
}
