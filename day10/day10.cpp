#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;
    std::vector<int> numbers{};
    while (file >> line) numbers.push_back(std::stoi(line));

    // PART A
    int start = 0;
    auto cursor = numbers.begin();
    std::map<int, int> list{};
    while (cursor != numbers.end())
    {   
        auto it = cursor;
        auto current = cursor;
        int min = std::numeric_limits<int>::max();
        while (it != numbers.end())
        {
            int diff = std::abs(start - *it);
            if (diff < min)
            {
                min = diff;
                current = it;
            }
            ++it;
        }

        list[min]++;
        start = *current;
        std::iter_swap(cursor, current);
        ++cursor;
    }

    list[3]++;
    std::cout << "a: " << list[1] * list[3] << std::endl;

    // PART B
    std::sort(numbers.begin(), numbers.end());
    numbers.push_back(numbers[numbers.size() - 1] + 3);

    std::map<int, long int> n_ways;
    n_ways[0] = 1;  
    for (int i : numbers)
    {
        n_ways[i] = n_ways[i - 1] + n_ways[i - 2] + n_ways[i - 3];
    }

    std::cout << "b: " << n_ways[numbers[numbers.size() - 1]] << std::endl;

    return 0;
}