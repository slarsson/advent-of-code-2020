#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream file{"input.txt"};

    std::string line;
    std::vector<std::pair<std::string, int>> instructions{};

    while (file >> line)
    {
        std::string tmp;
        file >> tmp;
        int n = std::stoi(tmp);
        instructions.push_back(std::pair<std::string, int>(line, n));
    }

    // PART A
    int accumulator = 0;
    int idx = 0;

    std::vector<bool> visited{};
    for (int i = 0; i < instructions.size(); ++i) visited.push_back(false);

    while (idx < instructions.size())
    {
        if (visited[idx])
        {
            std::cout << "a: " << accumulator << std::endl;
            break;
        }

        std::string action = instructions[idx].first;
        int n = instructions[idx].second;
        visited[idx] = true;

        if (action == "nop")
        {
            ++idx;
            continue;
        }
        else if (action == "acc")
        {
            accumulator += n;
            ++idx;
        }
        else
        {
            idx += n;    
        }
    }


    // PART B
    accumulator = 0;
    idx = 0;

    std::vector<int> nops{};
    std::vector<int> jmps{};

    for (int i = 0; i < instructions.size(); ++i)
    {
        if (instructions[i].first == "nop")
        {
            nops.push_back(i);
        }
        else if (instructions[i].first == "jmp")
        {
            jmps.push_back(i);
        }
    }

    // try jmp => nop
    for (int i : jmps)
    {
        instructions[i].first = "nop";
        accumulator = 0;
        idx = 0;
        int itr = 0;
        
        bool ok = true;
        while (idx < instructions.size())
        {
            if (itr > 10000)
            {
                ok = false;
                break;
            }

            std::string action = instructions[idx].first;
            int n = instructions[idx].second;

            if (action == "nop")
            {
                ++idx;
                continue;
            }
            else if (action == "acc")
            {
                accumulator += n;
                ++idx;
            }
            else
            {
                idx += n;    
            }

            ++itr;
        }

        if (ok)
        {
            std::cout << "b: " << accumulator << std::endl;
            break;
        }

        instructions[i].first = "jmp";
    }
}