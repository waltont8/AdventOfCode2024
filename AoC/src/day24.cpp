#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

typedef enum
{
    XOR,
    OR,
    AND,
    INPUT
} Type;
typedef struct Node
{
    string input1;
    string input2;
    string output;
    uint64_t value;
    Type operand;
} Node;

vector<Node *> nodes;

map<string, Node *> lookup;

Node *getNode(string outName)
{
    // Is it in the map?
    if (lookup.find(outName) != lookup.end())
    {
        return lookup[outName];
    }
    else // else not in the map
    {
        for (auto n : nodes)
        {
            if (outName == n->output)
            {
                return n;
            }
        }
    }
    return (Node *)0xdeadbeef;
}

uint64_t build(Node *n, bool force)
{
    if (n->operand == INPUT)
    {
        lookup[n->output] = n;
        return n->value;
    }

    if (force == false && lookup.find(n->output) != lookup.end())
    {
        return lookup[n->output]->value;
    }

    uint64_t in1 = build(getNode(n->input1), force);
    uint64_t in2 = build(getNode(n->input2), force);
    uint64_t out = 0;

    switch (n->operand)
    {
    case AND:
        out = in1 & in2;
        break;
    case OR:
        out = in1 | in2;
        break;
    case XOR:
        out = in1 ^ in2;
        break;
    default:
        break;
    }

    n->value = out;
    lookup[n->output] = n;

    return out;
}

void init()
{
    char *input_line = NULL;
    size_t lim = 0;

    string in1 = "XXX";
    string in2 = "XXX";
    string out = "XXX";

    while (getline(&input_line, &lim, stdin) >= 0)
    {
        if (strlen(input_line) < 2)
        {
            continue;
        }
        else if (strlen(input_line) < 10)
        {
            Node *n = new Node();
            in1[0] = input_line[0];
            in1[1] = input_line[1];
            in1[2] = input_line[2];

            n->output = in1;
            n->operand = INPUT;
            if (input_line[5] == '0')
            {
                n->value = 0;
            }
            else
            {
                n->value = 1;
            }
            lookup[n->output] = n;
            nodes.push_back(n);
        }
        else
        {
            Node *n = new Node();

            int o = 0;
            if (input_line[4] == 'A')
            {
                n->operand = AND;
            }
            else if (input_line[4] == 'X')
            {
                n->operand = XOR;
            }
            else
            {
                n->operand = OR;
                o = 1;
            }

            in1[0] = input_line[0];
            in1[1] = input_line[1];
            in1[2] = input_line[2];

            in2[0] = input_line[8 - o];
            in2[1] = input_line[9 - o];
            in2[2] = input_line[10 - o];

            out[0] = input_line[15 - o];
            out[1] = input_line[16 - o];
            out[2] = input_line[17 - o];

            n->output = out;
            n->input1 = in1;
            n->input2 = in2;

            nodes.push_back(n);
        }
    }
}

uint64_t getZ(bool force)
{
    uint64_t z = 0;
    for (auto n : nodes)
    {
        if (n->output[0] == 'z')
        {
            string num = "00";
            num[0] = n->output[1];
            num[1] = n->output[2];
            int pos = stoi(num);
            uint64_t val = build(n, force);
            z = z | (val << pos);
        }
    }
    return z;
}

uint64_t tabs(uint64_t a, uint64_t b)
{
    if (a > b) return a-b;
    return b-a;
}

void swapNodes(Node *a, Node *b)
{
    string tmp = a->output;
    a->output = b->output;
    b->output = tmp;
}

void part1()
{
    uint64_t z = getZ(false);
    cout << z << endl;
}

void part2()
{
    uint64_t x = 0;
    uint64_t y = 0;
    uint64_t z = 0;

    for (auto n : nodes)
    {
        if (n->output[0] == 'x' || n->output[0] == 'y' || n->output[0] == 'z')
        {
            string num = "00";
            num[0] = n->output[1];
            num[1] = n->output[2];
            int pos = stoi(num);
            uint64_t val = build(n,false);
            if (n->output[0] == 'x')
            {
                x = x | (val << pos);
            }
            else if (n->output[0] == 'y')
            {
                y = y | (val << pos);
            }
        }
    }
    z = getZ(false);

    uint64_t target = x + y;

    for (auto n : nodes)
    {
        if (n->operand == INPUT) continue;
        for (auto m : nodes)
        {
            if (n == m) continue;
            if (m->operand == INPUT) continue;

            swapNodes(n,m);

            uint64_t newZ = getZ(true);
            cout << "Target :" << target << " z:" << z << " newZ:" << newZ << endl;
            cout << "Checking :" << n->output << " and " << m->output << " ";
            if (tabs(target,newZ) >= tabs(target,z))
            {
                cout << tabs(target,newZ) << " <> " << tabs(target,z) << endl;
                swapNodes(n,m);
            }
            else
            {
                z = newZ;
                cout << "Swapped " << n->output << " and " << m->output << endl;
            }
        }
    }
}

int main(void)
{
    init();
    part1();
    part2();
}
