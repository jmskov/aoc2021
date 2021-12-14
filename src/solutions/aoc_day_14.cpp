#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_14.h"
#include "file_utils.h"

using namespace std;

AocDay14::AocDay14():AocDay(14)
{
}

AocDay14::~AocDay14()
{
}

vector<string> AocDay14::read_file_input(string filename)
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

string AocDay14::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_file_input(filename);
    string temp = data[0];
    map <string, string> connections;
    // Parse connections
    for (vector<string>::iterator iter=data.begin()+2; iter!=data.end(); ++iter)
    {
        int del_idx = iter->find("-");
        string s1 = iter->substr(0, del_idx-1);
        string s2 = iter->substr(del_idx+3);
        connections[s1]=s2;
    }

    int max_steps = 10;
    
    for (int k=0; k<max_steps; k++)
    {
        string new_poly = "";
        
        for (int j=0; j<temp.length(); j++)
        {
            string p2i = connections[temp.substr(j,1)+temp.substr(j+1,1)];
            new_poly += temp.substr(j,1) + p2i; 
            if (j==temp.length()-1)
            {
                new_poly += temp.substr(j+1,1);
            }
        } 
        if (k < 5)
        {
            cout << "After step " << k+1 << ": " << new_poly << endl;
        }
        temp = new_poly;
    }

    // Count steps
    map<string,int> count;
    for (int j=0; j<temp.length(); j++)
    {
        string t = temp.substr(j,1); 
        if (count.count(t))
        {
            count[t] += 1; 
        }
        else
        {
            count[t] = 1;
        }
    } 

    string max_s;
    string min_s;
    int max_count = 0;
    int min_count = 10000000;

    for (map<string,int>::iterator iter=count.begin(); iter!=count.end(); ++iter)
    {
        if (iter->second > max_count)
        {
            max_s = iter->first;
            max_count = iter->second;
        }
        if (iter->second < min_count)
        {
            min_s = iter->first;
            min_count = iter->second;
        }
    }

    ostringstream out;
    out << max_count - min_count; 
    return out.str();
}

string AocDay14::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_file_input(filename);
    string temp = data[0];
    string last_str = temp.substr(temp.length()-1);
    map <string, string> connections;
    // Parse connections
    for (vector<string>::iterator iter=data.begin()+2; iter!=data.end(); ++iter)
    {
        int del_idx = iter->find("-");
        string s1 = iter->substr(0, del_idx-1);
        string s2 = iter->substr(del_idx+3);
        connections[s1]=s2;
    }

    int max_steps = 40;
    
    map<string,long> pairs;
    for (int j=0; j<temp.length()-1; j++)
    {
        string s = temp.substr(j,2);
        if (pairs.count(s))
        {
            pairs[s] += 1;
        }
        else
        {
            pairs[s] = 1;
        }
    }

    for (int k=0; k<max_steps; k++)
    {
        //string new_poly = "";
        map<string,long> new_pairs;
        
        for (map<string, long>::iterator iter=pairs.begin(); iter!=pairs.end(); ++iter)
        {
            string pair = iter->first;
            string p2i = connections[pair];
            string new_poly1 = pair.substr(0,1) + p2i; 
            string new_poly2 = p2i + pair.substr(1,1); 

            if (new_pairs.count(new_poly1))
            {
                new_pairs[new_poly1]+=pairs[pair];
            }
            else
            {
                new_pairs[new_poly1] = pairs[pair];
            }
            if (new_pairs.count(new_poly2))
            {
                new_pairs[new_poly2]+=pairs[pair];
            }
            else
            {
                new_pairs[new_poly2] = pairs[pair];
            }
            
        }

        pairs = new_pairs;
    }

    // Count steps
    map<string,long> count;
    count[last_str] = 1;
    for (map<string,long>::iterator iter=pairs.begin(); iter!=pairs.end(); ++iter)
    {
        string t = iter->first.substr(0,1); 
        if (count.count(t))
        {
            count[t] += (long)iter->second; 
        }
        else
        {
            count[t] = (long)iter->second;
        }
    } 

    string max_s;
    string min_s;
    long max_count = 0;
    long min_count = 9223372036854775807; 

    for (map<string,long>::iterator iter=count.begin(); iter!=count.end(); ++iter)
    {
        if (iter->second > max_count)
        {
            max_s = iter->first;
            max_count = iter->second;
        }
        if (iter->second < min_count)
        {
            min_s = iter->first;
            min_count = iter->second;
        }
    }

    ostringstream out;
    out << max_count - min_count; 
    return out.str();
}

