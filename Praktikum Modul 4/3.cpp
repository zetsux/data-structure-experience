#include <bits/stdc++.h>
using namespace std;

vector<unsigned long long> probs;

void countTurn (unsigned int n)
{
    for (unsigned int i = probs.size(); i <= n; i++) 
    {
        unsigned long long num = 0;
        for (unsigned int j = 0; j < i; j++)
        {
            num += probs[j] * probs[i - j - 1];
        }
        probs.push_back(num);
    }
}

int main()
{
    int x;
    cin >> x;

    probs.push_back(1);
    probs.push_back(1);

    for (int i = 0; i < x ; i++)
    {
        unsigned int n;
        cin >> n;

        if (n == 0)
        {
            cout << "0\n";
            continue;
        }

        if (i == 0)
        {
            countTurn(n);
        }

        else
        {
            if (n >= probs.size())
            {
                countTurn(n);
            }
        }

        cout << probs[n] << endl;
    }
    return 0;
}