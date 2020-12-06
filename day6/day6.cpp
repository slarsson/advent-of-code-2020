#include <iostream>
#include <fstream>
#include <set>
#include <map>

int main()
{
    std::ifstream file{"input.txt"};

    std::string line;
    
    std::set<char> q;    
    size_t a_count = 0;

    std::map<char, int> qm;
    size_t b_count = 0;

    size_t n = 0;

    while(std::getline(file, line))
    {
        if (line == "") 
        {
            a_count += q.size();
            q.clear();

            int tmp = 0;
            for (auto const &val : qm)
            {
                if (val.second == n) ++tmp;
            }

            b_count += tmp;

            qm.clear();
            n = 0;
            continue;
        }

        for (char &c : line)
        {
            q.insert(c);
            qm[c]++;
        }

        ++n;
    }

    // meh..
    int tmp = 0;
    for (auto const &val : qm)
    {
        if (val.second == n) ++tmp;
    }
    b_count += tmp;

    std::cout << q.size() + a_count << std::endl;
    std::cout << b_count << std::endl;
    return 0;
}