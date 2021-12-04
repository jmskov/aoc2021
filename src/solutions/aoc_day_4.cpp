#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <bitset>

#include "aoc_day_4.h"
#include "file_utils.h"

using namespace std;

AocDay4::AocDay4():AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

vector<int> AocDay4::read_call_order(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<int> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    // Just need the first line!!
    // There is probably a better way to do this...
    string to_convert = raw_lines[0];
    // Now, parse out each call using comma delimitor
    int start_idx = 0;
    for (int j=0; j<to_convert.length(); j++)
    {
        if (to_convert[j] == ',')
        {
            string substr = to_convert.substr(start_idx,j-start_idx);
            int new_call = stoi(substr);
            data.push_back(new_call);
            start_idx = j+1;
        } 
        else if(j == to_convert.length()-1) 
        {
            string substr = to_convert.substr(start_idx);
            int new_call = stoi(substr);
            data.push_back(new_call);
        }
    }
    return data;
}

vector<vector<int>> AocDay4::read_game_boards(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<vector<int>> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
  
    vector<int> gameboard; 
    int count = 0;
    // Skip the first line!!
    for (int i=2; i<raw_lines.size(); i++)
    {
        string to_convert = raw_lines[i];
        vector<int> row;
        // Now, parse out each call using comma delimitor
        int start_idx = 0;
        for (int j=0; j<5; j++)
        {
            string substr = to_convert.substr(start_idx,2);
            substr.erase(remove(substr.begin(), substr.end(), ' '), substr.end());
            int new_call = stoi(substr);
            gameboard.push_back(new_call);
            start_idx += 3;
            count += 1;
        }
        if (count == 25)
        {
            count = 0;
            data.push_back(gameboard);
            gameboard.clear();
            i++;
        }
    }
    return data;
}

void print_vector(vector<int> vec) 
{
    for(int i=0; i<vec.size(); i++)
    {
        cout << vec[i] << ",";
    }
    cout << endl;
}

static bool is_board_winning(bitset<25> state)
{
    vector<int> col_sums(5,0);
    // check if any rows sum to 5
    for(int i=0; i<25; i+=5)
    {
        int row_sum = 0;
        for (int j=0; j<5; j++)
        {
            if (state[i+j]) 
            {
                row_sum += 1;
                col_sums[j] += 1;
            }
        }
        if (row_sum == 5)
        {
            return true;
        }
    }

    // Check if any columns sum to 5
    for (int i=0; i<5; i++)
    {
        if (col_sums[i] == 5)
        {
            return true;
        }
    }
    return false;
}

static bitset<25> update_game_board(vector<int> board, bitset<25> state, int call)
{
    bitset<25> new_state = state;
    for (int i=0; i<board.size(); i++)
    {
        if (board[i] == call) 
        {
            new_state.set(i,true);
            break;
        }
    }
    return new_state;
}

string AocDay4::part1(string filename, vector<string> extra_args)
{
    vector<int> calls = read_call_order(filename);
    vector<vector<int>> boards = read_game_boards(filename);
    vector<bitset<25>> board_states;
    for (int i=0; i<boards.size(); i++)
    {
        bitset<25> b;
        board_states.push_back(b);
    }

    print_vector(boards[boards.size()-1]);

    int winning_board;
    long last_num;

    for(int i=0; i<calls.size(); i++)
    {
        // Update the boards - return bool
        for(int j=0; j<boards.size(); j++)
        {
            board_states[j] = update_game_board(boards[j], board_states[j], calls[i]);
            bool is_winning = is_board_winning(board_states[j]);
            if (is_winning)
            {
                winning_board = j;
                last_num = calls[i];
                i = calls.size();   // crappy break 
            }
        }
    }
    
    // Now calculate the product
    long sum = 0;
    for (int i=0; i<25; i++)
    {
        if (!board_states[winning_board][i])
        {
            sum += boards[winning_board][i];
        }
    }

    ostringstream out;
    out << last_num*sum;
    return out.str();
}

string AocDay4::part2(string filename, vector<string> extra_args)
{
    vector<int> calls = read_call_order(filename);
    vector<vector<int>> boards = read_game_boards(filename);
    vector<bitset<25>> board_states;
    for (int i=0; i<boards.size(); i++)
    {
        bitset<25> b;
        board_states.push_back(b);
    }

    print_vector(boards[boards.size()-1]);

    int winning_board;
    long last_num;

    vector<int> winning_boards(boards.size(), -1);

    for(int i=0; i<calls.size(); i++)
    {
        // Update the boards - return bool
        for(int j=0; j<boards.size(); j++)
        {
            if (*find(winning_boards.begin(), winning_boards.end(), j) == j)
            {
                continue;
            }
            board_states[j] = update_game_board(boards[j], board_states[j], calls[i]);
            bool is_winning = is_board_winning(board_states[j]);
            if (is_winning) 
            {
                winning_board = j;
                winning_boards[j] = j;
                last_num = calls[i];
            }
        }
    }
    
    // Now calculate the product
    long sum = 0;
    for (int i=0; i<25; i++)
    {
        if (!board_states[winning_board][i])
        {
            sum += boards[winning_board][i];
        }
    }

    ostringstream out;
    out << last_num*sum;
    return out.str();
}
