#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream file{"input.txt"};

    int dim = 98 + 2;

    char grid[dim * dim];
    char tmp_grid[dim * dim];
    std::fill_n(grid, dim * dim, '.'); // orkar inte..
    std::fill_n(tmp_grid, dim * dim, '.'); // orkar inte..

    int offset = dim + 1;
    std::string line;
    while (std::getline(file, line))
    {  
        for (int i = 0; i <= line.size(); ++i)
        {
            if (line[i] != '.' && line[i] != 'L' && line[i] != '#') continue;
            grid[offset + i] = line[i];  
            tmp_grid[offset + i] = line[i];    
        }
        offset += dim;
    }

    int n_diffs = 1337;
    int occupied = 0;
    while (n_diffs > 0)
    {
        n_diffs = 0;
        occupied = 0;
        offset = dim + 1;
        for (int i = offset; i < (dim * dim - dim - 1); ++i)
        {
            if (grid[i] == '.') continue;

            int taken = 0;
            if (grid[i - 1] == '#') ++taken; 
            if (grid[i + 1] == '#') ++taken;
            if (grid[i - dim] == '#') ++taken;
            if (grid[i - dim - 1] == '#') ++taken;
            if (grid[i - dim + 1] == '#') ++taken;
            if (grid[i + dim] == '#') ++taken;
            if (grid[i + dim - 1] == '#') ++taken;
            if (grid[i + dim + 1] == '#') ++taken;

            if (taken == 0)
            {
                tmp_grid[i] = '#';
                if (grid[i] != tmp_grid[i]) ++n_diffs;
            }
            else if (taken >= 4)
            {
                tmp_grid[i] = 'L';
                if (grid[i] != tmp_grid[i]) ++n_diffs;
            }
        }
        
        for (int i = 0; i < (dim * dim); ++i) 
        {
            grid[i] = tmp_grid[i];
            if (grid[i] == '#') ++occupied;
        }
    }

    // for (int i = 0; i < (dim * dim); ++i)
    // {
    //     if (i % 12 == 0) std::cout << "\n";
    //     std::cout << grid[i];
    // }

    std::cout << "a: " << occupied << std::endl;
    return 0;
}