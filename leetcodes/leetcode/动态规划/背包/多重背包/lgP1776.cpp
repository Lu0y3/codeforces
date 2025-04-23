https://www.luogu.com.cn/problem/P1776


// 多重背包通过二进制分组转化成01背包(模版)

// 宝物筛选
// 一共有n种货物, 背包容量为t
// 每种货物的价值(v[i])、重量(w[i])、数量(c[i])都给出
// 请返回选择货物不超过背包容量的情况下，能得到的最大的价值

//二进制分组:  将i号商品按照它的数量进行分组（比如13个 分成 1、2、4、 6 个的 组合可将0-13的数包含 ，而每个小组又有"要或者不要?" 01背包的问题）


/*-----------------------------------------------*/
// 整个文件最重要的逻辑 : 二进制分组
                // 一般都使用这种技巧，这段代码非常重要
                // 虽然时间复杂度不如单调队列优化的版本
                // 但是好写，而且即便是比赛，时间复杂度也达标
                // 二进制分组的时间复杂度为O(log cnt)
                for (int k = 1; k <= cnt; k <<= 1) {
                    v[++m] = k * value;
                    w[m] = k * weight;
                    cnt -= k;
                }
                if (cnt > 0) {
                    v[++m] = cnt * value;
                    w[m] = cnt * weight;
                }


// 01背包的空间压缩代码(模版)
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

