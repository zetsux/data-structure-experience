#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> txt;
    txt.push_back("home");
    txt.push_back("anton");

    int n;
    cin >> n;

    while (n--) 
    {
        string com;
        cin >> com;

        if (com == "goto")
        {
            string con;
            cin >> con;

            txt.push_back(con);
        }

        else if (com == "goback")
        {
            if (txt.empty())
            {
                cout << "cannot go back\n";
                continue;
            }
            txt.pop_back();
        }

        else if (com == "whereami")
        {
            if (txt.empty())
            {
                cout << "i am nowhere\n";
                continue;
            }

            for (int i = 0; i < txt.size(); i++)
            {
                if (i != 0)
                {
                    cout << "/";
                }
                cout << txt[i];
            }
            cout << endl;
        }

        else
        {
            cout << "Query not found\n";
        }
    }

    return 0;
}