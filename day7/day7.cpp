#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cctype>
#include <string>
#include <set>

typedef std::map<std::string, std::vector<std::pair<std::string, int>>> bags;

int find_bags(std::string &key, bags &list)
{
    int n{0};
    for (auto &item : list[key])
    {
        if (list.count(item.first) == 0)
        {
            n += item.second;
        }
        else
        {
            n += item.second + item.second * find_bags(item.first, list);
        }
    }

    return n;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;
    bags list;

    while (std::getline(file, line))
    {
        int n{0};
        std::string color, key, word;
        std::istringstream ss{line};

        while (ss >> word)
        {
            if (word == "contain")
            {
                key = color;
                color = "";
                continue;
            }
            else if (word == "no")
            {
                color = "";
                break;
            }
            else if  (word == "bags")
            {
                continue;
            } 
            else if (word == "bag" || word == "bag," || word == "bag." || word == "bags," || word == "bags.")
            {                
                list[key].push_back(std::pair<std::string, int>(color, n));
                color = "";
                continue;
            }
            else if (std::isdigit(word[0])) // assume max = 9
            {
                n = std::stoi(word);
                continue;
            }

            color += word;
        }
    }

    std::vector<std::string> target_list{"shinygold"};
    std::set<std::string> colors;
    while (target_list.size() != 0)
    {
        std::string target = target_list[target_list.size() - 1];
        target_list.pop_back();
        for (auto &row : list)
        {
            for (const auto &item : row.second)
            {
                if (item.first == target)
                {
                   target_list.push_back(row.first);
                   colors.insert(row.first);
                }
            }
        }
    }

    std::cout << "a: " << colors.size() << std::endl;
    
    std::string start = "shinygold";
    std::cout << "b: " << find_bags(start, list) << std::endl;

    return 0;
}