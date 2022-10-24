#include <bits/stdc++.h>
using namespace std;

int caseNum = 1;

void treeConstruct(int left, int right, int h) 
{
    int n = (right - left) + 1;
    if(n == 0 || h == 0) 
    {
        return;
    }

    int hPow = pow(2, h);
    if((n > 1 || h > 1) && n > hPow - 1) 
    {
        cout << " Impossible."; 
        return; 
    }

    int checkLeft = max((n - (hPow / 2)), 0);
    cout << " " << left + checkLeft;

    if(checkLeft > 0)
    {
        treeConstruct(left, left + checkLeft - 1, h - 1);
    }

    treeConstruct(left + checkLeft + 1, right, h - 1);
}


int main()
{
    int n, h;
    cin >> n >> h;

    while (n != 0 || h != 0)
    {
        cout << "Case " << caseNum << ":";
        treeConstruct(1, n, h);
        cout << "\n";
        cin >> n >> h;
        caseNum++;
    }

    return 0;
}