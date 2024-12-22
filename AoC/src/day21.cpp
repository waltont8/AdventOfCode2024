#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const char *keypad[4] = {"789",
                         "456",
                         "123",
                         " 0A"};
const char *dirpad[2] = {" ^A",
                         "<v>"};

int keyX(char c)
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 4; y++)
            if (keypad[y][x] == c)
                return x;
    return 0xdeadbeef;
}

int keyY(char c)
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 4; y++)
            if (keypad[y][x] == c)
                return y;
    return 0xdeadbeef;
}

int dirX(char c)
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 2; y++)
            if (dirpad[y][x] == c)
                return x;
    return 0xdeadbeef;
}

int dirY(char c)
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 2; y++)
            if (dirpad[y][x] == c)
                return y;
    return 0xdeadbeef;
}

string sequence(int cx, int cy, int dx, int dy)
{
    string ret = "";

    int x = cx;
    int y = cy;

    int bad = 0;

    while (cx > dx)
    {
        ret += "<";
        cx--;
        if ((cx == 0) && (cy == 3))
            bad = 1;
    }
    while (cy < dy)
    {
        ret += "v";
        cy++;
        if ((cx == 0) && (cy == 3))
            bad = 1;
    }
    while (cy > dy)
    {
        ret += "^";
        cy--;
        if ((cx == 0) && (cy == 3))
            bad = 1;
    }
    while (cx < dx)
    {
        ret += ">";
        cx++;
        if ((cx == 0) && (cy == 3))
            bad = 1;
    }

    ret += "A";

    if (bad == 1)
    {
        ret = "";
        cx = x;
        cy = y;

        if (cx < dx)
        {
            ret += ">";
            cx++;
        }
        while (cy < dy)
        {
            ret += "v";
            cy++;
        }
        while (cy > dy)
        {
            ret += "^";
            cy--;
        }
        while (cx > dx)
        {
            ret += "<";
            cx--;
        }
        while (cx < dx)
        {
            ret += ">";
            cx++;
        }
        ret += "A";
    }

    return ret;
}

string seq2seq(int x, int y, string seq)
{
    string ret = "";

    for (char c : seq)
    {
        int dx = dirX(c);
        int dy = dirY(c);
        string s = sequence(x, y, dx, dy);
        ret = ret + s;
        x = dx;
        y = dy;
    }
    return ret;
}

string walk(string seq, int x, int y, int d, int m)
{
    if (d == m)
        return seq;

    string ret = "";

    if (d == 0)
    {
        for (char c : seq)
        {
            int dx = keyX(c);
            int dy = keyY(c);
            ret = ret + sequence(x, y, dx, dy);
            x = dx;
            y = dy;
        }
        ret = walk(ret, 2, 0, d + 1, m);
        return ret;
    }

    ret = seq2seq(2, 0, seq);

    ret = walk(ret, 2, 0, d + 1, m);

    return ret;
}

int main()
{
    string s = "";
    int total = 0;

    s = walk("593A", 2, 3, 0, 3);
    total += s.length() * 593;
    cout << s << endl;
    printf("Length is %d\n", s.length());

    s = walk("283A", 2, 3, 0, 3);
    cout << s << endl;
    printf("Length is %d\n", s.length());
    total += s.length() * 283;

    s = walk("670A", 2, 3, 0, 3);
    cout << s << endl;
    printf("Length is %d\n", s.length());
    total += s.length() * 670;

    s = walk("459A", 2, 3, 0, 3);
    cout << s << endl;
    printf("Length is %d\n", s.length());
    total += s.length() * 459;

    s = walk("279A", 2, 3, 0, 3);
    cout << s << endl;
    printf("Length is %d\n", s.length());
    total += s.length() * 279;

    /*
        s = walk("029A", 2, 3, 0, 3);
        total += s.length() * 29;
        cout << s << endl;
        printf("Length is %d\n", s.length());

        s = walk("980A", 2, 3, 0, 3);
        cout << s << endl;
        printf("Length is %d\n", s.length());
        total += s.length() * 980;

        s = walk("179A", 2, 3, 0, 3);
        cout << s << endl;
        printf("Length is %d\n", s.length());
        total += s.length() * 179;

        s = walk("456A", 2, 3, 0, 3);
        cout << s << endl;
        printf("Length is %d\n", s.length());
        total += s.length() * 456;

        s = walk("379A", 2, 3, 0, 3);
        cout << s << endl;
        printf("Length is %d\n", s.length());
        total += s.length() * 379;*/

    printf("%d\n", total);
}
