#include <bits/stdc++.h>
using namespace std;

void printBalancedBST(int arr[], int start, int end)
{
    if (start > end)
    {
        return;
    }
 
    int mid = (start + end)/2;
    cout << arr[mid] << endl;

    printBalancedBST(arr, start, mid-1);
    printBalancedBST(arr, mid+1, end);
}

int main()
{
    int n;
    cin >> n;

    int arr[n];

    for (int i = 0 ; i < n ; i++)
    {
        arr[i] = i+1;
    }

    printBalancedBST(arr, 0, n-1);
    return 0;
}