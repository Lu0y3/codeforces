https://www.luogu.com.cn/problem/P1757

// 分组背包(模版)
// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值


/*-------------------------------------------------*/
    // 严格位置依赖的动态规划
    public static int compute1() {
        int teams = 1;
        for (int i = 2; i <= n; i++) {
            if (arr[i - 1][2] != arr[i][2]) {
                teams++;
            }
        }
        // 组的编号1~teams
        // dp[i][j] : 1~i是组的范围，每个组的物品挑一件，容量不超过j的情况下，最大收益
        int[][] dp = new int[teams + 1][m + 1];
        // dp[0][....] = 0
        for (int start = 1, end = 2, i = 1; start <= n; i++) {
            while (end <= n && arr[end][2] == arr[start][2]) {
                end++;
            }
            // start ... end-1 -> i组
            for (int j = 0; j <= m; j++) {
                // arr[start...end-1]是当前组，组号一样
                // 其中的每一件商品枚举一遍
                dp[i][j] = dp[i - 1][j];
                for (int k = start; k < end; k++) {
                    // k是组内的一个商品编号
                    if (j - arr[k][0] >= 0) {
                        dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - arr[k][0]] + arr[k][1]);
                    }
                }
            }
            // start去往下一组的第一个物品
            // 继续处理剩下的组
            start = end++;
        }
        return dp[teams][m];
    }

    // 空间压缩
    public static int compute2() {
        // dp[0][...] = 0
        Arrays.fill(dp, 0, m + 1, 0);
        for (int start = 1, end = 2; start <= n;) {
            while (end <= n && arr[end][2] == arr[start][2]) {
                end++;
            }
            // start....end-1
            for (int j = m; j >= 0; j--) {
                for (int k = start; k < end; k++) {
                    if (j - arr[k][0] >= 0) {
                        dp[j] = Math.max(dp[j], arr[k][1] + dp[j - arr[k][0]]);
                    }
                }
            }
            start = end++;
        }
        return dp[m];
    }

/*--------------------------------------------------------------------*/



//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;

class GroupKnapsack {
    struct Item {
        int weight;  // 物品重量
        int value;   // 物品价值
        int group_id;// 所属组号
        Item(int w, int v, int g) : weight(w), value(v), group_id(g) {}
    };

    vector<Item> items;  // 所有物品
    vector<int> dp;      // 动态规划数组
    int capacity;        // 背包总容量

    void process_groups() {
        // 按组号排序
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.group_id < b.group_id;
            });

        int n = items.size();
        int start = 0;

        // 遍历所有组
        while (start < n) {
            int end = start;
            // 找到当前组的结束位置
            while (end < n && items[end].group_id == items[start].group_id) {
                end++;
            }

            // 逆序更新背包容量
            for (int j = capacity; j >= 0; --j) {
                // 遍历当前组内所有物品
                for (int k = start; k < end; ++k) {
                    if (j >= items[k].weight) {
                        dp[j] = max(dp[j], dp[j - items[k].weight] + items[k].value);
                    }
                }
            }
            start = end; // 处理下一组
        }
    }

public:
    GroupKnapsack(int cap) : capacity(cap), dp(cap + 1, 0) {}

    void add_item(int w, int v, int g) {
        items.emplace_back(w, v, g);
    }

    int solve() {
        fill(dp.begin(), dp.end(), 0); // 重置dp数组
        process_groups();
        return dp[capacity];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n; // m: 总重量, n: 物品数量
    cin >> m >> n;  // 修复输入顺序

    GroupKnapsack solver(m);

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        solver.add_item(a, b, c);
    }

    cout << solver.solve() << endl;

    return 0;
}




