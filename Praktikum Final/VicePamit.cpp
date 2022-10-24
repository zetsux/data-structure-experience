#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n, prev = 0;
    cin >> m >> n;
    
    vector<int> a, b, c;

    while (m--)
    {
        int x;
        cin >> x;

        a.push_back(x);
    }

    while (n--)
    {
        int x;
        cin >> x;

        b.push_back(x);
    }

    while (!a.empty() || !b.empty())
    {
        if (a.empty())
        {
            int num = b.back() + prev;
            if (num >= 10)
            {
                num -= 10;
                prev = 1;
            }

            else
            {
                prev = 0;
            }

            c.push_back(num);
            b.pop_back();
        }

        else if (b.empty())
        {
            int num = a.back() + prev;
            if (num >= 10)
            {
                num -= 10;
                prev = 1;
            }

            else
            {
                prev = 0;
            }

            c.push_back(num);
            a.pop_back();
        }

        else
        {
            int num = a.back() + b.back() + prev;
            if (num >= 10)
            {
                num -= 10;
                prev = 1;
            }

            else
            {
                prev = 0;
            }

            c.push_back(num);
            a.pop_back();
            b.pop_back();
        }
    }

    if (prev == 1)
    {
        c.push_back(1);
    }

    cout << "[";
    for (int i = c.size() - 1; i >= 0; i--)
    {
        cout << c[i];
    }
    cout << "]";

    return 0;
}