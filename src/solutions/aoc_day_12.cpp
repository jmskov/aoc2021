#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_12.h"
#include "file_utils.h"

using namespace std;

AocDay12::AocDay12():AocDay(12)
{
}

AocDay12::~AocDay12()
{
}

vector<string> AocDay12::read_file_input(string filename)
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

string AocDay12::part1(string filename, vector<string> extra_args)
{
    vector<string> connections_raw = read_file_input(filename);

    // For each path, keep track of what has been visited
    map<string, bool> smalls_visited;

    map <string, vector<string>> connections;
    // Parse connections
    for (vector<string>::iterator iter=connections_raw.begin(); iter!=connections_raw.end(); ++iter)
    {
        int del_idx = iter->find("-");
        string s1 = iter->substr(0, del_idx);
        string s2 = iter->substr(del_idx+1);

        if (s2 == "start")        
        {
            connections[s2].push_back(s1);
        } 
        else if (s1 == "start")
        {
            connections[s1].push_back(s2);
        }
        else if (s1 == "end")
        {
            connections[s2].push_back(s1);
        } 
        else if (s2 == "end")
        {
            connections[s1].push_back(s2);
        }
        else
        {
            connections[s1].push_back(s2);
            connections[s2].push_back(s1);
        }
    }

    vector<vector<string>> paths = {{"start"}};


    int max_loops = 50;
    int loops = 0;
    int path_num = 0;
    while (loops < max_loops) 
    {
        path_num = 0;
        vector<vector<string>> new_paths = paths; 
        for (int i=0; i<paths.size(); i++)
        {
            string last = paths[i][paths[i].size()-1];
            if (last == "end")
            {
                path_num += 1;
                continue;
            }

            vector<string> next_symbols;
            for (map<string,vector<string>>::iterator iter=connections.begin(); iter!=connections.end(); ++iter)
            {
                if (iter->first == last)
                {
                    for (int j=0; j<iter->second.size(); j++)
                    {
                        if (islower(iter->second[j][0]) && !count(paths[i].begin(), paths[i].end(), iter->second[j]))
                        {
                            next_symbols.push_back(iter->second[j]);
                        }
                        else if (!islower(iter->second[j][0]))
                        {
                            next_symbols.push_back(iter->second[j]);
                        }
                    }
                }
            }
   
            if (next_symbols.size() > 0)
            {
                new_paths[i].push_back(next_symbols[0]);
                for (int j=0; j<next_symbols.size()-1; j++)
                {
                    vector<string> new_path = paths[i];
                    new_path.push_back(next_symbols[j+1]); 
                    new_paths.push_back(new_path);
                }
            }
        }
        paths = new_paths;
        loops += 1;
    }

    // want to find all paths that go from start to end that visit small caves at most once 
    ostringstream out;
    out << path_num;
    return out.str();
}

bool num_entries_gt1(vector<string> strings)
{
    int sum = 0;
    map<string,int> m; 
    int x_idx = 0;
    for (int i=1; i<strings.size(); i++)
    {
        if (strings[i]== "start" || strings[i]== "end")
        {
            continue;
        }
        else 
        { 
            m[strings[i]] += 1; 
        }
    }

    for (map<string,int>::iterator iter=m.begin(); iter!=m.end(); ++iter)
    {
        sum += (iter->second > 1);
    }
    return sum;
}

string path_to_prefix(vector<string> path)
{
    string res = "";
    for (int i=0; i<path.size(); i++)
    {
        res += path[i] +  ",";
    }
    res.pop_back(); 
    return res;
}

int count_pattern_in_string(string pat, string txt)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;
   
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
  
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M) 
        {
           res++;
        }
    }
    return res;
}

string AocDay12::part2(string filename, vector<string> extra_args)
{
    vector<string> connections_raw = read_file_input(filename);
    map <string, vector<string>> connections;
    // Parse connections
    for (vector<string>::iterator iter=connections_raw.begin(); iter!=connections_raw.end(); ++iter)
    {
        int del_idx = iter->find("-");
        string s1 = iter->substr(0, del_idx);
        string s2 = iter->substr(del_idx+1);

        if (s2 == "start")        
        {
            connections[s2].push_back(s1);
        } 
        else if (s1 == "start")
        {
            connections[s1].push_back(s2);
        }
        else if (s1 == "end")
        {
            connections[s2].push_back(s1);
        } 
        else if (s2 == "end")
        {
            connections[s1].push_back(s2);
        }
        else
        {
            connections[s1].push_back(s2);
            connections[s2].push_back(s1);
        }
    }

    // Format: Current state, add lower case states visted already
    vector<vector<string>> paths = {{"start"}};

    int max_loops = 50;
    int loops = 0;
    int path_num = 0;
    while (loops < max_loops) 
    {
        vector<vector<string>> new_paths = paths; 
        vector<int> entries_to_del;
        for (int i=0; i<paths.size(); i++)
        {
            string last = paths[i][0];
            vector<string> next_symbols;
            for (map<string,vector<string>>::iterator iter=connections.begin(); iter!=connections.end(); ++iter)
            {
                if (iter->first == last)
                {
                    for (int j=0; j<iter->second.size(); j++)
                    {
                        if (islower(iter->second[j][0]) && num_entries_gt1(paths[i]) < 1 || iter->second[j] == "end")
                        {
                            next_symbols.push_back(iter->second[j]);
                        }
                        else if (islower(iter->second[j][0]) && count(paths[i].begin()+1,paths[i].end(), iter->second[j])<1)
                        {
                            next_symbols.push_back(iter->second[j]);
                        } 
                        else if (!islower(iter->second[j][0]))
                        {
                            next_symbols.push_back(iter->second[j]);
                        }
                    }
                }
            }
   
            if (next_symbols.size() > 0)
            {
                new_paths[i][0] = next_symbols[0];
                if (islower(next_symbols[0][0]))
                {
                    new_paths[i].push_back(next_symbols[0]);
                }

                for (int j=0; j<next_symbols.size()-1; j++)
                {
                    vector<string> new_path = paths[i];
                    new_path[0]=next_symbols[j+1]; 
                    if (islower(next_symbols[j+1][0]))
                    {
                        new_path.push_back(next_symbols[j+1]);
                    }
                    new_paths.push_back(new_path);
                }
            }
            else
            {
                new_paths[i][0] = "L"; 
            }
        }

        if (new_paths.size() == paths.size())
        {
            for (int i=0; i<new_paths.size(); i++)
            {
                if (!equal(new_paths[i].begin(), new_paths[i].end(), paths[i].begin()))
                {
                    break; 
                }
            }
            loops = 200;
        }

        for (vector<vector<string>>::iterator iter=new_paths.begin(); iter!=new_paths.end(); ++iter)
        {
            vector<string> vec = *iter;
            if (vec[0] == "end")
            {
                path_num++;
                new_paths.erase(iter);
                --iter;
            }
            else if (vec[0] == "L")
            {
                new_paths.erase(iter);
                --iter;
            }
        } 
        paths = new_paths;
        loops += 1;
    }

    // want to find all paths that go from start to end that visit small caves at most once 
    ostringstream out;
    out << path_num;
    return out.str();
}

