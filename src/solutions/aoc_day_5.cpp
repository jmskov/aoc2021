#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <bitset>

#include "aoc_day_5.h"
#include "file_utils.h"

using namespace std;

AocDay5::AocDay5():AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

vector<vector<int>> AocDay5::read_file_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<vector<int>> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        // Split string according to ->
        string raw = *iter;
        int end_idx = raw.find("-");
        string sub1 = raw.substr(0,end_idx-1);
        string sub2 = raw.substr(end_idx+3);

        int cidx1 = sub1.find(",");
        int cidx2 = sub2.find(","); 
        vector<int> coords = {(int)strtol(sub1.substr(0,cidx1).c_str(), NULL, 10), (int)strtol(sub1.substr(cidx1+1).c_str(), NULL, 10), (int)strtol(sub2.substr(0,cidx2).c_str(), NULL, 10), (int)strtol(sub2.substr(cidx2+1).c_str(), NULL, 10)}; 
        data.push_back(coords);
    }

    return data;
}

void print_vector5(vector<int> vec) 
{
    for(int i=0; i<vec.size(); i++)
    {
        cout << vec[i] << ",";
    }
    cout << endl;
}

int get_vec_idx(int x, int y)
{
    int base_size = 1000;
    int vec_idx = (base_size)*x + y;
    return vec_idx;
}

string AocDay5::part1(string filename, vector<string> extra_args)
{
    vector<vector<int>> all_lines = read_file_input(filename);

    int world_size = 1000*1000;
    vector<int> world_vec(world_size,0);

    for (int i=0; i<all_lines.size(); i++)
    {
        // If x coordinates are the same, iterate over y
        if (all_lines[i][0] == all_lines[i][2])
        {
            int midx = min(all_lines[i][1], all_lines[i][3]);
            int Midx = max(all_lines[i][1], all_lines[i][3]);
            for (int j=midx; j<=Midx; j++)
            {
                world_vec[get_vec_idx(all_lines[i][0], j)] += 1;
            }
        } 
        else if (all_lines[i][1] == all_lines[i][3])
        {
            int midx = min(all_lines[i][0], all_lines[i][2]);
            int Midx = max(all_lines[i][0], all_lines[i][2]);
            for (int j=midx; j<=Midx; j++)
            {
                world_vec[get_vec_idx(j, all_lines[i][1])] += 1;
            }
        }
    }

    int sum = 0;
    for (int i=0; i< world_vec.size(); i++)
    {
        if (world_vec[i] > 1) 
        {
            sum += 1;
        }
    }

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay5::part2(string filename, vector<string> extra_args)
{
    vector<vector<int>> all_lines = read_file_input(filename);

    int world_size = 1000*1000;
    vector<int> world_vec(world_size,0);

    for (int i=0; i<all_lines.size(); i++)
    {
        // If x coordinates are the same, iterate over y
        if (all_lines[i][0] == all_lines[i][2])
        {
            int midx = min(all_lines[i][1], all_lines[i][3]);
            int Midx = max(all_lines[i][1], all_lines[i][3]);
            for (int j=midx; j<=Midx; j++)
            {
                world_vec[get_vec_idx(all_lines[i][0], j)] += 1;
            }
        } 
        else if (all_lines[i][1] == all_lines[i][3])
        {
            int midx = min(all_lines[i][0], all_lines[i][2]);
            int Midx = max(all_lines[i][0], all_lines[i][2]);
            for (int j=midx; j<=Midx; j++)
            {
                world_vec[get_vec_idx(j, all_lines[i][1])] += 1;
            }
        }
        else 
        {
            int midx = min(all_lines[i][0], all_lines[i][2]);
            int Midx = max(all_lines[i][0], all_lines[i][2]);
            int midx2 = min(all_lines[i][1], all_lines[i][3]);
            int Midx2 = max(all_lines[i][1], all_lines[i][3]);
            bool pos_slope = (all_lines[i][1] < all_lines[i][3] && all_lines[i][0] < all_lines[i][2]) || (all_lines[i][1] > all_lines[i][3] && all_lines[i][0] > all_lines[i][2]);
;

            for (int j=0; j<=Midx-midx; j++)
            {
                if (pos_slope)
                {
                    world_vec[get_vec_idx(midx+j,midx2+j)] += 1;
                }
                else
                {
                    world_vec[get_vec_idx(midx+j,Midx2-j)] += 1;
                }
            }
        }
    }

    int sum = 0;
    for (int i=0; i< world_vec.size(); i++)
    {
        if (world_vec[i] > 1) 
        {
            sum += 1;
        }
    }

    ostringstream out;
    out << sum;
    return out.str();
}
