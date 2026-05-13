#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;

// arr[학생번호] = 그 학생의 점수
// score[점수] = 그 점수를 받은 학생 수
vector<int> arr;
vector<int> score;
vector<int> tree;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = score[start];
        return;
    }

    int mid = (start + end) / 2;

    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int node, int start, int end, int index, int diff) {
    if (index < start || end < index) return;

    if (start == end) {
        tree[node] += diff;
        return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, index, diff);
    update(node * 2 + 1, mid + 1, end, index, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int getCount(int node, int start, int end, int left, int right) {
    if (start > right || end < left) return 0;

    if (start >= left && end <= right) return tree[node];

    int mid = (start + end) / 2;

    return getCount(node * 2, start, mid, left, right)
        + getCount(node * 2 + 1, mid + 1, end, left, right);
}

// x번 학생의 등수 출력
void command1(int x, int N) {
    int rank = getCount(1, 1, MAX, arr[x] + 1, MAX);
    cout << rank + 1 << "\n";
}

// x번 학생 점수를 y로 변경
void command2(int x, int y) {
    update(1, 1, MAX, arr[x], -1);
    arr[x] = y;
    update(1, 1, MAX, arr[x], +1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, Q;
    cin >> N >> Q;

    arr.resize(N + 1);
    score.resize(MAX + 1);
    tree.resize(MAX * 4);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        score[arr[i]]++;
    }

    build(1, 1, MAX);

    while (Q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;

            command1(x, N);
        }
        else {
            int x, y;
            cin >> x >> y;

            command2(x, y);
        }
    }

    return 0;
}