#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define PI 3.14159265

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;
    std::vector<std::pair<char, int>> instructions;

    while (std::getline(file, line))
    {
        char c = line[0];
        std::string n = "";
        for (int i = 1; i < line.size(); ++i) n += line[i];
        instructions.push_back(std::pair<char, int>(c, std::stoi(n)));
    }

    // PART A
    int cur = 1;
    int pos[4] = {0, 0, 0, 0}; // N, E, S, W
    for (auto &item : instructions)
    {   
        if (item.first == 'N')
        {
            pos[0] += item.second;
        }
        else if (item.first == 'E')
        {
            pos[1] += item.second;
        }
        else if (item.first == 'S')
        {
            pos[2] += item.second;
        }
        else if (item.first == 'W')
        {
            pos[3] += item.second;
        }
        else if (item.first == 'F')
        {
            pos[cur] += item.second;
        }
        else
        {
            int n = item.second / 90;
            if (item.first == 'L') n *= -1;
            cur = (cur + n) % 4;
            if (cur < 0) cur += 4;
        }
    }

    std::cout << "a: " << std::abs(pos[0] - pos[2]) + std::abs(pos[1] - pos[3]) << std::endl;

    // PART B
    int y_ship = 0;
    int x_ship = 0;
    int y_waypoint = 1; 
    int x_waypoint = -10;
    for (auto &item : instructions)
    {   
        if (item.first == 'N')
        {
            y_waypoint += item.second;
        }
        else if (item.first == 'E')
        {
            x_waypoint -= item.second;
        }
        else if (item.first == 'S')
        {
            y_waypoint -= item.second; 
        }
        else if (item.first == 'W')
        {
            x_waypoint += item.second; 
        }
        else if (item.first == 'F')
        {
            int x_dist = std::abs(x_waypoint - x_ship);
            int y_dist = std::abs(y_waypoint - y_ship);
            if (x_waypoint < x_ship) x_dist *= -1;
            if (y_waypoint < y_ship) y_dist *= -1;
            x_ship += (x_dist * item.second);
            x_waypoint = x_ship + x_dist;
            y_ship += (y_dist * item.second);
            y_waypoint = y_ship + y_dist;
        }
        else
        {
            // translate to origo
            x_waypoint -= x_ship;
            y_waypoint -= y_ship;
           
            // rotate
            float deg = item.second * (PI / 180);
            if (item.first == 'L') deg *= -1;
            float x = x_waypoint * std::cos(deg) - y_waypoint * std::sin(deg);
            float y = x_waypoint * std::sin(deg) + y_waypoint * std::cos(deg);

            // hallå c++
            if (x < 0)
            {
                x -= 0.5;
            }
            else
            {
                x += 0.5;
            }

            if (y < 0)
            {
                y -= 0.5;
            }
            else
            {
                y += 0.5;
            }
            
            // translate back
            x_waypoint = (int)x + x_ship;
            y_waypoint = (int)y + y_ship;
        }
    }
    
    std::cout << "b: " << std::abs(x_ship) + std::abs(y_ship) << std::endl;

    return 0;
}