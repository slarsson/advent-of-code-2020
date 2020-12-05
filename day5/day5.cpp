#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream file{"input.txt"};

    int id = 0;
    std::string line{};
    std::vector<int> ids{};
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;

        int row = 127;
        int row_offset = 0;
        for (int i = 0; i < 8; ++i)
        {
            row /= 2;
            if (line[i] == 'B') row_offset += row + 1;
        }

        int col = 8;
        int col_offset = 0;
        for (int i = 0; i < 3; ++i)
        {
            col /= 2;
            if (line[i + 7] == 'R') col_offset += col;
        }

        int tmp = 8 * row_offset + col_offset;
        std::cout << row_offset << " " << col_offset << " " << tmp << std::endl;
        ids.push_back(tmp);
        if (tmp > id) id = tmp;
    }
    
    std::cout << id << std::endl;

    auto range = std::minmax_element(ids.begin(), ids.end());
    for (int i = *range.first; i <= *range.second; ++i)
    {
        bool p1 = false;
        bool m1 = false;
        bool self = false;
        for (int j = 0; j < ids.size(); ++j)
        {
            if (ids[j] == (i - 1)) m1 = true;
            if (ids[j] == (i + 1)) p1 = true;
            if (ids[j] == i) self = true;
        }

        if (!self && p1 && m1)
        {
            std::cout << i << std::endl;
        }
    }
}