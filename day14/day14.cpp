#include <iostream>
#include <fstream>
#include <map>
#include <vector>

long long int apply_mask_a(std::string &mask, unsigned int value)
{
    int r;
    unsigned long long int incr = 1;
    unsigned long long int tot = 0;

    for (int i = 35; i >= 0; --i)
    {
        r = value % 2;
        if (mask[i] == '1')
        {
            r = 1;
        }
        else if (mask[i] == '0')
        {
            r = 0;
        }

        if (i != 35) incr *= 2;
        tot += r * incr;
        value /= 2;
    }

    return tot;
}

void part_a()
{
    std::ifstream file{"input.txt"};
    std::string word;
    std::string cur_mask;
    std::map<int, unsigned long long int> memory;
    while (file >> word)
    {
        if (word == "mask")
        {
            file >> word;
            file >> word;
            cur_mask = word;
        }
        else
        {
            std::string key, tmp;
            for (int i = 4; i < (word.size() - 1); ++i)
            {
                key += word[i];
            }

            file >> tmp;
            file >> tmp;

            memory[std::stoi(key)] =  apply_mask_a(cur_mask, std::stoi(tmp));
        }
    }

    long long int tot{0};
    for (auto &item : memory) tot += item.second;
    std::cout << "a: " << tot << std::endl;
}

// return by value ok: https://stackoverflow.com/a/15704602
std::vector<unsigned long long int> apply_mask_b(std::string &mask, unsigned int value)
{
    int r;
    unsigned long long int incr = 1;
    std::vector<unsigned long long int> keys{0};

    for (int i = 35; i >= 0; --i)
    {
        r = value % 2;
        if (i != 35) incr *= 2;

        if (mask[i] == 'X')
        {
            size_t n = keys.size();
            for (int j = 0; j < n; ++j)
            {
                keys.push_back(keys[j] + incr); 
            }
        }
        else 
        {
            if (mask[i] == '1') r = 1;
            for (int j = 0; j < keys.size(); ++j)
            {
                keys[j] += r * incr;
            }
        }

        value /= 2;
    }

    return keys;
}

void part_b()
{
    std::ifstream file{"input.txt"};
    std::string word;
    std::string cur_mask;
    std::map<unsigned long long int, int> memory;
    while (file >> word)
    {
        if (word == "mask")
        {
            file >> word;
            file >> word;
            cur_mask = word;
        }
        else
        {
            std::string key, tmp;
            for (int i = 4; i < (word.size() - 1); ++i)
            {
                key += word[i];
            }

            file >> tmp;
            file >> tmp;

            int value = std::stoi(tmp); 
            for (auto &item : apply_mask_b(cur_mask, std::stoi(key))) 
            {
                memory[item] = value;
            }
        }
    }

    long long int tot{0};
    for (auto &item : memory) tot += item.second;
    std::cout << "b: " << tot << std::endl;     
}

int main()
{
    part_a();
    part_b();
    return 0;
}