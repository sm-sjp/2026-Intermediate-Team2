/* 힘 P, 위치 X, 건초더미 위치 N, 방어력 Di
입력: 
1. N, (발사 화살 갯수)Q
2. 방여력 Di 크기
3. Q개별 P
출력: N값의 최소 */

/*
1. 문제 (X, P)는 1번 ~ X번 건초만 볼 수 있다.
2. 최소 개수를 구하려면 방어력이 큰 건초부터 쓰면 된다.
3. 그래서 root[X]에는 “1번 ~ X번 건초들의 방어력 정보”를 저장해둔다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int left;
    int right;
    int count;      // (해당 구간) 건초 더미 개수
    long long sum;  // (해당 구간) 방어력 총합
};

int N, Q;
vector<int> arr; // i번 위치의 방어력 (D[i]) 저장
vector<int> value; // 방어력 값 정렬(오름차순) + 중복 제거
vector<int> root; // root[x] = arr[1] ~ arr[x]를 넣은 상태
vector<Node> tree; // segmetn tree

// prev: 기존 tree
int update(int prev, int start, int end, int index, int num) {
    int cur = tree.size();
    tree.push_back(tree[prev]);

    tree[cur].count++;
    tree[cur].sum += num;

    if (start == end) {
        return cur;
    }

    int mid = (start + end) / 2;

    if (index <= mid) {
        tree[cur].left = update(tree[prev].left, start, mid, index, num);
    }
    else {
        tree[cur].right = update(tree[prev].right, mid + 1, end, index, num);
    }

    return cur;
}

int getAnswer(int node, int start, int end, long long power) {
    if (tree[node].sum < power) {
        return -1;
    }

    if (start == end) {
        int defense = value[start - 1];
        return (power + defense - 1) / defense;
    }

    int mid = (start + end) / 2;

    int leftNode = tree[node].left;
    int rightNode = tree[node].right;

    if (tree[rightNode].sum >= power) {
        return getAnswer(rightNode, mid + 1, end, power);
    }
    else {
        int rightCount = tree[rightNode].count;
        int leftAnswer = getAnswer(leftNode, start, mid, power - tree[rightNode].sum);

        return rightCount + leftAnswer;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;

    arr.resize(N + 1);
    value.reserve(N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        value.push_back(arr[i]);
    }

    sort(value.begin(), value.end());
    value.erase(unique(value.begin(), value.end()), value.end());

    int M = value.size();

    tree.reserve((N + 1) * 20);
    tree.push_back({ 0, 0, 0, 0 });

    root.assign(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        int index = lower_bound(value.begin(), value.end(), arr[i]) - value.begin() + 1;
        root[i] = update(root[i - 1], 1, M, index, arr[i]);
    }

    while (Q--) {
        int X;
        long long P;

        cin >> X >> P;

        cout << getAnswer(root[X], 1, M, P) << '\n';
    }

    return 0;
}