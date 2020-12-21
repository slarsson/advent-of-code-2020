#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <vector>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    std::unordered_map<std::string, std::unordered_map<std::string, int>> allergens;
    std::unordered_map<std::string, std::vector<std::string>> list;
    
    std::vector<std::string> taken;
    std::map<std::string, std::string> taken_b; 

    int n_words = 0;
    std::unordered_map<std::string, int> count;

    while (std::getline(file, line))
    {
        std::istringstream ss{line};
        std::string word;

        std::vector<std::string> words;
        while (ss >> word)
        {
            if (word[0] == '(') break;
            words.push_back(word);
            count[word]++;
            ++n_words;
        }

        while (ss >> word)
        {
            if (word[word.size() - 1] == ',' || word[word.size() - 1] == ')')
            {
                word = word.substr(0, word.size() - 1);
            }

            for (auto &s : words)
            {
                allergens[word][s]++;
            }
        }
    }

    for (auto &allergen : allergens)
    {
        int max = 0;
        for (auto &item : allergen.second)
        {
            if (item.second > max)
            {
                max = item.second;
            }
        }

        auto it = allergen.second.begin();
        while (it != allergen.second.end())
        {
            if (it->second < max)
            {
                it = allergen.second.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto &item : allergen.second)
        {
            list[allergen.first].push_back(item.first);
        }
    }

    while (list.size() != 0)
    {
        auto it = list.begin();
        while (it != list.end())
        {
            if (it->second.size() == 1)
            {   
                auto val = it->second.begin();
                taken.push_back(val[0]);
                taken_b[it->first] = val[0];
                it = list.erase(it);
            } 
            else
            {
                auto v_it = it->second.begin();
                while (v_it != it->second.end())
                {
                    bool rm = false;
                    for (auto &item : taken)
                    {
                        if (item == *v_it)
                        {
                            v_it = it->second.erase(v_it);
                            rm = true;
                        }
                    }
                    if (!rm) ++v_it;
                }
                ++it;
            }
        }
    }

    int a = 0;
    for (auto &item : taken) a += count[item];
    std::cout << "a: " << n_words - a << std::endl;

    std::string b = "";
    for (auto &x : taken_b)
    {
        b += x.second + ',';
        std::cout << x.first << "=" << x.second << std::endl;
    }
    std::cout << "b: " << b.substr(0, b.size() - 1) << std::endl;

    return 0;
}