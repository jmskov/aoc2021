#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_9.h"
#include "file_utils.h"

using namespace std;

AocDay9::AocDay9():AocDay(9)
{
}

AocDay9::~AocDay9()
{
}

vector<int> AocDay9::read_file_input(string filename)
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

string AocDay9::part1(string filename, vector<string> extra_args)
{
    vector<int> data = read_file_input(filename);

    int num_rows = data[0];
    int rlength = (int) (data.size()-1)/num_rows;

    int sum = 0;
    int row = 0;
    int col = 0;
    for (int i=1; i<data.size(); i++)
    {
        bool is_low = true;  
        if (col > 0)
        {
            is_low = is_low && data[i] < data[i-1];
        }
        if (col < rlength - 1)
        {
            is_low = is_low && data[i] < data[i+1];
        }
        if (row > 0)
        {
            is_low = is_low && data[i] < data[i-rlength];
        }
        if (row < num_rows - 1)
        {
            is_low = is_low && data[i] < data[i+rlength];
        }

        sum += is_low*(data[i]+1);

        if ((i % rlength) == 0)
        {
            row += 1;
            col = 0;
        } else {
            col++;
        }
    }

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay9::part2(string filename, vector<string> extra_args)
{
    vector<int> data = read_file_input(filename);

    int num_rows = data[0];
    int rlength = (int) (data.size()-1)/num_rows;

    map<int, int> basin_sizes;
    map<int, vector<int>> neighbors;

    int row = 0;
    int col = 0;
    for (int i=1; i<data.size(); i++)
    {
        bool is_low = true;  
        vector<int> pns;
        if (col > 0)
        {
            is_low = is_low && data[i] < data[i-1];
            if (data[i-1] != 9)
            {
                pns.push_back(i-1);
            }
        }
        if (col < rlength - 1)
        {
            is_low = is_low && data[i] < data[i+1];
            if (data[i+1] != 9)
            {
                pns.push_back(i+1);
            }
        }
        if (row > 0)
        {
            is_low = is_low && data[i] < data[i-rlength];
            if (data[i-rlength] != 9)
            {
                pns.push_back(i-rlength);
            }
        }
        if (row < num_rows - 1)
        {
            is_low = is_low && data[i] < data[i+rlength];
            if (data[i+rlength] != 9)
            {
                pns.push_back(i+rlength);
            }
        }

        if (data[i] != 9)
        {
            neighbors[i] = pns;
        }

        if (is_low)
        {
            basin_sizes[i] = 1;
        }

        if ((i % rlength) == 0)
        {
            row += 1;
            col = 0;
        } else {
            col++;
        }
    }

    for(auto it = basin_sizes.cbegin(); it != basin_sizes.cend(); ++it)
    {
        int sink = it->first;
        vector<int> points_to_check = {sink}; 
        vector<int> checked_points;
        while (points_to_check.size() > 0) 
        {
            vector<int> new_points;
            for (vector<int>::iterator iter=points_to_check.begin(); iter!=points_to_check.end(); ++iter)
            {
                checked_points.push_back(*iter);
                vector<int> pns = neighbors[*iter];
                for(int j=0;j<pns.size();j++)
                {
                    // If point is not in checked_points
                        // Sum and add to new points    
                    if(find(checked_points.begin(), checked_points.end(), pns[j]) == checked_points.end() && find(new_points.begin(), new_points.end(), pns[j]) == new_points.end()) {
                        basin_sizes[sink] += 1;
                        new_points.push_back(pns[j]);
                    } 
                }
            }
            points_to_check = new_points;
        }
    }

    int prod = 1;
    vector<int> sizes;
    for(auto it = basin_sizes.cbegin(); it != basin_sizes.cend(); ++it)
    {
        // Get max three values
        sizes.push_back(it->second);
    }

    for(int i=0; i<3; i++)
    {
        auto me = max_element(sizes.begin(), sizes.end());
        prod *= *me;
        sizes.erase(me);
    }

    ostringstream out;
    out << prod;
    return out.str();
}

