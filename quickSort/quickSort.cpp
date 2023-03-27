#include <iostream>
#include <vector>

using namespace std;

int quickSort(vector<int>& a, int i, int j) {
    int temp = a[i];
    
    while (i < j) {
        while (i < j && a[j] >= temp) {
            j--;
        }
        if (i < j) {
            a[i] = a[j];
            i++;
        }

        while(i < j && a[i] < temp) {
            i++;
        }
        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = temp;
    // cout << "i: " << i;
    return i;
}

void sort(vector<int>& a, int i, int j) {
    if (i < j) {
        int temp = quickSort(a, i, j);
        sort(a, i, temp - 1);
        sort(a, temp + 1, j);
    }
}

int main() {
    vector<int> a = {1, 3, 2, 5, 4, 9, 8, 7, 6};
    // cout << a.size();
    // int f = quickSort(a, 0, 8);

    // cout << "f: " << f << "\n";
    sort(a, 0, a.size() - 1);

    for (int i = 0; i < a.size(); i++) {
        cout << "a[i]: " << a[i] << "\n";
    }
    return 0;
}