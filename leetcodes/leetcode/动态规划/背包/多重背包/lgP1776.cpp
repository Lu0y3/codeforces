https://www.luogu.com.cn/problem/P1776


// ���ر���ͨ�������Ʒ���ת����01����(ģ��)

// ����ɸѡ
// һ����n�ֻ���, ��������Ϊt
// ÿ�ֻ���ļ�ֵ(v[i])������(w[i])������(c[i])������
// �뷵��ѡ����ﲻ������������������£��ܵõ������ļ�ֵ

//�����Ʒ���:  ��i����Ʒ���������������з��飨����13�� �ֳ� 1��2��4�� 6 ���� ��Ͽɽ�0-13�������� ����ÿ��С������"Ҫ���߲�Ҫ?" 01���������⣩


/*-----------------------------------------------*/
// �����ļ�����Ҫ���߼� : �����Ʒ���
                // һ�㶼ʹ�����ּ��ɣ���δ���ǳ���Ҫ
                // ��Ȼʱ�临�ӶȲ��絥�������Ż��İ汾
                // ���Ǻ�д�����Ҽ����Ǳ�����ʱ�临�Ӷ�Ҳ���
                // �����Ʒ����ʱ�临�Ӷ�ΪO(log cnt)
                for (int k = 1; k <= cnt; k <<= 1) {
                    v[++m] = k * value;
                    w[m] = k * weight;
                    cnt -= k;
                }
                if (cnt > 0) {
                    v[++m] = cnt * value;
                    w[m] = cnt * weight;
                }


// 01�����Ŀռ�ѹ������(ģ��)
public static int compute() {
    Arrays.fill(dp, 0, t + 1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = t; j >= w[i]; j--) {
            dp[j] = Math.max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[t];
}
/*-----------------------------------------------*/


//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;

class BoundedKnapsack {
    vector<int> dp;
    vector<pair<int, int>> items; // weight, value
    int capacity;

    void binary_split(int cnt, int weight, int value) {
        for (int k = 1; k <= cnt; k <<= 1) {
            items.emplace_back(k * weight, k * value);
            cnt -= k;
        }
        if (cnt > 0) {
            items.emplace_back(cnt * weight, cnt * value);
        }
    }

public:
    BoundedKnapsack(int cap) : capacity(cap), dp(cap + 1) {}

    void add(int count, int weight, int value) {
        binary_split(count, weight, value);
    }

    int solve() {
        fill(dp.begin(), dp.end(), 0);
        for (const auto& [w, v] : items) {
            for (int j = capacity; j >= w; --j) {
                if (dp[j - w] + v > dp[j]) {
                    dp[j] = dp[j - w] + v;
                }
            }
        }
        return dp[capacity];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    while (cin >> n >> W) {
        BoundedKnapsack solver(W);

        for (int i = 0; i < n; ++i) {
            int v, w, m;
            cin >> v >> w >> m;
            solver.add(m, w, v);
        }

        cout << solver.solve() << '\n';
    }

    return 0;
}

