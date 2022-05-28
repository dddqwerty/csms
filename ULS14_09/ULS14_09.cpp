//Runtime complexity O(log(n) * log(n) * q + n * log(n));
//Space complexity  n * 4
#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > tree;

//Building segmant tree with sort
void build(int arr[], int l, int r, int index) {
    //Хэрвээ l r завсар тэнцүү болвол тухайн завсар дахь элемэнтийг модондоо нэмнэ.
    if (l == r) {
        tree[index].push_back(arr[l]);
        return;
    }
    // Дундах index-г олж байна. Нийлбэрийг олоод нэг бит хойшлуулав. Нэг хоёртийн зэрэг хойшлуулж байгаа гэсэн үг (l+r)/2.
    int mid = (l + r) >> 1; 
    // build function-aa l-ээс mid болон mid - r завсарт дуудаж baina.
    build(arr, l, mid, index<<1);
    build(arr, mid + 1, r, index<<1|1);
    //build function маань мод-г доорос нь эхэлж байгуулах хийх бөгөөд бид нар node болгон дээр тухан node ийн зүүн(l-mid) баруун(mid-r) талийн утгийг сорт хийж байна.
    //Та нар 2 sorted array-г сорт хийгээд үзээрэй.
    int right = 0, left = 0, lSize = tree[index<<1].size(), rSize = tree[index<<1|1].size();
    while(left < lSize && right < rSize) {
        if(tree[index<<1][left] < tree[index<<1|1][right]) tree[index].push_back(tree[index<<1][left++]);
        else tree[index].push_back(tree[index<<1|1][right++]);
    }
    while(left < lSize) tree[index].push_back(tree[index<<1][left++]);
    while(right < rSize) tree[index].push_back(tree[index<<1|1][right++]);
    return;
}
// Searching segmant tree.
int get(int node, int L, int R, int l, int r, int k) {
    //Хэрвээ бидний хайж буй завсар тухайн завсарт оршихгүй бол гаргана.
    if (L > r || R < l) return 0;
    //Хэрвээ оршиж байвал binary search хийж хэдэн элемэнт к-ас байга байгааг олж буцаана.
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
    //Бидний хайж буй завсар оршиж буй бүх завсарийг олж к -гаас байга элэментийн тоог нийлүүлнэ.
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

// Хэрэвээ бид нар энэ бодолго дээр brute force хийх юм бол хамгийн worst case дээр 150000 * 100000 үйлдэл хийх хэрэг гарна. 
// Энэ нь хугацааны хязгаарлалтанд амжихгүй билээ. Тийм тул бид нар хүснэгтээ segmant tree болгож(node болгон дээр утгуудийг sort хийнэ) дараа нь 
// хүсэлт болгондоо хариулахдаа тухайн завсараа segmant tree-гээс аваад дараа нь авсан завсарууд дээрээ binary search хийвэл бидний бодолт хэд дахин хурдан болж чадна. 
// Segmant tree n*log(n) хугацаанд байгуулна. Байгуулгахад гарж буй n үйлдэл нь sort-х болно. Дараа нь хүсэлтэд хариулахдаа segmant tree log(n) хугацаанд хайж
// давхар к-гаас бага элемэнтийг олохдоо binary search(log(n)) хийвэл бидний хугацаа: 
// модноос хайх -- > log(n) * log(n) * q
// модоо байгуулах  ---> log(n) * n буюу нийтдээ log(n) * log(n) * q + n*log(n) хугацаанд бодож чадна.

