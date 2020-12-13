#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;
    
    std::getline(file, line);
    int departure = std::stoi(line);

    std::vector<int> a_interval;
    std::vector<std::pair<int, int>> b_interval;

    int offset = -1;
    while (std::getline(file, line, ','))
    {
        ++offset;
        if (line == "x") continue;
        a_interval.push_back(std::stoi(line));
        b_interval.push_back(std::pair<int, int>(std::stoi(line), offset));
    }

    // PART A
    int min = std::numeric_limits<int>::max();
    int id = 0;
    for (int x : a_interval)
    {
        int timestamp = departure - (departure % x) + x;
        if (timestamp < min)
        {
            min = timestamp;
            id = x;
        }
    }
    
    std::cout << "a: " << id * (min - departure) << std::endl;

    // PART B
    // rip.. https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfozjr4/?utm_source=reddit&utm_medium=web2x&context=3
    long long int timestamp = 0;
    long long int incr = b_interval[0].first;
    for (int i = 1; i < b_interval.size(); ++i)
    {
        while (true)
        {
            timestamp += incr;
            if (((timestamp + b_interval[i].second) % b_interval[i].first) == 0) break;
        }        
        incr *= b_interval[i].first;  // wtf..
    }

    std::cout << "b: " << timestamp << std::endl;

    return 0;
}