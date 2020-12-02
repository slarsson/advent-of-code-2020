#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

int main()
{
    std::ifstream infile{"input.txt"};

    int a_count = 0;
    int b_count = 0;

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream ss{line};
        std::string numbers, c_temp, word;
        ss >> numbers >> c_temp >> word;

        int a, b;
        char c = c_temp[0];

        std::replace(numbers.begin(), numbers.end(), '-', ' ');
        std::istringstream temp{numbers};
        temp >> a >> b;

        int n = 0;
        for (size_t i = 0; i < word.size(); ++i)
        {
            if (word[i] == c)
            {
                n++;
            }
        }

        if (n <= b && n >= a)
        {
            a_count++;
        }

        bool _a = (c == word[a - 1]);
        bool _b = (c == word[b - 1]);

        // XOR
        if ((_a || _b) && _b != _a)
        {
            b_count++;
        } 
    }

    std::cout << a_count << "\n" << b_count << std::endl;
}