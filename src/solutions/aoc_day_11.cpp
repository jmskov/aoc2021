#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_11.h"
#include "file_utils.h"

using namespace std;

AocDay11::AocDay11():AocDay(11)
{
}

AocDay11::~AocDay11()
{
}

vector<int> AocDay11::read_file_input(string filename)
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

vector<int> get_neighbors(int i, int rsize, int colsize)
{
    vector<int> neighbors;

    int col = i%rsize; 
    int row = (i-col)/(rsize);

    if (col > 0)
    {
        neighbors.push_back(i-1);
    }
    if (col < rsize - 1)
    {
        neighbors.push_back(i+1);
    }
    if (row > 0)
    {
        neighbors.push_back(i-rsize);
        if (col < rsize - 1)
        {
            neighbors.push_back(i-rsize+1);
        }
        if (col > 0)
        {
            neighbors.push_back(i-rsize-1);
        }
    }
    if (row < colsize - 1)
    {
        neighbors.push_back(i+rsize);
        if (col < rsize - 1)
        {
            neighbors.push_back(i+rsize+1);
        }
        if (col > 0)
        {
            neighbors.push_back(i+rsize-1);
        }
    }

    return neighbors;
}

void print_board(vector<int> data, int rlength)
{
    for(int i=0; i<data.size(); i++)
    {
        cout << data[i] << " ";
        if((i+1)%(rlength) == 0)
        {
            cout << endl;
        }
    }
}

string AocDay11::part1(string filename, vector<string> extra_args)
{
    vector<int> data = read_file_input(filename);

    int num_rows = data[0];
    int rlength = (int) (data.size()-1)/num_rows;

    data.erase(data.begin());

    int num_steps = 100;
    int num_flashes = 0;

    // First, increase energy levels by 1 for everyone
        // Keep track of flashers for next step here 
        // Set energy to -10 so it can't flash again

    // Second, all octopi w/ energy >9 flashes
        // All adjacent increase energy by 1
            // Add to new flashers
        // Induce other flases
        // ADD 

    // Finally Set any octopus that flashed to zero energy
        // i.e. set all negative energy octopi to zero
    
    for (int k=0; k<num_steps; k++)
    {
        cout << "k=" << k << endl;
        print_board(data, rlength);
        // STEP 1
        vector<int> flashers;
        for (int i=0; i<data.size(); i++)
        {
            
            data[i] += 1;
            if (data[i] > 9)
            {
                flashers.push_back(i);
                data[i] = -100;
            } 
        }

        // STEP 2
        while (flashers.size() > 0)
        {
            vector<int> new_flashers;
            for (vector<int>::iterator iter=flashers.begin(); iter != flashers.end(); ++iter)
            {
                // Set the flasher to a large negative energy  
                data[*iter] = -100;
                // Record the flash
                num_flashes += 1;
                // Get neighbors, if neighbors energy <= 9, increment add to new flashers
                vector<int> neighbors = get_neighbors(*iter, rlength, num_rows);
                
                for (int j=0; j<neighbors.size(); j++)
                {
                    data[neighbors[j]] += 1;
                    if (data[neighbors[j]] > 9)
                    {
                        new_flashers.push_back(neighbors[j]); 
                        data[neighbors[j]] = -100;
                    }
                }
            }
            
            flashers = new_flashers;   
        }
        
        // STEP 3
        for (int i=0; i<data.size(); i++)
        {
            
            if (data[i] < 0)
            {
                data[i] = 0;
            } 
        }
    }


    ostringstream out;
    out << num_flashes;
    return out.str();
}

string AocDay11::part2(string filename, vector<string> extra_args)
{
    vector<int> data = read_file_input(filename);

    int num_rows = data[0];
    int rlength = (int) (data.size()-1)/num_rows;

    data.erase(data.begin());

    int num_steps = 10000;
    int num_flashes = 0;
    int first_step_sync = 0;

    // First, increase energy levels by 1 for everyone
        // Keep track of flashers for next step here 
        // Set energy to -10 so it can't flash again

    // Second, all octopi w/ energy >9 flashes
        // All adjacent increase energy by 1
            // Add to new flashers
        // Induce other flases
        // ADD 

    // Finally Set any octopus that flashed to zero energy
        // i.e. set all negative energy octopi to zero
    
    for (int k=0; k<num_steps; k++)
    {
        int num_flashes_step = 0;
        // STEP 1
        vector<int> flashers;
        for (int i=0; i<data.size(); i++)
        {
            
            data[i] += 1;
            if (data[i] > 9)
            {
                flashers.push_back(i);
                data[i] = -100;
            } 
        }

        // STEP 2
        while (flashers.size() > 0)
        {
            vector<int> new_flashers;
            for (vector<int>::iterator iter=flashers.begin(); iter != flashers.end(); ++iter)
            {
                // Set the flasher to a large negative energy  
                data[*iter] = -100;
                // Record the flash
                num_flashes += 1;
                num_flashes_step += 1;
                // Get neighbors, if neighbors energy <= 9, increment add to new flashers
                vector<int> neighbors = get_neighbors(*iter, rlength, num_rows);
                
                for (int j=0; j<neighbors.size(); j++)
                {
                    data[neighbors[j]] += 1;
                    if (data[neighbors[j]] > 9)
                    {
                        new_flashers.push_back(neighbors[j]); 
                        data[neighbors[j]] = -100;
                    }
                }
            }
            
            flashers = new_flashers;   
        }
        
        // STEP 3
        for (int i=0; i<data.size(); i++)
        {
            
            if (data[i] < 0)
            {
                data[i] = 0;
            } 
        }

        if (num_flashes_step == data.size())
        {  
            first_step_sync = k+1;
            break;
        }
    }


    ostringstream out;
    out << first_step_sync;
    return out.str();
}

