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

    int n_diffs = 1;
    int occupied = 0;
    while (n_diffs > 0)
    {
        occupied = 0;
        n_diffs = 0;
        offset = dim + 1;

        for (int i = offset; i < (dim * dim - dim - 1); ++i)
        {
            int col = i % dim;
            if (col == 0 || col == (dim  - 1) || grid[i] == '.') continue;

            int taken = 0;
            int end, tmp, j;

            // right
            end = i + dim - col - 1;
            j = i + 1;
            while (j < end)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                ++j;
            }

            // left
            end = i - col;
            j = i - 1;
            while (j > end)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                --j;
            }

            // top
            end = col;
            j = i - dim;
            while (j > end)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j -= dim;
            }

            // bottom
            end = (dim * dim) - (dim - col);
            j = i + dim;
            while (j < end)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j += dim;
            }

            // top-left
            end = 0;
            j = i - dim - 1;
            tmp = col - 1;
            while (j > end && tmp > 0)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j -= (dim + 1);
                --tmp;
            }

            // top-right
            end = dim - 1;
            j = i - dim + 1;
            tmp = col + 1;
            while (j > end && tmp < (dim - 1))
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j -= (dim - 1);
                ++tmp;
            }

            // bottom-left
            end = (dim * dim) - dim;
            j = i + dim - 1;
            tmp = col - 1;
            while (j < end && tmp > 0)
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j += (dim - 1);
                --tmp;
            }

            // bottom-right
            end = (dim * dim) - 1;
            j = i + dim + 1;
            tmp = col + 1;
            while (j < end && tmp < (dim - 1))
            {
                if (grid[j] == 'L') break;
                if (grid[j] == '#')
                {
                    ++taken;
                    break;
                }
                j += (dim + 1);
                ++tmp;
            }

            if (taken == 0)
            {
                tmp_grid[i] = '#';
                if (tmp_grid[i] != grid[i]) ++n_diffs;
            }
            else if (taken >= 5)
            {
                tmp_grid[i] = 'L';
                if (tmp_grid[i] != grid[i]) ++n_diffs;
            }
        }

        for (int i = 0; i < (dim * dim); ++i) 
        {
            grid[i] = tmp_grid[i];
            if (grid[i] == '#') ++occupied;
        }

        // for (int i = 0; i < (dim * dim); ++i)
        // {
        //     if (i % 12 == 0) std::cout << "\n";
        //     std::cout << grid[i];
        // }
    }

    std::cout << "b: " << occupied << std::endl;
    return 0;
}