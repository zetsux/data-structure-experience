#include <bits/stdc++.h>
using namespace std;

long long multiplier(vector<long long> user[], int id, long unsigned int a, int n)
{
    long long total = 0;
    for (long unsigned int i = a + 1; i < n ; i++)
    {
        total += (user[id][a]*user[id][i]);
    }

    return total;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<long long> comp;
    for (int i = 0; i < n; i++)
    {
        long long temp;
        cin >> temp;

        comp.push_back(temp);
    }

    vector<long long> user[m];
    map<int, int> compList[m];
    long long score[m] = {0};
    for (int i = 0; i < m; i++)
    {
        int c;
        cin >> c;

        for (int j = 0; j < c; j++)
        {
            long long temp;
            cin >> temp;

            user[i].push_back(temp);
            compList[i][temp] = j;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (long unsigned int j = 0; j < user[i].size() - 1; j++)
        {
            score[i] += multiplier(user, i, j, user[i].size());
        }
    }

    int q;
    cin >> q;

    while (q--)
    {
        int com;
        cin >> com;

        if (com == 1)
        {
            int oldCom, newCom;
            cin >> oldCom >> newCom;

            for (int i = 0; i < m; i++)
            {
                int index = compList[i][oldCom];
                if (index > 0)
                {
                    compList[i][oldCom] = 0;
                    compList[i][newCom] = index;
                    user[i][index] = newCom;
                    score[i] = 0;

                    for (long unsigned int j = 0; j < user[i].size() - 1; j++)
                    {
                        score[i] += multiplier(user, i, j, user[i].size());
                    }
                }

                else
                {
                    continue;
                }
            }
        }

        else if (com == 2)
        {
            int userIndex;
            cin >> userIndex;

            cout << score[userIndex - 1] << endl;
        }
    }

    return 0;
}