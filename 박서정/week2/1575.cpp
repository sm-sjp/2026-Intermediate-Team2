#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct ValNode {
    int minVal;
    int maxVal;
};

int N, Q;
vector<int> arr;
vector<ValNode> tree;

const int invalid = 1000000001;

ValNode mergeNode(ValNode left, ValNode right) {
    ValNode result;
    result.minVal = min(left.minVal, right.minVal);
    result.maxVal = max(left.maxVal, right.maxVal);
    return result;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].minVal = arr[start];
        tree[node].maxVal = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    tree[node] = mergeNode(tree[node * 2], tree[node * 2 + 1]);
}

ValNode find(int node, int start, int end, int left, int right) {
    if (right < start || end < left) {
        ValNode temp;
        temp.minVal = invalid;
        temp.maxVal = 0;
        return temp;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    ValNode leftResult = find(node * 2, start, mid, left, right);
    ValNode rightResult = find(node * 2 + 1, mid + 1, end, left, right);

    return mergeNode(leftResult, rightResult);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;

    arr.resize(N + 1);
    tree.resize(4 * N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    build(1, 1, N);

    for (int i = 0; i < Q; i++) {
        int A, B;
        cin >> A >> B;

        ValNode result = find(1, 1, N, A, B);

        cout << result.maxVal - result.minVal << '\n';
    }

    return 0;
}