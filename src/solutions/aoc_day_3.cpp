#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <bitset>

#include "aoc_day_3.h"
#include "file_utils.h"

using namespace std;

AocDay3::AocDay3():AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

vector<bitset<12>> AocDay3::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;

    // How to change this - vector of pairs? or just read and parse as we go!    
    vector<bitset<12>> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string to_convert = *iter;
        bitset<12> bs{to_convert};
        data.push_back(bs);
    }
    return data;
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
    vector<bitset<12>> data = read_input(filename);
    vector<int> num_pos(12,0);

    for (int i=0; i<data.size(); i++)
    {
        for (int j=0; j<12; j++)
        { 
           if (data[i][j] > 0) 
            {
                num_pos[j] += 1;
            } 
        } 
    }

    double n = data.size()/2.0f;
    bitset<12> gamma;
    bitset<12> epsilon;
    for (int i=0; i<12; i++)
    {
       if ((double)num_pos[i] > n)
        {
            gamma.set(i,true);
        }
        else 
        {
            epsilon.set(i,true);
        }
    } 

    ostringstream out;
    out << epsilon.to_ulong()*gamma.to_ulong(); 
    return out.str();
}

static int count_bits_in_pos(vector<bitset<12>> data, int pos)
{
    int count = 0;
    for (int i=0; i<data.size(); i++)
    {
       if (data[i][pos] > 0) 
        {
            count += 1;
        } 
    }
    return count;
}

static vector<bitset<12>> remove_data_entries(vector<bitset<12>> data, int pos, bool remove_ones)
{
    vector<bitset<12>> new_data;
    for (int i=0; i<data.size(); i++)
    {
        if ((data[i][pos] > 0 && !remove_ones) || (data[i][pos] < 1 && remove_ones))
        {
            new_data.push_back(data[i]);
        }
    }
    
    return new_data;
}

string AocDay3::part2(string filename, vector<string> extra_args)
{
    vector<bitset<12>> data = read_input(filename);

    // CO2
    vector<bitset<12>> co2_data = data;
    int i=11;
    while (i>=0 && co2_data.size() > 1)
    {
        int current_count = count_bits_in_pos(co2_data, i);
        if ((co2_data.size() - current_count) <= current_count) {
            co2_data = remove_data_entries(co2_data, i, true); 
        }
        else {
            co2_data = remove_data_entries(co2_data, i, false); 
        }
        i--;
    }
    
    // Oxygen 
    vector<bitset<12>> o2_data = read_input(filename);
    i=11;
    while (i>=0 && o2_data.size() > 1)
    {
        int current_count = count_bits_in_pos(o2_data, i);
        if ((o2_data.size() - current_count) <= current_count) {
            o2_data = remove_data_entries(o2_data, i, false); 
        }
        else {
            o2_data = remove_data_entries(o2_data, i, true); 
        }
        i--;
    }

    ostringstream out;
    cout << co2_data[0] << " " << o2_data[0] << endl;
    out << co2_data[0].to_ulong()*o2_data[0].to_ulong(); 
    return out.str();
}
