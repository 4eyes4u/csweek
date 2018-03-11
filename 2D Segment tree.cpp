/*
    Data structure: 2D Segment tree
    Complexity: O(logn * logm) [per operaton, where n and m are numbers of rows and cols respectively]

* * *
Merge operation is sum on submatrix.
*/        

#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;

int st[4 * N][4 * N], a[N][N];
int n, m;

void init(int idx_row, int left_row, int right_row, int idx_col, int left_col, int right_col) {
    if (left_col == right_col) {
        if (left_row == right_row) st[idx_row][idx_col] = a[left_row][left_col];
        else st[idx_row][idx_col] = st[2 * idx_row][idx_col] + st[2 * idx_row + 1][idx_col];
    } else {
        int mid = (left_col + right_col) / 2;
        init(idx_row, left_row, right_row, 2 * idx_col, left_col, mid);
        init(idx_row, left_row, right_row, 2 * idx_col + 1, mid + 1, right_col);
        st[idx_row][idx_col] = st[idx_row][2 * idx_col] + st[idx_row][2 * idx_col + 1]; 
    }
}

void init(int idx_row, int left_row, int right_row) {
    if (left_row != right_row) {
        int mid = (left_row + right_row) / 2;
        init(2 * idx_row, left_row, mid);
        init(2 * idx_row + 1, mid + 1, right_row);
    }
    
    init(idx_row, left_row, right_row, 1, 1, m);
}

void update(int idx_row, int left_row, int right_row, int idx_col, int left_col, int right_col, int r, int c, int val) {
    if (left_col == right_col) {
        if (left_row == right_row) st[idx_row][idx_col] = val;
        else st[idx_row][idx_col] = st[2 * idx_row][idx_col] + st[2 * idx_row + 1][idx_col];
    } else {
        int mid = (left_col + right_col) / 2;
        if (c <= mid) update(idx_row, left_row, right_row, 2 * idx_col, left_col, mid, r, c, val);
        else update(idx_row, left_row, right_row, 2 * idx_col + 1, mid + 1, right_col, r, c, val);
        st[idx_row][idx_col] = st[idx_row][2 * idx_col] + st[idx_row][2 * idx_col + 1];
    }
}

void update(int idx_row, int left_row, int right_row, int r, int c, int val) {
    if (left_row != right_row) {
        int mid = (left_row + right_row) / 2;
        if (r <= mid) update(2 * idx_row, left_row, mid, r, c, val);
        else update(2 * idx_row + 1, mid + 1, right_row, r, c, val);
    }

    update(idx_row, left_row, right_row, 1, 1, m, r, c, val);
}

int query(int idx_row, int left_row, int right_row, int idx_col, int left_col, int right_col, int r1, int c1, int r2, int c2) {
    if (c1 <= left_col && right_col <= c2) return st[idx_row][idx_col];
    
    int mid = (left_col + right_col) / 2;
    int ret = 0;
    if (c1 <= mid) ret += query(idx_row, left_row, right_row, 2 * idx_col, left_col, mid, r1, c1, r2, c2);
    if (c2 > mid) ret += query(idx_row, left_row, right_row, 2 * idx_col + 1, mid + 1, right_col, r1, c1, r2, c2);
    return ret;
}

int query(int idx_row, int left_row, int right_row, int r1, int c1, int r2, int c2) { // r1 <= r2, c1 <= c2
    if (r1 <= left_row && right_row <= r2) return query(idx_row, left_row, right_row, 1, 1, m, r1, c1, r2, c2);
    
    int mid = (left_row + right_row) / 2;
    int ret = 0;
    if (r1 <= mid) ret += query(2 * idx_row, left_row, mid, r1, c1, r2, c2);
    if (r2 > mid) ret += query(2 * idx_row + 1, mid + 1, right_row, r1, c1, r2, c2);
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    init(1, 1, n);
    printf("%d\n", query(1, 1, n, 1, 1, 8, 8));
    printf("%d\n", query(1, 1, n, 2, 3, 5, 7));
    update(1, 1, n, 5, 5, 10);
    printf("%d\n", query(1, 1, n, 1, 1, 8, 8));

    return 0;
}
