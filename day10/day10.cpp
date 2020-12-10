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

    long int tot = 1;
    int range = 0;
    int prev = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        int diff = *it - prev;
        prev = *it;

        // assume diff = 2 never happends :)
        if (diff >= 3)
        {
            if (range > 1)
            {
                if (range == 2)
                {
                    tot *= 2;
                }
                else if (range == 3)
                {
                    tot *= 4; // every 3-group has 4 possible combinations
                }
                else
                {
                    tot *= (4 + (range - 1));
                }
            }
            
            range = 0;
        }
        else
        {
            ++range;
        }

        *it = diff;
    }

    std::cout << "b: " << tot << std::endl;
    return 0;
}