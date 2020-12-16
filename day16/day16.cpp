#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>

// KAOZ :(
int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    int size = 20;

    std::map<std::string, std::vector<int>> ranges;
    int ticket[size];
    std::vector<std::vector<int>> tickets;

    while (std::getline(file, line))
    {
        if (line == "") continue;
        if (line == "your ticket:") break;

        std::cout << line << std::endl;

        std::istringstream s{line};
        
        std::string tmp = "";
        while (s >> tmp)
        {
            std::string key = tmp;

            std::string p1 = "";
            std::string p2 = "";

            s >> p1;
            s >> tmp;
            s >> p2;

            p1 += "-" + p2;

            std::string n = "";
            for (size_t i = 0; i < p1.size(); ++i)
            {
                if (p1[i] == '-')
                {
                    ranges[key].push_back(std::stoi(n));
                    n = "";
                }
                else
                {
                    n += p1[i];
                }
            }

            ranges[key].push_back(std::stoi(n));
        }
    }

    while (std::getline(file, line))
    {
        if (line == "") continue;
        if (line == "nearby tickets:") break;

        std::string tmp;
        int j = 0;
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == ',')
            {
                ticket[j] = std::stoi(tmp);
                ++j;
                tmp = "";
            }
            else
            {
                tmp += line[i];
            }
        }

        ticket[size - 1] = std::stoi(tmp);
    }

    int i = 0;
    int idx = 0;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
        tickets.push_back(std::vector<int>());
        
        std::string tmp = "";
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == ',')
            {
                tickets[idx].push_back(std::stoi(tmp));
                tmp = "";
            }
            else
            {
                tmp += line[i];
            }
        }
        tickets[idx].push_back(std::stoi(tmp));
        ++idx;
    }

    int z = 0;
    for (auto &t1 : tickets)
    {
        for (auto val : t1)
        {   
            bool ok = false;
            for (auto r : ranges)
            {
                if (
                    (val >= r.second[0] && val <= r.second[1]) || 
                    (val >= r.second[2] && val <= r.second[3])
                )
                {
                    ok = true;
                }
            }

            if (!ok)
            {
                z += val;
                t1[0] = -1;
            }
        }
    }

    std::cout << "a: " << z << std::endl;


    // b
    std::vector<std::vector<std::string>> cols;
   
    for (size_t i = 0; i < size; ++i)
    {
        cols.push_back(std::vector<std::string>());
        for (auto &r : ranges)
        {
            cols[i].push_back(r.first);
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        for (auto &cur_ticket : tickets)
        {
            if (cur_ticket[0] == -1) continue;
            for (auto &r : ranges) {
                if (!((cur_ticket[i] >= r.second[0] && cur_ticket[i] <= r.second[1]) || (cur_ticket[i] >= r.second[2] && cur_ticket[i] <= r.second[3])))
                {                    
                    auto it = std::find(cols[i].begin(), cols[i].end(), r.first);
                    if (it != cols[i].end())
                    {
                        cols[i].erase(it);
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << "i: " << i << " = " << cols[i].size() << " => ";
        for (auto &s : cols[i])
        {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "=================================" << std::endl;

    long int b = 1;
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            if (cols[j].size() == 1)
            { 
                std::string key = cols[j][0];
                std::cout << key << " => " << j << std::endl;

                if (
                    key == "departurelocation:" ||
                    key == "departurestation:" ||
                    key == "departureplatform:" ||
                    key == "departuretrack:" ||
                    key == "departuredate:" ||
                    key == "departuretime:"
                )
                {
                    b *= ticket[j];
                }

                for (auto &list : cols)
                {
                    auto it = std::find(list.begin(), list.end(), key);
                    if (it != list.end())
                    {
                        list.erase(it);
                    }
                }
            }
        }
    }

    std::cout << "b: " << b << std::endl;
    return 0;
}