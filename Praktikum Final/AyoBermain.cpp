#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  

    map<int, string> name;
    for (int i = 1; i <= 4 ; i++)
    {
        string txt;
        cin >> txt;

        name[i] = txt;
    }

    vector<int> caught;
    int x, seek = -1;
    string seeker;
    cin >> x;
    cin >> seeker;

    for (int i = 1; i < 5; i++)
    {
        if (name[i] == seeker)
        {
            seek = i;
            break;
        }
    }

    list<int> game[5];
    while (x--)
    {
        int p, d;
        cin >> p >> d;

        game[p].push_back(d);
    }

    while (1)
    {
        int flag = 1;
        for (int i = 1; i <= 4; i++)
        {
            if (!game[i].empty())
            {
                if (flag == 1)
                {
                    flag = 0;
                }

                if (i != seek)
                {
                    if (game[i].front() == game[seek].front())
                    {
                        caught.push_back(i);
                        game[i].clear();
                    }
                }

            }
        }

        if (flag == 1)
        {
            break;
        }

        for (int i = 1; i <= 4 ; i++)
        {
            if (!game[i].empty())
            {
                game[i].pop_front();
            }
        }
    }

    if (caught.size() == 0)
    {
        cout << name[seek] << " jaga lagi";
    }

    else if (caught.size() == 1)
    {
        cout << name[caught[0]] << " ditangkap oleh " << name[seek];
    }

    else
    {
        sort(caught.begin(), caught.end());
        for (long unsigned int i = 0; i < caught.size(); i++)
        {
            if (i == caught.size() - 1)
            {
                cout << "dan " << name[caught[i]] << " ";
            }

            else
            {
                cout << name[caught[i]] << ", ";
            }
        }

        cout << "ditangkap oleh " << name[seek];
    }

    return 0;
}