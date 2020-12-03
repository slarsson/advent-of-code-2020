#include <iostream>
#include <fstream>
#include <vector>

int slope(std::vector<std::string> &vec, int right, int down)
{
    auto it = vec.begin();
    int width = it->size();
    int left_pos = right;
    long int count = 0;
    
    it += down;
    while (it < vec.end())
    {
        left_pos %= width;
        if (it->operator[](left_pos) == '#') ++count;
        left_pos += right;
        it += down;
    }

    return count;
}

int main()
{
    std::ifstream file{"input.txt"};
    
    std::vector<std::string> rows{};
    std::string line;
    while(std::getline(file, line)) rows.push_back(line);

    int a = slope(rows, 3, 1);
    std::cout << a << std::endl;

    long int b = a;
    b *= slope(rows, 1, 1);
    b *= slope(rows, 5, 1);
    b *= slope(rows, 7, 1);
    b *= slope(rows, 1, 2);

    std::cout << b << std::endl;
    return 0;
}