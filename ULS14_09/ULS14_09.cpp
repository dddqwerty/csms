#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > tree;

void build(int arr[], int l, int r, int index) {
    if (l == r) {
        tree[index].push_back(arr[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(arr, l, mid, index<<1);
    build(arr, mid + 1, r, index<<1|1);
    
    int right = 0, left = 0, lSize = tree[index<<1].size(), rSize = tree[index<<1|1].size();
    while(left < lSize && right < rSize) {
        if(tree[index<<1][left] < tree[index<<1|1][right]) tree[index].push_back(tree[index<<1][left++]);
        else tree[index].push_back(tree[index<<1|1][right++]);
    }
    while(left < lSize) tree[index].push_back(tree[index<<1][left++]);
    while(right < rSize) tree[index].push_back(tree[index<<1|1][right++]);
    return;
}

int get(int node, int L, int R, int l, int r, int k) {
    if (L > r || R < l) return 0;
    if(L >= l && R <= r) {
        int left = 0, right = tree[node].size() - 1;
        while(left <= right) {
            int mid = (right + left) >> 1;
            if (k > tree[node][mid]) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    int mid = (L + R)>>1;
    return get(node<<1, L, mid, l, r, k) + get(node<<1|1, mid + 1, R, l, r, k);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    int a[n];

    for (int i = 0; i < n; i++) cin >> a[i];
    tree.resize(n<<2);
    build(a, 0, n - 1, 1);
    

    while(q--) {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        int ans = get(1, 0, n - 1, l - 1, r - 1, k);   
        printf("%d\n", ans);
    }
    
    return 0;
}

