#include <iostream>
#include <fstream>
#include <deque>
#include <unordered_map>

std::string to_string(std::deque<int> &q1, std::deque<int> &q2)
{
    std::string ret = "";
    for (int x : q1) ret += std::to_string(x) + ',';
    ret += "--";
    for (int x : q2) ret += std::to_string(x) + ',';
    return ret;
}

void print(std::deque<int> &q1, std::deque<int> &q2)
{
    std::string ret = "";
    for (int x : q1) ret += std::to_string(x) + ',';
    std::cout << "p1: " << ret << std::endl;

    ret = "";
    for (int x : q2) ret += std::to_string(x) + ',';
    std::cout << "p2: " << ret << std::endl;
    std::cout << "=====================" << std::endl;
}

int game(std::deque<int> &q1, std::deque<int> &q2)
{
    std::unordered_map<std::string, bool> plays;
    while (q1.size() != 0 && q2.size() != 0)
    {
        //print(q1, q2);
        std::string state = to_string(q1, q2);
        if (plays[state])
        {
            return 1;
        }
        else
        {
            plays[state] = true;
        }
    
        int v1 = q1[0];
        q1.pop_front();
        int v2 = q2[0]; 
        q2.pop_front();
        
        if (q1.size() >= v1 && q2.size() >= v2)
        {
            
            std::deque<int> new_q1;
            for (int i = 0; i < v1; ++i)
            {
                new_q1.push_back(q1[i]);
            }

            std::deque<int> new_q2;
            for (int i = 0; i < v2; ++i)
            {
                new_q2.push_back(q2[i]);
            }

            if (game(new_q1, new_q2) == 1)
            {
                q1.push_back(v1);
                q1.push_back(v2);
            }
            else
            {
                q2.push_back(v2);
                q2.push_back(v1);
            }
        }
        else
        {
            if (v1 > v2)
            {
                q1.push_back(v1);
                q1.push_back(v2);
            }
            else
            {
                q2.push_back(v2);
                q2.push_back(v1);
            }
        }
    }

    if (q1.size() == 0) return 2;
    return 1;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    std::deque<int> p1_a;
    std::deque<int> p1_b;
    std::deque<int> p2_a;
    std::deque<int> p2_b;
    std::deque<int> *cur = nullptr;

    while (std::getline(file, line))
    {
        if (line == "") continue;
        if (line == "Player 1:")
        {
            cur = &p1_a;
            continue;
        }
        else if (line == "Player 2:")
        {
            cur = &p2_a;
            continue;
        }
        cur->push_back(std::stoi(line));
    }

    for (int x : p1_a) p1_b.push_back(x);
    for (int x : p2_a) p2_b.push_back(x);

    // PART A
    while (p1_a.size() != 0 && p2_a.size() != 0)
    {
        int v1 = p1_a[0];
        p1_a.pop_front();
        int v2 = p2_a[0]; 
        p2_a.pop_front();
        
        if (v1 > v2)
        {
            p1_a.push_back(v1);
            p1_a.push_back(v2);
        }
        else
        {
            p2_a.push_back(v2);
            p2_a.push_back(v1);
        }
    }

    cur = &p1_a;
    if (cur->size() == 0) cur = &p2_a;
    
    int start = cur->size();
    int acc = 0;
    for (auto &val : *cur)
    {
        acc += start * val;
        --start;
    }

    std::cout << "a: " << acc << std::endl;

    // PART B
    game(p1_b, p2_b);
    cur = &p1_b;
    if (cur->size() == 0) cur = &p2_b;
    start = cur->size();
    acc = 0;
    for (auto &val : *cur)
    {
        acc += start * val;
        --start;
    }

    std::cout << "b: " << acc << std::endl;
}