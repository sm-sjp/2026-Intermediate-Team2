#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int EMPTY = 1000000001;

vector<pair<long long, int>> arr;
// arr[i].first  = value
// arr[i].second = index

vector<pair<long long, int>> tree;
// tree[node].first  = 해당 구간의 최솟값
// tree[node].second = 해당 최솟값을 가진 index

pair<long long, int> build(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }

    int mid = (start + end) / 2;

    pair<long long, int> left = build(node * 2, start, mid);
    pair<long long, int> right = build(node * 2 + 1, mid + 1, end);

    return tree[node] = min(left, right);
}

pair<long long, int> update(int node, int start, int end, int index, long long value) {
    if (start > index || end < index) {
        return tree[node];
    }

    if (start == end) {
        arr[index] = { value, index };
        return tree[node] = arr[index];
    }

    int mid = (start + end) / 2;

    pair<long long, int> left = update(node * 2, start, mid, index, value);
    pair<long long, int> right = update(node * 2 + 1, mid + 1, end, index, value);

    return tree[node] = min(left, right);
}

pair<long long, int> findMin(int node, int start, int end, int left, int right) {
    if (start > right || end < left) {
        return { EMPTY, 0 };
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    pair<long long, int> leftResult = findMin(node * 2, start, mid, left, right);
    pair<long long, int> rightResult = findMin(node * 2 + 1, mid + 1, end, left, right);

    return min(leftResult, rightResult);
}

void command1(int N, int k, long long val) {
    update(1, 1, N, k, val);
}

void command2(int N, int s, int e) {
    pair<long long, int> result = findMin(1, 1, N, s, e);

    if (result.first != EMPTY) {
        cout << result.second << '\n';
    }
}

void command3(int N, int s, int e) {
    pair<long long, int> result = findMin(1, 1, N, s, e);

    if (result.first != EMPTY) {
        update(1, 1, N, result.second, EMPTY);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<pair<long long, int>>arr(N + 1);
    vector<pair<long long, int>>tree(N * 4);

    for (int i = 1; i <= N; i++) {
        arr[i] = { EMPTY, i };
    }

    build(1, 1, N);

    for (int i = 0; i < M; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            int k;
            long long val;
            cin >> k >> val;

            command1(N, k, val);
        }
        else if (type == 2) {
            int s, e;
            cin >> s >> e;

            command2(N, s, e);
        }
        else if (type == 3) {
            int s, e;
            cin >> s >> e;

            command3(N, s, e);
        }
    }

    return 0;
}