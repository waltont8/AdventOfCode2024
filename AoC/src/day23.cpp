#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

typedef map<string, set<string>> conType;

conType cons;

bool hasCon(string k, string c)
{
    if (cons.find(k) != cons.end())
    {
        for (auto i : cons[k])
        {
            if (i == c)
                return true;
        }
    }
    return false;
}

void part1()
{
    int total = 0;

    set<string> res;

    for (auto it : cons)
    {
        string name = it.first;
        set<string> outs = it.second;

        for (auto it1 : outs)
        {
            string name1 = it1;
            set<string> outs1 = cons[name1];

            for (auto it2 : outs)
            {
                string name2 = it2;
                set<string> outs2 = cons[name2];

                 if (name2 == name1) continue;

                 if (hasCon(name2, name1) == false) continue;

                if (name[0] == 't' || name1[0] == 't' || name2[0] == 't')
                {
                    vector<string> net = {name, name1, name2};
                    sort(net.begin(), net.end());
                    res.insert(net[0]+","+net[1]+","+net[2]);
                }
            }
        }
    }

    cout << "Part1: " << res.size() << endl;
}

int best = 0;

set<string> que;

void part2(string comp)
{
    if (que.size() > best)
    {
        best = que.size();
        cout << best << endl;
        for (auto tmp : que) cout << tmp << ",";
        cout << endl;
    }

    for (auto child : cons[comp])
    {
        if (que.find(child) != que.end()) continue;

        // every child is connected to the queue
        bool noMatch = false;
        for (auto q : que) 
        {
            if (hasCon(child, q) == false) noMatch = true;
        }
        if (noMatch) continue;

        // add to the que
        
        que.insert(child);
        part2(child);
        que.erase(child);
    }

}

void init()
{
    char *input_line = NULL;
    size_t lim = 0;

    string s, e;

    while (getline(&input_line, &lim, stdin) > 5)
    {
        s = "";
        e = "";

        s += input_line[0];
        s += input_line[1];
        e += input_line[3];
        e += input_line[4];

        if (cons.find(s) == cons.end())
        {
            cons[s] = {e};
        }
        else
        {
            cons[s].insert(e);
        }

        if (cons.find(e) == cons.end())
        {
            cons[e] = {s};
        }
        else
        {
            cons[e].insert(s);
        }
    }
}

int main(void)
{
    init();
    part1();
    set<string> s = {"xr"};
    part2("xr");
}
