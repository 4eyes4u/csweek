/*
    Data structure: Segment tree with multiset
    Complexity: O(logn * logn) [per operaton]

* * *
We assume that no element can take value 0.
*/

#include <bits/stdc++.h>
#define mid (left + right) / 2
using namespace std;

const int N = 1e5 + 10;

multiset<int> st[4 * N];
int n, a[N];

void update(int idx, int left, int right, int x, int val) {
    st[idx].insert(val);
    st[idx].erase(a[x]);

    if (left == right) {
        st[idx].insert(a[x] = val);
        return;
    }

    if (x <= mid) update(2 * idx, left, mid, x, val);
    else update(2 * idx + 1, mid + 1, right, x, val);
}

bool query(int idx, int left, int right, int l, int r, int val) {
    if (l <= left && right <= r) return st[idx].count(val);

    bool ret = 0;
    if (l <= mid) ret |= query(2 * idx, left, mid, l, r, val);
    if (r > mid) ret |= query(2 * idx + 1, mid + 1, right, l, r, val);
    return ret;
}

int main() {
    n = 8;
    update(1, 1, n, 5, 6);
    update(1, 1, n, 1, 10);
    update(1, 1, n, 3, 7);
    update(1, 1, n, 7, 8);

    printf("%d\n", query(1, 1, n, 1, 8, 3));
    printf("%d\n", query(1, 1, n, 1, 8, 7));

    update(1, 1, n, 3, 6);
    printf("%d\n", query(1, 1, n, 1, 8, 7));

    return 0;
}