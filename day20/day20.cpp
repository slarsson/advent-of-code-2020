//
// 
// this is madness..

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>

typedef std::vector<std::pair<int, std::vector<std::vector<std::string>>>> Tilez;
const size_t GRID_SIZE = 12;

void print(std::string &tile)
{
    for (int i = 0; i < tile.size(); i += 10)
    {
        std::cout << tile.substr(i, 10) << "\n";
    }
}

std::string rotate(std::string &tile)
{
    std::string start[10];
    std::string end[10];
    
    int idx = 0;
    for (int i = 0; i < tile.size(); i += 10)
    {
        start[idx] = tile.substr(i, 10);
        end[idx] = start[idx];
        ++idx;
    }

    int n = 10;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            end[i][j] = start[n - j - 1][i];
        }
    }

    std::string ret = "";
    for (int i = 0; i < 10; ++i) ret += end[i];
    return ret;
}

std::string rotate_b(std::string &tile)
{
    std::string start[GRID_SIZE * 8];
    std::string end[GRID_SIZE * 8];
    
    int idx = 0;
    for (int i = 0; i < tile.size(); i += (GRID_SIZE * 8))
    {
        start[idx] = tile.substr(i, (GRID_SIZE * 8));
        end[idx] = start[idx];
        ++idx;
    }

    int n = GRID_SIZE * 8;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            end[i][j] = start[n - j - 1][i];
        }
    }

    std::string ret = "";
    for (int i = 0; i < (GRID_SIZE * 8); ++i) ret += end[i];
    return ret;
}

std::string flip_vr(std::string &tile)
{
    std::string ret = "";
    for (int i = (tile.size() - 10); i >= 0; i -= 10)
    {
        std::string part = tile.substr(i, 10);
        ret += part;
    }
    return ret;
}

std::string flip_vr_b(std::string &tile)
{
    std::string ret = "";
    for (int i = (tile.size() - (GRID_SIZE * 8)); i >= 0; i -= (GRID_SIZE * 8))
    {
        std::string part = tile.substr(i, (GRID_SIZE * 8));
        ret += part;
    }
    return ret;
}

// don't need this..
// std::string flip_hz(std::string &tile)
// {
//     std::string ret = "";
//     for (int i = 0; i < tile.size(); i += 10)
//     {
//         std::string part = tile.substr(i, 10);
//         std::reverse(part.begin(), part.end());
//         ret += part;
//     }
//     return ret;
// }

std::vector<std::string> get_borders(std::string &tile)
{
    std::vector<std::string> ret;
    
    // top
    ret.push_back(tile.substr(0, 10));

    // right
    std::string right = "";
    for (int i = 9; i < tile.size(); i += 10) right += tile[i];
    ret.push_back(right);

    // bottom
    ret.push_back(tile.substr(tile.size() - 10, 10));

    // left
    std::string left = "";
    for (int i = 0; i < tile.size(); i += 10) left += tile[i];
    ret.push_back(left);

    return ret;
}

std::string remove_borders(std::string &tile)
{
    std::string ret = "";

    int idx = 11;
    while (idx < (tile.size() - 10))
    {
        ret += tile.substr(idx, 8);
        idx += 10;
    }

    return ret;
}

bool brute_force(int r, int c, Tilez all_tiles, int grid[GRID_SIZE][GRID_SIZE], int grid_version[GRID_SIZE][GRID_SIZE], std::vector<int> seen = std::vector<int>())
{
    if (c == GRID_SIZE)
    {
        c = 0;
        ++r;
    }

    if (r == GRID_SIZE)
    {
        std::cout << "base case" << std::endl;
        return true;
    }

    for (int i = 0; i < all_tiles.size(); ++i)
    {
        if (std::find(seen.begin(), seen.end(), all_tiles[i].first) != seen.end()) continue;        
        for (int j = 0; j < all_tiles[i].second.size(); ++j)
        {
            int above = r - 1;
            int left = c - 1;
            bool ok_top = true;
            bool ok_left = true;
            
            if (above != -1)
            {
                ok_top = (all_tiles[grid[above][c]].second[grid_version[above][c]][2] == all_tiles[i].second[j][0]);
            }

            if (left != -1)
            {
                ok_left = (all_tiles[grid[r][left]].second[grid_version[r][left]][1] == all_tiles[i].second[j][3]);
            }

            if (ok_top && ok_left)
            {
                seen.push_back(all_tiles[i].first);
                grid[r][c] = i;
                grid_version[r][c] = j;
                bool k = brute_force(r, c + 1, all_tiles, grid, grid_version, seen);
                if (k) return true;
                seen.pop_back();
            }            
        }
    }
    
    return false;
}

int main()
{
    std::unordered_map<int, std::string> tiles;
    std::ifstream file{"input.txt"};
    std::string line;
    
    int key{0};
    bool next = true;
    while (std::getline(file, line))
    {
        if (line == "")
        {
            next = true;
            continue;
        }

        if (next)
        {
            key = std::stoi(line.substr(5, 4));
            next = false;
            continue;
        }
        
        tiles[key] += line;
    }

    Tilez all_tiles;
    std::vector<std::pair<int, std::vector<std::string>>> no_border;
    for (auto &p : tiles)
    {
        std::set<std::string> tmp;
        std::string x = p.second;
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);

        x = flip_vr(p.second);
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);
        x = rotate(x);
        tmp.insert(x);

        std::vector<std::vector<std::string>> one_tile;
        std::vector<std::string> the_tiles;
        for (auto t : tmp)
        {
            the_tiles.push_back(t); // REMPOVE BORDER!!!
            one_tile.push_back(get_borders(t));
        }

        no_border.push_back(std::pair<int, std::vector<std::string>>(p.first, the_tiles));
        all_tiles.push_back(std::pair<int, std::vector<std::vector<std::string>>>(p.first, one_tile));
    }

    int grid[GRID_SIZE][GRID_SIZE];
    int grid_version[GRID_SIZE][GRID_SIZE];
    if(brute_force(0, 0, all_tiles, grid, grid_version))
    {
        long long int a = all_tiles[grid[0][0]].first;
        a *= all_tiles[grid[0][GRID_SIZE - 1]].first;
        a *= all_tiles[grid[GRID_SIZE - 1][0]].first;
        a *= all_tiles[grid[GRID_SIZE - 1][GRID_SIZE - 1]].first;
        std::cout << "a: " << a << std::endl;
    }

    // row with cols
    std::vector<std::string> tmp_image;

    int r = 0;
    int c = 0;
    while (r != GRID_SIZE)
    {
        tmp_image.push_back(remove_borders(no_border[grid[r][c]].second[grid_version[r][c]]));

        ++c;
        if (c == GRID_SIZE)
        {
            c = 0;
            ++r;
        }
    }

    std::string the_image; 
    int idx = 0;
    while (idx < (GRID_SIZE * GRID_SIZE))
    {
        int offset = 0;
        for (int j = 0; j < 8; ++j)
        {
            for (int i = 0; i < GRID_SIZE; ++i)
            {
                the_image += tmp_image[idx + i].substr(offset, 8);
            }
            offset += 8;
        }

        idx += GRID_SIZE;
    }

    std::set<std::string> all_the_images;
    std::string the_tmp_img = the_image;
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);

    the_tmp_img = flip_vr_b(the_image);
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);
    the_tmp_img = rotate_b(the_tmp_img);
    all_the_images.insert(the_tmp_img);

    for (auto img_my_img : all_the_images)
    {
        int seamonster_width = 20;
        int n_seamonsterz = 0;
        
        r = 0; 
        c = 0;
        while (r < (8 * GRID_SIZE - 3))
        {
            int jmp = 8 * GRID_SIZE;
            int start = jmp * r + c;
            
            bool found = false;
            
            // row 1
            std::string tmp = img_my_img.substr(start, seamonster_width);
            if (tmp[18] == '#') found = true;
            
            // row 2
            if (found)
            {
                tmp = img_my_img.substr(start + jmp, seamonster_width);
                found = (
                    tmp[0] == '#' && 
                    tmp[5] == '#' && 
                    tmp[6] == '#' && 
                    tmp[11] == '#' && 
                    tmp[12] == '#' && 
                    tmp[17] == '#' && 
                    tmp[18] == '#' && 
                    tmp[19] == '#' 
                );
            }

            // row 3
            if (found)
            {
                tmp = img_my_img.substr(start + (2 * jmp), seamonster_width);
                found = (
                    tmp[1] == '#' && 
                    tmp[4] == '#' && 
                    tmp[7] == '#' && 
                    tmp[10] == '#' && 
                    tmp[13] == '#' && 
                    tmp[16] == '#' 
                );
            }

            if (found)
            {
                img_my_img[start + 18] = 'O';
                img_my_img[start + jmp] = 'O';
                img_my_img[start + jmp + 5] = 'O';
                img_my_img[start + jmp + 6] = 'O';
                img_my_img[start + jmp + 11] = 'O';
                img_my_img[start + jmp + 12] = 'O';
                img_my_img[start + jmp + 17] = 'O';
                img_my_img[start + jmp + 18] = 'O';
                img_my_img[start + jmp + 19] = 'O';
                img_my_img[start + 2 * jmp + 1] = 'O';
                img_my_img[start + 2 * jmp + 4] = 'O';
                img_my_img[start + 2 * jmp + 7] = 'O';
                img_my_img[start + 2 * jmp + 10] = 'O';
                img_my_img[start + 2 * jmp + 13] = 'O';
                img_my_img[start + 2 * jmp + 16] = 'O';
                std::cout << "seamonster found!!!1!!" << std::endl;
                ++n_seamonsterz;
            }
            
            ++c;
            if (c == (8 * GRID_SIZE - seamonster_width))
            {
                ++r;
                c = 0;
            }
        }

        // for (int i = 0; i < (8 * GRID_SIZE); ++i)
        // {
        //     std::cout << the_image.substr(i * 8 * GRID_SIZE, 8 * GRID_SIZE) << std::endl;
        // }

        if (n_seamonsterz == 0) continue;

        int b = 0;
        for (int i = 0; i < img_my_img.size(); ++i)
        {
            if (img_my_img[i] == '#') ++b;
        }

        std::cout << "b: " << b << std::endl;
    }

    return 0;
}