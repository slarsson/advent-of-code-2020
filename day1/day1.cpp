#include <iostream>
#include <fstream>
#include <vector>

void part_one(std::vector<int> &numbers)
{
    size_t size = numbers.size();
    [&] {
        for (int i = 0; i < (size - 1); ++i)
        {
            for (int j = (i + 1); j < size; ++j)
            {
                if (numbers[i] + numbers[j] == 2020)
                {
                    std::cout << numbers[i] * numbers[j] << std::endl; 
                    return;
                }
            }
        }
    }();
}

void part_two(std::vector<int> &numbers)
{
    size_t size = numbers.size();
    [&] {
        for (int i = 0; i < (size - 2); ++i)
        {
            for (int j = (i + 1); j < (size - 1); ++j)
            {
                for (int k = (j + 1); k < size; ++k)
                {
                    if (numbers[i] + numbers[j] + numbers[k] == 2020)
                    {
                        std::cout << numbers[i] * numbers[j] * numbers[k] << std::endl; 
                        return;
                    }
                }
            }
        }
    }();
}

int main()
{
    std::vector<int> numbers{};
    std::ifstream infile{"input.txt"};

    int x;
    while (infile >> x)
    {
        numbers.push_back(x);
    }

    part_one(numbers);
    part_two(numbers);

    return 0;
}