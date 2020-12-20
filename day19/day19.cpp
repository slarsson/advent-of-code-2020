#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>

int check_a(int rn, std::string target, std::unordered_map<int, std::vector<std::vector<int>>> &rules, int a, int b)
{
    // break if the "last" rule (a or b), otherwise the rule wont be vaild = return -1
    if (rules[rn].size() == 0)
    {
        if (rn == a && target[0] == 'a') return 1;
        if (rn == b && target[0] == 'b') return 1;
        return -1;
    }

    for (auto rule : rules[rn])
    {
        int acc = 0;
        for (int val : rule)
        {
            int ret = check_a(val, target.substr(acc, target.size()), rules, a, b);
            if (ret == -1)
            {
                acc = -1;
                break;
            }
            acc += ret;
        }
        if (acc != -1) return acc;
    }
    return -1;
}

std::vector<int> check_b(int rn, std::string target, std::unordered_map<int, std::vector<std::vector<int>>> &rules, int a, int b)
{
    if (rules[rn].size() == 0)
    {
        if (rn == a && target[0] == 'a') return std::vector<int>{1};
        if (rn == b && target[0] == 'b') return std::vector<int>{1};
        return std::vector<int>{};
    }

    std::vector<int> branches;
    for (auto rule : rules[rn])
    {
        std::vector<int> acc{0};
        for (int val : rule)
        {
            std::vector<int> swag;
            for (int ac : acc)
            {
                auto ret = check_b(val, target.substr(ac, target.size()), rules, a, b);
                for (auto c : ret)
                {
                    swag.push_back(c + ac);
                }
            }
            acc = swag;    
        }
        for (auto val : acc) branches.push_back(val);
    }
    return branches;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    std::unordered_map<int, std::vector<std::vector<int>>> rules;
    
    int a = -1;
    int b = -1;
    
    while (std::getline(file, line))
    {
        if (line == "") break;
        std::stringstream ss{line};
        std::string word;

        ss >> word;
        int key = std::stoi(word.substr(0, word.size() - 1));
        
        ss >> word;
        if (word == "\"a\"")
        {
            a = key;
            continue;
        }
        else if (word == "\"b\"")
        {
            b = key;
            continue;
        }
        else
        {
            rules[key] = std::vector<std::vector<int>>();
            rules[key].push_back(std::vector<int>());
            rules[key][0].push_back(std::stoi(word));
        }

        int idx = 0;
        while(ss >> word)
        {
            if (word == "|")
            {
                ++idx;
                rules[key].push_back(std::vector<int>());
            }
            else
            {
                rules[key][idx].push_back(std::stoi(word));
            }
        }
    }

    std::cout << "rules: " << rules.size() << " a: " << a << " b: " << b << std::endl;

    std::vector<std::string> input;
    while (std::getline(file, line)) input.push_back(line);

    int a_count = 0;
    int b_count = 0;
    for (auto s : input)
    {
        if (check_a(0, s, rules, a, b) == s.size()) ++a_count;
    }

    rules[8] = {{42}, {42, 8}};
    rules[11] = {{42, 31}, {42, 11, 31}};

    for (auto s : input)
    {
        std::vector<int> lengths = check_b(0, s, rules, a, b);
        for (auto l : lengths)
        {
            if (l == s.size()) ++b_count;
        }
    }

    std::cout << "a: " << a_count << std::endl;
    std::cout << "b: " << b_count << std::endl;

    return 0;
}