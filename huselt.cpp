#include <iostream>
#include <vector>
using namespace std;


int tree[2][400001];

void build(int values[], int l, int r, int index) {
    if (l == r) {    
        tree[1][index] = tree[0][index] = values[l];
        return;
    }
    int mid = (l + r)>>1;
    build(values, l, mid, index<<1);
    build(values, mid+1, r, index<<1|1);
    tree[0][index] = max(tree[0][index<<1], tree[0][index<<1|1]);
    tree[1][index] = min(tree[1][index<<1], tree[1][index<<1|1]);
    return;
}


pair<int, int> get(int node, int L, int R, int l, int r) {
    pair<int,int> ans;
    if(L > r || R < l) {
        ans.first = -1e9;
        ans.second = 1e9;
        return ans;
    };
    if(L >= l && R <= r) {
        ans.first = tree[0][node];
        ans.second = tree[1][node];
        return ans;
    };
    
    int mid = (L+R)>>1;
    pair<int,int> left = get(node<<1, L, mid, l, r);
    pair<int,int> right = get(node<<1|1, mid+1, R, l, r);
    ans.first = max(left.first, right.first);
    ans.second = min(left.second, right.second);
    return ans;
}

int main() {
    int n, q;
    cin >> n >> q;
    int arr[n];

    for(int i = 0; i < n; i++) cin >> arr[i];
    build(arr, 0, n - 1, 1);

    while(q--) {
        int a, b; cin >> a >> b;
        pair<int,int> c = get(1, 0, n - 1, a-1, b-1);
        cout << c.first - c.second << endl;
    }
    return 0;
}

