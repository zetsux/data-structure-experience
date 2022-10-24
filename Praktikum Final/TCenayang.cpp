#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, flag = 1;
    cin >> n;

    vector<int> x, y;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        x.push_back(a);
        y.push_back(b);
    }
    
    double inf = numeric_limits<double>::infinity();
    double area = inf;
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++) 
        {
            for (int k = j + 1; k < n; k++)
            {
                double newArea = abs(((x[j] - x[i])*(y[k] - y[i])) - ((x[k] - x[i])*(y[j] - y[i])))/2.0;

                if (newArea == 0)
                {
                    continue;
                }

                else
                {
                    if (newArea < area)
                    {
                        area = newArea;
                        flag = 1;
                    }

                    else if (newArea == area)
                    {
                        flag = -1;
                    }
                }
            }
        }
    }

    if (area == inf || flag != 1)
    {
        cout << "-1.00";
    }

    else
    {
        cout << fixed << setprecision(2) << area;
    }

    return 0;
}