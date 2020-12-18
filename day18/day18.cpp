#include <iostream>
#include <fstream>
#include <vector>

template <typename T1, typename T2>
struct Branch {
    T1 value;
    T2 action;
    Branch *next;
    Branch *prev;
};

long int parse_row_a(std::string &line)
{
    Branch<long int, char> *cur = new Branch<long int, char>();
    cur->value = 0;
    cur->action = '+';
    cur->next = nullptr;
    cur->prev = nullptr;

    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == '+' || line[i] == '*')
        {
            cur->action = line[i];
        }
        else if (line[i] == ' ')
        {
            continue;
        }
        else if (line[i] == '(')
        {
            cur->next = new Branch<long int, char>();
            Branch<long int, char> *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
            cur->value = 0;
            cur->action = '+';
            cur->next = nullptr;
        }
        else if (line[i] == ')')
        {
            long int val = cur->value;
            cur = cur->prev;
            delete cur->next;
            if (cur->action == '+')
            {
                cur->value += val;
            }   
            else if (cur->action == '*')
            {
                cur->value *= val;
            }
        }
        else
        {
            long int val = std::atoi(&line[i]);
            if (cur->action == '+')
            {
                cur->value += val;
            }   
            else if (cur->action == '*')
            {
                cur->value *= val;
            }
        }
    }

    long int sum = cur->value;
    delete cur;

    return sum;
}

// efterblivet, borde använda en stack ist typ..
long int sum(std::vector<char> actions, std::vector<long int> values)
{
    std::vector<long int> temp;
    long int n = 0;
    for (int j = 1; j < values.size(); ++j)
    {
        if (actions[j - 1] == '+') 
        {
            n += values[j];
        }
        else
        {
            temp.push_back(n);
            n = values[j];
        }
    }

    temp.push_back(n);

    long int sum = 1;
    for (auto val : temp) sum *= val;

    return sum;
}

long int parse_row_b(std::string &line)
{
    Branch<std::vector<long int>, std::vector<char>> *cur = new Branch<std::vector<long int>, std::vector<char>>();
    cur->value = std::vector<long int>{0};
    cur->action = std::vector<char>{'+'};
    cur->next = nullptr;
    cur->prev = nullptr;

    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == '+' || line[i] == '*')
        {
            cur->action.push_back(line[i]);
        }
        else if (line[i] == ' ')
        {
            continue;
        }
        else if (line[i] == '(')
        {
            cur->next = new Branch<std::vector<long int>, std::vector<char>>();
            Branch<std::vector<long int>, std::vector<char>> *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
            cur->value = std::vector<long int>{0};
            cur->action = std::vector<char>{'+'};
            cur->next = nullptr;
        }
        else if (line[i] == ')')
        {   
            long int tot = sum(cur->action, cur->value);
            cur = cur->prev;
            delete cur->next;
            cur->next = nullptr;
            cur->value.push_back(tot);
        }
        else
        {
            long int val = std::atoi(&line[i]);
            cur->value.push_back(val);
        }
    }

    long int tot = sum(cur->action, cur->value);
    delete cur;

    return tot;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line;
    long int a = 0;
    long int b = 0;

    while (std::getline(file, line))
    {
        a += parse_row_a(line);
        b += parse_row_b(line);
    }

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    return 0;
}