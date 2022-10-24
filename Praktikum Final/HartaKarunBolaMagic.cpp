#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  

    int n, before = -1, count = 1;
    cin >> n;

    vector<int> arr;

    while (n--)
    {
        int x;
        cin >> x;

        arr.push_back(x);

        if (before == x)
        {
            count++;
            if (count == before)
            {
                while (count--)
                {
                    arr.pop_back();
                }

                count = 1;
                before = arr.back();
                for (int i = arr.size() - 2; i >= 0; i--)
                {
                    if (arr[i] == before)
                    {
                        count++;
                    }

                    else
                    {
                        break;
                    }
                }
            }
        }

        else if (count != 1)
        {
            count = 1;
        }

        cout << arr.size() << "\n";
        before = arr.back();
    }

    return 0;
}