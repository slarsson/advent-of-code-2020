#include <iostream>

struct Node
{
    int value = 0;
    Node *next = nullptr;
    Node *prev = nullptr;
};

int main()
{
    Node *lookup[1000001]; // first index empty
    Node *tail;
    Node *cur = nullptr;

    int input = 739862541;
    while (input != 0)
    {          
        int val = input % 10;
        input /= 10;
        
        Node *my_node = new Node(); 
        my_node->value = val;
        lookup[val] = my_node;

        if (cur == nullptr)
        {
            tail = my_node;
            cur = my_node;
        }
        else
        {
            cur->prev = my_node;
            my_node->next = cur;
            cur = my_node;
        }
    }

    for (int i = 10; i <= 1000000; ++i)
    {
        Node *my_node = new Node();
        lookup[i] = my_node;
        my_node->value = i;

        tail->next = my_node;
        my_node->prev = tail;
        tail = my_node;
    }

    cur->prev = tail;
    tail->next = cur;
    
    int min = 1;
    int max = 1000000;
    int value = cur->value;
    Node *tmp[3] = { nullptr };
    for (int i = 0; i < 10000000; ++i)
    {
        Node *start = lookup[value];

        // uno
        Node *ptr = start->next;  
        tmp[0] = ptr;
        
        // dos
        ptr = ptr->next;
        tmp[1] = ptr;
        
        // tres
        ptr = ptr->next;
        tmp[2] = ptr;

        // next value
        ptr = ptr->next;
        
        // close loop
        start->next = ptr;
        ptr->prev = start;

        // calc dest value
        int label = value - 1;
        while (true)
        {
            if (label < min) label = max;
            if (label != tmp[0]->value && label != tmp[1]->value && label != tmp[2]->value) break;
            --label;
        }
        
        // set new value, for next iteration
        value = ptr->value;

        // add piece to loop
        Node *last = lookup[label]->next;

        tmp[0]->prev = lookup[label];
        lookup[label]->next = tmp[0];

        tmp[2]->next = last;
        last->prev = tmp[2];
    }

    cur = lookup[1]->next;
    long long int b = cur->value;
    cur = cur->next;
    b *= cur->value;
    std::cout << "b: " << b << std::endl;

    return 0;
}