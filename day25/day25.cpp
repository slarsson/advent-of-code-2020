#include <iostream>

int main()
{
    int keys[2] = {18499292, 8790390};
    int loops[2] = {0, 0};
    
    for (int i = 0; i < 2; ++i)
    {
        int value = 1;
        while (true)
        {
            value *= 7;
            value %= 20201227;
            ++loops[i];
            if (value == keys[i]) break;
        }
    }

    long int encryption_key = 1;
    for (int i = 0; i < loops[0]; ++i)
    {
        encryption_key *= keys[1];
        encryption_key %= 20201227;
    }

    std::cout << "ans: " << encryption_key << std::endl;
    return 0;
}