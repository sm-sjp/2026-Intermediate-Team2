// 구간의 최대값1

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// start, end: 현재 노드가 담당하는 배열 구간 [start ~ end]

long long build(vector<long long>& arr, vector<long long>& tree,
    int node, int start, int end) {

    if (start == end) {
        return tree[node] = arr[start];
    }

    int mid = (start + end) / 2;

    long long left = build(arr, tree, node * 2, start, mid);
    long long right = build(arr, tree, node * 2 + 1, mid + 1, end);

    // 현재 노드 = 왼쪽 구간 최댓값과 오른쪽 구간 최댓값 중 큰 값
    return tree[node] = max(left, right);
}

// left, right: 입력받은 질문 구간
// start, end: 현재 노드가 담당하는 배열 구간 [start ~ end]
long long findMax(vector<long long>& tree,
    int node, int start, int end, int left, int right) {

    // 현재 구간 != 질문 구간
    if (start > right || end < left) { return 0; }

    // 현재 구간이 질문 구간 안에 완전히 포함
    if (start >= left && end <= right) {
        return tree[node];
    }

    // 일부만 겹침
    int mid = (start + end) / 2;

    long long leftMax = findMax(tree, node * 2, start, mid, left, right);
    long long rightMax = findMax(tree, node * 2 + 1, mid + 1, end, left, right);

    return max(leftMax, rightMax);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;

    vector<long long> arr(N);
    vector<long long> tree(N * 4);

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    build(arr, tree, 1, 0, N - 1);

    for (int i = 0; i < Q; i++) {
        int A, B;
        cin >> A >> B;
        
        cout << findMax(tree, 1, 0, N - 1, A - 1, B - 1) << '\n';
    }

    return 0;
}