#include <iostream>
#include <fstream>
#include <set>

int check_neighbours(std::set<std::pair<int, int>> &black_tiles, std::pair<int, int> &black_tile)
{
    int black = 0;

    // w = -1 col
    std::pair<int, int> tmp(black_tile.first, black_tile.second - 1);
    if (black_tiles.count(tmp) != 0) ++black;

    // e = +1 col
    tmp.first = black_tile.first;
    tmp.second = black_tile.second + 1;
    if (black_tiles.count(tmp) != 0) ++black;

    // nw = -1 col, +1 row
    tmp.first = black_tile.first + 1;
    tmp.second = black_tile.second - 1;
    if (black_tiles.count(tmp) != 0) ++black;

    // ne = +1 row
    tmp.first = black_tile.first + 1;
    tmp.second = black_tile.second;
    if (black_tiles.count(tmp) != 0) ++black;

    // sw = -1 row
    tmp.first = black_tile.first - 1;
    tmp.second = black_tile.second;
    if (black_tiles.count(tmp) != 0) ++black;

    // se = +1 col, -1 row
    tmp.first = black_tile.first - 1;
    tmp.second = black_tile.second + 1;
    if (black_tiles.count(tmp) != 0) ++black;

    return black;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;

    // row, col
    std::set<std::pair<int, int>> black_tiles;

    // w = -1 col
    // e = +1 col
    // nw = -1 col, +1 row
    // ne = +1 row
    // sw = -1 row
    // se = +1 col, -1 row

    while (std::getline(file, line))
    {
        std::string dir;
        int r = 0;
        int c = 0;
        for (int i = 0; i < line.size(); ++i)
        {
            dir = line[i];
            if (line[i] == 'n' || line[i] == 's')
            {
                dir += line[i + 1];
                ++i;
            }

            if (dir == "w")
            {
                c -= 1;
            }
            else if (dir == "e")
            {
                c += 1;
            }
            else if (dir == "nw")
            {
                r += 1;
                c -= 1;
            }
            else if (dir == "ne")
            {
                r += 1;
            }
            else if (dir == "sw")
            {
                r -= 1;
            }
            else if (dir == "se")
            {
                r -= 1;
                c += 1;
            }
        }

        std::pair<int, int> cur(r, c);
        if (black_tiles.count(cur) == 0)
        {
            black_tiles.insert(cur);
        }
        else
        {
            black_tiles.erase(cur);
        }
    }

    std::cout << "a: " << black_tiles.size() << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::set<std::pair<int, int>> new_black_tiles;

        for (auto &black_tile : black_tiles)
        {
            std::pair<int, int> tmp(black_tile.first, black_tile.second);
            
            int black = check_neighbours(black_tiles, tmp);
            if (black > 0 && black <= 2)
            {
                new_black_tiles.insert(std::pair<int, int>(black_tile.first, black_tile.second));
            }

            //
            // this should be a loop maybe..
            //
            // w = -1 col
            tmp.first = black_tile.first;
            tmp.second = black_tile.second - 1;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }

            // e = +1 col
            tmp.first = black_tile.first;
            tmp.second = black_tile.second + 1;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }

            // nw = -1 col, +1 row
            tmp.first = black_tile.first + 1;
            tmp.second = black_tile.second - 1;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }

            // ne = +1 row
            tmp.first = black_tile.first + 1;
            tmp.second = black_tile.second;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }

            // sw = -1 row
            tmp.first = black_tile.first - 1;
            tmp.second = black_tile.second;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }

            // se = +1 col, -1 row
            tmp.first = black_tile.first - 1;
            tmp.second = black_tile.second + 1;
            if (black_tiles.count(tmp) == 0)
            {
                if (check_neighbours(black_tiles, tmp) == 2)
                {
                    new_black_tiles.insert(std::pair<int, int>(tmp.first, tmp.second));
                }
            }
        }
        
        black_tiles.swap(new_black_tiles);

    }
        std::cout << "b: " << black_tiles.size() << std::endl;

    return 0;
} 