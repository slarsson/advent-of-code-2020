#include <iostream>
#include <map>

int loop(int n)
{
    std::map<int, int> numbers;
    numbers[7] = 1;
    numbers[14] = 2;
    numbers[0] = 3;
    numbers[17] = 4;
    numbers[11] = 5;
    numbers[1] = 6;

    int cur = 2;
    int count = 7;
    while (count < n)
    {
        if (numbers[cur] == 0)
        {
            numbers[cur] = count;
            cur = 0;
        }
        else
        {
            int diff = count - numbers[cur];
            numbers[cur] = count;
            cur = diff;
        }

        ++count;
    }

    return cur;
}

int main()
{
    std::cout << "a: " << loop(2020) << std::endl;
    std::cout << "b: " << loop(30000000) << std::endl;
    return 0;
}