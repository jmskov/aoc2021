#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <map>

#include "aoc_day_8.h"
#include "file_utils.h"

using namespace std;

AocDay8::AocDay8():AocDay(8)
{
}

AocDay8::~AocDay8()
{
}

vector<map<char, vector<string>>> AocDay8::read_file_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<map<char, vector<string>>> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string raw = *iter;
        int mid_idx = raw.find('|');
        vector<string> codes;

        int str_x = 0;
        for (int i=0;i<=mid_idx;i++)
        {
            if (raw[i] == ' ' || i == mid_idx-1)
            {
                codes.push_back(raw.substr(str_x,i-str_x));
                str_x = i + 1;
            } 
        }
        
        vector<string> outputs;
        str_x = mid_idx+2;
        for (int i=mid_idx+3;i<raw.length();i++)
        {
            if (raw[i] == ' ')
            {
                outputs.push_back(raw.substr(str_x,i-str_x));
                str_x = i+1;
            } 
            else if (i == raw.length() - 1)
            {
                outputs.push_back(raw.substr(str_x,i-str_x + 1));
                str_x = i+1;
            } 
        }

        map<char, vector<string>> mm = { {'C', codes}, {'O', outputs} };
        data.push_back(mm);
    }

    return data;
}

string AocDay8::part1(string filename, vector<string> extra_args)
{
    vector<map<char, vector<string>>> data = read_file_input(filename);

    int sum = 0;
    for (int i=0; i<data.size(); i++)
    {
        vector<string> outputs = data[i]['O'];
        for (vector<string>::iterator iter=outputs.begin(); iter!=outputs.end(); ++iter)
        {
            if (iter->length() == 2 || iter->length() == 4 || iter->length() == 3 || iter->length() == 7)
            {
                sum += 1;
            }
        }
    }
    ostringstream out;
    out << (int) sum;
    return out.str();
}

string find_entry_with_length(vector<string> vec, int len)
{
    for (int i=0; i<vec.size(); i++)
    {
        if (vec[i].length() == len)
        {
            return vec[i];
        }
    }
    return "";
}

char find_diff_char(string a, string b)
{
    for (int i=0; i<a.length(); i++)
    {
        bool uncommon = true;
        for (int j=0; j<b.length(); j++)
        {
            if (b[j] == a[i])
            {
                uncommon = false;
                break;
            } 
        } 
        if (uncommon)
        {
            return a[i];
        }
    }
    return 'q';
}

string find_entry_with_chars_and_length(vector<string> entries, vector<char> chars, int len, string not_this)
{
    for(int i=0; i<entries.size(); i++)
    {
        if (entries[i].length() == len)
        {
           
            int chars_had = 0; 
            for (int j=0; j<chars.size(); j++)
            {
                bool has_char = false;
                for (int k=0; k<entries[i].length(); k++)
                {
                    if (chars[j] == entries[i][k]) 
                    {
                        has_char = true;
                        chars_had += 1;
                    } 
                } 
                if (!has_char)
                {
                    break;
                }
            }
            if (chars_had == chars.size() && entries[i] != not_this)
            {
                return entries[i];
            }
        }
    }
    return "";
}

char decode_number(string number, map<char, char> decoder)
{
    switch(number.length())
    {
        case 2:
            return '1';
        case 3:
            return '7';
        case 4: 
            return '4';
        case 7:
            return '8';
    }

    string decoded = "";
    for (int i=0; i<number.length(); i++)
    {
        decoded.push_back(decoder[number[i]]);
    }
    
    switch(decoded.length())
    {
        case 5:
            if (strchr(decoded.c_str(), 'e'))
            {
                return '2';
            }
            else if (strchr(decoded.c_str(), 'c'))
            {
                return '3';
            }
            else
            {
                return '5';
            }
            break;
        case 6:
            //if (decoded.find('c')!=string::npos && decoded.find('e')!=string::npos)
            if(strchr(decoded.c_str(), 'c') && strchr(decoded.c_str(), 'd'))
            {
                return '9';
            }
            else if(strchr(decoded.c_str(), 'e') && strchr(decoded.c_str(), 'd'))
            {
                return '6';
            }
            else
            {
                return '0';
            }
            break;
    }
    return ' ';
}

string AocDay8::part2(string filename, vector<string> extra_args)
{
    vector<map<char, vector<string>>> data = read_file_input(filename);

    long sum = 0;
    for (int i=0; i<data.size(); i++)
    {
        vector<string> outputs = data[i]['C'];
        vector<string> numbers = data[i]['O'];
        map<char, char> decoding;
        
        string one = find_entry_with_length(outputs, 2);
        string seven = find_entry_with_length(outputs, 3);
        decoding['a'] = find_diff_char(seven, one); 
        
        string four = find_entry_with_length(outputs, 4);   
        vector<char> one_chars(one.begin(), one.end());

        string three = find_entry_with_chars_and_length(outputs, one_chars, 5, "");
        decoding['b'] = find_diff_char(four, three);

        vector<char> five_help_chars = {decoding['b']};
        string five = find_entry_with_chars_and_length(outputs, five_help_chars, 5, ""); 
        decoding['c'] = find_diff_char(four, five); 

        if (one[0] == decoding['c'])
        {
            decoding['f'] = one[1];
        }
        else
        {
            decoding['f'] = one[0];
        }
        
        for (int i=0; i<four.length(); i++)
        {
            if (four[i] != decoding['f'] && four[i] != decoding['b'] && four[i] != decoding['c']) 
            {
                decoding['d'] = four[i];
                break;
            }
        } 

        for (int i=0; i<three.length(); i++)
        {
            if (three[i] != decoding['a'] && three[i] != decoding['c'] && three[i] != decoding['d'] && three[i] != decoding['f'])
            {
                decoding['g'] = three[i];
                break;
            }
        } 
        
        vector<char> two_help_chars = {decoding['a'], decoding['c'], decoding['d'], decoding['g']};
        string two = find_entry_with_chars_and_length(outputs, two_help_chars, 5, three);
        decoding['e'] = find_diff_char(two, three); 
      
        string num = "";

        map<char, char> decoder;
        for(auto it = decoding.cbegin(); it != decoding.cend(); ++it)
        {
            decoder[it->second] = it->first;
        }

        for(auto it = decoding.cbegin(); it != decoding.cend(); ++it)
        {
            int sum = 0; 
            
            for(auto it2 = decoding.cbegin(); it2 != decoding.cend(); ++it2)
            {
                if (it->second == it2->second)
                {
                    sum += 1;
                }
            }
            if (sum > 1)
            {
            }
        }
 
        for (int j=0; j<numbers.size(); j++)
        {
            num.push_back(decode_number(numbers[j], decoder));
        }
        sum += stol(num);           
    }

    ostringstream out;
    out << sum;
    return out.str();
}
