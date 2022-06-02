#include <iostream>
#include <set>
using namespace std;

int main() {
    int n, q; 
    scanf("%d%d", &n, &q);
    int a[n];
    set<int> val;

    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        // cin >> a[i];
    }

    for(int i = n - 1; i >= 0; i--) {
        val.insert(a[i]);
        a[i] = val.size();
    }

    while(q--) {
        int k; 
        scanf("%d", &k);
        printf("%d\n", a[k - 1]);
    }

    return 0;
}