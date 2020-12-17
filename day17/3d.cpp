#include <iostream>
#include <fstream>

template <size_t T>
int check_neighbors(bool (&arr)[T][T][T], int x, int y, int z)
{
    int count = 0;
    for (int i = (x - 1); i <= (x + 1); ++i)
    {
        for (int j = (y - 1); j <= (y + 1); ++j)
        {
            for (int k = (z - 1); k <= (z + 1); ++k)
            {
                if (x == i && y == j && k == z) continue;
                if (arr[i][j][k]) ++count;
            }
        }
    }

    return count;
}

int main()
{
    std::ifstream file{"input.txt"};

    const int init_size = 8;
    const int n_cycles = 6;

    const int size = init_size + 2 * n_cycles + 2 + 3; // padding
    bool source[size][size][size] = {false};
    bool temp[size][size][size] = {false};

    std::string line;
    int y_offset = (size / 2);
    int center = (size / 2) + 1;
    while (std::getline(file, line)) {
        int x_offset = (size / 2);
        for (int i = 0; i < line.size(); ++i)
        {
            source[x_offset][y_offset][center] = (line[i] == '#');
            std::cout << "insert => x: " << x_offset << " y: " << y_offset << " z: " << center << " val: " << source[x_offset][y_offset][center] << std::endl;
            ++x_offset;
        }
        ++y_offset;
        std::cout << line << " = " << line.size() << std::endl;
    }

    for (int cycles = 0; cycles < n_cycles; ++cycles)
    {
        for (int x = 1; x < (size - 1); ++x)
        {
            for (int y = 1; y < (size - 1); ++y)
            {
                for (int z = 1; z < (size - 1); ++z)
                {
                    int n = check_neighbors(source, x, y, z);
                    if (source[x][y][z])
                    {
                        temp[x][y][z] = (n == 2 || n == 3);
                    }
                    else
                    {
                        temp[x][y][z] = (n == 3);
                    }
                }
            }
        }

        for (int x = 1; x < (size - 1); ++x)
        {
            for (int y = 1; y < (size - 1); ++y)
            {
                for (int z = 1; z < (size - 1); ++z)
                {
                    source[x][y][z] = temp[x][y][z];
                }
            }
        }
    }

    int a = 0;
    for (int x = 1; x < (size - 1); ++x)
    {
        for (int y = 1; y < (size - 1); ++y)
        {
            for (int z = 1; z < (size - 1); ++z)
            {
                if(source[x][y][z]) ++a;
            }
        }
    }

    std::cout << "a: " << a << std::endl;
    return 0;
}
