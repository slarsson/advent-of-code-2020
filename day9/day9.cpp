#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    const int size = 25;
    int numbers[size];

    int idx = 0;
    int n = 0;
    std::vector<int> list{};

    while (std::getline(file, line))
    {
        n = std::stoi(line);
        if (idx >= size)
        {
            bool ok = false;
            for (int i = 0; i < size - 1; ++i)
            {
                for (int j = i + 1; j < size; ++j)
                {
                    if (numbers[i] + numbers[j] == n)
                    {                        
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }

            if (!ok)
            {
                std::cout << "a: " << n << std::endl;
                break;
            }
        }
        
        list.push_back(n);
        numbers[idx % size] = n;
        ++idx;
    }

    int sum = 0;    
    int start = 0;
    int cursor = 0;
    while (cursor < list.size())
    {
        sum += list[cursor];

        if (sum == n)
        {
            auto end = list.begin() + cursor + 1;
            auto it = list.begin() + start;
            int min = std::numeric_limits<int>::max();
            int max = 0;
            while (it != end)
            {
                if (*it < min) min = *it;
                if (*it > max) max = *it;
                ++it;
            }

            std::cout << "b: " << min + max << std::endl;
            break;
        }
        else if (sum > n)
        {
            sum = 0;
            ++start;
            cursor = start;
        }
        else
        {
            ++cursor;
        }
    }
}